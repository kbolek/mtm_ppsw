#include "lancuchy.h"
#include "konwersje.h"
#include "tokeny.h"

enum Result {OK,ERROR};
enum CompResult {DIFFERENT,EQUAL};
enum Result Test1, Test2, Test3, Test4, Test5, Test6, Test7, Test8, Test9, Test10, Test11;

//Testowanie funkcji z programu obowiazkowego - lancuchy znakowe - operacje proste

enum Result eTestOf_CopyString(){
	char pcTestSourceNormal[10] = "Krzysztof";
	char pcTestDestNormal[10];
	char pcTestSourceExtreme[3] = "";
	char pcTestDestExtreme[3];
	//Test0 Sprawdzenie dla wlasciwego przypadku
	CopyString(pcTestSourceNormal,pcTestDestNormal);
	if((eCompareString(pcTestSourceNormal,pcTestDestNormal)) == DIFFERENT){
		return ERROR;
	}
	//Test1 Sprawdzenie dla skrajnego przypadku
	else if((eCompareString(pcTestSourceExtreme,pcTestDestExtreme)) == DIFFERENT){
		return ERROR;
	}
	return OK;
}

enum Result eTestOf_eCompareString(){
	char pcTest1Normal[] = "Krzysztof";
	char pcTest2Normal[] = "Bolek";
	char pcTest3Extreme[] = "";
	char pcTest4Extreme[] = "";
	//Test0 Sprawdzenie dwoch poprawnych przypadkow
	if(eCompareString(pcTest1Normal,pcTest2Normal) == EQUAL){
		return ERROR;
	}
	//Test1 Sprawdzenie dla skrajnego przypadku
	else if(eCompareString(pcTest3Extreme,pcTest4Extreme) == DIFFERENT){
		return ERROR;
	}
	return OK;	
}

enum Result eTestOf_AppendString(){
	unsigned char ucCharCounter;
	char cTestDestNormal[15] = "Krzysztof";
	char cTestSourceNormal[] = " Bolek";
	char cTestDestExtreme[15] = "Skrajny";
	char cTestSourceExtreme[]= " ";
	char cWynikExtreme[15] = "Skrajny ";
	char cWynikNormal[15] = "Krzysztof Bolek";
	AppendString(cTestSourceNormal,cTestDestNormal);
	AppendString(cTestSourceExtreme,cTestDestExtreme);

	for(ucCharCounter=0;ucCharCounter<15;ucCharCounter++){
		//Test0 Sprawdzenie dodawania stringu dla poprawnych przypadkow
		if(cTestDestNormal[ucCharCounter] != cWynikNormal[ucCharCounter]){
			return ERROR;
		}
		//Test1 Sprawdzenie dodawania stringu dla skrajnych przypadkow
		else if(cTestDestExtreme[ucCharCounter] != cWynikExtreme[ucCharCounter]){
			return ERROR;
		}
	}
	return OK;	
}

enum Result eTestOf_ReplaceCharactersInString(){
	unsigned char ucCharCounter;
	char pcTestStringNormal[] = "Krzysztuf";
	char cWynikNormal[] = "Krzysztof";
	char pcTestStringExtreme[] = "Bolekz";
	char cWynikExtreme[] = "Bolek ";
	//Test0 - sprawdza zmiane znakow dla poprawnego przypadku
	ReplaceCharactersInString(pcTestStringNormal,'u','o');
	for(ucCharCounter=0;pcTestStringNormal[ucCharCounter]!='\0';ucCharCounter++){
		if(pcTestStringNormal[ucCharCounter] != cWynikNormal[ucCharCounter]){
			return ERROR;
		}
	}
	//Test1 - sprawdza zmiane znakow dla skrajnego przypadku
	ReplaceCharactersInString(pcTestStringExtreme,'z',' ');
	for(ucCharCounter=0;pcTestStringExtreme[ucCharCounter]!='\0';ucCharCounter++){
		if(pcTestStringExtreme[ucCharCounter] != cWynikExtreme[ucCharCounter]){
			return ERROR;
		}
	}

		return OK;
}
//KONIEC TESTOW LANCUCHOW ZNAKOWYCH - OPERACJI PROSTYCH

