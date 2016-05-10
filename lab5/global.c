#include "global.h"


static point_t alienBlockPosition;
static point_t tankPosition;



static short alienDirection;
static short guise = 0;
static short guiseBullet = 0;
static short aliens[55] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
		                   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
		                   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
		                   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
		                   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

static short bunker1[10] = {0,0,0,0,0,0,0,0,0,0};
static short bunker2[10] = {0,0,0,0,0,0,0,0,0,0};
static short bunker3[10] = {0,0,0,0,0,0,0,0,0,0};
static short bunker4[10] = {0,0,0,0,0,0,0,0,0,0};



static point_t tankBulletPosition;
static point_t alienBulletPosition1;
static point_t alienBulletPosition2;
static point_t alienBulletPosition3;
static point_t alienBulletPosition4;

static short tankBullet = 0;
static short alienBullet1 = 0;
static short alienBullet2 = 0;
static short alienBullet3 = 0;
static short alienBullet4 = 0;

static point_t ufoPosition;
static short ufo_state = 0;
static short ufo_left;


short getUfoDirection(){
	return ufo_left;
}
short setUfoDirection(){
	ufo_left = rand()%2;
}

short getUfoPositionY() {
	return ufoPosition.y;
}
void setUfoPositionY(short update) {
	ufoPosition.y = update;
}
short getUfoPositionX() {
	return ufoPosition.x;
}
void setUfoPositionX(short update) {
	ufoPosition.x = update;
}
short getUfoState(){
	return ufo_state;
}
void setUfoState(short state){
	ufo_state = state;
}

unsigned short getGuiseBullet() {
	return guiseBullet;
}

void setGuiseBullet(unsigned short frame) {
	guiseBullet = frame;
}

// for tank bullet
void setTankBulletState(short state) {
	tankBullet = state;
}

short getTankBulletState() {
	return tankBullet;
}

void initialTankBulletPosition() {
	tankBulletPosition.x = getTankPositionX()+11;
	tankBulletPosition.y = 410;
}

short getTankBulletPositionX() {
	return tankBulletPosition.x;
}

short getTankBulletPositionY() {
	return tankBulletPosition.y;
}

void setTankBulletPositionY(short update) {
	tankBulletPosition.y = update;
}

//for alien bullet1
void setAlien1BulletState(short state) {
	alienBullet1 = state;
}

short getAlien1BulletState() {
	return alienBullet1;
}

short getAlien1BulletPositionX() {
	return alienBulletPosition1.x;
}

short getAlien1BulletPositionY() {
	return alienBulletPosition1.y;
}

void setAlien1BulletPositionY(short update) {
	alienBulletPosition1.y = update;
}

void setAlien1BulletPosition(short x, short y) {
	alienBulletPosition1.x = x;
	alienBulletPosition1.y = y;
}
//for alien bullet2
void setAlien2BulletState(short state) {
	alienBullet2 = state;
}

short getAlien2BulletState() {
	return alienBullet2;
}

short getAlien2BulletPositionX() {
	return alienBulletPosition2.x;
}

short getAlien2BulletPositionY() {
	return alienBulletPosition2.y;
}

void setAlien2BulletPositionY(short update) {
	alienBulletPosition2.y = update;
}

void setAlien2BulletPosition(short x, short y) {
	alienBulletPosition2.x = x;
	alienBulletPosition2.y = y;
}

//for alien bullet3
void setAlien3BulletState(short state) {
	alienBullet3 = state;
}

short getAlien3BulletState() {
	return alienBullet3;
}

short getAlien3BulletPositionX() {
	return alienBulletPosition3.x;
}

short getAlien3BulletPositionY() {
	return alienBulletPosition3.y;
}

void setAlien3BulletPositionY(short update) {
	alienBulletPosition3.y = update;
}

void setAlien3BulletPosition(short x, short y) {
	alienBulletPosition3.x = x;
	alienBulletPosition3.y = y;
}

//for alien bullet4
void setAlien4BulletState(short state) {
	alienBullet4 = state;
}

short getAlien4BulletState() {
	return alienBullet4;
}

short getAlien4BulletPositionX() {
	return alienBulletPosition4.x;
}

short getAlien4BulletPositionY() {
	return alienBulletPosition4.y;
}

void setAlien4BulletPositionY(short update) {
	alienBulletPosition4.y = update;
}

void setAlien4BulletPosition(short x, short y) {
	alienBulletPosition4.x = x;
	alienBulletPosition4.y = y;
}
//for bunker
short* getBunker1() {
	return bunker1;
}

void setBunker1(unsigned short state, unsigned short block) {
	bunker1[block] = state;
}
short* getBunker2() {
	return bunker2;
}

void setBunker2(unsigned short state, unsigned short block) {
	bunker2[block] = state;
}
short* getBunker3() {
	return bunker3;
}

void setBunker3(unsigned short state, unsigned short block) {
	bunker3[block] = state;
}
short* getBunker4() {
	return bunker4;
}

void setBunker4(unsigned short state, unsigned short block) {
	bunker1[block] = state;
}

// Here are the accessors.
short* getAliens() {
	return aliens;
}

void setAliens(unsigned short alien, unsigned short position) {
	xil_printf("setting alien\r\n");
	aliens[position] = alien;
}

unsigned short getGuise() {
	return guise;
}

void setGuise(unsigned short frame) {
	guise = frame;
}

unsigned short getDirection() {
	return alienDirection;
}

void setDirection(unsigned short direction) {
	alienDirection = direction;
}

void setAlienBlockPosition(unsigned short x, unsigned short y) {
	alienBlockPosition.x = x;
	alienBlockPosition.y = y;
}

unsigned short getAlienBlockPositionX() {
  return alienBlockPosition.x;
}

unsigned short getAlienBlockPositionY() {
  return alienBlockPosition.y;
}
void setTankPosition(unsigned short x, unsigned short y) {
	tankPosition.x = x;
	tankPosition.y = y;
}

unsigned short getTankPositionX() {
  return tankPosition.x;
}

unsigned short getTankPositionY() {
  return tankPosition.y;
}

