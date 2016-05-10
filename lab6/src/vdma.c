#include <stdio.h>
#include "platform.h"
#include "xparameters.h"
#include "xaxivdma.h"
#include "xio.h"
#include "time.h"
#include "unistd.h"
#include "xgpio.h"          // Provides access to PB GPIO driver.
#include "mb_interface.h"   // provides the microblaze interrupt enables, etc.
#include "xintc_l.h"        // Provides handy macros for the interrupt controller.
#include "xac97_l.h"

#include "global.h"
#include "xuartlite.h"

#include <xuartlite_l.h>
#include "blink.h"

XGpio gpLED;  // This is a handle for the LED GPIO block.
XGpio gpPB;   // This is a handle for the push-button GPIO block.

XUartLite uart;

unsigned int delayValue;
char inputChar;


#define DEBUG
#define FRAME_BUFFER_0_ADDR 0xC5000000  // Starting location in DDR where we will store the images that we display.
#define VOL_ATTN_MIN 0x0
#define VOL_ATTN_MAX 0x1f

Xuint32 vol_attn = 0x10;

int mytimer = 0;
int mycounter = 0;

int onesec;
int fifteenms;
int fivems;
int tenms;
int buttonValid;
int currentButtonState;
int speed = 30;

int holding;

int gameState = 1;


void increaseVolume() {
  if((int)vol_attn > VOL_ATTN_MIN) {
	vol_attn = vol_attn - 0x1;
	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_MasterVol, vol_attn | (vol_attn << 8));
	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_AuxOutVol, vol_attn | (vol_attn << 8));
  }
}
void decreaseVolume() {
  if((int)vol_attn < VOL_ATTN_MAX) {
	vol_attn = vol_attn + 0x1;
	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_MasterVol, vol_attn | (vol_attn << 8));
	XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_AuxOutVol, vol_attn | (vol_attn << 8));
  }
}
void delayDying() {
	int counter = 0;
	while(counter < 500000){
		counter++;
	}
}

void setGameState(int mystate){
	gameState = mystate;
}

unsigned int * framePointer = (unsigned int *) FRAME_BUFFER_0_ADDR;

void pb_interrupt_handler();

int isBottom(int value) {
	short* aliens = getAliens();

	if(value > 43) {
		return 1;
	}
	if(value < 44 && value > 32) {
		if(aliens[value+11] == 0) {
			return 1;
		}
		else {
			return 0;
		}
	}
	if(value < 33 && value > 21) {
		if(aliens[value+11] == 0 && aliens[value+22] == 0) {
			return 1;
		}
		else {
			return 0;
		}
	}
	if(value < 22 && value > 10) {
		if(aliens[value+11] == 0 && aliens[value+22] == 0 && aliens[value+33] == 0) {
			return 1;
		}
		else {
			return 0;
		}
	}
	if(value < 11) {
		if(aliens[value+11] == 0 && aliens[value+22] == 0 && aliens[value+33] == 0 && aliens[value+44] == 0) {
			return 1;
		}
		else {
			return 0;
		}
	}
}

int whatRow(int position) {
	if(position > 43) {
		return 120;
	}
	if(position < 44 && position > 32) {
		return 94;
	}
	if(position < 33 && position > 21) {
		return 68;
	}
	if(position < 22 && position > 10) {
		return 42;
	}
	if(position < 11) {
		return 16;
	}

}

void collisionCleanUp(int x, int y) {
	setHaveAlienDeathSound(1);
	blankTankBullet(framePointer);
	setTankBulletPositionY(0);
	setTankBulletState(0);
	delayDying();
	dyingAlienHelper(framePointer, x, y);
	int guise = getGuise();
	if(guise == 0) {
		renderAlien2(framePointer);
	}
	else {
		renderAlien1(framePointer);
	}
	alienSpeed();
}