//Testowanie funkcji z konwersji
enum Result eTestOf_UIntToHexStr(){
	unsigned char ucCharCounter;
	char pcStrNormal[6];
	char pcStrTestNormal[6] = "0x0309";
	char pcStrExtreme[6];
	char pcStrTestExtreme[6] = "0xF0A9";
	UIntToHexStr(0x309,pcStrNormal);
	UIntToHexStr(0xF0A9,pcStrExtreme);		
	for(ucCharCounter=0;ucCharCounter<6;ucCharCounter++){
		//Test0- zamiana inta na hexa przy poprawnym przypadku
		if(pcStrNormal[ucCharCounter] != pcStrTestNormal[ucCharCounter]){
			return ERROR;
		}
		//Test01- zamiana inta na hexa przy skrajnym przypadku
		else if(pcStrExtreme[ucCharCounter] != pcStrTestExtreme[ucCharCounter]){
			return ERROR;
		}
	}	
		return OK;
}

enum Result eTestOf_eHexStringToUInt(){
	unsigned int puiValueNormal, puiValueTooLong,puiValueUnappropriate, puiValueExtreme;
	//Test0 - Sprawdza zamiane hexa na inta przy poprawnych danych
	eHexStringToUInt("0x309",&puiValueNormal);
	if(puiValueNormal != 0x309){
		return ERROR;
	}
	//Test1 - Sprawdza warunek dla zbyt duzego hexa (powyzej 4 cyfer)
	eHexStringToUInt("0x30915",&puiValueTooLong);
	if(puiValueTooLong == 0x30915){
		return ERROR;
	}
	//Test2 - Sprawdza warunek dla niewiasciwego formatu hexa
	eHexStringToUInt("309",&puiValueUnappropriate);
	if(puiValueUnappropriate == 0x309){
		return ERROR;
	}
	//Test3 - Sprawdza skrajne cyfry
	eHexStringToUInt("0xAF89",&puiValueExtreme);
	if(puiValueExtreme != 0xAF89){
		return ERROR;
	}
	
	return OK;	
}

enum Result eTestOf_AppendUIntToString(){  
	unsigned char ucCharCounter;
	unsigned int uiNumber = 0x3091;
	char pcString[33] = "Moja szczesliwa liczba to:";
	char pcStringTest[33] = "Moja szczesliwa liczba to:0x3091";
	AppendUIntToString(uiNumber,pcString);
	for(ucCharCounter=0;ucCharCounter<36;ucCharCounter++){
		//Test0- zamiana inta na hexa przy poprawnym przypadku
		if(pcString[ucCharCounter] != pcStringTest[ucCharCounter]){
			return ERROR;
		}
	}
	//Test1 - czy nadpisuje na koncu null'u lancucha
		if(pcString[32] != '\0'){
			return ERROR;
		}
		
		return OK;
}
//KONIEC TESTOW FUNKCJI Z KONWERSJI

//Testowanie funkcji z tokenow
enum Result eTestOf_ucFindTokensInString(){
	char cToken1Test[]= "     ";
	char cToken2Test[] = " Delimeter przed pierwszym";
	char cToken3Test[] = "Wiecej niz  jeden delimter";
	unsigned char wynik;
	//Test0 Szukanie tokenow w pustym stringu
	wynik = ucFindTokensInString(cToken1Test);
	if(wynik != 0){
		return ERROR;
	}
	//Test1 Szukanie tokenow kiedy pierwszy znak stringu to delimeter
	wynik = ucFindTokensInString(cToken2Test);
	if(wynik != 3){
		return ERROR;
	}
	//Test2 Szukanie tokenow kiedy sa dwa delimetery w srodku stringu
	wynik = ucFindTokensInString(cToken3Test);
	if(wynik != 4){
		return ERROR;
	}		
	return OK;
}

/*
struct Keyword asKeywordList[MAX_KEYWORD_NR] = {
	{MTM,"mikroelektronika"},
	{KB, "Krzysztof"},
	{PPSW, "programowanie"}
};*/

enum Result eTestOf_eStringToKeyword(){
	char cTestNormal[] = "mikroelektronika";
	char cTestUnappropriate[] = "systemywbudowane";
	char cTestUnappropriate2[] = "Krzysztoffff";
	enum KeywordCode eKeywordCodeNormal, eKeyWordCodenappropriate,eKeyWordCodenappropriate2;
	
