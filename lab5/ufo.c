#include "ufo.h"

void renderUfo(unsigned int* framePointer) {		// draw for the first time

	if(getUfoState()){
		short x=0, y=0;

		for(x = 0; x < UFO_HEIGHT; x++) {
			for(y = 0; y < UFO_WIDTH; y++){
				if ((ufo[x%UFO_HEIGHT] & (1<<(UFO_WIDTH-1-y)))) {
					framePointer[(getUfoPositionY()+x)*640 + getUfoPositionX()+y] = 0x00FF0000;
				} else {
					framePointer[(getUfoPositionY()+x)*640 + getUfoPositionX()+y] = 0x00000000;
				}
			}
		}
	}

}

void moveUfo(unsigned int* framePointer, int ufo_left) {
	short ufox, ufoy;
	ufox = getUfoPositionX();
	ufoy = getUfoPositionY();

	if((ufox+UFO_WIDTH) == 639 && !ufo_left) {
		setUfoPositionX(ufox);
		blankUfo(framePointer, getUfoPositionX(), getUfoPositionY());
		setUfoState(0);
	}
	if(ufox == 0 && ufo_left) {
		setUfoPositionX(ufox);
		blankUfo(framePointer, getUfoPositionX(), getUfoPositionY());
		setUfoState(0);
	}
	if(ufo_left) {
		ufox -= 1;
		setUfoPositionX(ufox);
	}
	else {
		ufox += 1;
		setUfoPositionX(ufox);
	}
}

void blankUfo(unsigned int* framePointer, int ufox, int ufoy){
	setHaveSpaceShipSound(0);
	short row=0, col=0;
	for(row = 0; row < UFO_HEIGHT; row++){
		for(col = 0; col < UFO_WIDTH; col++){
			framePointer[(ufoy+row)*640+(ufox+col)] = 0x00000000;
		}
	}
}

int selectingUfoscore(unsigned int* framePointer, int ufoscore){
	int x_position = getUfoPositionX();
	int y_position = getUfoPositionY();
	int updatingscore = 0;
	int counter = 0;

	switch(ufoscore){
	case 0:			// 50
		renderUfoscore(framePointer, 5, x_position, y_position);
		x_position = x_position + 8;
		renderUfoscore(framePointer, 0, x_position, y_position);
		updatingscore = 50;
		break;
	case 1: 		// 100
		renderUfoscore(framePointer, 1, x_position, y_position);
		x_position = x_position + 8;
		renderUfoscore(framePointer, 0, x_position, y_position);
		x_position = x_position + 8;
		renderUfoscore(framePointer, 0, x_position, y_position);

		updatingscore = 100;
		break;
	case 2:			// 150
		renderUfoscore(framePointer, 1, x_position, y_position);
		x_position = x_position + 8;
		renderUfoscore(framePointer, 5, x_position, y_position);
		x_position = x_position + 8;
		renderUfoscore(framePointer, 0, x_position, y_position);
		updatingscore = 150;
		break;
	case 3: 		// 200
		renderUfoscore(framePointer, 2, x_position, y_position);
		x_position = x_position + 8;
		renderUfoscore(framePointer, 0, x_position, y_position);
		x_position = x_position + 8;
		renderUfoscore(framePointer, 0, x_position, y_position);
		updatingscore = 200;
		break;
	case 4:			// 250
		renderUfoscore(framePointer, 2, x_position, y_position);
		x_position = x_position + 8;
		renderUfoscore(framePointer, 5, x_position, y_position);
		x_position = x_position + 8;
		renderUfoscore(framePointer, 0, x_position, y_position);
		updatingscore = 250;
		break;
	case 5:			// 300
		renderUfoscore(framePointer, 3, x_position, y_position);
		x_position = x_position + 8;
		renderUfoscore(framePointer, 0, x_position, y_position);
		x_position = x_position + 8;
		renderUfoscore(framePointer, 0, x_position, y_position);
		updatingscore = 300;

		break;
	case 6:			// 350
		renderUfoscore(framePointer, 3, x_position, y_position);
		x_position = x_position + 8;
		renderUfoscore(framePointer, 5, x_position, y_position);
		x_position = x_position + 8;
		renderUfoscore(framePointer, 0, x_position, y_position);
		updatingscore = 350;

		break;
	default:
		break;

	}

	while(counter < 500000){
		counter++;
	}

	blankUfo(framePointer, x_position-16, y_position);

	return updatingscore;
}

