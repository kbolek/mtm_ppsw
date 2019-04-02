/*4.2 cwiczenia podpunktu 19 */
#include <LPC21xx.H>
#define S0 0x10
#define S1 0x20
#define S2 0x40
#define S3 0x80
#define LED0_bm  0x10000
#define LED1_bm  0x20000 
#define LED2_bm  0x40000
#define LED3_bm 0x80000

/*Funkcja ustawiajaca wszystkie piny przyciskow S1-S4 na wejscie */
void KeyboardInit(){
	IO0DIR = IO0DIR&(~(S0|S1|S2|S3)); //bez modyfikacji innych bitow rejestru
}

/*W zaleznosci od przycisku zwraca taka wartosc */
int eKeyboardRead(){
	enum KeyboardState {RELEASED,BUTTON_1,BUTTON_2,BUTTON_3,BUTTON_4};
	enum KeyboardState eReturnNumber = RELEASED;
	KeyboardInit();
	if(S0 ==(~IO0PIN & S0)){
		eReturnNumber = BUTTON_1;
	}
	else if(S1 == (~IO0PIN&S1)){
		eReturnNumber = BUTTON_2;
	}
	else if(S2 == (~IO0PIN&S2)){
		eReturnNumber = BUTTON_3;
	}
	else if (S3 == (~IO0PIN&S3)){
		eReturnNumber = BUTTON_4;
	}
	
	return eReturnNumber;
}



/*Funkcja zapalajaca diode LED o podanym argumencie */
void LedOn(int Number){
	switch(Number){
		case 1:
			IO1SET = IO1SET|LED0_bm;
			break;
		case 2:
			IO1SET = IO1SET|LED1_bm;
			break;
		case 3:
			IO1SET = IO1SET|LED2_bm;
			break;
		case 4:
			IO1SET = IO1SET|LED3_bm;
			break;
	}
	
}
int main(){
	int GiveANumber;
	IO1DIR = IO1DIR|LED0_bm|LED1_bm|LED2_bm|LED3_bm;
	KeyboardInit();
	GiveANumber = eKeyboardRead();
	LedOn(GiveANumber);	
}