void alienCollision() {
	int curTankY = ((getTankBulletPositionY()-2)*640);
	int curTankX = getTankBulletPositionX()+3;
	int curAlienX = getAlienBlockPositionX();
	int curAlienY = getAlienBlockPositionY();
	int ufoscore = 0;
	int updatescore = 0;

	if(framePointer[((getTankBulletPositionY()-2)*640) + getTankBulletPositionX()+3] == 0x00FF0000) {
		setHaveSpaceShipDeathSound(1);
		blankUfo(framePointer, getUfoPositionX(), getUfoPositionY());
		setUfoState(0);
		blankTankBullet(framePointer);
		setTankBulletPositionY(0);
		setTankBulletState(0);
		// ufo score operation
		ufoscore = rand()%7;
		updatescore = selectingUfoscore(framePointer, ufoscore);
		updateMyscore(updatescore);
		updateNumber(framePointer);
	}
	if(framePointer[((getTankBulletPositionY()-2)*640) + getTankBulletPositionX()+3] == 0x00FFFFFF || \
			framePointer[((getTankBulletPositionY()-2)*640) + getTankBulletPositionX()+5] == 0x00FFFFFF ||\
			framePointer[((getTankBulletPositionY()-2)*640) + getTankBulletPositionX()] == 0x00FFFFFF){
		curTankY = curTankY/640;
		if(curAlienX > 1000) {
			curAlienX -= 65535;
		}
		if(curAlienY < curTankY && curTankY < curAlienY + 16 ) {
			if(curAlienX < curTankX && curTankX < (curAlienX + 32)) {
				dyingAlien(framePointer, (getAlienBlockPositionX()), (getAlienBlockPositionY()));
				setAliens(0, 0);
				collisionCleanUp((getAlienBlockPositionX()), (getAlienBlockPositionY()));
			}
			if(curAlienX + 32 < curTankX && curTankX < curAlienX + 64) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+32), (getAlienBlockPositionY()));
				setAliens(0, 1);
				collisionCleanUp((getAlienBlockPositionX()+32), (getAlienBlockPositionY()));
			}
			if(curAlienX + 64 < curTankX && curTankX < curAlienX + 96) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+64), (getAlienBlockPositionY()));
				setAliens(0, 2);
				collisionCleanUp((getAlienBlockPositionX()+64), (getAlienBlockPositionY()));
			}
			if(curAlienX + 96 < curTankX && curTankX < curAlienX + 128) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+96), (getAlienBlockPositionY()));
				setAliens(0, 3);
				collisionCleanUp((getAlienBlockPositionX()+96), (getAlienBlockPositionY()));
			}
			if(curAlienX + 128 < curTankX && curTankX < curAlienX + 160) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+128), (getAlienBlockPositionY()));
				setAliens(0, 4);
				collisionCleanUp((getAlienBlockPositionX()+128), (getAlienBlockPositionY()));
			}
			if(curAlienX + 160 < curTankX && curTankX < curAlienX + 192) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+160), (getAlienBlockPositionY()));
				setAliens(0, 5);
				collisionCleanUp((getAlienBlockPositionX()+160), (getAlienBlockPositionY()));
			}
			if(curAlienX + 192 < curTankX && curTankX < curAlienX + 224) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+192), (getAlienBlockPositionY()));
				setAliens(0, 6);
				collisionCleanUp((getAlienBlockPositionX()+192), (getAlienBlockPositionY()));
			}
			if(curAlienX + 224 < curTankX && curTankX < curAlienX + 256) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+ 224), (getAlienBlockPositionY()));
				setAliens(0, 7);
				collisionCleanUp((getAlienBlockPositionX()+ 224), (getAlienBlockPositionY()));
			}
			if(curAlienX + 256 < curTankX && curTankX < curAlienX + 288) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+ 256), (getAlienBlockPositionY()));
				setAliens(0, 8);
				collisionCleanUp((getAlienBlockPositionX()+256), (getAlienBlockPositionY()));
			}
			if(curAlienX + 288 < curTankX && curTankX < curAlienX + 320) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+288), (getAlienBlockPositionY()));
				setAliens(0, 9);
				collisionCleanUp((getAlienBlockPositionX()+288), (getAlienBlockPositionY()));
			}
			if(curAlienX + 320 < curTankX && curTankX < curAlienX + 352) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+320), (getAlienBlockPositionY()));
				setAliens(0, 10);
				collisionCleanUp((getAlienBlockPositionX()+320), (getAlienBlockPositionY()));
			}
			updateMyscore(40);
			updateNumber(framePointer);

		}
		if(curAlienY + 26 < curTankY && curTankY < curAlienY + 42) {
			if(curAlienX < curTankX && curTankX < (curAlienX + 32)) {
				dyingAlien(framePointer, (getAlienBlockPositionX()), (getAlienBlockPositionY()+26));
				setAliens(0, 11);
				collisionCleanUp((getAlienBlockPositionX()), (getAlienBlockPositionY()+26));
			}
			if(curAlienX + 32 < curTankX && curTankX < curAlienX + 64) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+32), (getAlienBlockPositionY()+26));
				setAliens(0, 12);
				collisionCleanUp((getAlienBlockPositionX()+32), (getAlienBlockPositionY()+26));
			}
			if(curAlienX + 64 < curTankX && curTankX < curAlienX + 96) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+64), (getAlienBlockPositionY()+26));
				setAliens(0, 13);
				collisionCleanUp((getAlienBlockPositionX()+64), (getAlienBlockPositionY()+26));
			}
			if(curAlienX + 96 < curTankX && curTankX < curAlienX + 128) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+96), (getAlienBlockPositionY()+26));
				setAliens(0, 14);
				collisionCleanUp((getAlienBlockPositionX()+96), (getAlienBlockPositionY()+26));
			}
			if(curAlienX + 128 < curTankX && curTankX < curAlienX + 160) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+128), (getAlienBlockPositionY()+26));
				setAliens(0, 15);
				collisionCleanUp((getAlienBlockPositionX()+128), (getAlienBlockPositionY()+26));
			}
			if(curAlienX + 160 < curTankX && curTankX < curAlienX + 192) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+160), (getAlienBlockPositionY()+26));
				setAliens(0, 16);
				collisionCleanUp((getAlienBlockPositionX()+160), (getAlienBlockPositionY()+26));
			}
			if(curAlienX + 192 < curTankX && curTankX < curAlienX + 224) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+192), (getAlienBlockPositionY()+26));
				setAliens(0, 17);
				collisionCleanUp((getAlienBlockPositionX()+192), (getAlienBlockPositionY()+26));
			}
			if(curAlienX + 224 < curTankX && curTankX < curAlienX + 256) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+224), (getAlienBlockPositionY()+26));
				setAliens(0, 18);
				collisionCleanUp((getAlienBlockPositionX()+224), (getAlienBlockPositionY()+26));
			}
			if(curAlienX + 256 < curTankX && curTankX < curAlienX + 288) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+256), (getAlienBlockPositionY()+26));
				setAliens(0, 19);
				collisionCleanUp((getAlienBlockPositionX()+256), (getAlienBlockPositionY()+26));
			}
			if(curAlienX + 288 < curTankX && curTankX < curAlienX + 320) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+288), (getAlienBlockPositionY()+26));
				setAliens(0, 20);
				collisionCleanUp((getAlienBlockPositionX()+288), (getAlienBlockPositionY()+26));
			}
			if(curAlienX + 320 < curTankX && curTankX < curAlienX + 352) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+320), (getAlienBlockPositionY()+26));
				setAliens(0, 21);
				collisionCleanUp((getAlienBlockPositionX()+320), (getAlienBlockPositionY()+26));
			}
			updateMyscore(20);
			updateNumber(framePointer);
		}
		if(curAlienY + 52 < curTankY && curTankY < curAlienY + 68) {
			if(curAlienX < curTankX && curTankX < (curAlienX + 32)) {
				dyingAlien(framePointer, (getAlienBlockPositionX()), (getAlienBlockPositionY()+52));
				setAliens(0, 22);
				collisionCleanUp((getAlienBlockPositionX()), (getAlienBlockPositionY()+52));
			}
			if(curAlienX + 32 < curTankX && curTankX < curAlienX + 64) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+32), (getAlienBlockPositionY()+52));
				setAliens(0, 23);
				collisionCleanUp((getAlienBlockPositionX()+32), (getAlienBlockPositionY()+52));
			}
			if(curAlienX + 64 < curTankX && curTankX < curAlienX + 96) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+64), (getAlienBlockPositionY()+52));
				setAliens(0, 24);
				collisionCleanUp((getAlienBlockPositionX()+64), (getAlienBlockPositionY()+52));
			}
			if(curAlienX + 96 < curTankX && curTankX < curAlienX + 128) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+96), (getAlienBlockPositionY()+52));
				setAliens(0, 25);
				collisionCleanUp((getAlienBlockPositionX()+96), (getAlienBlockPositionY()+52));
			}
			if(curAlienX + 128 < curTankX && curTankX < curAlienX + 160) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+128), (getAlienBlockPositionY()+52));
				setAliens(0, 26);
				collisionCleanUp((getAlienBlockPositionX()+128), (getAlienBlockPositionY()+52));
			}
			if(curAlienX + 160 < curTankX && curTankX < curAlienX + 192) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+160), (getAlienBlockPositionY()+52));
				setAliens(0, 27);
				collisionCleanUp((getAlienBlockPositionX()+160), (getAlienBlockPositionY()+52));
			}
			if(curAlienX + 192 < curTankX && curTankX < curAlienX + 224) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+192), (getAlienBlockPositionY()+52));
				setAliens(0, 28);
				collisionCleanUp((getAlienBlockPositionX()+192), (getAlienBlockPositionY()+52));
			}
			if(curAlienX + 224 < curTankX && curTankX < curAlienX + 256) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+224), (getAlienBlockPositionY()+52));
				setAliens(0, 29);
				collisionCleanUp((getAlienBlockPositionX()+224), (getAlienBlockPositionY()+52));
			}
			if(curAlienX + 256 < curTankX && curTankX < curAlienX + 288) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+256), (getAlienBlockPositionY()+52));
				setAliens(0, 30);
				collisionCleanUp((getAlienBlockPositionX()+256), (getAlienBlockPositionY()+52));
			}
			if(curAlienX + 288 < curTankX && curTankX < curAlienX + 320) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+288), (getAlienBlockPositionY()+52));
				setAliens(0, 31);
				collisionCleanUp((getAlienBlockPositionX()+288), (getAlienBlockPositionY()+52));
			}
			if(curAlienX + 320 < curTankX && curTankX < curAlienX + 352) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+320), (getAlienBlockPositionY()+52));
				setAliens(0, 32);
				collisionCleanUp((getAlienBlockPositionX()+320), (getAlienBlockPositionY()+52));
			}
			updateMyscore(20);
			updateNumber(framePointer);
		}
		if(curAlienY + 78 < curTankY && curTankY < curAlienY + 94) {
			if(curAlienX < curTankX && curTankX < (curAlienX + 32)) {
				dyingAlien(framePointer, (getAlienBlockPositionX()), (getAlienBlockPositionY()+78));
				setAliens(0, 33);
				collisionCleanUp((getAlienBlockPositionX()), (getAlienBlockPositionY()+78));
			}
			if(curAlienX + 32 < curTankX && curTankX < curAlienX + 64) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+32), (getAlienBlockPositionY()+78));
				setAliens(0, 34);
				collisionCleanUp((getAlienBlockPositionX()+32), (getAlienBlockPositionY()+78));
			}
			if(curAlienX + 64 < curTankX && curTankX < curAlienX + 96) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+64), (getAlienBlockPositionY()+78));
				setAliens(0, 35);
				collisionCleanUp((getAlienBlockPositionX()+64), (getAlienBlockPositionY()+78));
			}
			if(curAlienX + 96 < curTankX && curTankX < curAlienX + 128) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+96), (getAlienBlockPositionY()+78));
				setAliens(0, 36);
				collisionCleanUp((getAlienBlockPositionX()+96), (getAlienBlockPositionY()+78));
			}
			if(curAlienX + 128 < curTankX && curTankX < curAlienX + 160) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+128), (getAlienBlockPositionY()+78));
				setAliens(0, 37);
				collisionCleanUp((getAlienBlockPositionX()+128), (getAlienBlockPositionY()+78));
			}
			if(curAlienX + 160 < curTankX && curTankX < curAlienX + 192) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+160), (getAlienBlockPositionY()+78));
				setAliens(0, 38);
				collisionCleanUp((getAlienBlockPositionX()+160), (getAlienBlockPositionY()+78));
			}
			if(curAlienX + 192 < curTankX && curTankX < curAlienX + 224) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+192), (getAlienBlockPositionY()+78));
				setAliens(0, 39);
				collisionCleanUp((getAlienBlockPositionX()+192), (getAlienBlockPositionY()+78));
			}
			if(curAlienX + 224 < curTankX && curTankX < curAlienX + 256) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+224), (getAlienBlockPositionY()+78));
				setAliens(0, 40);
				collisionCleanUp((getAlienBlockPositionX()+224), (getAlienBlockPositionY()+78));
			}
			if(curAlienX + 256 < curTankX && curTankX < curAlienX + 288) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+256), (getAlienBlockPositionY()+78));
				setAliens(0, 41);
				collisionCleanUp((getAlienBlockPositionX()+256), (getAlienBlockPositionY()+78));
			}
			if(curAlienX + 288 < curTankX && curTankX < curAlienX + 320) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+288), (getAlienBlockPositionY()+78));
				setAliens(0, 42);
				collisionCleanUp((getAlienBlockPositionX()+288), (getAlienBlockPositionY()+78));
			}
			if(curAlienX + 320 < curTankX && curTankX < curAlienX + 352) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+320), (getAlienBlockPositionY()+78));
				setAliens(0, 43);
				collisionCleanUp((getAlienBlockPositionX()+320), (getAlienBlockPositionY()+78));
			}
			updateMyscore(10);
			updateNumber(framePointer);
		}
		if(curAlienY + 104 < curTankY && curTankY < curAlienY +120){
			if(curAlienX < curTankX && curTankX < (curAlienX + 32)) {
				dyingAlien(framePointer, (getAlienBlockPositionX()), (getAlienBlockPositionY()+104));
				setAliens(0, 44);
				collisionCleanUp((getAlienBlockPositionX()), (getAlienBlockPositionY()+104));
			}
			if(curAlienX + 32 < curTankX && curTankX < curAlienX + 64) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+32), (getAlienBlockPositionY()+104));
				setAliens(0,45);
				collisionCleanUp((getAlienBlockPositionX()+32), (getAlienBlockPositionY()+104));
			}
			if(curAlienX + 64 < curTankX && curTankX < curAlienX + 96) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+64), (getAlienBlockPositionY()+104));
				setAliens(0, 46);
				collisionCleanUp((getAlienBlockPositionX()+64), (getAlienBlockPositionY()+104));
			}
			if(curAlienX + 96 < curTankX && curTankX < curAlienX + 128) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+96), (getAlienBlockPositionY()+104));
				setAliens(0, 47);
				collisionCleanUp((getAlienBlockPositionX()+96), (getAlienBlockPositionY()+104));
			}
			if(curAlienX + 128 < curTankX && curTankX < curAlienX + 160) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+128), (getAlienBlockPositionY()+104));
				setAliens(0, 48);
				collisionCleanUp((getAlienBlockPositionX()+128), (getAlienBlockPositionY()+104));
			}
			if(curAlienX + 160 < curTankX && curTankX < curAlienX + 192) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+160), (getAlienBlockPositionY()+104));
				setAliens(0, 49);
				collisionCleanUp((getAlienBlockPositionX()+160), (getAlienBlockPositionY()+104));
			}
			if(curAlienX + 192 < curTankX && curTankX < curAlienX + 224) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+192), (getAlienBlockPositionY()+104));
				setAliens(0, 50);
				collisionCleanUp((getAlienBlockPositionX()+192), (getAlienBlockPositionY()+104));
			}
			if(curAlienX + 224 < curTankX && curTankX < curAlienX + 256) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+224), (getAlienBlockPositionY()+104));
				setAliens(0, 51);
				collisionCleanUp((getAlienBlockPositionX()+224), (getAlienBlockPositionY()+104));
			}
			if(curAlienX + 256 < curTankX && curTankX < curAlienX + 288) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+256), (getAlienBlockPositionY()+104));
				setAliens(0, 52);
				collisionCleanUp((getAlienBlockPositionX()+256), (getAlienBlockPositionY()+104));
			}
			if(curAlienX + 288 < curTankX && curTankX < curAlienX + 320) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+288), (getAlienBlockPositionY()+104));
				setAliens(0, 53);
				collisionCleanUp((getAlienBlockPositionX()+288), (getAlienBlockPositionY()+104));
			}
			if(curAlienX + 320 < curTankX && curTankX < curAlienX + 352) {
				dyingAlien(framePointer, (getAlienBlockPositionX()+320), (getAlienBlockPositionY()+104));
				setAliens(0, 54);
				collisionCleanUp((getAlienBlockPositionX()+320), (getAlienBlockPositionY()+104));
			}
			updateMyscore(10);
			updateNumber(framePointer);
		}
	}
}

