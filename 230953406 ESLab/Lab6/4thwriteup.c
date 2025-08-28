//Code for the execution for Johnson Counter.
#include <LPC17xx.h>
int main(){
	unsigned long x, i;
    LPC_PINCON->PINSEL3 &= 0x0000FFFF;
    LPC_GPIO1->FIODIR = 0xFF000000;
    while(1) {
		x = 0x01000000;
		for(i=0; i<8; i++){
			LPC_GPIO1->FIOSET = x;
			x = x<<1;
		}
		for(i=0; i<1000; i++);
		x = 0x01000000;
		for(i=0; i<8; i++){
			LPC_GPIO1->FIOCLR = x;
			x = x<<1;
		}
		for(i=0; i<1000; i++);
    }
}