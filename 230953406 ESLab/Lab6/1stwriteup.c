//Write an embedded C program to blink an LED.
#include <LPC17xx.h>
int main(){
	int i, j;
	LPC_PINCON->PINSEL0 &= 0xFF0000FF;
	LPC_GPIO0->FIODIR = 0x00000FF0;
	while(1){
		LPC_GPIO0->FIOSET = 0x00000FF0;
		for(i=0; i<1000; i++);
		LPC_GPIO0->FIOCLR = 0x00000FF0;
		for(j=0; j<1000; j++);
	}
}