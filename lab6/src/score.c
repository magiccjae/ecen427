#include "score.h"
#include "xintc_l.h"        // Provides handy macros for the interrupt controller.

#define SCORE_START1 20
#define SCORE_START2 360
int score_position[10] = {SCORE_START1, SCORE_START1+12, SCORE_START1+24, SCORE_START1+36, SCORE_START1+48,    \
							SCORE_START2, SCORE_START2+12, SCORE_START2+24, SCORE_START2+36, SCORE_START2+48};

int score_x = 20;
int score_y = 10;


int number_position[4] = {100, 116, 132, 148};
int number_x = 100;
int number_y = 10;

int tank_position[3] = {440, 480, 520};
int tank_x = 440;
int tank_y = 10;

int lives = 3;


#define GAMEOVER_X 250

int gameover_position[8] = {GAMEOVER_X, GAMEOVER_X+12, GAMEOVER_X+24, GAMEOVER_X+36, GAMEOVER_X+64, GAMEOVER_X+76, GAMEOVER_X+88, GAMEOVER_X+100};
int game_x = 250;
int game_y = 200;


int total_score = 0;


#define TANK_HEIGHT 16
#define TANK_WIDTH 32
extern int tank[TANK_HEIGHT];

void renderScore(unsigned int* framePointer) {		// draw for the first time
	short x=0, y=0;
	int i;

	for(i=0; i<10; i++){
		score_x = score_position[i];
		switch(i){
		case 0:
			for(x = 0; x < SCORE_HEIGHT; x++) {
				for(y = 0; y < SCORE_WIDTH; y++){
					if ((s_block[x%SCORE_HEIGHT] & (1<<(SCORE_WIDTH-1-y)))) {
						framePointer[(score_y+x)*640 + score_x+y] = 0x00FFFFFF;
					} else {
						framePointer[(score_y+x)*640 + score_x+y] = 0x00000000;
					}
				}
			}
			break;
		case 1:
			for(x = 0; x < SCORE_HEIGHT; x++) {
				for(y = 0; y < SCORE_WIDTH; y++){
					if ((c_block[x%SCORE_HEIGHT] & (1<<(SCORE_WIDTH-1-y)))) {
						framePointer[(score_y+x)*640 + score_x+y] = 0x00FFFFFF;
					} else {
						framePointer[(score_y+x)*640 + score_x+y] = 0x00000000;
					}
				}
			}
			break;
		case 2:
			for(x = 0; x < SCORE_HEIGHT; x++) {
				for(y = 0; y < SCORE_WIDTH; y++){
					if ((o_block[x%SCORE_HEIGHT] & (1<<(SCORE_WIDTH-1-y)))) {
						framePointer[(score_y+x)*640 + score_x+y] = 0x00FFFFFF;
					} else {
						framePointer[(score_y+x)*640 + score_x+y] = 0x00000000;
					}
				}
			}
			break;

		case 3:
			for(x = 0; x < SCORE_HEIGHT; x++) {
				for(y = 0; y < SCORE_WIDTH; y++){
					if ((r_block[x%SCORE_HEIGHT] & (1<<(SCORE_WIDTH-1-y)))) {
						framePointer[(score_y+x)*640 + score_x+y] = 0x00FFFFFF;
					} else {
						framePointer[(score_y+x)*640 + score_x+y] = 0x00000000;
					}
				}
			}

			break;
		case 4:
			for(x = 0; x < SCORE_HEIGHT; x++) {
				for(y = 0; y < SCORE_WIDTH; y++){
					if ((e_block[x%SCORE_HEIGHT] & (1<<(SCORE_WIDTH-1-y)))) {
						framePointer[(score_y+x)*640 + score_x+y] = 0x00FFFFFF;
					} else {
						framePointer[(score_y+x)*640 + score_x+y] = 0x00000000;
					}
				}
			}
			break;
		case 5:
			for(x = 0; x < SCORE_HEIGHT; x++) {
				for(y = 0; y < SCORE_WIDTH; y++){
					if ((l_block[x%SCORE_HEIGHT] & (1<<(SCORE_WIDTH-1-y)))) {
						framePointer[(score_y+x)*640 + score_x+y] = 0x00FFFFFF;
					} else {
						framePointer[(score_y+x)*640 + score_x+y] = 0x00000000;
					}
				}
			}
			break;
		case 6:
			for(x = 0; x < SCORE_HEIGHT; x++) {
				for(y = 0; y < SCORE_WIDTH; y++){
					if ((i_block[x%SCORE_HEIGHT] & (1<<(SCORE_WIDTH-1-y)))) {
						framePointer[(score_y+x)*640 + score_x+y] = 0x00FFFFFF;
					} else {
						framePointer[(score_y+x)*640 + score_x+y] = 0x00000000;
					}
				}
			}
			break;
		case 7:
			for(x = 0; x < SCORE_HEIGHT; x++) {
				for(y = 0; y < SCORE_WIDTH; y++){
					if ((v_block[x%SCORE_HEIGHT] & (1<<(SCORE_WIDTH-1-y)))) {
						framePointer[(score_y+x)*640 + score_x+y] = 0x00FFFFFF;
					} else {
						framePointer[(score_y+x)*640 + score_x+y] = 0x00000000;
					}
				}
			}
			break;
		case 8:
			for(x = 0; x < SCORE_HEIGHT; x++) {
				for(y = 0; y < SCORE_WIDTH; y++){
					if ((e_block[x%SCORE_HEIGHT] & (1<<(SCORE_WIDTH-1-y)))) {
						framePointer[(score_y+x)*640 + score_x+y] = 0x00FFFFFF;
					} else {
						framePointer[(score_y+x)*640 + score_x+y] = 0x00000000;
					}
				}
			}
			break;
		case 9:
			for(x = 0; x < SCORE_HEIGHT; x++) {
				for(y = 0; y < SCORE_WIDTH; y++){
					if ((s_block[x%SCORE_HEIGHT] & (1<<(SCORE_WIDTH-1-y)))) {
						framePointer[(score_y+x)*640 + score_x+y] = 0x00FFFFFF;
					} else {
						framePointer[(score_y+x)*640 + score_x+y] = 0x00000000;
					}
				}
			}
			break;

		default :

			break;
		}
	}

}


