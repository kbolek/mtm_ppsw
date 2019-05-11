#include "led.h"
#include "timer_interrupts.h"
#include "servo.h"
#include "uart.h"
#include "timer.h"
#define PRESCALER 10000


int main (){
	extern char cOdebranyZnak;
	UART_InitWithInt(9600);
	InitTimer();
	LedInit();
	while(1)
	{
		WaitOnTimer0(PRESCALER*5);
		switch(cOdebranyZnak){
			case '1':
				LedOn(0);
				break;			
			case '2':
				LedOn(1);
				break;
			case '3':
				LedOn(2);
				break;
			case '4':
				LedOn(3);
				break;
			case 'c':
				LedOn(4);
				break;
			default:{}
		}
	}
}
