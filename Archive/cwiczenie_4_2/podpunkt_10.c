/*4.2 cwiczenia podpunktu 11 */
#include <LPC21xx.H>
#define MILI 4615
#define LED3_bm 0x80000 

/*Miganie diody LED3 */
int main(){
	IO1DIR = IO1DIR|LED3_bm;
	while(1){
		IO1SET = IO1SET|LED3_bm;
		IO1CLR = IO1SET|LED3_bm;	
	}
}