void updateMyscore(int adding_score){
	total_score += adding_score;
}

void drawNumber(unsigned int* framePointer, int digit, int number){
	short x=0, y=0;

	for(x = 0; x < SCORE_HEIGHT; x++) {
		for(y = 0; y < SCORE_WIDTH; y++){
			framePointer[(number_y+x)*640 + number_position[digit]+y] = 0x00000000;
		}
	}

	switch(number){
	case 0:
		for(x = 0; x < SCORE_HEIGHT; x++) {
			for(y = 0; y < SCORE_WIDTH; y++){
				if ((o_block[x%SCORE_HEIGHT] & (1<<(SCORE_WIDTH-1-y)))) {
					framePointer[(number_y+x)*640 + number_position[digit]+y] = 0x0000FF00;
				} else {
					framePointer[(number_y+x)*640 + number_position[digit]+y] = 0x00000000;
				}
			}
		}
		break;
	case 1:
		for(x = 0; x < SCORE_HEIGHT; x++) {
			for(y = 0; y < SCORE_WIDTH; y++){
				if ((one_block[x%SCORE_HEIGHT] & (1<<(SCORE_WIDTH-1-y)))) {
					framePointer[(number_y+x)*640 + number_position[digit]+y] = 0x0000FF00;
				} else {
					framePointer[(number_y+x)*640 + number_position[digit]+y] = 0x00000000;
				}
			}
		}
		break;
	case 2:
		for(x = 0; x < SCORE_HEIGHT; x++) {
			for(y = 0; y < SCORE_WIDTH; y++){
				if ((two_block[x%SCORE_HEIGHT] & (1<<(SCORE_WIDTH-1-y)))) {
					framePointer[(number_y+x)*640 + number_position[digit]+y] = 0x0000FF00;
				} else {
					framePointer[(number_y+x)*640 + number_position[digit]+y] = 0x00000000;
				}
			}
		}
		break;
	case 3:
		for(x = 0; x < SCORE_HEIGHT; x++) {
			for(y = 0; y < SCORE_WIDTH; y++){
				if ((three_block[x%SCORE_HEIGHT] & (1<<(SCORE_WIDTH-1-y)))) {
					framePointer[(number_y+x)*640 + number_position[digit]+y] = 0x0000FF00;
				} else {
					framePointer[(number_y+x)*640 + number_position[digit]+y] = 0x00000000;
				}
			}
		}
		break;
	case 4:
		for(x = 0; x < SCORE_HEIGHT; x++) {
			for(y = 0; y < SCORE_WIDTH; y++){
				if ((four_block[x%SCORE_HEIGHT] & (1<<(SCORE_WIDTH-1-y)))) {
					framePointer[(number_y+x)*640 + number_position[digit]+y] = 0x0000FF00;
				} else {
					framePointer[(number_y+x)*640 + number_position[digit]+y] = 0x00000000;
				}
			}
		}
		break;
	case 5:
		for(x = 0; x < SCORE_HEIGHT; x++) {
			for(y = 0; y < SCORE_WIDTH; y++){
				if ((five_block[x%SCORE_HEIGHT] & (1<<(SCORE_WIDTH-1-y)))) {
					framePointer[(number_y+x)*640 + number_position[digit]+y] = 0x0000FF00;
				} else {
					framePointer[(number_y+x)*640 + number_position[digit]+y] = 0x00000000;
				}
			}
		}
		break;
	case 6:
		for(x = 0; x < SCORE_HEIGHT; x++) {
			for(y = 0; y < SCORE_WIDTH; y++){
				if ((six_block[x%SCORE_HEIGHT] & (1<<(SCORE_WIDTH-1-y)))) {
					framePointer[(number_y+x)*640 + number_position[digit]+y] = 0x0000FF00;
				} else {
					framePointer[(number_y+x)*640 + number_position[digit]+y] = 0x00000000;
				}
			}
		}
		break;
	case 7:
		for(x = 0; x < SCORE_HEIGHT; x++) {
			for(y = 0; y < SCORE_WIDTH; y++){
				if ((seven_block[x%SCORE_HEIGHT] & (1<<(SCORE_WIDTH-1-y)))) {
					framePointer[(number_y+x)*640 + number_position[digit]+y] = 0x0000FF00;
				} else {
					framePointer[(number_y+x)*640 + number_position[digit]+y] = 0x00000000;
				}
			}
		}
		break;
	case 8:
		for(x = 0; x < SCORE_HEIGHT; x++) {
			for(y = 0; y < SCORE_WIDTH; y++){
				if ((eight_block[x%SCORE_HEIGHT] & (1<<(SCORE_WIDTH-1-y)))) {
					framePointer[(number_y+x)*640 + number_position[digit]+y] = 0x0000FF00;
				} else {
					framePointer[(number_y+x)*640 + number_position[digit]+y] = 0x00000000;
				}
			}
		}
		break;
	case 9:
		for(x = 0; x < SCORE_HEIGHT; x++) {
			for(y = 0; y < SCORE_WIDTH; y++){
				if ((nine_block[x%SCORE_HEIGHT] & (1<<(SCORE_WIDTH-1-y)))) {
					framePointer[(number_y+x)*640 + number_position[digit]+y] = 0x0000FF00;
				} else {
					framePointer[(number_y+x)*640 + number_position[digit]+y] = 0x00000000;
				}
			}
		}
		break;
	default:
		break;
	}

}

