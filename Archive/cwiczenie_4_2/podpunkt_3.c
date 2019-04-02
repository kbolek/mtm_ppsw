/*4.2 Cwiczenia */
#include <LPC21xx.H>


int main(){
	//ustawienie pinu 16 portu P1 jako wyjsciowy
	IO1DIR = 0x10000;
	//ustawienie pinu 16 portu P1 na 1
	IO1SET = 0x10000;
	//ustawienie pinu 16 portu P1 na 0
	IO1CLR = 0x10000;
	
	
	//wejscie w petle nieskonczona
	while(1){
		//realizacja podpunktu 3
		IO1SET = 0x10000;
		IO1CLR = 0x10000;
	}
	
	
}