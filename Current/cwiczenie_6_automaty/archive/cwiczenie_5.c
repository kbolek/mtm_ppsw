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
	KeyboardInit();
	LedInit();
	while(1){
		switch(eStateOfDirection){
			case STAY:	
				if(eKeyboardRead() == BUTTON_2){
            eStateOfDirection = MOVE_RIGHT;	
        }
				break;
			
				case MOVE_RIGHT:
					 if(eKeyboardRead() == BUTTON_1){
							eStateOfDirection = STAY;
        }
					 else{
						 LedStepRight();  
					}
					break;
				}	
				Delay(200);				
}
}