void updateNumber(unsigned int* framePointer){
	int i;
	int first;
	int second;
	int third;
	int fourth;

	int temp_score = total_score;

	if(temp_score >= 1000){		// 4-digit scores
		for(i = 0; i < 4; i++){
			switch(i){
			case 0:
				fourth = 0;
				drawNumber(framePointer, 3, fourth);
				break;
			case 1:
				third = temp_score % 10;
				temp_score -= third;
				drawNumber(framePointer, 2, third);
				break;
			case 2:
				second = temp_score % 10;
				temp_score -= second;
				drawNumber(framePointer, 1, second);
				break;
			case 3:
				first = temp_score;
				drawNumber(framePointer, 0, first);
				break;

			default:
				break;
			}
			temp_score = temp_score / 10;
		}


	}
	else if(temp_score >= 100 && temp_score < 1000){		// 3-digit scores
		for(i = 0; i < 3; i++){
			switch(i){
			case 0:
				third = temp_score % 10;
				temp_score -= third;
				drawNumber(framePointer, 2, third);
				break;
			case 1:
				second = temp_score % 10;
				temp_score -= second;
				drawNumber(framePointer, 1, second);
				break;
			case 2:
				first = temp_score;
				drawNumber(framePointer, 0, first);
				break;
			default:
				break;
			}
			temp_score = temp_score / 10;
		}

	}
	else if(temp_score >= 10 && temp_score < 100){		// 2-digit scores
		for(i = 0; i < 2; i++){
			switch(i){
			case 0:
				second = temp_score % 10;
				temp_score -= second;
				drawNumber(framePointer, 1, second);
				break;
			case 1:
				first = temp_score;
				drawNumber(framePointer, 0, first);
				break;
			default:
				break;
			}
			temp_score = temp_score / 10;
		}

	}
}



