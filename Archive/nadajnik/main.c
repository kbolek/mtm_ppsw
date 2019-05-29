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
	unsigned char fUnkownCommand;
	char cTransmitString[TRANSMITER_SIZE];
	Timer1Interrupts_Init(1000000,&WatchUpdate);
	ServoInit(50);
	UART_InitWithInt(9600);
		while(1){
			if(eReciever_GetStatus() == READY){
				Reciever_GetStringCopy(sCalculator.cReceivedString);
				DecodeMsg(sCalculator.cReceivedString);
				if((ucTokenNr > 0) & (asToken[0].eType == KEYWORD)){
					switch(asToken[0].uValue.eKeyword){
						case CALC:
							sCalculator.fCalcChanged = 1;
							sCalculator.uiCalcValue = asToken[1].uValue.uiNumber*2;
						case CALLIB:
							ServoCallib();
						break;
						case GOTO:
							if(asToken[1].eType == NUMBER){
								ServoGoTo(asToken[1].uValue.uiNumber);
						}
						break;
						default:
							fUnkownCommand = 1;
						break;
					}
				}	
				else {
					fUnkownCommand = 1;
				}					
			}
			if(Transmiter_GetStatus() == FREE){
					if(sWatch.fSecondsValueChanged==1){
						sWatch.fSecondsValueChanged=0;
						CopyString("sec ",cTransmitString);
						AppendUIntToString(sWatch.ucSeconds,cTransmitString);
						Transmiter_SendString(cTransmitString);
					}
					else if(sWatch.fMinutesValueChanged==1){
						sWatch.fMinutesValueChanged=0;
						CopyString("min ",cTransmitString);
						AppendUIntToString(sWatch.ucMinutes,cTransmitString);
						Transmiter_SendString(cTransmitString);
					}
					else if(sCalculator.fCalcChanged == 1){
						CopyString("calc ",cTransmitString);
						AppendUIntToString(sCalculator.uiCalcValue,cTransmitString);
						Transmiter_SendString(cTransmitString);
						sCalculator.fCalcChanged = 0;
					}
					else if(fUnkownCommand == 1){
						fUnkownCommand = 0;
						CopyString("unkowncommand",cTransmitString);
						Transmiter_SendString(cTransmitString);	
					}
			}			
		}
	}
	
		
