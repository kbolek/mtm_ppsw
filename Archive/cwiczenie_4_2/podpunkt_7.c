/*4.2 cwiczenia podpunktn 8 */
#include <LPC21xx.H>
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


/*Miganie diody z czestotliwoscia 10Hz */
int main(){
	IO1DIR = 0x10000;
	while(1){
		Delay(50);
		IO1SET = 0x10000;
		Delay(50);
	}
}
	
