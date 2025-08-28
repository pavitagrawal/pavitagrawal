//write the above same program for blinking, for P1.24 to P1.31
#include <LPC17xx.h>
int main() {
    int i, j;
    LPC_PINCON->PINSEL3 &= 0x0000FFFF;
    LPC_GPIO1->FIODIR = 0xFF000000;
    while(1) {
        LPC_GPIO1->FIOSET = 0xFF000000;
        for (i = 0; i < 1000; i++);
        LPC_GPIO1->FIOCLR = 0xFF000000;
        for (j = 0; j < 1000; j++);
    }
}