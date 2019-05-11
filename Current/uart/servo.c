#include <LPC21xx.H>
#include "led.h"
#include "timer_interrupts.h"
#define MULTIPIER 10000
#define DETECTOR_bm (1<<10)


enum State {ACTIVE,INACTIVE};

enum ServoState {CALLIB,IDLE,IN_PROGRESS};
struct Servo{
	enum ServoState eState;
	unsigned int uiCurrentPosition;
	unsigned int uiDesiredPostion;

};
struct Servo eServo;

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
void ServoCallib(void){
	eServo.eState = CALLIB;
}

void ServoGoTo(unsigned int uiPosition){
	eServo.eState = IN_PROGRESS;
	eServo.uiDesiredPostion = uiPosition;
}

void TestServo(void){
	while(eServo.eState != IDLE){};
	ServoGoTo(14);
	while(eServo.eState != IN_PROGRESS){};
	while(eServo.eState != IDLE) {};
	ServoGoTo(24);		
}

void Automat(){
	switch(eServo.eState){
		case IDLE:
			if(eServo.uiCurrentPosition != eServo.uiDesiredPostion){
				eServo.eState = IN_PROGRESS;
			}
			else{
				eServo.eState = IDLE;
			}
			break;
		case IN_PROGRESS:
			if(eServo.uiCurrentPosition < eServo.uiDesiredPostion){
				eServo.eState = IN_PROGRESS;
				LedStepRight();
				eServo.uiCurrentPosition++;
			}
			else if(eServo.uiCurrentPosition > eServo.uiDesiredPostion){
				eServo.eState = IN_PROGRESS;
				LedStepLeft();
				eServo.uiCurrentPosition--;
			}
			else {
				eServo.eState = IDLE;
			}
			break;
		case CALLIB: 
			if(eReadDetector()==INACTIVE){
				LedStepRight();
			}
			else{
				eServo.eState = IDLE;
				eServo.uiCurrentPosition = 0;
				eServo.uiDesiredPostion = 0;
			}
		
	}
}

void ServoInit(unsigned int uiServoFrequency){
		Timer0Interrupts_Init(1000000/uiServoFrequency, &Automat);
		LedInit();
		DetectorInit();
		ServoCallib();
	
}