void renderNumber(unsigned int* framePointer) {		// draw for the first time
	short x=0, y=0;

	for(x = 0; x < SCORE_HEIGHT; x++) {
		for(y = 0; y < SCORE_WIDTH; y++){
			if ((o_block[x%SCORE_HEIGHT] & (1<<(SCORE_WIDTH-1-y)))) {
				framePointer[(number_y+x)*640 + number_position[0]+y] = 0x0000FF00;
			} else {
				framePointer[(number_y+x)*640 + number_position[0]+y] = 0x00000000;
			}
		}
	}

}

void renderTanks(unsigned int* framePointer) {		// draw for the first time
	short x=0, y=0;
	int i;

	for(i=0; i<3; i++){
		tank_x = tank_position[i];
		switch(i){
		case 0:
			for(x = 0; x < TANK_HEIGHT; x++) {
				for(y = 0; y < TANK_WIDTH; y++){
					if ((tank[x%TANK_HEIGHT] & (1<<(TANK_WIDTH-1-y)))) {
						framePointer[(tank_y+x)*640 + tank_x+y] = 0x0000FF00;
					} else {
						framePointer[(tank_y+x)*640 + tank_x+y] = 0x00000000;
					}
				}
			}
			break;
		case 1:
			for(x = 0; x < TANK_HEIGHT; x++) {
				for(y = 0; y < TANK_WIDTH; y++){
					if ((tank[x%TANK_HEIGHT] & (1<<(TANK_WIDTH-1-y)))) {
						framePointer[(tank_y+x)*640 + tank_x+y] = 0x0000FF00;
					} else {
						framePointer[(tank_y+x)*640 + tank_x+y] = 0x00000000;
					}
				}
			}
			break;
		case 2:
			for(x = 0; x < TANK_HEIGHT; x++) {
				for(y = 0; y < TANK_WIDTH; y++){
					if ((tank[x%TANK_HEIGHT] & (1<<(TANK_WIDTH-1-y)))) {
						framePointer[(tank_y+x)*640 + tank_x+y] = 0x0000FF00;
					} else {
						framePointer[(tank_y+x)*640 + tank_x+y] = 0x00000000;
					}
				}
			}
			break;

		default :

			break;
		}
	}

}

void blankTanks(unsigned int* framePointer, int which_tank){
	short x=0, y=0;

	tank_x = tank_position[which_tank];

	for(x = 0; x < TANK_HEIGHT; x++) {
		for(y = 0; y < TANK_WIDTH; y++){
			framePointer[(tank_y+x)*640 + tank_x+y] = 0x00000000;

		}
	}

}

