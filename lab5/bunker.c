#include "bunker.h"
#include "stdlib.h"
#include "xintc_l.h"        // Provides handy macros for the interrupt controller.

int x_y[4] = {BUNKER1_X, BUNKER2_X, BUNKER3_X, BUNKER4_X};
int initial_x = 70;
int initial_y = 300;
int tank_y_position = 420;

void renderBunker(unsigned int* framePointer) {		// draw for the first time
	short x=0, y=0;

	int i,j;
	for(j = 0; j < 4; j++) {
		initial_x = x_y[j];
		for(i=0; i<10; i++){
			switch(i){
			case 0:
				for(x = 0; x < BLOCK_HEIGHT; x++) {
					for(y = 0; y < BLOCK_WIDTH; y++){
						if ((block_left0[x%16] & (1<<(BLOCK_WIDTH-1-y)))) {
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
						if ((block_normal0[x%16] & (1<<(BLOCK_WIDTH-1-y)))) {
							framePointer[(initial_y+x)*640 + initial_x+y+BLOCK_WIDTH] = 0x0000FF00;
						} else {
							framePointer[(initial_y+x)*640 + initial_x+y+BLOCK_WIDTH] = 0x00000000;
						}
					}
				}
				break;
			case 2:
				for(x = 0; x < BLOCK_HEIGHT; x++) {
					for(y = 0; y < BLOCK_WIDTH; y++){
						if ((block_normal0[x%16] & (1<<(BLOCK_WIDTH-1-y)))) {
							framePointer[(initial_y+x)*640 + initial_x+y+BLOCK_WIDTH*2] = 0x0000FF00;
						} else {
							framePointer[(initial_y+x)*640 + initial_x+y+BLOCK_WIDTH*2] = 0x00000000;
						}
					}
				}
				break;

			case 3:
				for(x = 0; x < BLOCK_HEIGHT; x++) {
					for(y = 0; y < BLOCK_WIDTH; y++){
						if ((block_right0[x%16] & (1<<(BLOCK_WIDTH-1-y)))) {
							framePointer[(initial_y+x)*640 + initial_x+y+BLOCK_WIDTH*3] = 0x0000FF00;
						} else {
							framePointer[(initial_y+x)*640 + initial_x+y+BLOCK_WIDTH*3] = 0x00000000;
						}
					}
				}

				break;
			case 4:
				for(x = 0; x < BLOCK_HEIGHT; x++) {
					for(y = 0; y < BLOCK_WIDTH; y++){
						if ((block_normal0[x%16] & (1<<(BLOCK_WIDTH-1-y)))) {
							framePointer[(initial_y+x+BLOCK_HEIGHT)*640 + initial_x+y] = 0x0000FF00;
						} else {
							framePointer[(initial_y+x+BLOCK_HEIGHT)*640 + initial_x+y] = 0x00000000;
						}
					}
				}
				break;
			case 5:
				for(x = 0; x < BLOCK_HEIGHT; x++) {
					for(y = 0; y < BLOCK_WIDTH; y++){
						if ((block_center_left0[x%16] & (1<<(BLOCK_WIDTH-1-y)))) {
							framePointer[(initial_y+x+BLOCK_HEIGHT)*640 + initial_x+y+BLOCK_WIDTH] = 0x0000FF00;
						} else {
							framePointer[(initial_y+x+BLOCK_HEIGHT)*640 + initial_x+y+BLOCK_WIDTH] = 0x00000000;
						}
					}
				}
				break;
			case 6:
				for(x = 0; x < BLOCK_HEIGHT; x++) {
					for(y = 0; y < BLOCK_WIDTH; y++){
						if ((block_center_right0[x%16] & (1<<(BLOCK_WIDTH-1-y)))) {
							framePointer[(initial_y+x+BLOCK_HEIGHT)*640 + initial_x+y+BLOCK_WIDTH*2] = 0x0000FF00;
						} else {
							framePointer[(initial_y+x+BLOCK_HEIGHT)*640 + initial_x+y+BLOCK_WIDTH*2] = 0x00000000;
						}
					}
				}
				break;
			case 7:
				for(x = 0; x < BLOCK_HEIGHT; x++) {
					for(y = 0; y < BLOCK_WIDTH; y++){
						if ((block_normal0[x%16] & (1<<(BLOCK_WIDTH-1-y)))) {
							framePointer[(initial_y+x+BLOCK_HEIGHT)*640 + initial_x+y+BLOCK_WIDTH*3] = 0x0000FF00;
						} else {
							framePointer[(initial_y+x+BLOCK_HEIGHT)*640 + initial_x+y+BLOCK_WIDTH*3] = 0x00000000;
						}
					}
				}
				break;

			case 8:
				for(x = 0; x < BLOCK_HEIGHT; x++) {
					for(y = 0; y < BLOCK_WIDTH; y++){
						if ((block_normal0[x%16] & (1<<(BLOCK_WIDTH-1-y)))) {
							framePointer[(initial_y+x+BLOCK_HEIGHT*2)*640 + initial_x+y] = 0x0000FF00;
						} else {
							framePointer[(initial_y+x+BLOCK_HEIGHT*2)*640 + initial_x+y] = 0x00000000;
						}
					}
				}
				break;
			case 9:
				for(x = 0; x < BLOCK_HEIGHT; x++) {
					for(y = 0; y < BLOCK_WIDTH; y++){
						if ((block_normal0[x%16] & (1<<(BLOCK_WIDTH-1-y)))) {
							framePointer[(initial_y+x+BLOCK_HEIGHT*2)*640 + initial_x+y+BLOCK_WIDTH*3] = 0x0000FF00;
						} else {
							framePointer[(initial_y+x+BLOCK_HEIGHT*2)*640 + initial_x+y+BLOCK_WIDTH*3] = 0x00000000;
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

void erodeBunker(unsigned int* framePointer, int which_bunker, int which_block){
	//	int which_block = rand()%10;
	short* bunker;
	int i, j;
	int block_row, block_col;
	switch(which_bunker){ 		// select a bunker that I want to erode
	case 0:
		bunker = getBunker1();
		break;
	case 1:
		bunker = getBunker2();
		break;
	case 2:
		bunker = getBunker3();
		break;
	case 3:
		bunker = getBunker4();
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
	case 2:
		block_row = 0;
		block_col = 2;
		blankBlock(framePointer, which_bunker, which_block, block_row, block_col);
		updateBlock(framePointer, which_bunker, which_block, block_row, block_col, bunker);

		break;
	case 3:
		block_row = 0;
		block_col = 3;
		blankBlock(framePointer, which_bunker, which_block, block_row, block_col);
		updateBlock(framePointer, which_bunker, which_block, block_row, block_col, bunker);

		break;
	case 4:
		block_row = 1;
		block_col = 0;
		blankBlock(framePointer, which_bunker, which_block, block_row, block_col);
		updateBlock(framePointer, which_bunker, which_block, block_row, block_col, bunker);

		break;
	case 5:
		block_row = 1;
		block_col = 1;
		blankBlock(framePointer, which_bunker, which_block, block_row, block_col);
		updateBlock(framePointer, which_bunker, which_block, block_row, block_col, bunker);

		break;
	case 6:
		block_row = 1;
		block_col = 2;
		blankBlock(framePointer, which_bunker, which_block, block_row, block_col);
		updateBlock(framePointer, which_bunker, which_block, block_row, block_col, bunker);

		break;
	case 7:
		block_row = 1;
		block_col = 3;
		blankBlock(framePointer, which_bunker, which_block, block_row, block_col);
		updateBlock(framePointer, which_bunker, which_block, block_row, block_col, bunker);

		break;
	case 8:
		block_row = 2;
		block_col = 0;
		blankBlock(framePointer, which_bunker, which_block, block_row, block_col);
		updateBlock(framePointer, which_bunker, which_block, block_row, block_col, bunker);

		break;
	case 9:
		block_row = 2;
		block_col = 3;
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

	if(bunker[which_block]==0){ 		// depending on the block selected and bunker status, 'which_state' points to a pre-defined eroded block
		bunker[which_block] = 1;
		if(which_block == 0){
			which_state = block_left1;
		}
		else if(which_block == 1 || which_block == 2 || which_block == 4 || which_block == 7 || which_block == 8 || which_block == 9){
			which_state = block_normal1;
		}
		else if(which_block == 3){
			which_state = block_right1;
		}
		else if(which_block == 5){
			which_state = block_center_left1;
		}
		else if(which_block == 6){
			which_state = block_center_right1;
		}
	}
	else if(bunker[which_block]==1){
		bunker[which_block] = 2;
		if(which_block == 0){
			which_state = block_left2;
		}
		else if(which_block == 1 || which_block == 2 || which_block == 4 || which_block == 7 || which_block == 8 || which_block == 9){
			which_state = block_normal2;
		}
		else if(which_block == 3){
			which_state = block_right2;
		}
		else if(which_block == 5){
			which_state = block_center_left2;
		}
		else if(which_block == 6){
			which_state = block_center_right2;
		}
	}
	else if(bunker[which_block]==2){
		bunker[which_block] = 3;
		if(which_block == 0){
			which_state = block_left3;
		}
		else if(which_block == 1 || which_block == 2 || which_block == 4 || which_block == 7 || which_block == 8 || which_block == 9){
			which_state = block_normal3;
		}
		else if(which_block == 3){
			which_state = block_right3;
		}
		else if(which_block == 5){
			which_state = block_center_left3;
		}
		else if(which_block == 6){
			which_state = block_center_right3;
		}
	}
	else{
		bunker[which_block] = 4;
		which_state = empty;
	}

	for(i = 0; i < BLOCK_HEIGHT; i++){
		for(j = 0; j < BLOCK_WIDTH; j++){
			if ((which_state[i%16] & (1<<(BLOCK_WIDTH-1-j)))) {
				framePointer[(initial_y+i+BLOCK_HEIGHT*block_row)*640 + initial_x+j+BLOCK_WIDTH*block_col] = 0x0000FF00;
			} else {
				framePointer[(initial_y+i+BLOCK_HEIGHT*block_row)*640 + initial_x+j+BLOCK_WIDTH*block_col] = 0x00000000;
			}
		}
	}
}
void selectBlock(unsigned int* framePointer, int bullet){
	int bullet_x;
	int bullet_y;
	short hit = 0;
	short* bunker;
	int counter=0;
	short dying = 0;
	int gameover = 0;

	switch(bullet){
	case 1:
		bullet_x = getAlien1BulletPositionX()+3;
		bullet_y = getAlien1BulletPositionY()+10;
		break;
	case 2:
		bullet_x = getAlien2BulletPositionX()+3;
		bullet_y = getAlien2BulletPositionY()+10;
		break;
	case 3:
		bullet_x = getAlien3BulletPositionX()+3;
		bullet_y = getAlien3BulletPositionY()+10;
		break;
	case 4:
		bullet_x = getAlien4BulletPositionX()+3;
		bullet_y = getAlien4BulletPositionY()+10;
		break;
	case 5:
		bullet_x = getTankBulletPositionX()+3;
		bullet_y = getTankBulletPositionY();
	default:
		break;
	}

	if(bullet_x >= BUNKER1_X-3 && bullet_x < BUNKER1_X+64+3){
		bunker = getBunker1();
		if(bullet_y > initial_y && bullet_y < initial_y+16){
			if(bullet_x >= BUNKER1_X-3 && bullet_x < BUNKER1_X+16 && bunker[0] != 4){
				erodeBunker(framePointer, 0, 0);
				hit = 1;
			}
			if(bullet_x >= BUNKER1_X+16 && bullet_x < BUNKER1_X+32 && bunker[1] != 4){
				erodeBunker(framePointer, 0, 1);
				hit = 1;
			}
			if(bullet_x >= BUNKER1_X+32 && bullet_x < BUNKER1_X+48 && bunker[2] != 4){
				erodeBunker(framePointer, 0, 2);
				hit = 1;
			}
			if(bullet_x >= BUNKER1_X+48 && bullet_x < BUNKER1_X+64+3 && bunker[3] != 4){
				erodeBunker(framePointer, 0, 3);
				hit = 1;
			}
		}
		if(bullet_y>initial_y+16 && bullet_y<initial_y+32){
			if(bullet_x >= BUNKER1_X-3 && bullet_x < BUNKER1_X+16 && bunker[4] != 4){
				erodeBunker(framePointer, 0, 4);
				hit = 1;
			}
			if(bullet_x >= BUNKER1_X+16 && bullet_x < BUNKER1_X+32 && bunker[5] != 4){
				erodeBunker(framePointer, 0, 5);
				hit = 1;
			}
			if(bullet_x >= BUNKER1_X+32 && bullet_x < BUNKER1_X+48 && bunker[6] != 4){
				erodeBunker(framePointer, 0, 6);
				hit = 1;
			}
			if(bullet_x >= BUNKER1_X+48 && bullet_x < BUNKER1_X+64+3 && bunker[7] != 4){
				erodeBunker(framePointer, 0, 7);
				hit = 1;
			}
		}
		if(bullet_y>initial_y+32 && bullet_y<initial_y+48){
			if(bullet_x >= BUNKER1_X-3 && bullet_x<BUNKER1_X+16 && bunker[8] != 4){
				erodeBunker(framePointer, 0, 8);
				hit = 1;
			}
			if(bullet_x >= BUNKER1_X+48 && bullet_x<BUNKER1_X+64+3 && bunker[9] != 4){
				erodeBunker(framePointer, 0, 9);
				hit = 1;
			}
		}

	}

	if(bullet_x > BUNKER2_X-3 && bullet_x < BUNKER2_X+64+3){
		bunker = getBunker2();
		if(bullet_y>initial_y && bullet_y<initial_y+16){
			if(bullet_x >= BUNKER2_X-3 && bullet_x<BUNKER2_X+16 && bunker[0] != 4){
				erodeBunker(framePointer, 1, 0);
				hit = 1;
			}
			if(bullet_x >= BUNKER2_X+16 && bullet_x<BUNKER2_X+32 && bunker[1] != 4){
				erodeBunker(framePointer, 1, 1);
				hit = 1;
			}
			if(bullet_x >= BUNKER2_X+32 && bullet_x<BUNKER2_X+48 && bunker[2] != 4){
				erodeBunker(framePointer, 1, 2);
				hit = 1;
			}
			if(bullet_x >= BUNKER2_X+48 && bullet_x<BUNKER2_X+64+3 && bunker[3] != 4){
				erodeBunker(framePointer, 1, 3);
				hit = 1;
			}
		}
		if(bullet_y>initial_y+16 && bullet_y<initial_y+32){
			if(bullet_x >= BUNKER2_X-3 && bullet_x<BUNKER2_X+16 && bunker[4] != 4){
				erodeBunker(framePointer, 1, 4);
				hit = 1;
			}
			if(bullet_x >= BUNKER2_X+16 && bullet_x<BUNKER2_X+32 && bunker[5] != 4){
				erodeBunker(framePointer, 1, 5);
				hit = 1;
			}
			if(bullet_x >= BUNKER2_X+32 && bullet_x<BUNKER2_X+48 && bunker[6] != 4){
				erodeBunker(framePointer, 1, 6);
				hit = 1;
			}
			if(bullet_x >= BUNKER2_X+48 && bullet_x<BUNKER2_X+64+3 && bunker[7] != 4){
				erodeBunker(framePointer, 1, 7);
				hit = 1;
			}
		}
		if(bullet_y>initial_y+32 && bullet_y<initial_y+48){
			if(bullet_x >= BUNKER2_X-3 && bullet_x<BUNKER2_X+16 && bunker[8] != 4){
				erodeBunker(framePointer, 1, 8);
				hit = 1;
			}
			if(bullet_x >= BUNKER2_X+48 && bullet_x<BUNKER2_X+64+3 && bunker[9] != 4){
				erodeBunker(framePointer, 1, 9);
				hit = 1;
			}
		}

	}

	if(bullet_x > BUNKER3_X-3 && bullet_x < BUNKER3_X+64+3){
		bunker = getBunker3();
		if(bullet_y>initial_y && bullet_y<initial_y+16){
			if(bullet_x >= BUNKER3_X-3 && bullet_x<BUNKER3_X+16 && bunker[0] != 4){
				erodeBunker(framePointer, 2, 0);
				hit = 1;
			}
			if(bullet_x >= BUNKER3_X+16 && bullet_x<BUNKER3_X+32 && bunker[1] != 4){
				erodeBunker(framePointer, 2, 1);
				hit = 1;
			}
			if(bullet_x >= BUNKER3_X+32 && bullet_x<BUNKER3_X+48 && bunker[2] != 4){
				erodeBunker(framePointer, 2, 2);
				hit = 1;
			}
			if(bullet_x >= BUNKER3_X+48 && bullet_x<BUNKER3_X+64+3 && bunker[3] != 4){
				erodeBunker(framePointer, 2, 3);
				hit = 1;
			}
		}
		if(bullet_y>initial_y+16 && bullet_y<initial_y+32){
			if(bullet_x >= BUNKER3_X-3 && bullet_x<BUNKER3_X+16 && bunker[4] != 4){
				erodeBunker(framePointer, 2, 4);
				hit = 1;
			}
			if(bullet_x >= BUNKER3_X+16 && bullet_x<BUNKER3_X+32 && bunker[5] != 4){
				erodeBunker(framePointer, 2, 5);
				hit = 1;
			}
			if(bullet_x >= BUNKER3_X+32 && bullet_x<BUNKER3_X+48 && bunker[6] != 4){
				erodeBunker(framePointer, 2, 6);
				hit = 1;
			}
			if(bullet_x >= BUNKER3_X+48 && bullet_x<BUNKER3_X+64+3 && bunker[7] != 4){
				erodeBunker(framePointer, 2, 7);
				hit = 1;
			}
		}
		if(bullet_y>initial_y+32 && bullet_y<initial_y+48){
			if(bullet_x >= BUNKER3_X-3 && bullet_x<BUNKER3_X+16 && bunker[8] != 4){
				erodeBunker(framePointer, 2, 8);
				hit = 1;
			}
			if(bullet_x >= BUNKER3_X+48 && bullet_x<BUNKER3_X+64+3 && bunker[9] != 4){
				erodeBunker(framePointer, 2, 9);
				hit = 1;
			}
		}
	}

	if(bullet_x > BUNKER4_X-3 && bullet_x < BUNKER4_X+64+3){
		bunker = getBunker4();
		if(bullet_y>initial_y && bullet_y<initial_y+16){
			if(bullet_x >= BUNKER4_X-3 && bullet_x<BUNKER4_X+16 && bunker[0] != 4){
				erodeBunker(framePointer, 3, 0);
				hit = 1;
			}
			if(bullet_x >= BUNKER4_X+16 && bullet_x<BUNKER4_X+32 && bunker[1] != 4){
				erodeBunker(framePointer, 3, 1);
				hit = 1;
			}
			if(bullet_x >= BUNKER4_X+32 && bullet_x<BUNKER4_X+48 && bunker[2] != 4){
				erodeBunker(framePointer, 3, 2);
				hit = 1;
			}
			if(bullet_x >= BUNKER4_X+48 && bullet_x<BUNKER4_X+64+3 && bunker[3] != 4){
				erodeBunker(framePointer, 3, 3);
				hit = 1;
			}
		}
		if(bullet_y>initial_y+16 && bullet_y<initial_y+32){
			if(bullet_x >= BUNKER4_X-3 && bullet_x<BUNKER4_X+16 && bunker[4] != 4){
				erodeBunker(framePointer, 3, 4);
				hit = 1;
			}
			if(bullet_x >= BUNKER4_X+16 && bullet_x<BUNKER4_X+32 && bunker[5] != 4){
				erodeBunker(framePointer, 3, 5);
				hit = 1;
			}
			if(bullet_x >= BUNKER4_X+32 && bullet_x<BUNKER4_X+48 && bunker[6] != 4){
				erodeBunker(framePointer, 3, 6);
				hit = 1;
			}
			if(bullet_x >= BUNKER4_X+48 && bullet_x<BUNKER4_X+64+3 && bunker[7] != 4){
				erodeBunker(framePointer, 3, 7);
				hit = 1;
			}
		}
		if(bullet_y>initial_y+32 && bullet_y<initial_y+48){
			if(bullet_x >= BUNKER4_X-3 && bullet_x<BUNKER4_X+16 && bunker[8] != 4){
				erodeBunker(framePointer, 3, 8);
				hit = 1;
			}
			if(bullet_x >= BUNKER4_X+48 && bullet_x<BUNKER4_X+64+3 && bunker[9] != 4){
				erodeBunker(framePointer, 3, 9);
				hit = 1;
			}
		}
	}

	if(bullet_y > tank_y_position && bullet_y < tank_y_position+16){
		if(bullet_x >= getTankPositionX()-3 && bullet_x < getTankPositionX()+32+3){
		    setHaveTankDeathSound(1);

			counter = 0;
		//	xil_printf("tank dies\r\n");

			// disable interrupt to stop the whole game for little bit
//			XIntc_MasterDisable(XPAR_INTC_0_BASEADDR);

			setAlien1BulletState(0);
			blankAlienBullet(framePointer, getAlien1BulletPositionX(), getAlien1BulletPositionY());
			setAlien2BulletState(0);
			blankAlienBullet(framePointer, getAlien2BulletPositionX(), getAlien2BulletPositionY());
			setAlien3BulletState(0);
			blankAlienBullet(framePointer, getAlien3BulletPositionX(), getAlien3BulletPositionY());
			setAlien4BulletState(0);
			blankAlienBullet(framePointer, getAlien4BulletPositionX(), getAlien4BulletPositionY());
			setTankBulletState(0);
			blankTankBullet(framePointer, getTankBulletPositionX(), getTankBulletPositionY());

			gameover = tankDied(framePointer);

			if(!gameover){

				// for tank dying animation
				while(counter < 1000){
					//				if(counter%250){

					if(dying == 0){
						dying = 1;
						blankTank(framePointer);
						renderDying1(framePointer);
					}
					else{
						dying = 0;
						blankTank(framePointer);
						renderDying2(framePointer);
					}
					//				}
					counter++;
				}

				// reenable interrupt
//				XIntc_MasterEnable(XPAR_INTC_0_BASEADDR);
				renderTank(framePointer);
			}
		}
	}

	if(hit){

		switch(bullet){
		case 1:
			setAlien1BulletState(0);
			blankAlienBullet(framePointer, bullet_x-3, bullet_y-10);
			break;
		case 2:
			setAlien2BulletState(0);
			blankAlienBullet(framePointer, bullet_x-3, bullet_y-10);
			break;
		case 3:
			setAlien3BulletState(0);
			blankAlienBullet(framePointer, bullet_x-3, bullet_y-10);
			break;
		case 4:
			setAlien4BulletState(0);
			blankAlienBullet(framePointer, bullet_x-3, bullet_y-10);
			break;
		case 5:
			setTankBulletState(0);
			blankTankBullet(framePointer, bullet_x, bullet_y);
			break;

		default:
			break;
		}
	}

}
