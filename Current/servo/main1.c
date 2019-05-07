#include <LPC21xx.H>

#include "timer_interrupts.h"
#include "led.h"
#include "keyboard.h"

#define MULTIPIER 10000
#define DETECTOR_bm (1<<10)

enum State {ACTIVE,INACTIVE};

void DetectorInit(){
	IO0DIR = IO0DIR&(~DETECTOR_bm);
}

enum State eReadDetector(){
	if((IO0PIN&DETECTOR_bm)==0){
		return ACTIVE;
	}
	else{
		return INACTIVE;
	}
}

void Automat(){
	enum StateOfDirection {STAY, MOVE_RIGHT, MOVE_LEFT,CALLIB};
	enum StateOfDirection eStateOfDirection = CALLIB;
	KeyboardInit();
	LedInit();
	switch(eStateOfDirection){
			case STAY:
				if(eKeyboardRead() == BUTTON_1){
					eStateOfDirection = MOVE_LEFT;
				}
				else if(eKeyboardRead() == BUTTON_3){
					eStateOfDirection = MOVE_RIGHT;
				}
				break;		
			case MOVE_RIGHT:
				 if(eKeyboardRead() == BUTTON_2){
						eStateOfDirection = STAY;
					}
				 else{
						LedStepRight();  
					}
					break;
					
		  case MOVE_LEFT:
					if(eKeyboardRead() == BUTTON_2){
						eStateOfDirection = STAY;
					}
					else {
						LedStepLeft();
					}
					break;
			case CALLIB:
					if(eReadDetector()==INACTIVE){
						LedStepRight();
					}
					else{
						eStateOfDirection = STAY;
					}
				}		
			}			


int main (){
	
	unsigned int iMainLoopCtr;
	Timer0Interrupts_Init(MULTIPIER*25,&Automat); //tak aby byly 4 przerwania na sekunde
	LedInit();
	KeyboardInit();
	DetectorInit();

	while(1){
	 	iMainLoopCtr++;
	}
}