void alienSpeed() {
	short* aliens = getAliens();
	int i;
	int total = 0;
	for(i = 0; i < 55; i++) {
		if(aliens[i] == 1) {
			total++;
		}
	}
	if(total < 55) {
		speed = 30;
	}
	if(total < 44) {
		speed = 28;
	}
	if(total < 33) {
		speed = 26;
	}
	if(total < 22) {
		speed = 24;
	}
	if(total < 11) {
		speed = 20;
	}
	if(total == 0) {
		gameOver(framePointer);
	}
}

void timer_interrupt_handler() {
	onesec++;
	fifteenms++;
	fivems++;
	tenms++;
	mytimer++;

	if(mytimer == 5000){
		mytimer = 0;
		xil_printf("my counter value: %d\r\n", mycounter);
	}

	if(onesec == 100) {
		onesec = 0;
	}
	if(fifteenms == speed) {
		fifteenms = 0;
		incrementAlienSoundCadence();
		moveAlien(framePointer);
		renderAlien(framePointer);
		if(getAlienBlockPositionY() > 240){
			int col;
			for(col=0; col<640; col++) {
				if(framePointer[360*640 + col] == 0x00FFFFFF) {
					gameOver(framePointer);
				}

			}
		}

	}
	if(tenms == 2){
		tenms = 0;
		if(getUfoState() == 1){
			moveUfo(framePointer, getUfoDirection());
			renderUfo(framePointer);

		}

	}
	if(fivems == 1) {
		fivems = 0;
		if(getTankBulletState() == 1 || getAlien1BulletState() == 1 || getAlien2BulletState() == 1 || \
				getAlien3BulletState() == 1 || getAlien4BulletState() == 1) {
			int i;
			for(i = 0; i < 3; i++) {
				moveBullets(framePointer);
				renderBullet(framePointer);
			}
			if(getAlien1BulletState()){
				selectBlock(framePointer, 1);
			}
			if(getAlien2BulletState()){
				selectBlock(framePointer, 2);
			}
			if(getAlien3BulletState()){
				selectBlock(framePointer, 3);
			}
			if(getAlien4BulletState()){
				selectBlock(framePointer, 4);
			}
			if(getTankBulletState()){
				selectBlock(framePointer, 5);
			}
		}
	}
}

