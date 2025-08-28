//Code for the execution for Binary Up Counter.
#include <LPC17xx.h>
int main() {
    unsigned long counter = 0;
    unsigned int i;
    LPC_PINCON->PINSEL3 &= 0x0000FFFF;
    LPC_GPIO1->FIODIR |= 0xFF000000;
    while (1) {
        LPC_GPIO1->FIOCLR = 0xFF000000;
        LPC_GPIO1->FIOSET = (counter << 24);
        counter++;
        for (i = 0; i < 1000000; i++);
    }
}