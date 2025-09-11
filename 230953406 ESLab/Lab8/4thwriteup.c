
#include <LPC17xx.h>

int main() {
    unsigned long x, i, j;
    LPC_PINCON->PINSEL0 &= 0x00000000;       // Set all pins as GPIO
    LPC_GPIO0->FIODIR = 0xFF << 4;           // P0.4 to P0.11 as output (for LEDs)
    LPC_GPIO2->FIODIR &= ~(1 << 12);          // P0.0 as input (switch)
    while (1) {
        if ((LPC_GPIO2->FIOPIN & (1 << 12)) == 0) {
            // Switch OFF: count UP
            x = 0x00000001;
            for (i = 0; i < 8; i++) {
                LPC_GPIO0->FIOSET = x << 4;
                x = x << 1;
                for (j = 0; j < 1000000; j++);
            }
						x = 0x00000001;
            for (i = 0; i < 8; i++) {
                LPC_GPIO0->FIOCLR = x << 4; // clear others (optional)
                x = x << 1;
                for (j = 0; j < 1000000; j++);
            }
        } else {
            // Switch ON: count DOWN
            x = 0x80;  // Start from MSB for down count
            for (i = 0; i < 8; i++) {
                LPC_GPIO0->FIOSET = x << 4;
                x = x >> 1;
                for (j = 0; j < 1000000; j++);
            }
						x = 0x80;  // Start from MSB for down count
            for (i = 0; i < 8; i++) {
                LPC_GPIO0->FIOCLR = x << 4;
                x = x >> 1;
                for (j = 0; j < 1000000; j++);
            }
        }
    }
}
