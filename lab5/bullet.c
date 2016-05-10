#include "bullet.h"

void renderBullet(unsigned int* framePointer) {
	if(getGuiseBullet() == 0) {
		setGuiseBullet(1);
		renderBullet1(framePointer);
	}else {
		setGuiseBullet(0);
		renderBullet2(framePointer);
	}
}

void renderBullet1(unsigned int* framePointer) {
	if(getTankBulletState() == 1) {
		short initial_x = getTankBulletPositionX();
		short initial_y = getTankBulletPositionY();
		int x, y;
		for(x = 0; x < BLOCK_HEIGHT; x++) {
			for(y = 0; y < BLOCK_WIDTH; y++){
				if ((tankBullet[x%10] & (1<<(BLOCK_WIDTH-1-y)))) {
					framePointer[(initial_y+x)*640 + initial_x+y] = 0x00FFFFFE;
				} else {
					framePointer[(initial_y+x)*640 + initial_x+y] = 0x00000000;
				}
			}
		}
	}
	if(getAlien1BulletState() == 1) {
		short initial_x = getAlien1BulletPositionX();
		short initial_y = getAlien1BulletPositionY();
		int x, y;
		for(x = 0; x < BLOCK_HEIGHT; x++) {
			for(y = 0; y < BLOCK_WIDTH; y++){
				if ((alienBullet1_1[x%10] & (1<<(BLOCK_WIDTH-1-y)))) {
					framePointer[(initial_y+x)*640 + initial_x+y] = 0x00FFFFFE;
				} else {
					framePointer[(initial_y+x)*640 + initial_x+y] = 0x00000000;
				}
			}
		}
	}
	if(getAlien2BulletState() == 1) {
		short initial_x = getAlien2BulletPositionX();
		short initial_y = getAlien2BulletPositionY();
		int x, y;
		for(x = 0; x < BLOCK_HEIGHT; x++) {
			for(y = 0; y < BLOCK_WIDTH; y++){
				if ((alienBullet2_1[x%10] & (1<<(BLOCK_WIDTH-1-y)))) {
					framePointer[(initial_y+x)*640 + initial_x+y] = 0x00FFFFFE;
				} else {
					framePointer[(initial_y+x)*640 + initial_x+y] = 0x00000000;
				}
			}
		}
	}
	if(getAlien3BulletState() == 1) {
		short initial_x = getAlien3BulletPositionX();
		short initial_y = getAlien3BulletPositionY();
		int x, y;
		for(x = 0; x < BLOCK_HEIGHT; x++) {
			for(y = 0; y < BLOCK_WIDTH; y++){
				if ((alienBullet3_1[x%10] & (1<<(BLOCK_WIDTH-1-y)))) {
					framePointer[(initial_y+x)*640 + initial_x+y] = 0x00FFFFFE;
				} else {
					framePointer[(initial_y+x)*640 + initial_x+y] = 0x00000000;
				}
			}
		}
	}
	if(getAlien4BulletState() == 1) {
		short initial_x = getAlien4BulletPositionX();
		short initial_y = getAlien4BulletPositionY();
		int x, y;
		for(x = 0; x < BLOCK_HEIGHT; x++) {
			for(y = 0; y < BLOCK_WIDTH; y++){
				if ((alienBullet1_1[x%10] & (1<<(BLOCK_WIDTH-1-y)))) {
					framePointer[(initial_y+x)*640 + initial_x+y] = 0x00FFFFFE;
				} else {
					framePointer[(initial_y+x)*640 + initial_x+y] = 0x00000000;
				}
			}
		}
	}
}

