#include "alien.h"

void renderAlien(unsigned int* framePointer) {
	blankAlien(framePointer);
	if(getGuise() == 0) {
		setGuise(1);
		renderAlien1(framePointer);
	}else {
		setGuise(0);
		renderAlien2(framePointer);
	}
}

void renderAlien1(unsigned int* framePointer) {
	short alienx, alieny;
	alienx = getAlienBlockPositionX();
	alieny = getAlienBlockPositionY();
	short row=0, col=0;
	short line = 0;
	short position = 0;
	short* aliens = getAliens();
	for(line = 0; line < 10; line++) {
		if(line % 2 == 1) {
			alieny += 10;
		}
		else {
			if(line == 0) {
				for(row=0; row<16; row++) {
					short position_helper = -1;
					for(col=0; col<352; col++) {
						if (((topAlien1[row%16] & (1<<(32-1-col)))) && aliens[position+position_helper] == 1) {
							framePointer[alieny*640 + alienx] = 0x00FFFFFF;
						} else {
							framePointer[alieny*640 + alienx] = 0x00000000;
						}
						if(col % 32 == 0) {
							position_helper++;
						}
						alienx++;
					}
					alienx=getAlienBlockPositionX();
					alieny++;
				}
			}
			if(line == 2 || line == 4) {
				position += 11;
				for(row=0; row<16; row++) {
					short position_helper = -1;
					for(col=0; col<352; col++) {
						if (((middleAlien1[row%16] & (1<<(32-1-col)))) && aliens[position+position_helper] == 1) {
							framePointer[alieny*640 + alienx] = 0x00FFFFFF;
						} else {
							framePointer[alieny*640 + alienx] = 0x00000000;
						}
						if(col % 32 == 0) {
							position_helper++;
						}
						alienx++;
					}
					alienx=getAlienBlockPositionX();
					alieny++;
				}
			}
			if(line == 6 || line == 8) {
				position += 11;
				for(row=0; row<16; row++) {
					short position_helper = -1;
					for(col=0; col<352; col++) {
						if (((bottomAlien1[row%16] & (1<<(32-1-col))))&& aliens[position+position_helper] == 1) {
							framePointer[alieny*640 + alienx] = 0x00FFFFFF;
						} else {
							framePointer[alieny*640 + alienx] = 0x00000000;
						}
						if(col % 32 == 0) {
							position_helper++;
						}
						alienx++;
					}
					alienx=getAlienBlockPositionX();
					alieny++;
				}
			}
		}
	}
}

void renderAlien2(unsigned int* framePointer) {
	short alienx, alieny;
	alienx = getAlienBlockPositionX();
	alieny = getAlienBlockPositionY();
	short row=0, col=0;
	short line = 0;
	short position = 0;
	short* aliens = getAliens();
	for(line = 0; line < 10; line++) {
		if(line % 2 == 1) {
			alieny += 10;
		}
		else {
			if(line == 0) {
				for(row=0; row<16; row++) {
					short position_helper = -1;
					for(col=0; col<352; col++) {
						if (((topAlien2[row%16] & (1<<(32-1-col)))) && aliens[position+position_helper] == 1) {
							framePointer[alieny*640 + alienx] = 0x00FFFFFF;
						} else {
							framePointer[alieny*640 + alienx] = 0x00000000;
						}
						if(col % 32 == 0) {
							position_helper++;
						}
						alienx++;
					}
					alienx=getAlienBlockPositionX();
					alieny++;
				}
			}
			if(line == 2 || line == 4) {
				position += 11;
				for(row=0; row<16; row++) {
					short position_helper = -1;
					for(col=0; col<352; col++) {
						if (((middleAlien2[row%16] & (1<<(32-1-col))))&& aliens[position+position_helper] == 1) {
							framePointer[alieny*640 + alienx] = 0x00FFFFFF;
						} else {
							framePointer[alieny*640 + alienx] = 0x00000000;
						}
						if(col % 32 == 0) {
							position_helper++;
						}
						alienx++;
					}
					alienx=getAlienBlockPositionX();
					alieny++;
				}
			}
			if(line == 6 || line == 8) {
				position += 11;
				for(row=0; row<16; row++) {
					short position_helper = -1;
					for(col=0; col<352; col++) {
						if (((bottomAlien2[row%16] & (1<<(32-1-col))))&& aliens[position+position_helper] == 1) {
							framePointer[alieny*640 + alienx] = 0x00FFFFFF;
						} else {
							framePointer[alieny*640 + alienx] = 0x00000000;
						}
						if(col % 32 == 0) {
							position_helper++;
						}
						alienx++;
					}
					alienx=getAlienBlockPositionX();
					alieny++;
				}
			}
		}
	}
}

void blankAlien(unsigned int* framePointer){
	short alienx, alieny;
	alienx = getAlienBlockPositionX();
	alieny = getAlienBlockPositionY();
	short row=0, col=0;
	for(row = 0; row < 130; row++){
		for(col = 0; col < 352; col++){
			framePointer[alieny*640 + alienx] = 0x00000000;
			alienx++;
		}
		alienx=getAlienBlockPositionX();
		alieny++;
	}
}

void moveAlien(unsigned int* framePointer) {
	short dir = getDirection();
	short alienx, alieny;
	alienx = getAlienBlockPositionX();
	alieny = getAlienBlockPositionY();
	if((alienx+352) == 640 && dir == 0) {
		setDirection(1);
		blankAlien(framePointer);
		alieny += 8;
		setAlienBlockPosition(alienx, alieny);
	}
	if(alienx == 0 && dir == 1) {
		setDirection(0);
		blankAlien(framePointer);
		alieny += 8;
		setAlienBlockPosition(alienx, alieny);

	}
	if(dir == 0) {
		alienx += 2;
		setAlienBlockPosition(alienx, alieny);
	}
	else {
		alienx -= 2;
		setAlienBlockPosition(alienx, alieny);
	}
}

