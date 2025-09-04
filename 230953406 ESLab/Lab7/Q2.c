//Connect a key on P1.23 and LEDs on P0.4 to P0.11. Write a program to display the no. of times the switch is pressed on LEDs.
#include <LPC17xx.h>

int main() {
    unsigned char count = 0;
    unsigned int i;
    unsigned char prev_switch_state = 1; // Assume switch is open initially (active low)

    // Configure P0.4 to P0.11 as output for LEDs
    LPC_PINCON->PINSEL0 &= 0xFF0000FF; // Clear bits for P0.4 to P0.11
    LPC_GPIO0->FIODIR |= 0x00000FF0;   // Set P0.4 to P0.11 as output

    // Configure P1.23 as input for the switch
    LPC_PINCON->PINSEL3 &= ~(0x3 << 14); // Clear bits for P1.23 (ensure GPIO function)
    LPC_GPIO1->FIODIR &= ~(1 << 23);    // Set P1.23 as input

    while (1) {
        // Read current switch state (assuming active low switch)
        unsigned char current_switch_state = (LPC_GPIO1->FIOPIN >> 23) & 0x01;

        // Debounce and detect falling edge (switch press)
        if (current_switch_state == 0 && prev_switch_state == 1) {
            // Wait for a short delay for debouncing
            for (i = 0; i < 50000; i++); // Adjust delay as needed

            // Re-read switch state after debounce delay
            current_switch_state = (LPC_GPIO1->FIOPIN >> 23) & 0x01;

            if (current_switch_state == 0) {
                count = (count + 1) % 256;
            }
        }
        prev_switch_state = current_switch_state;
        LPC_GPIO0->FIOPIN = (count << 4);
		}
}