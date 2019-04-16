#include "konwersje.h"
#define NULL 0

void UIntToHexStr(unsigned int uiValue, char pcStr[]){

	unsigned char ucTetradCounter;
	unsigned char ucCurrentHex;

	pcStr[0]='0';
	pcStr[1]='x';
	pcStr[6] = NULL;

	for(ucTetradCounter = 0; ucTetradCounter<4; ucTetradCounter++){
		ucCurrentHex = (uiValue >> (ucTetradCounter*4)) & 0xF;
		if(ucCurrentHex < 10){
			pcStr[5-ucTetradCounter] = '0' + ucCurrentHex;
		}
		else{
			pcStr[5-ucTetradCounter] = 'A' + (ucCurrentHex-10);
		}
	}
}
/*------------------------------------------------------------------ */

enum Result {OK, ERROR};
enum Result eHexStringToUInt(char pcStr[],unsigned int *puiValue){
	unsigned char ucHexCounter, ucHexCurrentNumber; 
	
	if(pcStr[0] != '0' || pcStr[1] != 'x' || pcStr[2] == NULL){
		return ERROR;
	}
	*puiValue = 0;
	for(ucHexCounter = 2; pcStr[ucHexCounter] != NULL; ucHexCounter++){
		ucHexCurrentNumber = pcStr[ucHexCounter];
		
		if(ucHexCurrentNumber == 6){
			return ERROR;
		}
		*puiValue = *puiValue << 4;
		if((ucHexCurrentNumber >= '0') && (ucHexCurrentNumber <= '9') ){	
			 *puiValue = *puiValue | (ucHexCurrentNumber - '0');
		}
		else if((ucHexCurrentNumber >= 'A') && (ucHexCurrentNumber <= 'F')){
			  *puiValue = *puiValue	| (ucHexCurrentNumber - 'A' + 10);
		}
	}
	return OK;
}

/*------------------------------------------------------------------ */
void AppendUIntToString(unsigned int uiValue, char pcDestinationStr[]){
	unsigned char ucHowLongIsDestStr;
	for(ucHowLongIsDestStr=0;pcDestinationStr[ucHowLongIsDestStr]!= NULL;ucHowLongIsDestStr++){ }
	UIntToHexStr(uiValue, &pcDestinationStr[ucHowLongIsDestStr]);
}



