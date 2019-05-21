#include "servo.h"
#include "uart.h"
#include "string.h"
#include "command_decoder.h"

int main(void){
	char cOdebranyString[RECIEVER_SIZE];
	unsigned int uiPreviousPos;
	ServoInit(50);
	UART_InitWithInt(9600);
	while(1){
		if(eReciever_GetStatus() == READY){
			Reciever_GetStringCopy(cOdebranyString);
			DecodeMsg(cOdebranyString);
			if((ucTokenNr>0) && (asToken[0].eType == KEYWORD)){
				switch(asToken[0].uValue.eKeyword){
					case CALLIB:
						ServoCallib();
						break;
					case GOTO:
						if(asToken[1].eType == NUMBER){
							ServoGoTo(asToken[1].uValue.uiNumber);
							uiPreviousPos = asToken[1].uValue.uiNumber;
							
						}
						break;
					case STEP:
							if(asToken[1].eType == NUMBER){
								ServoGoTo(uiPreviousPos + asToken[1].uValue.uiNumber);
								uiPreviousPos = uiPreviousPos + asToken[1].uValue.uiNumber;
							}
							break;
					default:
							break;
				}

				
			}
		}
	}
}
	

