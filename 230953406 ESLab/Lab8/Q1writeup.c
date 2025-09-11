#include <LPC17xx.h>
int main(){
	unsigned long i;
	LPC_PINCON->PINSEL0=0x00000000;
	LPC_GPIO0->FIODIR=0xFF<<15;
	while(1){
		LPC_GPIO0->FIOSET = 0xFF<<15;
		for(i=0;i<1000000;i++);
		LPC_GPIO0->FIOCLR = 0xFF<<15;
		for(i=0;i<1000000;i++);
	}
}