#include "alien.h"

int leftLim;
int rightLim;

void renderAlien(unsigned int* framePointer) {
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
						}
//						else if(aliens[position+position_helper] == 0) {
//
//						}
						else {
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
						}
//						else if(aliens[position+position_helper] == 0) {
//
//						}
						else {
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
						}
//						else if( aliens[position+position_helper] == 0) {
//
//						}
						else {
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
						}
//						else if(aliens[position+position_helper] == 0) {
//
//						}
						else {
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
						}
//						else if(aliens[position+position_helper] == 0) {
//
//						}
						else {
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
						}
//						else if(aliens[position+position_helper] == 0) {
//
//						}
						else {
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

void dyingAlien(unsigned int* framePointer, short alienx, short alieny) {
	short row=0, col=0;
	for(row = 0; row < 16; row++){
		for(col = 0; col < 32; col++){
			if ((dying_alien[row%16] & (1<<(32-1-col)))) {
				framePointer[(alieny+row)*640 + alienx+col] = 0x00FFFFFE;
			} else {
				framePointer[(alieny+row)*640 + alienx+col] = 0x00000000;
			}
		}
	}
}

void dyingAlienHelper(unsigned int* framePointer, short alienx, short alieny) {
	short row=0, col=0;
	for(row = 0; row < 16; row++){
		for(col = 0; col < 32; col++){
				framePointer[(alieny+row)*640 + alienx+col] = 0x00000000;
		}
	}
}

int columnCheck(int value) {
	short* aliens = getAliens();
	if(aliens[value] == 0 && aliens[value+11] == 0 && aliens[value+22] == 0 && aliens[value+33] == 0 && aliens[value+44] == 0) {
		return 0;
	}
	return 1;
}

int setRightMax() {
	int max = 352;
	if(!columnCheck(10)) {
		max = 320;
		if(!columnCheck(9)) {
			max = 288;
			if(!columnCheck(8)) {
				max = 256;
				if(!columnCheck(7)) {
					max = 224;
					if(!columnCheck(6)) {
						max = 192;
						if(!columnCheck(5)) {
							max = 160;
							if(!columnCheck(4)) {
								max = 128;
								if(!columnCheck(3)) {
									max = 96;
									if(!columnCheck(2)) {
										max = 64;
										if(!columnCheck(1)) {
											max = 32;
											if(!columnCheck(0)) {
												max = 0;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return max;
}

int setLeftMin() {
	int min = 0;
		if(!columnCheck(0)) {
			min = 32;
			if(!columnCheck(1)) {
				min = 64;
				if(!columnCheck(2)) {
					min = 96;
					if(!columnCheck(3)) {
						min = 128;
						if(!columnCheck(4)) {
							min = 160;
							if(!columnCheck(5)) {
								min = 192;
								if(!columnCheck(6)) {
									min = 224;
									if(!columnCheck(7)) {
										min = 256;
										if(!columnCheck(8)) {
											min = 288;
											if(!columnCheck(9)) {
												min = 320;
												if(!columnCheck(10)) {
													min = 352;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		return min;
}

void moveAlien(unsigned int* framePointer) {
	short dir = getDirection();
	short alienx, alieny;
	alienx = getAlienBlockPositionX();
	alieny = getAlienBlockPositionY();
	int right = setRightMax();
	if((alienx+right) == 640 && dir == 0) {
		setDirection(1);
		blankAlien(framePointer);
		alieny += 8;
		setAlienBlockPosition(alienx, alieny);

	}
	int left = 0 - setLeftMin();
	if(alienx == left && dir == 1) {
		setDirection(0);
		blankAlien(framePointer);
		alieny += 8;
		setAlienBlockPosition(alienx, alieny);

	}
	if(dir == 0) {
		alienx += 4;
		setAlienBlockPosition(alienx, alieny);
	}
	else {
		alienx -= 4;
		setAlienBlockPosition(alienx, alieny);
	}
}

