/*4.2 cwiczenia podpunkt 4,5 */
#include <LPC21xx.H>

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
	IO1DIR = 0x10000;
	IO1SET = 0x10000;
	Delay();
	IO1CLR = 0x10000;

}
