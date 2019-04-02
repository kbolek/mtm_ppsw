/*4.2 cwiczenia podpunktu 17 */
#include <LPC21xx.H>
#define S0 0x10
#define S1 0x20
#define S2 0x40
#define S3 0x80
#define LED0_bm  0x10000
#define LED1_bm  0x20000 
#define LED2_bm  0x40000 
#define LED3_bm 0x80000 


/*Funkcja zwracajaca stan przycisku S1 */
int iReadButton1(){
	enum ButtonState {RELEASED,PRESSED}; 
	enum ButtonState iReturnNumber = RELEASED;
	iReturnNumber = ((IO0PIN&S1)== S1) ? PRESSED: RELEASED;
	return iReturnNumber;
}

/*Funkcja ustawiajaca wszystkie piny przyciskow S1-S4 na wejscie */
void KeyboardInit(){
	IO0DIR = IO0DIR&(~(|S0|S1|S2|S3)); 
}

/*Funkcja zapalajaca diode LED o podanym argumencie */
void LedOn(int Number){
	switch(Number){
		//etykiety zapalajace poszczegolne diody
		case 0:
			IO1SET = IO1SET|LED0_bm;
			break;
		case 1:
			IO1SET = IO1SET|LED1_bm;
			break;
	}
	
}
int main(){
	int iGiveANumber;
	IO1DIR = IO1DIR|LED0_bm|LED1_bm;
	KeyboardInit();
	IO0SET = IO0SET|S1;
	iGiveANumber = iReadButton1();
	LedOn(iGiveANumber);	
}
