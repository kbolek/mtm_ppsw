#include <LPC21xx.H>
#include "servo.h"
#include "led.h"
#include "keyboard.h"


int main (){
	KeyboardInit();
	ServoInit(50);
	
	
	while(1){
		switch(eKeyboardRead()){
			case BUTTON_1:
				ServoCallib();
				break;			
			case BUTTON_2:
				ServoGoTo(14);
				break;
			case BUTTON_3:
				ServoGoTo(24);
				break;
			case BUTTON_4:
				ServoGoTo(36);
			break;
			case RELEASED:
				break;
			default:{}
		}
	}
	
}
