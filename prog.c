
// CONFIG
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-Up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF      // GP3/MCLR pin function select (GP3/MCLR pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)

#include "includes.h"

unsigned char COUNTER [] = {0xFF, 0xFF, 0xFF};

#define CELL_CAPACITY (sizeof(COUNTER))
#define END_OF_CELLS (CELL_CAPACITY * CELLS_COUNT)



void countPowerOn() {
    ReadArrayFromEEPROM(COUNTER, 0x7D, CELL_CAPACITY);

    unsigned long int counter = 0;
    for (unsigned char i = CELL_CAPACITY; i >= 1; i--) {
        counter = (counter << 8) + COUNTER[i - 1];
    }
    unsigned long int default_value = 0;
    for (unsigned char i = CELL_CAPACITY; i >= 1; i--) {
        default_value = (default_value << 8) + 0xFF;
    }
    
    if (counter == default_value) {
        counter = 0;
    }
    counter++;

    for (unsigned char i = 0; i < CELL_CAPACITY; i++) {
        COUNTER[i] = (counter >> (i * 8)) & 0xFF;
    }
    WriteArrayToEEPROM(COUNTER, 0x7D, CELL_CAPACITY);
}

void main(void) {
    INTCON = 0;
    OPTION_REG = 0b00000111;
    TRISIO = 0b00000000;
    GPIO = 0b00111111;
    CMCON = 0b00000111;
    
    countPowerOn();
    //InitI2C();
    // https://kipdoc.ru/pic/389-podklyuchenie-displeya-lcd1602-k-mikrokontrolleru-pic.html
    // https://radiolaba.ru/microcotrollers/podklyuchenie-lcd-1602-po-i2c-interfeysu.html
    
    
    unsigned char i = 0;
    while(i < 7) {
        GPIO = 0b00000000;
        __delay_ms(30);
        GPIO = 0b00100000;
        __delay_ms(120);
        i++;
    }
    TRISIO = 0b00111110;
    while(1) {
        GPIO = 0b00000001;
        __delay_ms(625);
        GPIO = 0b00000000;
        __delay_ms(625);
    }
 }