// This is invoked each time there is a change in the button state (result of a push or a bounce).
void pb_interrupt_handler() {
	// Clear the GPIO interrupt.
	XGpio_InterruptGlobalDisable(&gpPB);                // Turn off all PB interrupts for now.
	currentButtonState = XGpio_DiscreteRead(&gpPB, 1);  // Get the current state of the buttons.
	if(currentButtonState == 16) {
		increaseVolume();
	}
	if(currentButtonState == 4) {
		decreaseVolume();
	}
	XGpio_InterruptClear(&gpPB, 0xFFFFFFFF);            // Ack the PB interrupt.
	XGpio_InterruptGlobalEnable(&gpPB);                 // Re-enable PB interrupts.
}

// Main interrupt handler
void interrupt_handler_dispatcher(void* ptr) {
	int intc_status = XIntc_GetIntrStatus(XPAR_INTC_0_BASEADDR);

	// Check the AC97. Just one method - no need for a separate handler
	if (intc_status & XPAR_AXI_AC97_0_INTERRUPT_MASK) {
		XIntc_AckIntr(XPAR_INTC_0_BASEADDR, XPAR_AXI_AC97_0_INTERRUPT_MASK);
		fillSound();
	}
	// Check the FIT interrupt first.
//	if (intc_status & XPAR_FIT_TIMER_0_INTERRUPT_MASK){
//		XIntc_AckIntr(XPAR_INTC_0_BASEADDR, XPAR_FIT_TIMER_0_INTERRUPT_MASK);
//		timer_interrupt_handler();
//	}
	// Check the FIT interrupt first.
	if (intc_status & XPAR_BLINK_0_INTERRUPT_MASK){
		XIntc_AckIntr(XPAR_INTC_0_BASEADDR, XPAR_BLINK_0_INTERRUPT_MASK);
		timer_interrupt_handler();
	}

	// Check the push buttons.
	if (intc_status & XPAR_PUSH_BUTTONS_5BITS_IP2INTC_IRPT_MASK){
		XIntc_AckIntr(XPAR_INTC_0_BASEADDR, XPAR_PUSH_BUTTONS_5BITS_IP2INTC_IRPT_MASK);
		pb_interrupt_handler();
	}
}