void gameOver(unsigned int* framePointer){
	short x=0, y=0;
	int i;
	int counter;

	XIntc_MasterDisable(XPAR_INTC_0_BASEADDR);
	setGameState(0);

	int row = 0;
	int col = 0;
	for(row=0; row<480; row++) {
		for(col=0; col<640; col++) {
			framePointer[row*640 + col] = 0x00000000;

		}
	}


	for(i=0; i<8; i++){
		counter = 0;
		game_x = gameover_position[i];
		switch(i){
		case 0:
			for(x = 0; x < SCORE_HEIGHT; x++) {
				for(y = 0; y < SCORE_WIDTH; y++){
					if ((g_block[x%SCORE_HEIGHT] & (1<<(SCORE_WIDTH-1-y)))) {
						framePointer[(game_y+x)*640 + game_x+y] = 0x00FF0000;
					} else {
						framePointer[(game_y+x)*640 + game_x+y] = 0x00000000;
					}
				}
			}
			break;
		case 1:
			for(x = 0; x < SCORE_HEIGHT; x++) {
				for(y = 0; y < SCORE_WIDTH; y++){
					if ((a_block[x%SCORE_HEIGHT] & (1<<(SCORE_WIDTH-1-y)))) {
						framePointer[(game_y+x)*640 + game_x+y] = 0x0000FF00;
					} else {
						framePointer[(game_y+x)*640 + game_x+y] = 0x00000000;
					}
				}
			}
			break;
		case 2:
			for(x = 0; x < SCORE_HEIGHT; x++) {
				for(y = 0; y < SCORE_WIDTH; y++){
					if ((m_block[x%SCORE_HEIGHT] & (1<<(SCORE_WIDTH-1-y)))) {
						framePointer[(game_y+x)*640 + game_x+y] = 0x000000FF;
					} else {
						framePointer[(game_y+x)*640 + game_x+y] = 0x00000000;
					}
				}
			}
			break;

		case 3:
			for(x = 0; x < SCORE_HEIGHT; x++) {
				for(y = 0; y < SCORE_WIDTH; y++){
					if ((e_block[x%SCORE_HEIGHT] & (1<<(SCORE_WIDTH-1-y)))) {
						framePointer[(game_y+x)*640 + game_x+y] = 0x00FFFF00;
					} else {
						framePointer[(game_y+x)*640 + game_x+y] = 0x00000000;
					}
				}
			}
			break;
		case 4:
			for(x = 0; x < SCORE_HEIGHT; x++) {
				for(y = 0; y < SCORE_WIDTH; y++){
					if ((o_block[x%SCORE_HEIGHT] & (1<<(SCORE_WIDTH-1-y)))) {
						framePointer[(game_y+x)*640 + game_x+y] = 0x0000FFFF;
					} else {
						framePointer[(game_y+x)*640 + game_x+y] = 0x00000000;
					}
				}
			}
			break;
		case 5:
			for(x = 0; x < SCORE_HEIGHT; x++) {
				for(y = 0; y < SCORE_WIDTH; y++){
					if ((v_block[x%SCORE_HEIGHT] & (1<<(SCORE_WIDTH-1-y)))) {
						framePointer[(game_y+x)*640 + game_x+y] = 0x00FF00FF;
					} else {
						framePointer[(game_y+x)*640 + game_x+y] = 0x00000000;
					}
				}
			}
			break;
		case 6:
			for(x = 0; x < SCORE_HEIGHT; x++) {
				for(y = 0; y < SCORE_WIDTH; y++){
					if ((e_block[x%SCORE_HEIGHT] & (1<<(SCORE_WIDTH-1-y)))) {
						framePointer[(game_y+x)*640 + game_x+y] = 0x008888FF;
					} else {
						framePointer[(game_y+x)*640 + game_x+y] = 0x00000000;
					}
				}
			}
			break;

		case 7:
			for(x = 0; x < SCORE_HEIGHT; x++) {
				for(y = 0; y < SCORE_WIDTH; y++){
					if ((r_block[x%SCORE_HEIGHT] & (1<<(SCORE_WIDTH-1-y)))) {
						framePointer[(game_y+x)*640 + game_x+y] = 0x00448844;
					} else {
						framePointer[(game_y+x)*640 + game_x+y] = 0x00000000;
					}
				}
			}
			break;

		default :

			break;
		}

		while(counter < 3000000){
			counter++;
		}

	}
	exit(0);

}

int tankDied(unsigned int* framePointer){

	switch(lives){

	case 3:
		blankTanks(framePointer, 2);

		break;

	case 2:
		blankTanks(framePointer, 1);
		break;

	case 1:
		blankTanks(framePointer, 0);

		break;

	case 0:
		gameOver(framePointer);
		return 1;
		break;

	default:

		break;
	}
	lives--;

	return 0;
}
