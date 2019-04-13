#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"
#include "timer.h"

#define M_MULTIPIER 1000000

int main(){
	LedInit();
	InitTimer();
	while(1){
		LedStepLeft();
		WaitOnTimer0(1*M_MULTIPIER);
	}
	
	
}
