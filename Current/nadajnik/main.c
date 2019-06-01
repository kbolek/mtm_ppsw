#include <LPC21xx.H>
#include "servo.h"
#include "uart.h"
#include "string.h"
#include "command_decoder.h"
#include "timer_interrupts.h"

//ADC Control Register
#define ADC_PIN_SEL (1<<26) //P0.29
#define ADCR_SEL (1<<2) //AIN2
#define ADCR_PDN (1<<21)
#define ADCR_START (1<<24)
//ADC Data Register
#define ADCD_DONE (1<<31)
#define ADCD_MASK 0xFFC0
#define VREF 3.3 
#define MAX_POT 0x03FF


void ADCConverterInit() {
	PINSEL1 = ADC_PIN_SEL; //control the function ADC
	ADCR = ADCR|ADCR_SEL; //AIN2 pin is to be sampled 
	ADCR = ADCR|ADCR_PDN;	//ADC is operational
}

long int ADC_ReadPosition() {
	ADCR = ADCR | ADCR_START;
	while((ADDR & ADCD_DONE) == 0) {}
	return ((ADDR&ADCD_MASK)>>6);
}

int main (){
	long unsigned int uiServoPosition;
	float fVoltage;
	char cTransmitString[TRANSMITER_SIZE];
	ServoInit(150);
	ADCConverterInit();
	ServoCallib();
	UART_InitWithInt(9600);
	while(1)
	{
		uiServoPosition = ADC_ReadPosition();
		if(Transmiter_GetStatus() == FREE){
			CopyString("mV = ",cTransmitString); //min 0x0000 max 0x03FF
			fVoltage = (uiServoPosition*VREF)/MAX_POT;
			AppendUIntToString((int)(fVoltage*1000),cTransmitString);
			Transmiter_SendString(cTransmitString);		
		}
		uiServoPosition = uiServoPosition/21;
		ServoGoTo(uiServoPosition);
	}
 
}


	