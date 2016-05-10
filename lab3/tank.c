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
	if(tankx == 0 || tankx+32 == 640) {
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
	if(tankx == 0 || tankx+32 == 640) {
	}
	else {
		tankx += 2;
		setTankPosition(tankx, tanky);
	}
}
