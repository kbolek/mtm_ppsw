#include "lancuchy.h"
#include "konwersje.h"
#include "tokeny.h"

enum Result {OK,ERROR};
enum CompResult {DIFFERENT,EQUAL};
enum Result Test1, Test2, Test3, Test4, Test5, Test6, Test7, Test8, Test9, Test10, Test11;

//Testowanie funkcji z programu obowiazkowego - lancuchy znakowe - operacje proste
enum Result eTestOf_CopyString(){
	unsigned char ucCharCounter;
	char pcTestSource[10] = "Krzysztof";
	char pcTestDest[10];
	//Test1 - sprawdza czy dobrze kopiuje stringi
	CopyString(pcTestSource,pcTestDest);
	for(ucCharCounter=0;ucCharCounter<9;ucCharCounter++){
		if(pcTestDest[ucCharCounter] != pcTestSource[ucCharCounter]){
			return ERROR;
		}
	}
	return OK;
}

enum Result eTestOf_eCompareString(){
	char pcTest1[] = "Krzysztof";
	char pcTest2[] = "Bolek";
	//Test2 - sprawdza czy funkcja dobrze porownuje stringi
	if(eCompareString(pcTest1,pcTest2) == EQUAL){
		return ERROR;
	}
	else{
		return OK;
	}
}

enum Result eTestOf_AppendString(){
	char cTestDest[15] = "Krzysztof";
	char cTestSource[] = " Bolek";
	char cWynik[15] = "Krzysztof Bolek";
	//Test3 - sprawdza czy funkcja dobrze dopisuje stringi
	AppendString(cTestSource,cTestDest);
	if(eCompareString(cTestDest,cWynik) == DIFFERENT){
		return ERROR;
	}
	else{
	return OK;
	}
}

enum Result eTestOf_ReplaceCharactersInString(){
	char pcTestString[] = "Krzysztuf";
	char cWynik[] = "Krzysztof";
	//Test4 - sprawdza czy funkcja dobrze zamienia lancuch znakow
	ReplaceCharactersInString(pcTestString,'u','o');
	if(eCompareString(pcTestString,cWynik) == DIFFERENT){
		return ERROR;
	}
	else{
		return OK;
	}
}
//KONIEC TESTOW LANCUCHOW ZNAKOWYCH - OPERACJI PROSTYCH

//Testowanie funkcji z konwersji
enum Result eTestOf_UIntToHexStr(){
	unsigned int uiValue = 777; 
	char pcStr[6];
	char pcStrTest[6] = "0x0309";
	//Test5- sprawdza czy funkcja zamienia inta na hexa
	UIntToHexStr(uiValue,pcStr);	
	if(eCompareString(pcStr,pcStrTest) == DIFFERENT){
		return ERROR;
	}
	else{
		return OK;
	}
}

enum Result eTestOf_eHexStringToUInt(){
	unsigned int puiValue;
	char pcStr[7] = "0x309";
	//Test6- sprawdza czy funkcja dobrze zaienia hexa na inta	
	eHexStringToUInt(pcStr,&puiValue);
	if(puiValue != 777){
		return ERROR;
	}
	else{
		return OK;
	}
}

enum Result eTestOf_AppendUIntToString(){  
	unsigned int uiNumber = 0x3091;
	char pcString[35] = "Moja szczesliwa liczba to:";
	char pcStringTest[35] = "Moja szczesliwa liczba to:0x3091";
	//Test7 - sprawdza czy funkcja dodaje hexa do stringa
	AppendUIntToString(uiNumber,pcString);
	if(eCompareString(pcString,pcStringTest) == DIFFERENT){
		return ERROR;
	}
	else{
		return OK;
	}
}
//KONIEC TESTOW FUNKCJI Z KONWERSJI

//Testowanie funkcji z tokenow
enum Result eTestOf_ucFindTokensInString(){
	char cToken1Test[]= "     ";
	char cToken2Test[] = " Delimeter przed pierwszym";
	char cToken3Test[] = "Wiecej niz  jeden delimter";
	unsigned char wynik;
	//Test8 - sprawdza czy funkcja zwraca poprawna ilosc tokenow
	wynik = ucFindTokensInString(cToken1Test);
	if(wynik != 0){
		return ERROR;
	}
	wynik = ucFindTokensInString(cToken2Test);
	if(wynik != 3){
		return ERROR;
	}
	wynik = ucFindTokensInString(cToken3Test);
	if(wynik != 4){
		return ERROR;
	}		
	return OK;
}

enum Result eTestOf_eStringToKeyword(){
	char cTest[] = "mikroelektronika ";
	enum KeywordCode eKeywordCode;
	//Test9 - sprawdzanie czy funkcja poprawnie zamienia lancuchy znakow na keywordy
	ReplaceCharactersInString(cTest,' ','\0');
	eStringToKeyword(cTest,&eKeywordCode);
	if (eKeywordCode != MTM) 
		return ERROR;
	else 
		return OK;
}

enum Result eTestOf_DecodeTokens(){
	char cTest[] = "Krzysztof Bolek 0x3091";
	struct Token *psCurrentToken;
	//Test10 -sprawdzanie czy funkcja poprawnie dekoduje tokeny
	ucFindTokensInString(cTest);
	ReplaceCharactersInString(cTest,' ','\0');
	DecodeTokens();
	psCurrentToken = &asToken[0];
	if(psCurrentToken->eType != KEYWORD){
		return ERROR;
	}
	else if (psCurrentToken->uValue.eKeyword != KB){
		return ERROR;
	}
	psCurrentToken = &asToken[1];
	if(psCurrentToken->eType != STRING){
		return ERROR;
	}
	psCurrentToken = &asToken[2];
	if(psCurrentToken->eType != NUMBER){
			return ERROR;
	}
	
return OK;
}

//KONIEC TESTOW FUNKCJI Z TOKENOW

int main(void){
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
}
