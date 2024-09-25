/****************************************************************************/
/* This File Defines the Hardware board configuration                       */
/* This file nees to be modified as per hardware changes                    */
/*                                                                          */
/* DAN Electronics                                                          */
/* 14 April 2009                                                            */
/* Author - SANTANU ROY                                                     */
/****************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __Configure_HW_H
#define __Configure_HW_H

// BOARD DEFINATION AND FEATURE SELECTION
#define BAUD_RATE_GPS       4800            // Option - 2400,4800,9600,19200,115200
#define BAUD_RATE_CLOCK	    4800

/*Digit Control Definations*/
#define PORT_SEG_ENB    GPIOA
#define SEG_ENB         GPIO_Pin_6   // PA6 // PWM Ch1 Timer 3

#define PORT_SEG_RST    GPIOC
#define SEG_RST         GPIO_Pin_13  // PC13

#define PORT_SEG_LATCH  GPIOA
#define SEG_LATCH       GPIO_Pin_0   // PA0

#define PORT_SEG_CLOCK  GPIOA
#define SEG_CLOCK       GPIO_Pin_1   // PA1

#define PORT_SEG_DATA   GPIOA
#define SEG_DATA        GPIO_Pin_4   // PA4

/* Digit Control Defination */
#define PORT_DIG_HHT    GPIOB
#define DIG_HHT         GPIO_Pin_2   // PB2

#define PORT_DIG_HHU    GPIOB
#define DIG_HHU         GPIO_Pin_10  // PB10

#define PORT_DIG_MMT    GPIOB
#define DIG_MMT         GPIO_Pin_11  // PB11

#define PORT_DIG_MMU    GPIOB
#define DIG_MMU         GPIO_Pin_12   // PB12

#define PORT_DOT        GPIOA
#define DOT             GPIO_Pin_7   // PA7

/* Transmitter Control */
#define PORT_RxTx       GPIOA							// Transmitter Selector
#define RxTx            GPIO_Pin_8  // PA8

/* Mode LED Control */
#define PORT_LED_RED    GPIOB
#define LED_RED         GPIO_Pin_13  // PB13

#define PORT_LED_GRN    GPIOB
#define LED_GRN         GPIO_Pin_14   // PB14

/* Touch Key board interface */

#define PORT_1224	GPIOB
#define KEY_1224	GPIO_Pin_1	// PB1

#define PORT_KPRG	GPIOB
#define KEY_PRG		GPIO_Pin_15	// PB3

#define PORT_KINC	GPIOA
#define KEY_INC		GPIO_Pin_15	// PA15

#define PORT_KDEC	GPIOB
#define KEY_DEC		GPIO_Pin_3 	// PB3

#define PORT_KINT	GPIOB
#define KEY_INT		GPIO_Pin_0 	// PB0

/* Address Input definations */
#define PORT_ADD1       GPIOA							// Address Bit 1
#define ADD_BIT1        GPIO_Pin_12 // PA12

#define PORT_ADD2       GPIOB							// Address Bit 2
#define ADD_BIT2        GPIO_Pin_4  // PB4

#define PORT_ADD4       GPIOB							// Address Bit 3
#define ADD_BIT4        GPIO_Pin_5  // PB5

#define PORT_ADD8       GPIOB							// Address Bit 4
#define ADD_BIT8        GPIO_Pin_8  // PB8

#define PORT_ADD16      GPIOB							// Address Bit 5
#define ADD_BIT16       GPIO_Pin_9  // PB9


#endif
