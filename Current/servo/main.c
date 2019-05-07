#include <LPC21xx.H>
#include "servo.h"
#include "led.h"
#include "keyboard.h"


int main (){
	KeyboardInit();
	ServoInit(500);
	ServoGoTo(100);
	
	while(1){
		switch(eKeyboardRead()){
			case BUTTON_1:
				ServoCallib();
				break;			
			case BUTTON_2:
				ServoGoTo(50);
				break;
			case BUTTON_3:
				ServoGoTo(100);
				break;
			case BUTTON_4:
				ServoGoTo(150);
			break;
			case RELEASED:
				break;
			default:{}
		}
	}
	
}
