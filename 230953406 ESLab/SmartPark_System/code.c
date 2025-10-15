#include <LPC17xx.h>
#include <stdio.h>
#include <string.h>

// ---------- DEFINITIONS ----------
#define LED_Pinsel 0xFF       // LEDs on P0.4–P0.11
#define TRIGGER_PIN (1 << 15) // Ultrasonic Trigger P0.15
#define ECHO_PIN (1 << 16)    // Ultrasonic Echo P0.16
#define BUZZER_PIN (1 << 17)  // Buzzer on P0.17

// ---------- VARIABLES ----------
char ans[20];
int temp, temp1, temp2;
int flag_command = 0;
int i, j;
unsigned int echoTime;
float distance;

// ---------- FUNCTION DECLARATIONS ----------
void lcd_wr(void);
void port_wr(void);
void delay(int r1);
void timer_start(void);
float timer_stop(void);
void timer_init(void);
void delay_us(unsigned int microseconds);
void delay_ms(unsigned int milliseconds);

// ---------- MICROSECOND DELAY ----------
void delay_us(unsigned int microseconds)
{
    LPC_TIM0->TCR = 0x02;       // Reset Timer
    LPC_TIM0->PR = 0;           // Prescaler = 0
    LPC_TIM0->MR0 = microseconds - 1;
    LPC_TIM0->MCR = 0x04;       // Stop on Match
    LPC_TIM0->TCR = 0x01;       // Start Timer

    while (LPC_TIM0->TC < microseconds);
    LPC_TIM0->TCR = 0x00;
}

// ---------- MILLISECOND DELAY ----------
void delay_ms(unsigned int milliseconds)
{
    unsigned int i;
    for (i = 0; i < milliseconds; i++)
        delay_us(1000);
}

// ---------- TIMER INITIALIZATION ----------
void timer_init(void)
{
    LPC_TIM0->CTCR = 0x0;
    LPC_TIM0->PR = 11; // 12 MHz PCLK ? 1µs tick
    LPC_TIM0->TCR = 0x02; // Reset
}

// ---------- TIMER START ----------
void timer_start(void)
{
    LPC_TIM0->TCR = 0x02; // Reset
    LPC_TIM0->TCR = 0x01; // Start
}

// ---------- TIMER STOP ----------
float timer_stop(void)
{
    LPC_TIM0->TCR = 0x00;
    return LPC_TIM0->TC;
}

// ---------- SIMPLE LOOP DELAY ----------
void delay(int r1)
{
    int r;
    for (r = 0; r < r1; r++);
}

// ---------- LCD PORT WRITE ----------
void port_wr(void)
{
    LPC_GPIO0->FIOPIN = temp2 << 23; // P0.23–P0.26 for data
    if (flag_command == 0)
        LPC_GPIO0->FIOCLR = 1 << 27; // RS = 0 ? Command
    else
        LPC_GPIO0->FIOSET = 1 << 27; // RS = 1 ? Data

    LPC_GPIO0->FIOSET = 1 << 28;     // EN = 1
    for (j = 0; j < 50; j++);
    LPC_GPIO0->FIOCLR = 1 << 28;     // EN = 0
    for (j = 0; j < 10000; j++);
}

// ---------- LCD WRITE ----------
void lcd_wr(void)
{
    temp2 = (temp1 >> 4) & 0xF;
    port_wr();
    temp2 = temp1 & 0xF;
    port_wr();
}

// ---------- MAIN FUNCTION ----------
int main(void)
{
    int command_init[] = {3, 3, 3, 2, 0x01, 0x06, 0x0C, 0x80};

    SystemInit();
    SystemCoreClockUpdate();
    timer_init();

    // --- GPIO Setup ---
    LPC_PINCON->PINSEL0 &= 0xFFFFF00F; // P0.4–P0.11 GPIO (LED)
    LPC_PINCON->PINSEL0 &= ~(3 << 30); // P0.15 GPIO
    LPC_PINCON->PINSEL1 &= 0xFFFFFFF0; // P0.16 GPIO
    LPC_GPIO0->FIODIR |= LED_Pinsel << 4 | TRIGGER_PIN | BUZZER_PIN | 0xF << 23 | 1 << 27 | 1 << 28;
    LPC_GPIO0->FIODIR &= ~ECHO_PIN; // Echo input

    // --- LCD Initialization ---
    flag_command = 0;
    for (i = 0; i < 8; i++)
    {
        temp1 = command_init[i];
        lcd_wr();
        delay(30000);
    }

    while (1)
    {
        // --- Trigger Ultrasonic Pulse ---
        LPC_GPIO0->FIOCLR = TRIGGER_PIN;
        delay_us(2);
        LPC_GPIO0->FIOSET = TRIGGER_PIN;
        delay_us(10);
        LPC_GPIO0->FIOCLR = TRIGGER_PIN;

        // --- Wait for Echo High ---
        while (!(LPC_GPIO0->FIOPIN & ECHO_PIN));
        timer_start();

        // --- Wait for Echo Low ---
        while (LPC_GPIO0->FIOPIN & ECHO_PIN);
        echoTime = timer_stop();

        // --- Calculate Distance ---
        distance = (0.0343f * echoTime) / 2.0f;

        // --- Display on LCD ---
        sprintf(ans, "Distance: %.1fcm", distance);
        flag_command = 0;
        temp1 = 0x01;
        lcd_wr();

        flag_command = 1;
        i = 0;
        while (ans[i] != '\0')
        {
            temp1 = ans[i];
            lcd_wr();
            delay(30000);
            i++;
        }

        // --- LED + Buzzer Alerts ---
        if (distance < 20)
        {
            LPC_GPIO0->FIOSET = (LED_Pinsel << 4) | BUZZER_PIN;
        }
        else
        {
            LPC_GPIO0->FIOCLR = (LED_Pinsel << 4) | BUZZER_PIN;
        }

        delay(500000);
    }
}
