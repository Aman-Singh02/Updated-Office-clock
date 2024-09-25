
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SW_I2C_H
#define __SW_I2C_H

void Delay_1us(unsigned int);

void INIT_SW_I2C(void);
void I2C_START(void);
void I2C_STOP(void);
void I2C_ACK(void);
void Serial_Out(unsigned char);
unsigned char Serial_In(void);

void I2C_Write(unsigned char,unsigned char);
unsigned char I2C_Read(unsigned char);

#define LOOP_DLY_1US   4

#define PORT_SDA	GPIOB
#define PIN_SDA		LL_GPIO_PIN_7	// PB7

#define PORT_SCL	GPIOB
#define PIN_SCL		LL_GPIO_PIN_6	// PB6


#define SET_SDA         PORT_SDA->BSRR = PIN_SDA
#define RST_SDA         PORT_SDA->BRR  = PIN_SDA

#define SET_SCL         PORT_SCL->BSRR = PIN_SCL
#define RST_SCL         PORT_SCL->BRR  = PIN_SCL

        


#endif


