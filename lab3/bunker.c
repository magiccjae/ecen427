#include "bunker.h"
#include "stdlib.h"

int x_y[4] = {490, 350, 210, 70};
int initial_x = 70;
int initial_y = 300;


void renderBunker(unsigned int* framePointer) {		// draw for the first time
	short x=0, y=0;

	int i,j;
	for(j = 0; j < 4; j++) {
		initial_x = x_y[j];
		for(i=0; i<9; i++){
			switch(i){
			case 0:
				for(x = 0; x < BLOCK_HEIGHT; x++) {
					for(y = 0; y < BLOCK_WIDTH; y++){
						if ((block_left0[x%16] & (1<<(24-1-y)))) {
							framePointer[(initial_y+x)*640 + initial_x+y] = 0x0000FF00;
						} else {
							framePointer[(initial_y+x)*640 + initial_x+y] = 0x00000000;
						}
					}
				}
				break;
			case 1:
				for(x = 0; x < BLOCK_HEIGHT; x++) {
					for(y = 0; y < BLOCK_WIDTH; y++){
						if ((block_normal0[x%16] & (1<<(24-1-y)))) {
							framePointer[(initial_y+x)*640 + initial_x+y+BLOCK_WIDTH] = 0x0000FF00;
						} else {
							framePointer[(initial_y+x)*640 + initial_x+y+BLOCK_WIDTH] = 0x00000000;
						}
					}
				}
				break;
			case 2  :
				for(x = 0; x < BLOCK_HEIGHT; x++) {
					for(y = 0; y < BLOCK_WIDTH; y++){
						if ((block_right0[x%16] & (1<<(24-1-y)))) {
							framePointer[(initial_y+x)*640 + initial_x+y+BLOCK_WIDTH*2] = 0x0000FF00;
						} else {
							framePointer[(initial_y+x)*640 + initial_x+y+BLOCK_WIDTH*2] = 0x00000000;
						}
					}
				}

				break;
			case 3  :
				for(x = 0; x < BLOCK_HEIGHT; x++) {
					for(y = 0; y < BLOCK_WIDTH; y++){
						if ((block_normal0[x%16] & (1<<(24-1-y)))) {
							framePointer[(initial_y+x+BLOCK_HEIGHT)*640 + initial_x+y] = 0x0000FF00;
						} else {
							framePointer[(initial_y+x+BLOCK_HEIGHT)*640 + initial_x+y] = 0x00000000;
						}
					}
				}
				break;
			case 4  :
				for(x = 0; x < BLOCK_HEIGHT; x++) {
					for(y = 0; y < BLOCK_WIDTH; y++){
						if ((block_center0[x%16] & (1<<(24-1-y)))) {
							framePointer[(initial_y+x+BLOCK_HEIGHT)*640 + initial_x+y+BLOCK_WIDTH] = 0x0000FF00;
						} else {
							framePointer[(initial_y+x+BLOCK_HEIGHT)*640 + initial_x+y+BLOCK_WIDTH] = 0x00000000;
						}
					}
				}
				break;
			case 5  :
				for(x = 0; x < BLOCK_HEIGHT; x++) {
					for(y = 0; y < BLOCK_WIDTH; y++){
						if ((block_normal0[x%16] & (1<<(24-1-y)))) {
							framePointer[(initial_y+x+BLOCK_HEIGHT)*640 + initial_x+y+BLOCK_WIDTH*2] = 0x0000FF00;
						} else {
							framePointer[(initial_y+x+BLOCK_HEIGHT)*640 + initial_x+y+BLOCK_WIDTH*2] = 0x00000000;
						}
					}
				}
				break;
			case 6  :
				for(x = 0; x < BLOCK_HEIGHT; x++) {
					for(y = 0; y < BLOCK_WIDTH; y++){
						if ((block_normal0[x%16] & (1<<(24-1-y)))) {
							framePointer[(initial_y+x+BLOCK_HEIGHT*2)*640 + initial_x+y] = 0x0000FF00;
						} else {
							framePointer[(initial_y+x+BLOCK_HEIGHT*2)*640 + initial_x+y] = 0x00000000;
						}
					}
				}
				break;
			case 7  :
				for(x = 0; x < BLOCK_HEIGHT; x++) {
					for(y = 0; y < BLOCK_WIDTH; y++){
						if ((block_normal0[x%16] & (1<<(24-1-y)))) {
							framePointer[(initial_y+x+BLOCK_HEIGHT*2)*640 + initial_x+y+BLOCK_WIDTH*2] = 0x0000FF00;
						} else {
							framePointer[(initial_y+x+BLOCK_HEIGHT*2)*640 + initial_x+y+BLOCK_WIDTH*2] = 0x00000000;
						}
					}
				}
				break;
			default :

				break;
			}
		}
	}
}

