#include <stdio.h>
#include <string.h>
#include "LPC17xx.h"

/* --- Pin definitions --- */
#define LED_MASK       (0xFFU << 4)    /* P0.4 - P0.11 */
#define TRIG_PIN       (1U << 15)      /* P0.15 */
#define ECHO_PIN       (1U << 16)      /* P0.16 */
#define BUZZER_PIN     (1U << 17)      /* P0.17 */

#define LCD_D4_SHIFT   23U             /* P0.23..P0.26 */
#define LCD_RS_PIN     (1U << 27)
#define LCD_EN_PIN     (1U << 28)

char lcd_buf[32];

/* Function prototypes */
void delay_ms(uint32_t ms);
void delay_us(uint32_t us);
void timer0_init_for_us(void);
void timer0_start(void);
uint32_t timer0_stop_and_read(void);

static void lcd_pulse_enable(void);
static void lcd_write_nibble(uint8_t nibble);
static void lcd_cmd(uint8_t cmd);
static void lcd_data(uint8_t data);
static void lcd_print(const char *s);
static void lcd_init(void);

void hcsr04_trigger_pulse(void);
float hcsr04_get_distance_cm(void);

void busy_wait(volatile uint32_t count) {
    while(count--) { __NOP(); }
}

int main(void) {
    float distance;

    SystemInit();
    SystemCoreClockUpdate();
    timer0_init_for_us();

    LPC_PINCON->PINSEL0 &= ~( (0x3U<<30) | (0x3U<<0) ); // P0.15 GPIO
    LPC_PINCON->PINSEL1 &= ~( (0x3U<<0) );              // P0.16 GPIO
    LPC_GPIO0->FIODIR |= TRIG_PIN | BUZZER_PIN | LED_MASK | (0xFU << LCD_D4_SHIFT) | LCD_RS_PIN | LCD_EN_PIN;
    LPC_GPIO0->FIODIR &= ~ECHO_PIN;

    LPC_GPIO0->FIOCLR = TRIG_PIN | BUZZER_PIN | LED_MASK | (0xFU << LCD_D4_SHIFT) | LCD_RS_PIN | LCD_EN_PIN;

    lcd_init();

    for(;;) {
        distance = hcsr04_get_distance_cm();

        snprintf(lcd_buf, sizeof(lcd_buf), "Distance: %5.2f cm", distance);
        lcd_cmd(0x80);
        lcd_print(lcd_buf);

        if (distance > 0 && distance < 20.0f) {
            LPC_GPIO0->FIOSET = LED_MASK;
            LPC_GPIO0->FIOSET = BUZZER_PIN;
        } else {
            LPC_GPIO0->FIOCLR = LED_MASK;
            LPC_GPIO0->FIOCLR = BUZZER_PIN;
        }

        delay_ms(300);
    }

    return 0;
}

/* -------------------- HC-SR04 -------------------- */
void hcsr04_trigger_pulse(void) {
    LPC_GPIO0->FIOCLR = TRIG_PIN;
    delay_us(2);
    LPC_GPIO0->FIOSET = TRIG_PIN;
    delay_us(11);
    LPC_GPIO0->FIOCLR = TRIG_PIN;
}

float hcsr04_get_distance_cm(void) {
    uint32_t t;
    uint32_t timeout_us;
    uint32_t elapsed;
    float dist_cm;

    dist_cm = -1.0f;
    timeout_us = 30000U;
    elapsed = 0U;

    hcsr04_trigger_pulse();

    while (!(LPC_GPIO0->FIOPIN & ECHO_PIN)) {
        delay_us(1);
        elapsed++;
        if (elapsed > timeout_us) {
            return -1.0f;
        }
    }

    timer0_start();

    while (LPC_GPIO0->FIOPIN & ECHO_PIN) {
        delay_us(1);
        elapsed++;
        if (elapsed > timeout_us) {
            timer0_stop_and_read();
            return -1.0f;
        }
    }

    t = timer0_stop_and_read();
    dist_cm = (0.0343f * (float)t) / 2.0f;
    return dist_cm;
}

/* -------------------- Timer0 microsecond base -------------------- */
void timer0_init_for_us(void) {
    uint32_t pclk;
    uint32_t pr;

    LPC_TIM0->TCR = 0x02;
    pclk = SystemCoreClock / 4U;
    pr = (pclk / 1000000U) - 1U;
    LPC_TIM0->PR = pr;
    LPC_TIM0->TCR = 0x00;
    LPC_TIM0->TC = 0;
    LPC_TIM0->CTCR = 0x0;
}

void timer0_start(void) {
    LPC_TIM0->TCR = 0x02;
    LPC_TIM0->TCR = 0x01;
}

uint32_t timer0_stop_and_read(void) {
    LPC_TIM0->TCR = 0x00;
    return LPC_TIM0->TC;
}

/* -------------------- Simple delays -------------------- */
void delay_us(uint32_t us) {
    timer0_start();
    while (LPC_TIM0->TC < us) { }
    timer0_stop_and_read();
}

void delay_ms(uint32_t ms) {
    while (ms--) {
        delay_us(1000U);
    }
}

/* -------------------- LCD -------------------- */
static void lcd_write_nibble(uint8_t nibble) {
    uint32_t gpio_val;
    gpio_val = ((nibble & 0x0FU) << LCD_D4_SHIFT);
    LPC_GPIO0->FIOCLR = (0xFU << LCD_D4_SHIFT);
    LPC_GPIO0->FIOSET = gpio_val;
    lcd_pulse_enable();
}

static void lcd_pulse_enable(void) {
    LPC_GPIO0->FIOSET = LCD_EN_PIN;
    busy_wait(200);
    LPC_GPIO0->FIOCLR = LCD_EN_PIN;
    busy_wait(200);
}

static void lcd_cmd(uint8_t cmd) {
    LPC_GPIO0->FIOCLR = LCD_RS_PIN;
    lcd_write_nibble(cmd >> 4);
    lcd_write_nibble(cmd & 0x0F);
    if (cmd == 0x01 || cmd == 0x02) delay_ms(2); else delay_us(200);
}

static void lcd_data(uint8_t data) {
    LPC_GPIO0->FIOSET = LCD_RS_PIN;
    lcd_write_nibble(data >> 4);
    lcd_write_nibble(data & 0x0F);
    delay_us(50);
}

static void lcd_print(const char *s) {
    while (*s) {
        lcd_data((uint8_t)(*s++));
    }
}

static void lcd_init(void) {
    delay_ms(40);
    LPC_GPIO0->FIOCLR = LCD_RS_PIN;
    lcd_write_nibble(0x03);
    delay_ms(5);
    lcd_write_nibble(0x03);
    delay_us(150);
    lcd_write_nibble(0x03);
    delay_us(150);

    lcd_write_nibble(0x02);
    delay_us(150);

    lcd_cmd(0x28);
    lcd_cmd(0x0C);
    lcd_cmd(0x01);
    delay_ms(2);
    lcd_cmd(0x06);
}
