#define NULL 0
#define MAX_TOKEN_NR 4
#define MAX_KEYWORD_STRING_LTH 20
#define MAX_KEYWORD_NR 3

enum KeywordCode {MTM, KB, PPSW};
enum CompResult {DIFFERENT , EQUAL };
enum Stan {TOKEN,DELIMITER};
enum Result {OK, ERROR};
unsigned char ucTokenNr = 0;

union TokenValue {
	enum KeywordCode eKeyword; 
	unsigned int uiNumber;
	char *pcString;
};

enum TokenType {KEYWORD, NUMBER, STRING};
struct Token{
	enum TokenType eType;
	union TokenValue uValue;
};
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


enum CompResult eCompareString(char pcStr1[], char pcStr2[])
{
	unsigned char ucCharCounter;
	for(ucCharCounter=0;pcStr1[ucCharCounter] != '\0';ucCharCounter++)
	{
		if (pcStr1[ucCharCounter] != pcStr2[ucCharCounter]) return DIFFERENT;
	}
	return EQUAL;
}


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
 
void ReplaceCharactersInString(char pcString[], char cOldChar,char cNewChar) {
	unsigned char ucLoopCounter;
	for(ucLoopCounter = 0; pcString[ucLoopCounter]; ucLoopCounter++){
		if(pcString[ucLoopCounter] == cOldChar){
			pcString[ucLoopCounter] = cNewChar;
		}
	}
}



unsigned char ucFindTokensInString (char *pcString){
	unsigned char ucCharacterCounter;
	unsigned char ucCurrentCharacter;
	enum Stan eStan = DELIMITER;
	
	for(ucCharacterCounter=0;;ucCharacterCounter++){
		ucCurrentCharacter = pcString[ucCharacterCounter];
		switch(eStan){
			case TOKEN:
			{
				if(ucCurrentCharacter == ' '){
					eStan = DELIMITER;
				}
				else if((ucCurrentCharacter==NULL)|(ucTokenNr == MAX_TOKEN_NR)){
					return ucTokenNr;
				}
				break;
			}
			case DELIMITER:
			{
				if(ucCurrentCharacter != ' '){
					eStan = TOKEN;
					asToken[ucTokenNr].uValue.pcString = pcString + ucCharacterCounter;
					ucTokenNr = ucTokenNr + 1;

				}
				else if((ucCurrentCharacter==NULL)|(ucTokenNr == MAX_TOKEN_NR)){
					return ucTokenNr;
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




int main(){
	char pcString[35] = "Krzysztof Bolek mikroelektronika";
	DecodeMsg(pcString);
}