void renderBullet2(unsigned int* framePointer) {
	if(getTankBulletState() == 1) {
		short initial_x = getTankBulletPositionX();
		short initial_y = getTankBulletPositionY();
		int x, y;
		for(x = 0; x < BLOCK_HEIGHT; x++) {
			for(y = 0; y < BLOCK_WIDTH; y++){
				if ((tankBullet[x%10] & (1<<(BLOCK_WIDTH-1-y)))) {
					framePointer[(initial_y+x)*640 + initial_x+y] = 0x00FFFFFE;
				} else {
					framePointer[(initial_y+x)*640 + initial_x+y] = 0x00000000;
				}
			}
		}
	}
	if(getAlien1BulletState() == 1) {
		short initial_x = getAlien1BulletPositionX();
		short initial_y = getAlien1BulletPositionY();
		int x, y;
		for(x = 0; x < BLOCK_HEIGHT; x++) {
			for(y = 0; y < BLOCK_WIDTH; y++){
				if ((alienBullet1_2[x%10] & (1<<(BLOCK_WIDTH-1-y)))) {
					framePointer[(initial_y+x)*640 + initial_x+y] = 0x00FFFFFE;
				} else {
					framePointer[(initial_y+x)*640 + initial_x+y] = 0x00000000;
				}
			}
		}
	}
	if(getAlien2BulletState() == 1) {
		short initial_x = getAlien2BulletPositionX();
		short initial_y = getAlien2BulletPositionY();
		int x, y;
		for(x = 0; x < BLOCK_HEIGHT; x++) {
			for(y = 0; y < BLOCK_WIDTH; y++){
				if ((alienBullet2_2[x%10] & (1<<(BLOCK_WIDTH-1-y)))) {
					framePointer[(initial_y+x)*640 + initial_x+y] = 0x00FFFFFE;
				} else {
					framePointer[(initial_y+x)*640 + initial_x+y] = 0x00000000;
				}
			}
		}
	}
	if(getAlien3BulletState() == 1) {
		short initial_x = getAlien3BulletPositionX();
		short initial_y = getAlien3BulletPositionY();
		int x, y;
		for(x = 0; x < BLOCK_HEIGHT; x++) {
			for(y = 0; y < BLOCK_WIDTH; y++){
				if ((alienBullet3_2[x%10] & (1<<(BLOCK_WIDTH-1-y)))) {
					framePointer[(initial_y+x)*640 + initial_x+y] = 0x00FFFFFE;
				} else {
					framePointer[(initial_y+x)*640 + initial_x+y] = 0x00000000;
				}
			}
		}
	}
	if(getAlien4BulletState() == 1) {
		short initial_x = getAlien4BulletPositionX();
		short initial_y = getAlien4BulletPositionY();
		int x, y;
		for(x = 0; x < BLOCK_HEIGHT; x++) {
			for(y = 0; y < BLOCK_WIDTH; y++){
				if ((alienBullet1_2[x%10] & (1<<(BLOCK_WIDTH-1-y)))) {
					framePointer[(initial_y+x)*640 + initial_x+y] = 0x00FFFFFE;
				} else {
					framePointer[(initial_y+x)*640 + initial_x+y] = 0x00000000;
				}
			}
		}
	}
}

void blankTankBullet(unsigned int* framePointer){
	short tankx, tanky;
    tankx = getTankBulletPositionX();
    tanky = getTankBulletPositionY();
	short row=0, col=0;
	for(row = 0; row < BLOCK_HEIGHT; row++){
		for(col = 0; col < BLOCK_WIDTH; col++){
			framePointer[(tanky+row)*640 + tankx+col] = 0x00000000;
		}
	}
}

void blankAlienBullet(unsigned int* framePointer, short alienx, short alieny) {
	short row=0, col=0;
	for(row = 0; row < BLOCK_HEIGHT; row++){
		for(col = 0; col < BLOCK_WIDTH; col++){
			framePointer[(alieny+row)*640 + alienx+col] = 0x00000000;
		}
	}
}

void moveBullets(unsigned int* framePointer) {
	if(getTankBulletState() == 1) {
		if(getTankBulletPositionY() == 30) {
			blankTankBullet(framePointer);
			setTankBulletState(0);
		}
		else {
			setTankBulletPositionY(getTankBulletPositionY()-1);
		}
	}
	if(getAlien1BulletState() == 1) {
		if(getAlien1BulletPositionY() == 450) {
			blankAlienBullet(framePointer, getAlien1BulletPositionX(), getAlien1BulletPositionY());
			setAlien1BulletState(0);
		}
		else {
			setAlien1BulletPositionY(getAlien1BulletPositionY()+1);
		}
	}
	if(getAlien2BulletState() == 1) {
		if(getAlien2BulletPositionY() == 450) {
			blankAlienBullet(framePointer, getAlien2BulletPositionX(), getAlien2BulletPositionY());
			setAlien2BulletState(0);
		}
		else {
			setAlien2BulletPositionY(getAlien2BulletPositionY()+1);
		}
	}
	if(getAlien3BulletState() == 1) {
		if(getAlien3BulletPositionY() == 450) {
			blankAlienBullet(framePointer, getAlien3BulletPositionX(), getAlien3BulletPositionY());
			setAlien3BulletState(0);
		}
		else {
			setAlien3BulletPositionY(getAlien3BulletPositionY()+1);
		}
	}
	if(getAlien4BulletState() == 1) {
		if(getAlien4BulletPositionY() == 450) {
			blankAlienBullet(framePointer, getAlien4BulletPositionX(), getAlien4BulletPositionY());
			setAlien4BulletState(0);
		}
		else {
			setAlien4BulletPositionY(getAlien4BulletPositionY()+1);
		}
	}
}
