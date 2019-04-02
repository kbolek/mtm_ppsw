/*4.2 cwiczenia podpunktn 9 */
#include <LPC21xx.H>
#include <stdio.h>
#define MILI 4615
#define LED0_bm 0x10000 //16 bit ma wartosc 1

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
		Delay(50);
		IO1SET = LED0_bm;
		Delay(50);
		IO1CLR = LED0_bm;
	}

}
