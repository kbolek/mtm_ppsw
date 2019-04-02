/*4.2 cwiczenia podpunktu 22 */
#include <LPC21xx.H>
#define LED0_bm  0x10000
#define LED1_bm  0x20000 
#define LED2_bm  0x40000
#define LED3_bm 0x80000
#define MILI 4615

/*Zmienna enum do okreslenia kierunku przesuniecia punktu swietlnego*/
enum DIRECTION {LEFT,RIGHT};

/*Funkcja odpowiedzialna za opoznienie
dla mojego kompilatora 1 ms to 4615 iteracji*/
void Delay(int iHowLong){
	unsigned long int uiIntCounter;
	char cCharIncrementation;
	for(uiIntCounter=0; uiIntCounter<(iHowLong*MILI);uiIntCounter++){
		cCharIncrementation++;
	}
}

/*Funkcja zapalajaca diode LED o podanym argumencie */
void LedOn(int Number){
	IO1CLR = IO1SET;
	switch(Number){
		case 0:
			IO1SET = IO1SET|LED0_bm;
			break;
		case 1:
			IO1SET = IO1SET|LED1_bm;
			break;
		case 2:
			IO1SET = IO1SET|LED2_bm;
			break;
		case 3:
			IO1SET = IO1SET|LED3_bm;
			break;
	}	
}

/*Funkcja która ustawia piny podpiete do LED0-LED3 na wyjsciowe
i zapala LED0*/
void LedInit(){
		IO1DIR = IO1DIR|LED0_bm|LED1_bm|LED2_bm|LED3_bm;
		LedOn(0);
	
}
/* Funkcja przesuwajaca o jeden punkt w prawo albo w lewo w zaleznosci
od argumentu enum*/
void LedStep(enum DIRECTION eWhere){
	static unsigned int uiActualLedPoint = 0; 
	if(eWhere == RIGHT){
		++uiActualLedPoint;
		LedOn(uiActualLedPoint%4);
	}
	else if (eWhere == LEFT){
		--uiActualLedPoint;
		LedOn(uiActualLedPoint%4);
	}
}


int main(){
	LedInit();
	//przesunie LED0 na LED1
	while(1){
		int iCount;
		for(iCount=0;iCount<=9;iCount++){
			LedStep(RIGHT);
			Delay(50);
		}
		for(iCount=0;iCount<=9;iCount++){
			LedStep(LEFT);
			Delay(50);
		}	
	}
	
}