int main() {
	init_platform();                   // Necessary for all programs.
	// Initialize the GPIO peripherals.
	 XAC97_HardReset(XPAR_AXI_AC97_0_BASEADDR);  //Reset XAC97
	 XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_MasterVol, AC97_VOL_ATTN_23_5_DB);  // Set default volume

	 XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR, AC97_ExtendedAudioStat, 1);
	 XAC97_WriteReg(XPAR_AXI_AC97_0_BASEADDR,AC97_PCM_DAC_Rate,AC97_PCM_RATE_11025_HZ);

	 XAC97_mSetControl(XPAR_AXI_AC97_0_BASEADDR, AC97_ENABLE_IN_FIFO_INTERRUPT);   //Enable AC97 Interrupts

	//interrupt code from clock lab
	int success;
	success = XGpio_Initialize(&gpPB, XPAR_PUSH_BUTTONS_5BITS_DEVICE_ID);
	// Set the push button peripheral to be inputs.
	XGpio_SetDataDirection(&gpPB, 1, 0x0000001F);
	// Enable the global GPIO interrupt for push buttons.
	XGpio_InterruptGlobalEnable(&gpPB);
	// Enable all interrupts in the push button peripheral.
	XGpio_InterruptEnable(&gpPB, 0xFFFFFFFF);

    BLINK_mWriteSlaveReg0(XPAR_BLINK_0_BASEADDR, 0, 0x7);
    BLINK_mWriteSlaveReg1(XPAR_BLINK_0_BASEADDR, 0, 0x001fffff);


	microblaze_register_handler(interrupt_handler_dispatcher, NULL);
