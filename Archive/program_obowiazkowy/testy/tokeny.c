#include "tokeny.h"
#include "konwersje.h"
#include "lancuchy.h"
#define NULL 0
#define MAX_KEYWORD_STRING_LTH 30
#define MAX_KEYWORD_NR 3

enum Stan {TOKEN,DELIMITER};
enum Result {OK, ERROR};
enum CompResult {DIFFERENT , EQUAL };
unsigned char ucTokenNr = 0;

struct Token asToken[MAX_TOKEN_NR];

struct Keyword{
	enum KeywordCode eCode;
	char cString[MAX_KEYWORD_STRING_LTH+1];
};

struct Keyword asKeywordList[MAX_KEYWORD_NR] = {
	{MTM,"mikroelektronika"},
	{KB, "Krzysztof"},
	{PPSW, "programowanie"}
};


unsigned char ucFindTokensInString(char *pcString){
	unsigned char ucCharacterCounter;
	unsigned char ucCurrentCharacter;
	enum Stan eStan = DELIMITER;
	ucTokenNr = 0;
	
	for(ucCharacterCounter=0;;ucCharacterCounter++){
		ucCurrentCharacter = pcString[ucCharacterCounter];
		switch(eStan){
			case TOKEN:
			{
				if((ucCurrentCharacter==NULL)|(ucTokenNr == MAX_TOKEN_NR)){
					return ucTokenNr;
				}	
			  else if(ucCurrentCharacter == ' '){
					eStan = DELIMITER;
				}
				break;
				}
				
		
			case DELIMITER:
			{
				if((ucCurrentCharacter==NULL)|(ucTokenNr == MAX_TOKEN_NR)){
					return ucTokenNr;
				}
				else if(ucCurrentCharacter != ' '){
					eStan = TOKEN;
					asToken[ucTokenNr].uValue.pcString = pcString + ucCharacterCounter;
					ucTokenNr = ucTokenNr + 1;

				}

				break;
			}
		}
	}

};

enum Result eStringToKeyword(char pcStr[],enum KeywordCode *peKeywordCode){
	unsigned char ucKeywordCounter;
	for(ucKeywordCounter=0;ucKeywordCounter<MAX_TOKEN_NR;ucKeywordCounter++)
	{
		if (eCompareString(pcStr,asKeywordList[ucKeywordCounter].cString) == EQUAL) 
		{
			*peKeywordCode = asKeywordList[ucKeywordCounter].eCode;
			return OK;
		}
	}
	return ERROR;
};

void DecodeTokens() {
	unsigned char ucTokenCounter;
	struct Token *psCurrentToken;
	unsigned int uiTokenValue;
	enum KeywordCode eTokenCode;

	for(ucTokenCounter= 0; ucTokenCounter< ucTokenNr; ucTokenCounter++){
		psCurrentToken= &asToken[ucTokenCounter];

		if(OK == eStringToKeyword(psCurrentToken->uValue.pcString, &eTokenCode)){
			psCurrentToken->eType=KEYWORD;
			psCurrentToken->uValue.eKeyword=eTokenCode;
		}
		
		else if(OK == eHexStringToUInt(psCurrentToken->uValue.pcString, &uiTokenValue)){
			psCurrentToken->eType = NUMBER;
			psCurrentToken->uValue.uiNumber = uiTokenValue;
		}
		
		else{
			psCurrentToken->eType=STRING;
		}
	}
	}

void DecodeMsg(char *pcString){

	ucTokenNr = ucFindTokensInString(pcString);
	ReplaceCharactersInString(pcString, ' ', NULL);
	DecodeTokens();
}
