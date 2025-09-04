//Code for the execution for Binary Up Counter on P0.4 to P0.11.
#include <LPC17xx.h>
int main() {
    unsigned char x = 0;
		unsigned int i;
    LPC_PINCON->PINSEL0 &= 0xFF0000FF;
    LPC_GPIO0->FIODIR |= 0x00000FF0;
    while (1) {
        LPC_GPIO0->FIOPIN = x<<4;
        x = (x+1)%256;
				for(i=0;i<100000;i++);
    }
}