#define MAX_TOKEN_NR 6
enum KeywordCode {MTM, KB, PPSW};
enum TokenType {KEYWORD, NUMBER, STRING};
union TokenValue {
	enum KeywordCode eKeyword; 
	unsigned int uiNumber;
	char *pcString;
};

struct Token{
	enum TokenType eType;
	union TokenValue uValue;
};

extern struct Token asToken[MAX_TOKEN_NR];

unsigned char ucFindTokensInString(char *pcString);
enum Result eStringToKeyword(char pcStr[],enum KeywordCode *peKeywordCode);
void DecodeTokens(void);
void DecodeMsg(char *pcString);