	//Test0 poprawny Keyword
	eStringToKeyword(cTestNormal,&eKeywordCodeNormal);
	if (eKeywordCodeNormal != MTM){ 
		return ERROR;
	}
	//Test1 Brak takiego keyworda na li[cie
	eStringToKeyword(cTestUnappropriate,&eKeyWordCodenappropriate);
	if (eKeyWordCodenappropriate == PPSW){ 
		return ERROR;
	}
	//Test2 Pomylony Keyword
	eStringToKeyword(cTestUnappropriate2,&eKeyWordCodenappropriate2);
	if (eKeyWordCodenappropriate2 == KB){ 
		return ERROR;
	}
	else 
		return OK;
}

enum Result eTestOf_DecodeTokens(){
	struct Token *psCurrentToken;
	asToken[0].uValue.pcString = "Krzysztof";
	asToken[1].uValue.pcString = "Bolek";
	asToken[2].uValue.pcString = "0x3091";
	DecodeTokens();
	
	//Test0 - dekodowanie tokenu typu Keyword
	psCurrentToken = &asToken[0];
	if(psCurrentToken->eType != KEYWORD){
		return ERROR;
	}
	else if (psCurrentToken->uValue.eKeyword != KB){
		return ERROR;
	}
	//Test1 - dekodowanie tokenu typu STRING
	else if((psCurrentToken+1)->eType != STRING){
		return ERROR;
	}
	else if(eCompareString("Bolek",(psCurrentToken+1)->uValue.pcString) == DIFFERENT){
		return ERROR;
	}
	//Test2 - dekodowanie tokenu typu NUMBER
	else if((psCurrentToken+2)->eType != NUMBER){
			return ERROR;
	}
	else if((psCurrentToken+2)->uValue.uiNumber != 0x3091){
		return ERROR;
	}
	
return OK;
}

enum Result eTestOf_DecodeMsg(){
	struct Token *psCurrentToken;
	//Test0 Skrajny lancuch do zdekodowania
	char pcStringExtreme[] = "  Krzysztof MTM  3091 0x3091";
	DecodeMsg(pcStringExtreme);
	//Test01 - dekodowanie tokenu typu Keyword
	psCurrentToken = &asToken[0];
	if(psCurrentToken->eType != KEYWORD){
		return ERROR;
	}
	else if (psCurrentToken->uValue.eKeyword != KB){
		return ERROR;
	}
	//Test02 dekodowanie tokenu typu STRING
	else if((psCurrentToken+1)->eType != STRING){
		return ERROR;
	}
	else if(eCompareString("MTM",(psCurrentToken+1)->uValue.pcString) == DIFFERENT){
		return ERROR;
	}
	//Test03-dekodowanie tokenu typu NUMBER
	else if((psCurrentToken+2)->eType != STRING){
			return ERROR;
	}
	else if(eCompareString("3091",(psCurrentToken+2)->uValue.pcString) == DIFFERENT){
		return ERROR;
	}
	//Test04-dekodowanie tokenu typu NUMBER
	else if((psCurrentToken+3)->eType != NUMBER){
			return ERROR;
	}
	else if((psCurrentToken+3)->uValue.uiNumber != 0x3091){
		return ERROR;
	}
	
	return OK;
}


//KONIEC TESTOW FUNKCJI Z TOKENOW

int main(void) {
	//TESTY FUNKCJI - LANCUCHY ZNAKOWE - OPERACJE PROSTE
	Test1 = eTestOf_CopyString();
	Test2 = eTestOf_eCompareString();
	Test3 = eTestOf_AppendString(); 
	Test4 = eTestOf_ReplaceCharactersInString();
	//TESTY FUNKCJI - KONWERSJE
	Test5 = eTestOf_UIntToHexStr();
	Test6 = eTestOf_eHexStringToUInt();
	Test7 = eTestOf_AppendUIntToString();
	//TESTY FUNKCJI - TOKENY
	Test8 = eTestOf_ucFindTokensInString();
	Test9 = eTestOf_eStringToKeyword();
	Test10 = eTestOf_DecodeTokens();
	Test11 = eTestOf_DecodeMsg();
}
