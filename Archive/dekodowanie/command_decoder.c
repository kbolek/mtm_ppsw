#include "command_decoder.h"
#include "string.h"


struct Keyword asKeywordList[MAX_KEYWORD_NR]=
	{
		{CALLIB, "callib"},
		{GOTO, "goto"},
		{STEP, "step"}
	};
struct Token asToken[MAX_TOKEN_NR];
enum Stan {TOKEN,DELIMITER};
unsigned char ucTokenNr = 0;

unsigned char ucFindTokensInString(char *pcString){
	enum Stan eState = DELIMITER;
	unsigned char ucTokenCounter = 0;
	unsigned char ucCharCounter = 0;
	char cActualChar;
	
	for(ucCharCounter=0; pcString[ucCharCounter] != NULL; ucCharCounter++){
		cActualChar = pcString[ucCharCounter];
		switch(eState){
			case DELIMITER: 	
				if(cActualChar == DELIMITER_CHAR){
					eState = DELIMITER;
				}else if(ucTokenCounter < MAX_TOKEN_NR){
					eState = TOKEN;
					asToken[ucTokenCounter].uValue.pcString = pcString + ucCharCounter; 
					ucTokenCounter++;
				}else{
					return(ucTokenCounter);
				}
				break;
			case TOKEN: 
				if(cActualChar!= DELIMITER_CHAR){
					eState = TOKEN;
				}else{
					eState = DELIMITER;
				}
				break;
		}	
	}
	return(ucTokenCounter);
}

enum Result eStringToKeyword(char pcStr[],enum KeywordCode *peKeywordCode){
	unsigned char ucKeywordCounter;
	for(ucKeywordCounter=0;ucKeywordCounter<MAX_KEYWORD_NR;ucKeywordCounter++)
	{
		if (eCompareString(pcStr,asKeywordList[ucKeywordCounter].cString) == EQUAL) 
		{
			*peKeywordCode = asKeywordList[ucKeywordCounter].eCode;
			return OK;
		}
	}
	return ERROR;
};

void DecodeTokens(void){
	
	unsigned int uiNumber;
	unsigned char ucTokenIndex;
	enum KeywordCode eKeyword;
	
	for(ucTokenIndex=0; ucTokenIndex < ucTokenNr; ucTokenIndex++){
		if((eStringToKeyword (asToken[ucTokenIndex].uValue.pcString, &eKeyword))== OK){
			asToken[ucTokenIndex].eType = KEYWORD;
			asToken[ucTokenIndex].uValue.eKeyword=eKeyword;
		}else if((eHexStringToUInt(asToken[ucTokenIndex].uValue.pcString,&uiNumber))== OK){
			asToken[ucTokenIndex].eType = NUMBER;
			asToken[ucTokenIndex].uValue.uiNumber = uiNumber;		
		}else{
			asToken[ucTokenIndex].eType = STRING;
		}
	}
}

void DecodeMsg(char *pcString){

	ucTokenNr = ucFindTokensInString(pcString);
	ReplaceCharactersInString(pcString, ' ', NULL);
	DecodeTokens();
}