//	XIntc_EnableIntr(XPAR_INTC_0_BASEADDR,
//			(XPAR_FIT_TIMER_0_INTERRUPT_MASK | XPAR_PUSH_BUTTONS_5BITS_IP2INTC_IRPT_MASK |XPAR_AXI_AC97_0_INTERRUPT_MASK ));
	XIntc_EnableIntr(XPAR_INTC_0_BASEADDR,
			(XPAR_BLINK_0_INTERRUPT_MASK | XPAR_PUSH_BUTTONS_5BITS_IP2INTC_IRPT_MASK |XPAR_AXI_AC97_0_INTERRUPT_MASK ));

	XIntc_MasterEnable(XPAR_INTC_0_BASEADDR);
	microblaze_enable_interrupts();
	//end of interrupt code from clock lab


	int Status;                        // Keep track of success/failure of system function calls.
	XAxiVdma videoDMAController;
	// There are 3 steps to initializing the vdma driver and IP.
	// Step 1: lookup the memory structure that is used to access the vdma driver.
    XAxiVdma_Config * VideoDMAConfig = XAxiVdma_LookupConfig(XPAR_AXI_VDMA_0_DEVICE_ID);
    // Step 2: Initialize the memory structure and the hardware.
    if(XST_FAILURE == XAxiVdma_CfgInitialize(&videoDMAController, VideoDMAConfig,	XPAR_AXI_VDMA_0_BASEADDR)) {
    	xil_printf("VideoDMA Did not initialize.\r\n");
    }
    // Step 3: (optional) set the frame store number.
    if(XST_FAILURE ==  XAxiVdma_SetFrmStore(&videoDMAController, 2, XAXIVDMA_READ)) {
    	xil_printf("Set Frame Store Failed.");
    }
    // Initialization is complete at this point.

    // Setup the frame counter. We want two read frames. We don't need any write frames but the
    // function generates an error if you set the write frame count to 0. We set it to 2
    // but ignore it because we don't need a write channel at all.
    XAxiVdma_FrameCounter myFrameConfig;
    myFrameConfig.ReadFrameCount = 2;
    myFrameConfig.ReadDelayTimerCount = 10;
    myFrameConfig.WriteFrameCount =2;
    myFrameConfig.WriteDelayTimerCount = 10;
    Status = XAxiVdma_SetFrameCounter(&videoDMAController, &myFrameConfig);
    if (Status != XST_SUCCESS) {
	   xil_printf("Set frame counter failed %d\r\n", Status);
	   if(Status == XST_VDMA_MISMATCH_ERROR)
		   xil_printf("DMA Mismatch Error\r\n");
    }
    // Now we tell the driver about the geometry of our frame buffer and a few other things.
    // Our image is 480 x 640.
    XAxiVdma_DmaSetup myFrameBuffer;
    myFrameBuffer.VertSizeInput = 480;    // 480 vertical pixels.
    myFrameBuffer.HoriSizeInput = 640*4;  // 640 horizontal (32-bit pixels).
    myFrameBuffer.Stride = 640*4;         // Dont' worry about the rest of the values.
    myFrameBuffer.FrameDelay = 0;
    myFrameBuffer.EnableCircularBuf=1;
    myFrameBuffer.EnableSync = 0;
    myFrameBuffer.PointNum = 0;
    myFrameBuffer.EnableFrameCounter = 0;
    myFrameBuffer.FixedFrameStoreAddr = 0;
    if(XST_FAILURE == XAxiVdma_DmaConfig(&videoDMAController, XAXIVDMA_READ, &myFrameBuffer)) {
    	xil_printf("DMA Config Failed\r\n");
     }
    // We need to give the frame buffer pointers to the memory that it will use. This memory
    // is where you will write your video data. The vdma IP/driver then streams it to the HDMI
    // IP.
     myFrameBuffer.FrameStoreStartAddr[0] = FRAME_BUFFER_0_ADDR;

     if(XST_FAILURE == XAxiVdma_DmaSetBufferAddr(&videoDMAController, XAXIVDMA_READ,
    		               myFrameBuffer.FrameStoreStartAddr)) {
    	 xil_printf("DMA Set Address Failed Failed\r\n");
     }
     // Print a sanity message if you get this far.
     xil_printf("Woohoo! I made it through initialization.\n\r");
     // Now, let's get ready to start displaying some stuff on the screen.
     // The variables framePointer and framePointer1 are just pointers to the base address
     // of frame 0 and frame 1.
     //unsigned int * framePointer = (unsigned int *) FRAME_BUFFER_0_ADDR;
     int row = 0;
     int col = 0;

     for(row=0; row<480; row++) {
    	 for(col=0; col<640; col++) {
    		 framePointer[row*640 + col] = 0x00000000;
    	 }
     }
     for(row=0; row<480; row++) {
    	 for(col=0; col<640; col++) {
    		 if(row > 460 && row < 464) {
    			 framePointer[row*640 + col] = 0x0000FF00;
    		 }
    		 else {
    			 framePointer[row*640 + col] = 0x00000000;
    		 }
    	 }
     }

     // This tells the HDMI controller the resolution of your display (there must be a better way to do this).
     XIo_Out32(XPAR_AXI_HDMI_0_BASEADDR, 640*480);

     // Start the DMA for the read channel only.
     if(XST_FAILURE == XAxiVdma_DmaStart(&videoDMAController, XAXIVDMA_READ)){
    	 xil_printf("DMA START FAILED\r\n");
     }
     int frameIndex = 0;
     // We have two frames, let's park on frame 0. Use frameIndex to index them.
     // Note that you have to start the DMA process before parking on a frame.
     if (XST_FAILURE == XAxiVdma_StartParking(&videoDMAController, frameIndex,  XAXIVDMA_READ)) {
    	 xil_printf("vdma parking failed\n\r");
     }

     setAlienBlockPosition(0, 120);
	 setTankPosition(300, 420);
	 renderTank(framePointer);
	 renderAlien(framePointer);
	 renderBunker(framePointer);
	 renderScore(framePointer);
	 renderNumber(framePointer);
	 renderTanks(framePointer);
	 alienSpeed();

	 int looping = 1;
	 while(looping){
		 inputChar = XUartLite_RecvByte(XPAR_RS232_UART_1_BASEADDR);
		 if(inputChar == '\r'){

			 BLINK_mWriteSlaveReg1(XPAR_BLINK_0_BASEADDR, 0, delayValue);
			 xil_printf("delay value set to: %d\n\r", delayValue);
			 delayValue = 0;
			 looping = 0;
		 }
		 if((inputChar >= '0') && (inputChar <= '9')){

			 delayValue = delayValue*10 + (inputChar - '0');

		 }
	 }


	 while (gameState) {

		 mycounter++;

		 alienCollision();
		 if(currentButtonState == 0x08) {
			xil_printf("we are in left\r\n");
			 moveTankL(framePointer);
			 renderTank(framePointer);
		 }
		 if(currentButtonState == 0x02) {
			 xil_printf("we are in right\r\n");
			 moveTankR(framePointer);
			 renderTank(framePointer);
		 }
		 if(currentButtonState == 0x01) {
			 xil_printf("we are in mid\r\n");
			 if(getTankBulletState() == 1) {
				 continue;
			 }
			 else {
				 setHaveTankBulletSound(1);
				 setTankBulletState(1);
				 initialTankBulletPosition();
				 renderBullet(framePointer);
			 }
		 }
		 if(currentButtonState == 0x09) {
			 xil_printf("we are in mid\r\n");
			 moveTankL(framePointer);
			 renderTank(framePointer);
			 if(getTankBulletState() == 1) {
				 continue;
			 }
			 else {
				 setHaveTankBulletSound(1);
				 setTankBulletState(1);
				 initialTankBulletPosition();
				 renderBullet(framePointer);
			 }
		 }
		 if(currentButtonState == 0x03) {
			 xil_printf("we are in mid\r\n");
			 moveTankR(framePointer);
			 renderTank(framePointer);
			 if(getTankBulletState() == 1) {
				 continue;
			 }
			 else {
				 setHaveTankBulletSound(1);
				 setTankBulletState(1);
				 initialTankBulletPosition();
				 renderBullet(framePointer);
			 }
		 }

		 int ufo_show = rand() % 3000;
		 if(ufo_show == 100){
			 if(getUfoState() == 0){
				 setHaveSpaceShipSound(1);
				 setUfoState(1);
				 setUfoDirection();
				 if(getUfoDirection()){		// getUfoDirection = 1 means ufo going left
					 setUfoPositionX(610);
					 setUfoPositionY(45);
					 renderUfo(framePointer);
				 }
				 else{				   	    // getUfoDirection = 0 means ufo going right
					 setUfoPositionX(0);
					 setUfoPositionY(45);
					 renderUfo(framePointer);
				 }
			 }
		 }

		 int alienShot = rand() % 100000;	// this controls how frequent bullets are fired by aliens
		 if(alienShot == 50) {	//key 3
			 int i = 0;
			 int j = rand() % 4;
			 int k[4] = {getAlien1BulletState(), getAlien2BulletState(), getAlien3BulletState(), getAlien4BulletState()};
			 for(i = 0; i < 16; i ++) {
				 if(k[j] == 0) {
					 break;
				 }
				 else {
					 j = rand()%4;
				 }
			 }
			 int bottomAlien = 0;
			 short* aliens = getAliens();
			 int a;
			 while(bottomAlien == 0) {
				 a = rand () % 54;
				 if(aliens[a] == 1 && isBottom(a)) {
					 bottomAlien = 1;
				 }
			 }
			 int position = whatRow(a);
			 int x = a % 11;

			 switch(j){
			 case 0:
				 if(getAlien1BulletState() == 0) {
					 setAlien1BulletState(1);
					 setAlien1BulletPosition(((getAlienBlockPositionX()+10) + 32 * x), getAlienBlockPositionY()+position);
					 renderBullet(framePointer);
				 }
				 break;
			 case 1:
				 if(getAlien2BulletState() == 0) {
					 setAlien2BulletState(1);
					 setAlien2BulletPosition(((getAlienBlockPositionX()+10) + 32 * x), getAlienBlockPositionY()+position);
					 renderBullet(framePointer);
				 }
				 break;
			 case 2:
				 if(getAlien3BulletState() == 0) {
					 setAlien3BulletState(1);
					 setAlien3BulletPosition(((getAlienBlockPositionX()+10) + 32 * x), getAlienBlockPositionY()+position);
					 renderBullet(framePointer);
				 }
				 break;
			 case 3:
				 if(getAlien4BulletState() == 0) {
					 setAlien4BulletState(1);
					 setAlien4BulletPosition(((getAlienBlockPositionX()+10) + 32 * x), getAlienBlockPositionY()+position);
					 renderBullet(framePointer);
				 }
				 break;
			 default :
				 break;
			 }
		 }
	 }
	 cleanup_platform();

	 return 0;
}
