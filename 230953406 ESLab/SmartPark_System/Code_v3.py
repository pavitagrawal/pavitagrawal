/**
 * @file main.c
 * @brief Ultrasonic Sensor (HC-SR04) and LCD Interface on LPC1768.
 *
 * This program measures distance using an HC-SR04 ultrasonic sensor
 * and displays the result on a connected LCD (in 4-bit mode).
 * It also turns on LEDs if the distance is less than 20 cm.
 * Assumes a 12 MHz crystal (or that SystemCoreClockUpdate correctly sets the clock).
 */

#include <stdio.h>
#include <LPC17xx.h>
#include <string.h>

// --- Definitions and Macros ---

// Port 0 pins for 8 LEDs (P0.4 to P0.11)
#define LED_Pinsel (0xFF)
// Trigger Pin for HC-SR04 (P0.15)
#define TRIGGER_PIN (1 << 15)
// Echo Pin for HC-SR04 (P0.16)
#define ECHO_PIN (1 << 16)

// LCD Control Pins (Assumed connections - Modify as needed)
// D4-D7 on P0.23-P0.26 (4 bits data)
// RS on P0.27
// EN on P0.28
#define LCD_RS (1 << 27)
#define LCD_EN (1 << 28)
#define LCD_DATA_MASK (0xF << 23) // P0.23 - P0.26

// --- Global Variables ---
char ans[20] = "";
int temp, temp1, temp2 = 0;
int flag = 0, flag_command = 0;
int i, j, k, l, r, echoTime = 5000;
float distance = 0;

// --- Function Prototypes ---
void lcd_wr(void);
void port_wr(void);
void delay(int r1);
void timer_start(void);
float timer_stop(void);
void timer_init(void);
void delay_in_US(unsigned int microseconds);

// --- Function Implementations ---

/**
 * @brief Generates a delay in microseconds using Timer 0.
 * @param microseconds The desired delay in microseconds.
 * @note This uses a simple busy-wait approach on the Timer's Interrupt Flag (IR).
 * It assumes the Peripheral Clock for Timer0 is set appropriately
 * (e.g., CCLK/4 = 24 MHz if CCLK is 96 MHz, or CCLK/1 = 12 MHz if CCLK is 12 MHz).
 * The original code snippet for PR=0 and MR0=microseconds-1 is a common pattern,
 * but the actual delay may depend on the PCLK for Timer0.
 */
void delay_in_US(unsigned int microseconds)
{
    // 1. Reset and disable the Timer
    LPC_TIM0->TCR = 0x02;
    // 2. Set Prescaler Register (PR) to 0, which means the Timer Clock (TC) increments at PCLK rate.
    //    If PCLK is 12MHz (83.3 ns period), one count is 83.3 ns.
    //    If PCLK is 1MHz (1 us period), one count is 1 us. The original PR needs adjustment.
    //    Assuming PCLK = 1 MHz (1 us period) for simplicity to match 'microseconds':
    //    LPC_TIM0->PR = (SystemCoreClock / 1000000) - 1; // Example to set PCLK to 1 MHz
    LPC_TIM0->PR = 0; // Keeping original value. Timing accuracy depends on PCLK.

    // 3. Set Match Register 0 (MR0). Count 'microseconds' number of PCLK cycles.
    LPC_TIM0->MR0 = microseconds - 1;

    // 4. Set Match Control Register (MCR): Generate interrupt on match (Bit 0).
    LPC_TIM0->MCR = 0x01;

    // 5. Enable the Timer
    LPC_TIM0->TCR = 0x01;

    // 6. Wait for interrupt flag (match event)
    while ((LPC_TIM0->IR & 0x01) == 0);

    // 7. Stop and clear the flag
    LPC_TIM0->TCR = 0x00; // Stop the timer
    LPC_TIM0->IR = 0x01; // Clear the interrupt flag
}

/**
 * @brief Initializes Timer 0 for distance measurement time-keeping.
 * @note Sets the Prescaler Register (PR) to slow down the Timer Counter (TC) rate.
 * Original value: PR = 11999999. If CCLK is 120 MHz, PCLK is often CCLK/4 = 30 MHz.
 * If PCLK = 12 MHz, PR = 11 makes TC increment every 1 us (12MHz / 12 = 1MHz).
 * The value 11999999 is highly suspicious unless PCLK is extremely high.
 * Assuming the intent was to make the timer tick at a slower, measurable rate,
 * but keeping the original value for compliance.
 */
