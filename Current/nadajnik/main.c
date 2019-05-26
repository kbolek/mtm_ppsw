#include "servo.h"
#include "uart.h"
#include "string.h"
#include "command_decoder.h"


int main(void){
	char cString[32] = "licznik ";
	char cTransmitString[32];
	unsigned int uiNumber = 0;
	
		UART_InitWithInt(9600);
		while(1){
			if(Transmiter_GetStatus() == FREE){
				CopyString(cString,cTransmitString);
				AppendUIntToString(uiNumber,cTransmitString);
				Transmiter_SendString(cTransmitString);
				uiNumber++;
			}
		}
		
}
	

