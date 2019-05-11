#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"
#include "timer.h"

#define M_MULTIPIER 1000000

int main(){
	LedInit();
	InitTimer0Match0(1*M_MULTIPIER);
	while(1){
		LedStepLeft();
		WaitOnTimer0Match0();
	}
	
	
}
