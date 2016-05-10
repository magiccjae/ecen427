#ifndef BULLET_H_
#define BULLET_H_

#define BLOCK_HEIGHT 10
#define BLOCK_WIDTH 8
#define packWord24(b7,b6,b5,b4,b3,b2,b1,b0) \
( (b7  << 7 ) | (b6  << 6 ) | (b5  << 5 ) | (b4  << 4 ) | (b3  << 3 ) | (b2  << 2 ) | (b1  << 1 ) | (b0  << 0 ))

int alienBullet1_1[BLOCK_HEIGHT] =
{
		packWord24(0,0,0,0,0,0,0,0),
		packWord24(0,0,0,1,1,0,0,0),
		packWord24(0,0,0,1,1,0,0,0),
		packWord24(0,0,0,1,1,0,0,0),
		packWord24(0,0,0,1,1,0,0,0),
		packWord24(0,0,0,1,1,0,0,0),
		packWord24(0,1,1,1,1,1,1,0),
		packWord24(0,1,1,1,1,1,1,0),
		packWord24(0,0,0,1,1,0,0,0),
		packWord24(0,0,0,0,0,0,0,0),
};

int alienBullet1_2[BLOCK_HEIGHT] =
{
		packWord24(0,0,0,0,0,0,0,0),
		packWord24(0,0,0,1,1,0,0,0),
		packWord24(0,1,1,1,1,1,1,0),
		packWord24(0,1,1,1,1,1,1,0),
		packWord24(0,0,0,1,1,0,0,0),
		packWord24(0,0,0,1,1,0,0,0),
		packWord24(0,0,0,1,1,0,0,0),
		packWord24(0,0,0,1,1,0,0,0),
		packWord24(0,0,0,1,1,0,0,0),
		packWord24(0,0,0,0,0,0,0,0),
};

int alienBullet2_1[BLOCK_HEIGHT] =
{
		packWord24(0,0,0,0,0,0,0,0),
		packWord24(0,0,0,0,0,1,1,0),
		packWord24(0,0,0,0,1,1,0,0),
		packWord24(0,0,0,1,1,0,0,0),
		packWord24(0,0,1,1,0,0,0,0),
		packWord24(0,0,1,1,0,0,0,0),
		packWord24(0,0,0,1,1,0,0,0),
		packWord24(0,0,0,0,1,1,0,0),
		packWord24(0,0,0,0,0,1,1,0),
		packWord24(0,0,0,0,0,0,0,0),
};

int alienBullet2_2[BLOCK_HEIGHT] =
{
		packWord24(0,0,0,0,0,0,0,0),
		packWord24(0,0,0,1,1,0,0,0),
		packWord24(0,0,0,0,1,1,0,0),
		packWord24(0,0,0,1,1,0,0,0),
		packWord24(0,0,0,0,1,1,0,0),
		packWord24(0,0,0,0,0,1,1,0),
		packWord24(0,0,0,0,1,1,0,0),
		packWord24(0,0,0,1,1,0,0,0),
		packWord24(0,0,1,1,0,0,0,0),
		packWord24(0,0,0,0,0,0,0,0),
};

int alienBullet3_1[BLOCK_HEIGHT] =
{
		packWord24(0,0,0,0,0,0,0,0),
		packWord24(0,1,1,0,0,0,0,0),
		packWord24(0,0,1,1,0,0,0,0),
		packWord24(0,0,0,1,1,0,0,0),
		packWord24(0,0,0,0,1,1,0,0),
		packWord24(0,0,0,0,1,1,0,0),
		packWord24(0,0,0,1,1,0,0,0),
		packWord24(0,0,1,1,0,0,0,0),
		packWord24(0,1,1,0,0,0,0,0),
		packWord24(0,0,0,0,0,0,0,0),
};

int alienBullet3_2[BLOCK_HEIGHT] =
{
		packWord24(0,0,0,0,0,0,0,0),
		packWord24(0,1,1,0,0,0,0,0),
		packWord24(0,0,1,1,0,0,0,0),
		packWord24(0,0,0,1,1,0,0,0),
		packWord24(0,0,1,1,0,0,0,0),
		packWord24(0,1,1,0,0,0,0,0),
		packWord24(0,0,1,1,0,0,0,0),
		packWord24(0,0,0,1,1,0,0,0),
		packWord24(0,0,0,0,1,1,0,0),
		packWord24(0,0,0,0,0,0,0,0),
};

int tankBullet[BLOCK_HEIGHT] =
{
		packWord24(0,0,0,0,0,0,0,0),
		packWord24(0,0,0,1,1,0,0,0),
		packWord24(0,0,0,1,1,0,0,0),
		packWord24(0,0,0,1,1,0,0,0),
		packWord24(0,0,0,1,1,0,0,0),
		packWord24(0,0,0,1,1,0,0,0),
		packWord24(0,0,0,1,1,0,0,0),
		packWord24(0,0,0,1,1,0,0,0),
		packWord24(0,0,0,1,1,0,0,0),
		packWord24(0,0,0,0,0,0,0,0),
};

void renderBullet(unsigned int*);
void moveBullets();
#endif /* BULLET_H_ */
