#ifndef GLOBAL_H_
#define GLOBAL_H_
#define WORD_WIDTH 32;

typedef struct {unsigned short x; unsigned short y;} point_t;

void setAlienBlockPosition(unsigned short x, unsigned short y);
unsigned short getAlienBlockPositionX();
unsigned short getAlienBlockPositionY();

void setTankPosition(unsigned short x, unsigned short y);
unsigned short getTankPositionX();
unsigned short getTankPositionY();


#endif /* GLOBAL_H_ */
