#include "lancuchy.h"

enum CompResult { DIFFERENT, EQUAL };

void CopyString(char pcSource[], char pcDestination[]) {
	unsigned char ucCountCharPosition;
		for(ucCountCharPosition = 0; pcSource[ucCountCharPosition]; ucCountCharPosition++) {
			pcDestination[ucCountCharPosition] = pcSource[ucCountCharPosition];
	}
		pcDestination[ucCountCharPosition] = '\0';

}

int eCompareString(char pcStr1[],  char pcStr2[]) {
	unsigned char ucLoopCounter;
	for (ucLoopCounter = 0; pcStr1[ucLoopCounter]; ucLoopCounter++) {
		if(pcStr1[ucLoopCounter] != pcStr2[ucLoopCounter]) {
			return DIFFERENT;
		}
	}
	if(pcStr1[ucLoopCounter] != pcStr2[ucLoopCounter]) {
			return DIFFERENT;
		}
		
	return EQUAL;
}

void AppendString (char pcSourceStr[],char pcDestinationStr[])
{
	unsigned char ucEndPointer,something;
	for(ucEndPointer=0;pcDestinationStr[ucEndPointer]!='\0';ucEndPointer++) {
		something++;
	}
	CopyString(pcSourceStr,pcDestinationStr+ucEndPointer);
}


void ReplaceCharactersInString(char pcString[], char cOldChar, char cNewChar) {
	unsigned char ucLoopCounter;
	for(ucLoopCounter = 0; pcString[ucLoopCounter]; ucLoopCounter++){
		if(pcString[ucLoopCounter] == cOldChar){
			pcString[ucLoopCounter] = cNewChar;
		}
	}
}
