
#ifndef INTERNALEEPROM_H
#define	INTERNALEEPROM_H

void EEWR(unsigned char, unsigned char);
unsigned char EERD(unsigned char);
void ReadArrayFromEEPROM(unsigned char*, unsigned char, unsigned char);
void WriteArrayToEEPROM(unsigned char*, unsigned char, unsigned char);


#endif