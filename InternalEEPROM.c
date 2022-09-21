#include <pic.h>

void EEWR(unsigned char address, unsigned char data) {
    volatile unsigned char INTCON_BUP = INTCON;
    INTCONbits.GIE = 0;
    EEADR = address;
    EEDATA = data;
    EECON1bits.WREN = 1;
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;
    EECON1bits.WREN = 0;
    while (EECON1bits.WR == 1) {
    }
    INTCON = INTCON_BUP;
}

unsigned char EERD(unsigned char address) {
    volatile unsigned char INTCON_BUP = INTCON;
    volatile unsigned char EEDATA_BUP;
    INTCONbits.GIE = 0;
    EEADR = address;
    EECON1bits.RD = 1;
    EEDATA_BUP = EEDATA;
    INTCON = INTCON_BUP;
    return EEDATA_BUP;
}

void ReadArrayFromEEPROM(unsigned char *container, unsigned char address_start, unsigned char quantity) {
    for (unsigned char i = 0; i < quantity; i++) {
        container[i] = EERD(address_start + i);
    }
}

void WriteArrayToEEPROM(unsigned char * container, unsigned char address_start, unsigned char quantity) {
    for (unsigned char i = 0; i < quantity; i++) {
        EEWR(address_start + i, container[i]);
    }
}