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
	enum LedState {STATE0,STATE1,STATE2,STATE3,STATE4,STATE5};
	enum LedState eLedState = STATE0;
	//KeyboardInit();
	LedInit();
	while(1){
		switch(eLedState){
			case STATE0 :
				eLedState = STATE1;
				LedStepRight();
			break;
			case STATE1:
				eLedState = STATE2 ;
				LedStepRight();
			break;
			case STATE2:
				eLedState = STATE3 ;
				LedStepRight();
			break;
			case STATE3:
				eLedState = STATE4 ;
				LedStepLeft();
			break;
			case STATE4:
				eLedState = STATE5 ;
				LedStepLeft();
			break;
			case STATE5:
				eLedState = STATE0 ;
				LedStepLeft();
			break;
}
Delay(500);
}
}