void renderUfoscore(unsigned int* framePointer, int number, int x_position, int y_position){

	short x=0, y=0;

	switch(number){
	case 0:
		for(x = 0; x < UFOSCORE_HEIGHT; x++) {
			for(y = 0; y < UFOSCORE_WIDTH; y++){
				if ((ufo_zero_block[x%UFOSCORE_HEIGHT] & (1<<(UFOSCORE_WIDTH-1-y)))) {
					framePointer[(y_position+x)*640 + x_position+y] = 0x00FF00FF;
				} else {
					framePointer[(y_position+x)*640 + x_position+y] = 0x00000000;
				}
			}
		}
		break;
	case 1:
		for(x = 0; x < UFOSCORE_HEIGHT; x++) {
			for(y = 0; y < UFOSCORE_WIDTH; y++){
				if ((ufo_one_block[x%UFOSCORE_HEIGHT] & (1<<(UFOSCORE_WIDTH-1-y)))) {
					framePointer[(y_position+x)*640 + x_position+y] = 0x00FF00FF;
				} else {
					framePointer[(y_position+x)*640 + x_position+y] = 0x00000000;
				}
			}
		}

		break;
	case 2:
		for(x = 0; x < UFOSCORE_HEIGHT; x++) {
			for(y = 0; y < UFOSCORE_WIDTH; y++){
				if ((ufo_two_block[x%UFOSCORE_HEIGHT] & (1<<(UFOSCORE_WIDTH-1-y)))) {
					framePointer[(y_position+x)*640 + x_position+y] = 0x00FF00FF;
				} else {
					framePointer[(y_position+x)*640 + x_position+y] = 0x00000000;
				}
			}
		}
		break;
	case 3:
		for(x = 0; x < UFOSCORE_HEIGHT; x++) {
			for(y = 0; y < UFOSCORE_WIDTH; y++){
				if ((ufo_three_block[x%UFOSCORE_HEIGHT] & (1<<(UFOSCORE_WIDTH-1-y)))) {
					framePointer[(y_position+x)*640 + x_position+y] = 0x00FF00FF;
				} else {
					framePointer[(y_position+x)*640 + x_position+y] = 0x00000000;
				}
			}
		}
		break;
	case 4:
		for(x = 0; x < UFOSCORE_HEIGHT; x++) {
			for(y = 0; y < UFOSCORE_WIDTH; y++){
				if ((ufo_four_block[x%UFOSCORE_HEIGHT] & (1<<(UFOSCORE_WIDTH-1-y)))) {
					framePointer[(y_position+x)*640 + x_position+y] = 0x00FF00FF;
				} else {
					framePointer[(y_position+x)*640 + x_position+y] = 0x00000000;
				}
			}
		}
		break;
	case 5:
		for(x = 0; x < UFOSCORE_HEIGHT; x++) {
			for(y = 0; y < UFOSCORE_WIDTH; y++){
				if ((ufo_five_block[x%UFOSCORE_HEIGHT] & (1<<(UFOSCORE_WIDTH-1-y)))) {
					framePointer[(y_position+x)*640 + x_position+y] = 0x00FF00FF;
				} else {
					framePointer[(y_position+x)*640 + x_position+y] = 0x00000000;
				}
			}
		}
		break;
	case 6:
		for(x = 0; x < UFOSCORE_HEIGHT; x++) {
			for(y = 0; y < UFOSCORE_WIDTH; y++){
				if ((ufo_six_block[x%UFOSCORE_HEIGHT] & (1<<(UFOSCORE_WIDTH-1-y)))) {
					framePointer[(y_position+x)*640 + x_position+y] = 0x00FF00FF;
				} else {
					framePointer[(y_position+x)*640 + x_position+y] = 0x00000000;
				}
			}
		}
		break;
	case 7:
		for(x = 0; x < UFOSCORE_HEIGHT; x++) {
			for(y = 0; y < UFOSCORE_WIDTH; y++){
				if ((ufo_seven_block[x%UFOSCORE_HEIGHT] & (1<<(UFOSCORE_WIDTH-1-y)))) {
					framePointer[(y_position+x)*640 + x_position+y] = 0x00FF00FF;
				} else {
					framePointer[(y_position+x)*640 + x_position+y] = 0x00000000;
				}
			}
		}
		break;
	case 8:
		for(x = 0; x < UFOSCORE_HEIGHT; x++) {
			for(y = 0; y < UFOSCORE_WIDTH; y++){
				if ((ufo_eight_block[x%UFOSCORE_HEIGHT] & (1<<(UFOSCORE_WIDTH-1-y)))) {
					framePointer[(y_position+x)*640 + x_position+y] = 0x00FF00FF;
				} else {
					framePointer[(y_position+x)*640 + x_position+y] = 0x00000000;
				}
			}
		}
		break;
	case 9:
		for(x = 0; x < UFOSCORE_HEIGHT; x++) {
			for(y = 0; y < UFOSCORE_WIDTH; y++){
				if ((ufo_nine_block[x%UFOSCORE_HEIGHT] & (1<<(UFOSCORE_WIDTH-1-y)))) {
					framePointer[(y_position+x)*640 + x_position+y] = 0x00FF00FF;
				} else {
					framePointer[(y_position+x)*640 + x_position+y] = 0x00000000;
				}
			}
		}
		break;
	default:
		break;

	}

}
