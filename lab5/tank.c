#include "tank.h"

void renderTank(unsigned int* framePointer) {
	short tankx, tanky;
	tankx = getTankPositionX();
	tanky = getTankPositionY();
	int row, col;

	for(row=0; row < 16; row++) {
		for(col=0; col < 32; col++) {
			if ((tank[row%16] & (1<<(32-1-col)))) {
				framePointer[tanky*640 + tankx] = 0x0000FF00;

			} else {
				framePointer[tanky*640 + tankx] = 0x00000000;
			}
			tankx++;
		}
		tankx=getTankPositionX();
		tanky++;
	}
}
void renderDying1(unsigned int* framePointer) {
	short tankx, tanky;
	tankx = getTankPositionX();
	tanky = getTankPositionY();
	int row, col;

	for(row=0; row < 16; row++) {
		for(col=0; col < 32; col++) {
			if ((tank_dying1[row%16] & (1<<(32-1-col)))) {
				framePointer[tanky*640 + tankx] = 0x0000FF00;

			} else {
				framePointer[tanky*640 + tankx] = 0x00000000;
			}
			tankx++;
		}
		tankx=getTankPositionX();
		tanky++;
	}
}
void renderDying2(unsigned int* framePointer) {
	short tankx, tanky;
	tankx = getTankPositionX();
	tanky = getTankPositionY();
	int row, col;

	for(row=0; row < 16; row++) {
		for(col=0; col < 32; col++) {
			if ((tank_dying2[row%16] & (1<<(32-1-col)))) {
				framePointer[tanky*640 + tankx] = 0x0000FF00;

			} else {
				framePointer[tanky*640 + tankx] = 0x00000000;
			}
			tankx++;
		}
		tankx=getTankPositionX();
		tanky++;
	}
}

void blankTank(unsigned int* framePointer) {
	short tankx, tanky;
	tankx = getTankPositionX();
	tanky = getTankPositionY();
	int row, col;
	for(row=0; row < 16; row++) {
		for(col=0; col < 32; col++) {
			framePointer[tanky*640 + tankx] = 0x00000000;
			tankx++;
		}
		tankx=getTankPositionX();
		tanky++;
	}

}
void moveTankL(unsigned int* framePointer) {
	short dir = getDirection();
	short tankx, tanky;
	tankx = getTankPositionX();
	tanky = getTankPositionY();
	if(tankx+32 == 638) {
		tankx -= 2;
		setTankPosition(tankx, tanky);
	}
	if(tankx == 4 || tankx+32 == 638) {
	}
	else {
		tankx -= 2;
		setTankPosition(tankx, tanky);
	}
}

void moveTankR(unsigned int* framePointer) {
	short dir = getDirection();
	short tankx, tanky;
	tankx = getTankPositionX();
	tanky = getTankPositionY();
	if(tankx == 0) {
		tankx += 2;
		setTankPosition(tankx, tanky);
	}
	if(tankx == 0 || tankx+32 == 638) {
	}
	else {
		tankx += 2;
		setTankPosition(tankx, tanky);
	}
}
