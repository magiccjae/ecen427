/*
 * sounds.c
 *
 *  Created on: Oct 26, 2013
 *      Author: superman
 */

#include "sounds.h"

extern int shoot_numberOfSamples;
extern int tankDeath_numberOfSamples;
extern int spaceShipSound_numberOfSamples;
extern int spaceShipDeathSound_numberOfSamples;
extern int alienDeathSound_numberOfSamples;
extern int alienMovement1Sound_numberOfSamples;
extern int alienMovement2Sound_numberOfSamples;
extern int alienMovement3Sound_numberOfSamples;
extern int alienMovement4Sound_numberOfSamples;


extern int shoot_soundData[];
extern int tankDeath_soundData[];
extern int spaceShipSound_soundData[];
extern int spaceShipDeathSound_soundData[];
extern int alienDeathSound_soundData[];
extern int alienMovement1Sound_soundData[];
extern int alienMovement2Sound_soundData[];
extern int alienMovement3Sound_soundData[];
extern int alienMovement4Sound_soundData[];
extern int alienSilenceSound_soundData[];
int haveTankBulletSound = 0;
int haveTankDeathSound = 0;
int haveSpaceShipSound = 0;
int haveSpaceShipDeathSound = 0;
int haveAlienDeathSound = 0;
int haveAlienMoveSound =1;

int bulletSoundIndex = 0;
int tankDeathIndex = 0;
int spaceShipIndex = 0;
int spaceShipDeathIndex = 0;
int alienDeathIndex = 0;
int alienCadenceIndex = 1;
int alien1Index=0;
int alien2Index=0;
int alien3Index=0;
int alien4Index=0;
int isHaveTankBulletSound() {
  return haveTankBulletSound;
}
void setHaveTankBulletSound(int x) {
  haveTankBulletSound = x;
}

int isHaveTankDeathSound() {
  return haveTankDeathSound;
}
void setHaveTankDeathSound(int x) {
  haveTankDeathSound = x;
}

int isHaveSpaceShipSound() {
  return haveSpaceShipSound;
}
void setHaveSpaceShipSound(int x) {
  haveSpaceShipSound = x;
}

int isHaveSpaceShipDeathSound() {
  return haveSpaceShipDeathSound;
}
void setHaveSpaceShipDeathSound(int x) {
  haveSpaceShipDeathSound = x;
}

int isHaveAlienDeathSound() {
  return haveAlienDeathSound;
}
void setHaveAlienDeathSound(int x) {
  haveAlienDeathSound = x;
}
int isAlienSoundCadence(){
	return alienCadenceIndex;
}
void setAlienSoundCadence(int x){
	alienCadenceIndex = x;
}
//Responsible for rotating the different alien sounds called in the timer
void incrementAlienSoundCadence(){
	if(isAlienSoundCadence() == 8)
		setAlienSoundCadence(1);
	else
		setAlienSoundCadence(isAlienSoundCadence() + 1);
}

void fillSound(){
  int i;
  for(i=0;i<256;i++){
    Xuint32 sample = getNextSample();
    XAC97_mSetInFifoData(XPAR_AXI_AC97_0_BASEADDR,sample);
  }
}


Xuint32 getNextSample(){

  Xuint32 sample = 0x00000000; //Play no sound

  if (haveTankBulletSound != 0) {
    sample = (shoot_soundData[bulletSoundIndex] | (shoot_soundData[bulletSoundIndex])<<16);
    if(bulletSoundIndex < (shoot_numberOfSamples - 1)){
      bulletSoundIndex++;
    } else {
      bulletSoundIndex = 0;
      haveTankBulletSound = 0;
    }
  } else if (haveTankDeathSound != 0) {
    sample = (tankDeath_soundData[tankDeathIndex] | (tankDeath_soundData[tankDeathIndex])<<16);
    if (tankDeathIndex < (tankDeath_numberOfSamples - 1)) {
      tankDeathIndex++;
    } else {
      tankDeathIndex = 0;
      haveTankDeathSound = 0;
    }
  } else if (haveSpaceShipSound != 0 ) { //set in setHaveSpaceShip global
    sample = (spaceShipSound_soundData[spaceShipIndex] | (spaceShipSound_soundData[spaceShipIndex])<<16);
    if (spaceShipIndex < (spaceShipSound_numberOfSamples -1)) {
      spaceShipIndex++;
    } else {
      spaceShipIndex = 0;
      //Set no sound when it goes off the page - Done by setHaveSpaceShip global

    }
  } else if (haveSpaceShipDeathSound != 0) {
    sample = (spaceShipDeathSound_soundData[spaceShipDeathIndex] | (spaceShipDeathSound_soundData[spaceShipDeathIndex])<<16);
    if (spaceShipDeathIndex < (spaceShipDeathSound_numberOfSamples - 1)) {
      spaceShipDeathIndex++;
    } else {
      spaceShipDeathIndex = 0;
      haveSpaceShipDeathSound = 0;
    }

  }
  else if (haveAlienDeathSound != 0) {
      sample = (alienDeathSound_soundData[alienDeathIndex] | (alienDeathSound_soundData[alienDeathIndex])<<16);
      if (alienDeathIndex < (alienDeathSound_numberOfSamples - 1)) {
        alienDeathIndex++;
      } else {
        alienDeathIndex = 0;
        haveAlienDeathSound = 0;
      }
    }
//Set to always on since aliens are always in the game
  else if (haveAlienMoveSound != 0){
	  //Performs the change in the four different sounds which are incremented by the alienCounter which is in timer_interrupt_handler()
	  switch (isAlienSoundCadence()){
	  case 1:
		  sample = (alienMovement1Sound_soundData[alien1Index] | (alienMovement1Sound_soundData[alien1Index]) <<16);

		  if(alien1Index < (alienMovement1Sound_numberOfSamples -1)){
			  alien1Index++;
		  }
		  else{
			  alien1Index = 0;
		  }


	  break;
	  case 3:
		  sample = (alienMovement2Sound_soundData[alien2Index] | (alienMovement2Sound_soundData[alienCadenceIndex]) <<16);

		  if(alien2Index < (alienMovement2Sound_numberOfSamples -1)){
		  			  alien2Index++;
		  		  }
		  		  else{
		  			  alien2Index = 0;
		  		  }
		  break;
	 case 5:
		  sample = (alienMovement3Sound_soundData[alien3Index] | (alienMovement3Sound_soundData[alienCadenceIndex]) <<16);

		  if(alien3Index < (alienMovement3Sound_numberOfSamples -1)){
		  			  alien3Index++;
		  		  }
		  		  else{
		  			  alien3Index = 0;
		  		  }
		  break;
	  case 7:


		  sample = (alienMovement4Sound_soundData[alien4Index] | (alienMovement4Sound_soundData[alienCadenceIndex]) <<16);

		  if(alien4Index < (alienMovement4Sound_numberOfSamples -1)){
		  			  alien4Index++;
		  		  }
		  		  else{
		  			  alien4Index = 0;
		  		  }
		  break;
	  default:
	 		  sample = 0x00000080;

	 		 		  break;

	  }



  }

  return sample;
}


