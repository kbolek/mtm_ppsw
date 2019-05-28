#include "servo.h"
#include "uart.h"
#include "string.h"
#include "command_decoder.h"
#include "timer_interrupts.h"

struct Calculator {
	char cReceivedString[RECIEVER_SIZE];
	unsigned char fCalcChanged;
	unsigned int uiCalcValue;
};
struct Calculator sCalculator;

struct Watch {
	unsigned char ucMinutes, ucSeconds;
	unsigned char fSecondsValueChanged, fMinutesValueChanged;
};

struct Watch sWatch;

void WatchUpdate(){
	sWatch.ucSeconds++;
	sWatch.fSecondsValueChanged = 1;
	if(sWatch.ucSeconds == 60){
		sWatch.ucSeconds = 0;
		sWatch.ucMinutes++;
		sWatch.fMinutesValueChanged = 1;
	}
	if(sWatch.ucMinutes == 60){
		sWatch.ucMinutes = 0;
	}
}


int main(void){
	char cSeconds[5] = "sec ";
	char cMinutes[5] = "min ";
	char cCalc[6] = "calc ";
	char cSpace[2] = " ";
	char cTransmitString[TRANSMITER_SIZE];
	Timer0Interrupts_Init(1000000,&WatchUpdate);
		UART_InitWithInt(9600);
		while(1){
			if(eReciever_GetStatus() == READY){
				Reciever_GetStringCopy(sCalculator.cReceivedString);
				DecodeMsg(sCalculator.cReceivedString);
				if((ucTokenNr > 0) & (asToken[0].eType == KEYWORD)){
					if((asToken[0].uValue.eKeyword == CALC) & (asToken[1].eType == NUMBER)){
						sCalculator.fCalcChanged = 1;
						sCalculator.uiCalcValue = asToken[1].uValue.uiNumber*2;				
				}
			}
		}
			if(eReciever_GetStatus() == FREE){
				if(sWatch.fSecondsValueChanged==1){
				sWatch.fSecondsValueChanged=0;
				CopyString(cSeconds,cTransmitString);
				AppendUIntToString(sWatch.ucSeconds,cTransmitString);
				AppendString(cSpace,cTransmitString);
				Transmiter_SendString(cTransmitString);
			}
			else if(sWatch.fMinutesValueChanged==1){
				sWatch.fMinutesValueChanged=0;
				CopyString(cMinutes,cTransmitString+10);
				AppendUIntToString(sWatch.ucMinutes,cTransmitString);
				AppendString(cSpace,cTransmitString);
				Transmiter_SendString(cTransmitString);
					}
			else if(sCalculator.fCalcChanged == 1){
				CopyString(cCalc,cTransmitString);
				AppendUIntToString(sCalculator.uiCalcValue,cTransmitString);
				AppendString(cSpace,cTransmitString);
				Transmiter_SendString(cTransmitString);
				sCalculator.fCalcChanged = 0;
			}							
				}			
			}		
		}
	
		