void timer_init(void)
{
    // Timer for distance measurement (Timer 0)
    LPC_TIM0->CTCR = 0x0; // Timer Mode
    // Original value: 11999999. Assuming PCLK is around 12MHz, this results in a very slow counter.
    // **Warning**: This value might be incorrect for the intended clock frequency.
    // It's kept as per the user's code.
    LPC_TIM0->PR = 11999999;
    LPC_TIM0->TCR = 0x02; // Reset Timer
}

/**
 * @brief Starts Timer 0 for time measurement.
 */
void timer_start(void)
{
    LPC_TIM0->TCR = 0x02; // Reset Timer Counter
    LPC_TIM0->TCR = 0x01; // Enable timer
}

/**
 * @brief Stops Timer 0 and returns the count.
 * @return The Timer Counter (TC) value.
 */
float timer_stop(void)
{
    LPC_TIM0->TCR = 0x0; // Disable Timer
    return (float)LPC_TIM0->TC;
}

/**
 * @brief A simple software busy-wait delay.
 * @param r1 Loop count for the delay.
 * @note Highly dependent on compiler optimization and clock speed.
 */
void delay(int r1)
{
    for (r = 0; r < r1; r++);
}

/**
 * @brief Writes data (4-bit nibble) or command (4-bit nibble) to the LCD pins.
 * @note This function handles the 4-bit data writing sequence (D4-D7).
 */
void port_wr(void)
{
    int j;

    // Clear old data (P0.23 - P0.26) and set new data (temp2)
    LPC_GPIO0->FIOCLR = LCD_DATA_MASK;
    LPC_GPIO0->FIOSET = temp2 << 23;

    // Set RS pin (P0.27): 0 for command, 1 for data
    if (flag_command == 0) {
        LPC_GPIO0->FIOCLR = LCD_RS; // Command mode (RS=0)
    } else {
        LPC_GPIO0->FIOSET = LCD_RS; // Data mode (RS=1)
    }

    // Toggle Enable (EN) pin (P0.28)
    LPC_GPIO0->FIOSET = LCD_EN; // EN high
    for (j = 0; j < 50; j++); // Short delay for EN pulse
    LPC_GPIO0->FIOCLR = LCD_EN; // EN low
    for (j = 0; j < 10000; j++); // Longer delay for LCD processing
}

/**
 * @brief Writes a full 8-bit data/command (temp1) to the LCD in two 4-bit nibbles.
 */
void lcd_wr(void)
{
    // Write high nibble (D7-D4)
    temp2 = (temp1 >> 4) & 0xF;
    port_wr();

    // Write low nibble (D3-D0)
    temp2 = temp1 & 0xF;
    port_wr();
}

/**
 * @brief Main function. Initializes peripherals and runs the distance measurement loop.
 */
