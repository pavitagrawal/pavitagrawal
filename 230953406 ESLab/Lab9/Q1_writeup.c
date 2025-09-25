//Write a C program for 4 digit BCD up/down counter on seven segment using a switch and timer with a delay of 1-second between each count.
#include <LPC17xx.h>

int main(void){
    unsigned long i, j, n;
		unsigned int x;
    unsigned long number = 0;
    unsigned long count = 0;
    unsigned char seven_seg[16] = {
        0x3F, 0x06, 0x5B, 0x4F,
        0x66, 0x6D, 0x7D, 0x07,
        0x7F, 0x6F, 0x77, 0x7C,
        0x39, 0x5E, 0x79, 0x71
    };

    LPC_PINCON->PINSEL0 = 0;
    LPC_GPIO0->FIODIR |= (0xFF << 4);
    LPC_PINCON->PINSEL3 = 0;
    LPC_GPIO1->FIODIR |= (0x0F << 23);
    LPC_GPIO0->FIODIR &= ~(1 << 21); // SWITCH MAPS to 7TH PIN FROM CNC (or CNX depending on wiring)

    while (1) {
        n = number;
				x = LPC_GPIO0->FIOPIN & (1 << 21);
			
        for (i = 0; i < 4; i++) {
            LPC_GPIO1->FIOCLR = (0x0F << 23);
            LPC_GPIO1->FIOSET = (i << 23);
            LPC_GPIO0->FIOCLR = (0xFF << 4);
            LPC_GPIO0->FIOSET = ((unsigned long)seven_seg[n % 10] << 4);
            n = n / 10;
            for (j = 0; j < 1000; j++);
            LPC_GPIO0->FIOCLR = (0xFF << 4);
        }

        count++;
        if (count == 1000) {
            count = 0;
            if (x) {
                number = (number + 1) % 10000;
            } else {
                if (number == 0) number = 9999;
                else number--;
            }
        }
    }
}
