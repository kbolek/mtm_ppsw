/*4.2 cwiczenia podpunktu 11 */
#include <LPC21xx.H>
#define MILI 4615
#define LED0_bm  0x10000 
#define LED1_bm  0x60000 
#define LED2_bm  0x40000 
#define LED3_bm 0x80000 

/*Zapalenie diod od 1 do 4 */
int main(){
	IO1DIR = IO1DIR|LED0_bm|LED1_bm|LED2_bm|LED3_bm;
	IO1SET = IO1SET|LED0_bm;
	IO1SET = IO1SET|LED1_bm;
	IO1SET = IO1SET|LED2_bm;
	IO1SET = IO1SET|LED3_bm;
}
