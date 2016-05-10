/*
 * sounds.h
 *
 *  Created on: Oct 29, 2013
 *      Author: superman
 */

#ifndef SOUNDS_H_
#define SOUNDS_H_

#include <xbasic_types.h>
#include "xparameters.h"
#include "xac97_l.h"



/**
 * These are the Getters and setters to control global sounds
 * Set the value to (1) in order to allow sound generation
 * Set the value to (0) in order to halt the sound
 */
int isHaveTankBulletSound();
void setHaveTankBulletSound(int x);

int isHaveTankDeathSound();
void setHaveTankDeathSound(int x);

int isHaveSpaceShipSound();
void setHaveSpaceShipSound(int x);

int isHaveSpaceShipDeathSound();
void setHaveSpaceShipDeathSound(int x);

int isHaveAlienDeathSound(); 
void setHaveAlienDeathSound(int x); 

int isAlienSoundCadence();
void setAlienSoundCadence();
void incrementAlienSoundCadence();
//This loops through 128 values to control the fifo input of ac97
void fillSound();


Xuint32 getNextSample();

#endif /* SOUNDS_H_ */

