#include <pic.h>

#ifndef __I2C_H
#define __I2C_H

// Define i2c pins
#define SDA			GP4				// Data pin for i2c
#define SCK			GP5				// Clock pin for i2c
#define SDA_DIR		TRISIO4			// Data pin direction
#define SCK_DIR		TRISIO5			// Clock pin direction


//#define DataPinADCMask		ANS3
//#define ClockPinADCMask		ANS3


// Define i2c speed
#define I2C_SPEED	1				// kbps 
#define HalfBitDelay 500/I2C_SPEED	// usec

// Define macros
#define Set_SDA_Low		SDA_DIR = 0
#define Set_SDA_High	SDA_DIR = 1
#define Set_SCK_Low		SCK_DIR = 0
#define Set_SCK_High	SCK_DIR = 1

//Function Declarations
void InitI2C(void);
void I2C_Start(void);
void I2C_ReStart(void);
void I2C_Stop(void);
void I2C_Send_ACK(void);
void I2C_Send_NACK(void);
unsigned char I2C_Write_Byte(unsigned char);
unsigned char I2C_Read_Byte(void);

#endif
