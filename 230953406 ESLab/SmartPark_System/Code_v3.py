#include <stdio.h>
#include <LPC17xx.h>
#include <string.h>

#define LED_Pinsel 0xFF        // P0.4–P0.11 (LEDs)
#define TRIGGER_PIN (1 << 15)  // P0.15 (Trigger)
#define ECHO_PIN (1 << 16)     // P0.16 (Echo)

// New additional GPIO pins
#define EXT_LED_P1_MASK ((1 << 23) | (1 << 24) | (1 << 25) | (1 << 26))
#define EXT_LED_P2_MASK ((1 << 10) | (1 << 11) | (1 << 12) | (1 << 13))

char ans[20] = "";
int temp, temp1, temp2 = 0;
int flag = 0, flag_command = 0;
int i, j, k, l, r, echoTime = 5000;
float distance = 0;
int b;

void lcd_wr(void);
void port_wr(void);
void delay(int r1);
void timer_start(void);
float timer_stop(void);
void timer_init(void);
void delay_in_US(unsigned int microseconds);

// ---------------- Delay in Microseconds ----------------
void delay_in_US(unsigned int microseconds) {
    LPC_TIM0->TCR = 0x02;                  // Reset Timer
    LPC_TIM0->PR = 0;                      // Prescaler = 0
    LPC_TIM0->MR0 = microseconds - 1;      // Match register
    LPC_TIM0->MCR = 0x01;                  // Interrupt on match
    LPC_TIM0->TCR = 0x01;                  // Start timer
    while ((LPC_TIM0->IR & 0x01) == 0);    // Wait for interrupt flag
    LPC_TIM0->TCR = 0x00;                  // Stop timer
    LPC_TIM0->IR = 0x01;                   // Clear flag
}

// ---------------- Timer Initialization ----------------
void timer_init(void) {
    LPC_TIM0->CTCR = 0x0;
    LPC_TIM0->PR = 11999999;   // 12 MHz base
    LPC_TIM0->TCR = 0x02;      // Reset timer
}

// ---------------- Timer Start ----------------
void timer_start(void) {
    LPC_TIM0->TCR = 0x02;  // Reset
    LPC_TIM0->TCR = 0x01;  // Enable
}

// ---------------- Timer Stop ----------------
float timer_stop(void) {
    LPC_TIM0->TCR = 0x0;
    return LPC_TIM0->TC;
}

// ---------------- Simple Software Delay ----------------
void delay(int r1) {
    for (r = 0; r < r1; r++);
}

// ---------------- LCD Write Port ----------------
void port_wr(void) {
    int j;
    LPC_GPIO0->FIOPIN = temp2 << 23;
    if (flag_command == 0)
        LPC_GPIO0->FIOCLR = 1 << 27;
    else
        LPC_GPIO0->FIOSET = 1 << 27;

    LPC_GPIO0->FIOSET = 1 << 28;
    for (j = 0; j < 50; j++);
    LPC_GPIO0->FIOCLR = 1 << 28;
    for (j = 0; j < 10000; j++);
}

// ---------------- LCD Write ----------------
void lcd_wr(void) {
    temp2 = (temp1 >> 4) & 0xF;
    port_wr();
    temp2 = temp1 & 0xF;
    port_wr();
}

// ---------------- MAIN FUNCTION ----------------
int main(void) {
    int command_init[] = {3, 3, 3, 2, 2, 0x01, 0x06, 0x0C, 0x80};

    SystemInit();
    SystemCoreClockUpdate();
    timer_init();

    // GPIO Configurations
    LPC_PINCON->PINSEL0 &= 0xFFFFF00F; // P0.4–P0.11 as GPIO (LEDs)
    LPC_PINCON->PINSEL0 &= 0x3FFFFFFF; // P0.15 as GPIO (Trigger)
    LPC_PINCON->PINSEL1 &= 0xFFFFFFF0; // P0.16 as GPIO (Echo)

    // Clear all function bits for the new extended LED pins
    LPC_PINCON->PINSEL3 &= ~((3 << 14) | (3 << 16) | (3 << 18) | (3 << 20)); // P1.23–P1.26 GPIO
    LPC_PINCON->PINSEL4 &= ~((3 << 20) | (3 << 22) | (3 << 24) | (3 << 26)); // P2.10–P2.13 GPIO

    LPC_GPIO0->FIODIR |= TRIGGER_PIN;       // Trigger as Output
    LPC_GPIO0->FIODIR &= ~ECHO_PIN;         // Echo as Input
    LPC_GPIO0->FIODIR |= LED_Pinsel << 4;   // P0.4–P0.11 LEDs Output
    LPC_GPIO0->FIODIR |= 0xF << 23 | 1 << 27 | 1 << 28; // LCD Pins Output
    LPC_GPIO0->FIODIR |= 1 << 17;           // Indicator LED
    LPC_GPIO1->FIODIR |= EXT_LED_P1_MASK;   // P1.23–P1.26 as Output
    LPC_GPIO2->FIODIR |= EXT_LED_P2_MASK;   // P2.10–P2.13 as Output

    // LCD Initialization
    flag_command = 0;
    for (i = 0; i < 9; i++) {
        temp1 = command_init[i];
        lcd_wr();
        for (j = 0; j < 30000; j++);
    }

    LPC_GPIO0->FIOCLR |= TRIGGER_PIN;

    while (1) {
        // Trigger Pulse (10 µs)
        LPC_GPIO0->FIOSET = TRIGGER_PIN;
        delay_in_US(10);
        LPC_GPIO0->FIOCLR = TRIGGER_PIN;

        // Wait for Echo High
        while (!(LPC_GPIO0->FIOPIN & ECHO_PIN));
        timer_start();
        // Wait for Echo Low
        while (LPC_GPIO0->FIOPIN & ECHO_PIN);
        echoTime = timer_stop();

        // Distance Calculation
        distance = (0.00343 * echoTime) / 2; // in cm
        sprintf(ans, " Distance: %.2f cm", distance);

        // Clear LCD and Display Distance
        flag_command = 0;
        temp1 = 0x01;
        lcd_wr();

        flag_command = 1;
        i = 0;
        while (ans[i] != '\0') {
            temp1 = ans[i];
            lcd_wr();
            for (j = 0; j < 300000; j++);
            i++;
        }

        // ---------------- LED BLINK CONTROL ----------------
        if (distance < 20) {
            // Faster, brighter blink for close object
            for (b = 0; b < 10; b++) {
                // All LED groups ON
                LPC_GPIO0->FIOSET = LED_Pinsel << 4; // P0 LEDs ON
                LPC_GPIO1->FIOSET = EXT_LED_P1_MASK; // P1 LEDs ON
                LPC_GPIO2->FIOSET = EXT_LED_P2_MASK; // P2 LEDs ON
                delay(30000);                        // ON ? brighter

                // All LED groups OFF
                LPC_GPIO0->FIOCLR = LED_Pinsel << 4;
                LPC_GPIO1->FIOCLR = EXT_LED_P1_MASK;
                LPC_GPIO2->FIOCLR = EXT_LED_P2_MASK;
                delay(5000);                         // OFF ? faster blink
            }
            LPC_GPIO0->FIOSET = 1 << 17; // Indicator LED ON
        } else {
            // LEDs OFF when object far
            LPC_GPIO0->FIOCLR = LED_Pinsel << 4;
            LPC_GPIO1->FIOCLR = EXT_LED_P1_MASK;
            LPC_GPIO2->FIOCLR = EXT_LED_P2_MASK;
            LPC_GPIO0->FIOCLR = 1 << 17;
        }

        // General delay between sensor readings
        delay(60000);
    }
}
