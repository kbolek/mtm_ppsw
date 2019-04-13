#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"

void Delay(int iHowLong){
	int iMiliSeconds = 4615; 
	unsigned long int uiIntCounter;
	char cCharIncrementation;
	for(uiIntCounter=0; uiIntCounter<(iHowLong*iMiliSeconds);uiIntCounter++){
		cCharIncrementation++;
	}
}

int main(){
	enum StateOfDirection {STAY, MOVE_RIGHT, MOVE_LEFT,CHANGE_DIRECTION};
	enum StateOfDirection eStateOfDirection = STAY;
  char cStepCounter = 0;
	KeyboardInit();
	LedInit();
	while(1){
		switch(eStateOfDirection){
			case STAY:
				if(eKeyboardRead() == BUTTON_1){
					eStateOfDirection = MOVE_LEFT;
				}
				else if(eKeyboardRead() == BUTTON_3){
					eStateOfDirection = MOVE_RIGHT;
				}
				else{
					eStateOfDirection = STAY;
				}
				break;		
			case MOVE_RIGHT:
				 if(eKeyboardRead() == BUTTON_2){
						eStateOfDirection = STAY;
					}				
				 else{
						LedStepRight();  
					 eStateOfDirection = MOVE_RIGHT;
					}
					break;
				
					
		  case MOVE_LEFT:
					if(eKeyboardRead() == BUTTON_2){
						eStateOfDirection = STAY;
					}
					else if(eKeyboardRead() == BUTTON_3){	
			
							eStateOfDirection = CHANGE_DIRECTION;
						}	
					else {
						LedStepLeft();
						eStateOfDirection = MOVE_LEFT;
					}
					break;
					
			case CHANGE_DIRECTION:	
				if(cStepCounter > 10){
					cStepCounter = 0;
					eStateOfDirection = MOVE_RIGHT;
				}
				else {
					LedStepLeft();
					cStepCounter = cStepCounter + 1;
				}
				break;

				}
				Delay(500);					
			}			                                                                                     
}
//git test

