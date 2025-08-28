//write the above same program for blinking, for P2.15 to P2.22
#include <LPC17xx.h>
int main() {
    int i, j;
    LPC_PINCON->PINSEL4 &= 0x3FFFFFFF;
    LPC_PINCON->PINSEL5 &= 0xFFFFC000;
    LPC_GPIO2->FIODIR = 0x007F8000;
    while (1) {
        LPC_GPIO2->FIOSET = 0x007F8000;
        for (i = 0; i < 1000; i++);
        LPC_GPIO2->FIOCLR = 0x007F8000;
        for (j = 0; j < 1000; j++);
    }
}