void erodeBunker(unsigned int* framePointer, int which_bunker){
	int which_block = rand()%8;
	short* bunker;
	int i, j;
	int block_row, block_col;
	switch(which_bunker){ 		// select a bunker that I want to erode
	case 0:
		bunker = getBunker4();
		break;
	case 1:
		bunker = getBunker3();
		break;
	case 2:
		bunker = getBunker2();
		break;
	case 3:
		bunker = getBunker1();
		break;
	default :
		break;
	}

	switch(which_block){ 		// 'block_row, block_col' are used to calculate to find out the position of framePointer
	case 0:
		block_row = 0;
		block_col = 0;
		blankBlock(framePointer, which_bunker, which_block, block_row, block_col);
		updateBlock(framePointer, which_bunker, which_block, block_row, block_col, bunker);
		break;
	case 1:
		block_row = 0;
		block_col = 1;
		blankBlock(framePointer, which_bunker, which_block, block_row, block_col);
		updateBlock(framePointer, which_bunker, which_block, block_row, block_col, bunker);

		break;
	case 2  :
		block_row = 0;
		block_col = 2;
		blankBlock(framePointer, which_bunker, which_block, block_row, block_col);
		updateBlock(framePointer, which_bunker, which_block, block_row, block_col, bunker);

		break;
	case 3  :
		block_row = 1;
		block_col = 0;
		blankBlock(framePointer, which_bunker, which_block, block_row, block_col);
		updateBlock(framePointer, which_bunker, which_block, block_row, block_col, bunker);

		break;
	case 4  :
		block_row = 1;
		block_col = 1;
		blankBlock(framePointer, which_bunker, which_block, block_row, block_col);
		updateBlock(framePointer, which_bunker, which_block, block_row, block_col, bunker);

		break;
	case 5  :
		block_row = 1;
		block_col = 2;
		blankBlock(framePointer, which_bunker, which_block, block_row, block_col);
		updateBlock(framePointer, which_bunker, which_block, block_row, block_col, bunker);

		break;
	case 6  :
		block_row = 2;
		block_col = 0;
		blankBlock(framePointer, which_bunker, which_block, block_row, block_col);
		updateBlock(framePointer, which_bunker, which_block, block_row, block_col, bunker);

		break;
	case 7  :
		block_row = 2;
		block_col = 2;
		blankBlock(framePointer, which_bunker, which_block, block_row, block_col);
		updateBlock(framePointer, which_bunker, which_block, block_row, block_col, bunker);

		break;
	default :

		break;
	}

}
// This function runs first to make a block empty, and then draw an eroded block by 'updateBlock()' function
void blankBlock(unsigned int* framePointer, int which_bunker, int which_block, int block_row, int block_col){
	int i, j;
	initial_x = x_y[which_bunker];
	for(i = 0; i < BLOCK_HEIGHT; i++){
		for(j = 0; j < BLOCK_WIDTH; j++){
			framePointer[(initial_y+i+BLOCK_HEIGHT*block_row)*640 + initial_x+j+BLOCK_WIDTH*block_col] = 0x00000000;
		}
	}
}

void updateBlock(unsigned int* framePointer, int which_bunker, int which_block, int block_row, int block_col, short* bunker){
	int i, j;
	initial_x = x_y[which_bunker];

	int* which_state;

	if(bunker[which_block]==0){ 		// depending on the block selected and bunker status, 'which_state' points to a predefined eroded block
		bunker[which_block] = 1;
		if(which_block == 0){
			which_state = block_left1;
		}
		else if(which_block == 1 || which_block == 3 || which_block == 5 || which_block == 6 || which_block == 7){
			which_state = block_normal1;
		}
		else if(which_block == 2){
			which_state = block_right1;
		}
		else if(which_block == 4){
			which_state = block_center1;
		}
	}
	else if(bunker[which_block]==1){
		bunker[which_block] = 2;
		if(which_block == 0){
			which_state = block_left2;
		}
		else if(which_block == 1 || which_block == 3 || which_block == 5 || which_block == 6 || which_block == 7){
			which_state = block_normal2;
		}
		else if(which_block == 2){
			which_state = block_right2;
		}
		else if(which_block == 4){
			which_state = block_center2;
		}
	}
	else if(bunker[which_block]==2){
		bunker[which_block] = 3;
		if(which_block == 0){
			which_state = block_left3;
		}
		else if(which_block == 1 || which_block == 3 || which_block == 5 || which_block == 6 || which_block == 7){
			which_state = block_normal3;
		}
		else if(which_block == 2){
			which_state = block_right3;
		}
		else if(which_block == 4){
			which_state = block_center3;
		}
	}
	else{
		which_state = empty;
	}

	for(i = 0; i < BLOCK_HEIGHT; i++){
		for(j = 0; j < BLOCK_WIDTH; j++){
			if ((which_state[i%16] & (1<<(24-1-j)))) {
				framePointer[(initial_y+i+BLOCK_HEIGHT*block_row)*640 + initial_x+j+BLOCK_WIDTH*block_col] = 0x0000FF00;
			} else {
				framePointer[(initial_y+i+BLOCK_HEIGHT*block_row)*640 + initial_x+j+BLOCK_WIDTH*block_col] = 0x00000000;
			}
		}
	}

}
