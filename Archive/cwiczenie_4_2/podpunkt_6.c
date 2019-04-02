/*4.2 cwiczenia podpunkt 6 */
/*4.2 cwiczenia podpunkt 7 */
#include <LPC21xx.H>
#include <stdio.h>
#define MILI 4615

/*Funkcja odpowiedzialna za opoznienie
dla mojego kompilatora 1 ms to 4615 iteracji*/
void Delay(int iHowLong){
	unsigned long int uiIntCounter;
	char cCharIncrementation;
	for(uiIntCounter=0; uiIntCounter<(iHowLong*MILI);uiIntCounter++){
		cCharIncrementation++;
	}
}

int main(){
	while(1){
		Delay(1000);
		IO1SET = 0x10000;
		Delay(1000);
		IO1CLR = 0x10000;
	}
