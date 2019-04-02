#include <LPC21xx.H>

enum CompResult { DIFFERENT, EQUAL };

void CopyString(unsigned char pcSource[], unsigned char pcDestination[]) {
	unsigned char ucCountCharPosition;
		for(ucCountCharPosition = 0; pcSource[ucCountCharPosition]; ucCountCharPosition++) {
			pcDestination[ucCountCharPosition] = pcSource[ucCountCharPosition];
	}
		pcDestination[ucCountCharPosition] = '\0';

}

int eCompareString(unsigned char pcStr1[], unsigned char pcStr2[]) {
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

void AppendString(unsigned char pcSourceStr[], unsigned char pcDestinationStr[]){
	unsigned char ucLoopCounter;
	for(ucLoopCounter = 0; pcDestinationStr[ucLoopCounter]; ++ucLoopCounter){
	} 
	CopyString(pcSourceStr, pcDestinationStr + ucLoopCounter);
}

void ReplaceCharactersInString(unsigned char pcString[],unsigned char cOldChar,unsigned char cNewChar) {
	unsigned char ucLoopCounter;
	for(ucLoopCounter = 0; pcString[ucLoopCounter]; ucLoopCounter++){
		if(pcString[ucLoopCounter] == cOldChar){
			pcString[ucLoopCounter] = cNewChar;
		}
	}
}


int main(){
	unsigned char ucName[] = "Krzysztof";
	unsigned char ucSurname[] = "Bolek";
	unsigned char ucNewName[14];
	CopyString(ucName,ucNewName);
	AppendString(ucSurname,ucNewName);
	ReplaceCharactersInString(ucNewName,'t','m');	
}









