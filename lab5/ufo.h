#ifndef UFO_H_
#define UFO_H_

#define UFO_HEIGHT 16
#define UFO_WIDTH 30
#define UFOSCORE_HEIGHT 6
#define UFOSCORE_WIDTH 6

#define packWord6(b5,b4,b3,b2,b1,b0) \
		((b5  << 5 ) | (b4  << 4 ) | (b3  << 3 ) | (b2  << 2 ) | (b1  << 1 ) | (b0  << 0 ))


#define packWord30(b29,b28,b27,b26,b25,b24,b23,b22,b21,b20,b19,b18,b17,b16,b15,b14,b13,b12,b11,b10,b9,b8,b7,b6,b5,b4,b3,b2,b1,b0) \
		((b29 << 29) | (b28 << 28) | (b27 << 27) | (b26 << 26) | (b25 << 25) | (b24 << 24) |						  \
				(b23 << 23) | (b22 << 22) | (b21 << 21) | (b20 << 20) | (b19 << 19) | (b18 << 18) | (b17 << 17) | (b16 << 16) |						  \
				(b15 << 15) | (b14 << 14) | (b13 << 13) | (b12 << 12) | (b11 << 11) | (b10 << 10) | (b9  << 9 ) | (b8  << 8 ) |						  \
				(b7  << 7 ) | (b6  << 6 ) | (b5  << 5 ) | (b4  << 4 ) | (b3  << 3 ) | (b2  << 2 ) | (b1  << 1 ) | (b0  << 0 ) )

int ufo[UFO_HEIGHT] =
{
		packWord30(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
		packWord30(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
		packWord30(0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0),
		packWord30(0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0),
		packWord30(0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0),
		packWord30(0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0),
		packWord30(0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0),
		packWord30(0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0),
		packWord30(0,0,0,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,1,1,1,1,0,0,0),
		packWord30(0,0,0,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,1,1,1,1,0,0,0),
		packWord30(0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0),
		packWord30(0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0),
		packWord30(0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0),
		packWord30(0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0),
		packWord30(0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0),
		packWord30(0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0),

};

int ufo_zero_block[UFOSCORE_HEIGHT] =		// 0 block
{
		packWord6(0,0,1,1,0,0),
		packWord6(0,0,1,1,0,0),
		packWord6(1,1,0,0,1,1),
		packWord6(1,1,0,0,1,1),
		packWord6(0,0,1,1,0,0),
		packWord6(0,0,1,1,0,0),
};

int ufo_one_block[UFOSCORE_HEIGHT] =		// 1 block
{
		packWord6(0,0,1,1,0,0),
		packWord6(0,0,1,1,0,0),
		packWord6(0,0,1,1,0,0),
		packWord6(0,0,1,1,0,0),
		packWord6(0,0,1,1,0,0),
		packWord6(0,0,1,1,0,0),
};
int ufo_two_block[UFOSCORE_HEIGHT] =		// 2 block
{
		packWord6(1,1,1,1,1,1),
		packWord6(0,0,0,0,0,1),
		packWord6(0,0,0,0,0,1),
		packWord6(1,1,1,1,1,1),
		packWord6(1,0,0,0,0,0),
		packWord6(1,1,1,1,1,1),
};

int ufo_three_block[UFOSCORE_HEIGHT] =		// 3 block
{
		packWord6(1,1,1,1,1,1),
		packWord6(0,0,0,0,1,0),
		packWord6(0,0,1,1,0,0),
		packWord6(0,0,0,0,1,0),
		packWord6(0,0,0,0,0,1),
		packWord6(1,1,1,1,1,0),
};
int ufo_four_block[UFOSCORE_HEIGHT] =		// 4 block
{
		packWord6(1,0,0,0,0,1),
		packWord6(1,0,0,0,0,1),
		packWord6(1,0,0,0,0,1),
		packWord6(1,1,1,1,1,1),
		packWord6(0,0,0,0,0,1),
		packWord6(0,0,0,0,0,1),
};
int ufo_five_block[UFOSCORE_HEIGHT] =		// 5 block
{
		packWord6(1,1,1,1,1,1),
		packWord6(1,0,0,0,0,0),
		packWord6(1,1,1,1,1,1),
		packWord6(0,0,0,0,0,1),
		packWord6(0,0,0,0,0,1),
		packWord6(1,1,1,1,1,1),
};
int ufo_six_block[UFOSCORE_HEIGHT] =		// 6 block
{
		packWord6(1,1,1,1,1,1),
		packWord6(1,0,0,0,0,0),
		packWord6(1,0,0,0,0,0),
		packWord6(1,1,1,1,1,1),
		packWord6(1,0,0,0,0,1),
		packWord6(1,1,1,1,1,1),
};
int ufo_seven_block[UFOSCORE_HEIGHT] =		// 7 block
{
		packWord6(1,1,1,1,1,1),
		packWord6(1,1,1,1,1,1),
		packWord6(0,0,0,0,1,1),
		packWord6(0,0,0,0,1,1),
		packWord6(0,0,0,0,1,1),
		packWord6(0,0,0,0,1,1),
};
int ufo_eight_block[UFOSCORE_HEIGHT] =		// 8 block
{
		packWord6(0,0,1,1,0,0),
		packWord6(1,1,0,0,1,1),
		packWord6(0,0,1,1,0,0),
		packWord6(1,1,0,0,1,1),
		packWord6(1,1,0,0,1,1),
		packWord6(0,0,1,1,0,0),
};
int ufo_nine_block[UFOSCORE_HEIGHT] =		// 9 block
{
		packWord6(0,0,1,1,0,0),
		packWord6(1,1,0,0,1,1),
		packWord6(1,1,0,0,1,1),
		packWord6(0,0,1,1,1,1),
		packWord6(0,0,0,0,1,1),
		packWord6(1,1,1,1,1,1),
};


#endif /* UFO_H_ */
