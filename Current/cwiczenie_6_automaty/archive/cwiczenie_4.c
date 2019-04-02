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
	enum StateOfDirection {STAY, MOVE_RIGHT};
	enum StateOfDirection eStateOfDirection = MOVE_RIGHT;
	char cStepCounter = 0;
	KeyboardInit();
	LedInit();
	while(1){
		switch(eStateOfDirection){
			case STAY:	
				if(eKeyboardRead() == BUTTON_1){
            eStateOfDirection = MOVE_RIGHT;	
        }
				break;
			case MOVE_RIGHT:
					 LedStepRight();
					 cStepCounter = cStepCounter +1;
					 if (cStepCounter > 3){
							eStateOfDirection = STAY;
							cStepCounter = 0;
						}
						break;
				}	
		Delay(500);				
}
}