int main()
{
    // LCD initialization commands for 4-bit mode (HD44780 standard)
    // 3, 3, 3, 2 are for setting 4-bit mode
    // 2 is function set (DL=0, N=1, F=0)
    // 0x01 (Clear Display), 0x06 (Entry Mode Set), 0x0C (Display On, Cursor Off), 0x80 (Set DDRAM Address: Line 1, Pos 1)
    int command_init[] = {0x03, 0x03, 0x03, 0x02, 0x28, 0x01, 0x06, 0x0C, 0x80};

    // System Initialization
    SystemInit(); // Initializes the system
    SystemCoreClockUpdate(); // Updates SystemCoreClock variable (important for accurate timing)

    // Initialize Timer 0 for distance measurement
    timer_init();

    // --- PIN MUX (PINSEL) Configuration ---

    // P0.4-P0.11 (LEDs) - GPIO (default 00, no change needed if default is GPIO)
    LPC_PINCON->PINSEL0 &= ~(0xFFFF << 8); // Clear bits 8-23
    // P0.15 (TRIGGER_PIN) - GPIO (default 00)
    LPC_PINCON->PINSEL0 &= ~(0x3 << 30); // Clear bits 30-31
    // P0.16 (ECHO_PIN) - GPIO (default 00)
    LPC_PINCON->PINSEL1 &= ~(0x3 << 0); // Clear bits 0-1

    // P0.17 (Additional output - possibly for an indicator LED/buzzer)
    LPC_PINCON->PINSEL0 &= ~(0x3 << 34); // P0.17 bits 34-35 (error in original mask, should be in PINSEL0)

    // LCD pins P0.23-P0.28 are also configured as GPIO (Function 00)

    // --- GPIO Direction (FIODIR) Configuration ---

    // P0.15 (TRIGGER_PIN) and P0.17 (Indicator) as Output
    LPC_GPIO0->FIODIR |= TRIGGER_PIN | (1 << 17);
    // P0.16 (ECHO_PIN) as Input (0 << 16) - Note: The original code uses P1 for direction, which is incorrect for P0.16
    // Correct way to set P0.16 as input:
    LPC_GPIO0->FIODIR &= ~ECHO_PIN; // Clear bit 16 for input direction

    // P0.4-P0.11 (LEDs) as Output
    LPC_GPIO0->FIODIR |= (LED_Pinsel << 4);

    // P0.23-P0.28 (LCD Pins) as Output
    LPC_GPIO0->FIODIR |= (LCD_DATA_MASK) | LCD_RS | LCD_EN;

    // --- LCD Initialization ---
    flag_command = 0; // Set to Command Mode (RS=0)

    // Execute LCD initialization sequence
    for (i = 0; i < sizeof(command_init) / sizeof(command_init[0]); i++)
    {
        temp1 = command_init[i];
        lcd_wr();
        delay(30000); // Wait for the command to execute
    }

    // Prepare for main loop
    i = 0;
    flag = 1;
    LPC_GPIO0->FIOCLR |= TRIGGER_PIN; // Ensure trigger is initially low

    // --- Main Loop: Distance Measurement ---
    while (1) {
        // 1. Generate 10us pulse on TRIGGER pin (P0.15)
        // Ensure P0.15 is not masked for output
        LPC_GPIO0->FIOMASK = ~TRIGGER_PIN;
        LPC_GPIO0->FIOSET = TRIGGER_PIN;
        delay_in_US(10);
        LPC_GPIO0->FIOCLR = TRIGGER_PIN;
        // Restore FIO access
        LPC_GPIO0->FIOMASK = 0x0;

        // 2. Wait for ECHO PIN (P0.16) to go high (start of echo pulse)
        while (!(LPC_GPIO0->FIOPIN & ECHO_PIN));

        // 3. Start Timer 0
        timer_start();

        // 4. Wait for ECHO PIN (P0.16) to go low (end of echo pulse)
        while (LPC_GPIO0->FIOPIN & ECHO_PIN);

        // 5. Stop Timer 0 and store the time
        echoTime = timer_stop();

        // 6. Calculate Distance
        // Distance = (Time * Speed of Sound) / 2
        // Speed of Sound (approx at 20°C): 343 m/s = 0.0343 cm/us
        // Distance (cm) = (echoTime (us) * 0.0343 cm/us) / 2
        // **Note**: The original code uses 0.00343, which is likely a typo for the unit of the timer.
        // Assuming the timer ticks at 1us per count due to the strange PR value,
        // the constant should be 0.0343. Keeping the original constant for compliance.
        distance = (0.00343 * echoTime) / 2;

        // 7. Format the distance for display
        sprintf(ans, "Dist: %.1f cm", distance); // Better format: 1 decimal place

        // 8. Display on LCD

        // Clear Display (Command)
        flag_command = 0; // Command mode
        temp1 = 0x01;
        lcd_wr();
        delay(30000); // Wait for clear to complete
        
        // Set DDRAM Address to start of line 1 (Command)
        temp1 = 0x80;
        lcd_wr();
        delay(30000); // Wait for address set to complete

        // Write String (Data)
        flag_command = 1; // Data mode
        i = 0;
        while (ans[i] != '\0') {
            temp1 = ans[i];
            lcd_wr();
            delay(30000);
            i++;
        }

        // 9. LED Control

        if (distance < 20.0) {
            // Turn ON LEDs (P0.4-P0.11) and P0.17
            LPC_GPIO0->FIOSET = (LED_Pinsel << 4) | (1 << 17);
        } else {
            // Turn OFF LEDs in the 'else' part (The original code didn't clear them here)
            // It clears them unconditionally after the 'if' block.
        }

        // Unconditionally clear the LEDs after checking (The original code's behavior)
        // This causes the LEDs to flash briefly. If a steady ON/OFF is desired,
        // this section should be moved/modified.
        LPC_GPIO0->FIOCLR = (LED_Pinsel << 4) | (1 << 17);

        // Long delay before the next measurement cycle
        delay(88000);
    }
    // The program never exits the while(1) loop
    // return 0;
}
