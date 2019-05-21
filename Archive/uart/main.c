#include "servo.h"
#include "uart.h"
#include "timer.h"
#include "keyboard.h"
#define PRESCALER 10000


int main (){
	extern char cOdebranyZnak;
	UART_InitWithInt(9600);
	ServoInit(500);
	InitTimer();
	KeyboardInit();
	while(1)
	{
		WaitOnTimer0(PRESCALER*5);
		switch(cOdebranyZnak){
			case '1':
				ServoGoTo(50);
				break;			
			case '2':
				ServoGoTo(100);
				break;
			case '3':
				ServoGoTo(150);
				break;
			case '4':
				break;
			case 'c':
				ServoCallib();
				break;
			default:
			break;
		}
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
			default:
			break;
		}
	}
		
	}

