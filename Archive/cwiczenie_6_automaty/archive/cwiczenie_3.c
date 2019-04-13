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
	enum LedState {LED_LEFT, LED_RIGHT};
	enum LedState eLedState = LED_LEFT;
	char cStepCounter = 0;
	//KeyboardInit();
	LedInit();
	while(1){
		switch(eLedState){
			case LED_LEFT:
				uiStepCounter = uiStepCounter +1;
				LedStepLeft();	
				if(uiStepCounter % 3 == 0){
					eLedState = LED_RIGHT;
				}
			break;
			
			case LED_RIGHT:
				uiStepCounter = uiStepCounter +1;
				LedStepRight();
				if(uiStepCounter % 3 == 0){
					eLedState = LED_LEFT;
				}			
			
}
Delay(500);
}
}
