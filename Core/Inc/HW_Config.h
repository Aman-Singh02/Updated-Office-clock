
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __Configure_HW_H
#define __Configure_HW_H

// BOARD DEFINATION AND FEATURE SELECTION
#define BAUD_RATE_GPS       9600            // Option - 2400,4800,9600,19200,115200
#define BAUD_RATE_CLOCK	    4800

/*Digit Control Definations*/
/* INPUT  Key  */
#define K12_24_GPIO_Port       GPIOB
#define K12_24_Pin	       LL_GPIO_PIN_14	

#define PORT_KPRG	       GPIOB
#define KEY_PRG		       LL_GPIO_PIN_15

#define PORT_KINC	       GPIOB
#define KEY_INC		       LL_GPIO_PIN_3	

#define PORT_KDEC	       GPIOD
#define KEY_DEC		       LL_GPIO_PIN_3 	

#define PORT_KINT	       GPIOB
#define KEY_INT		       LL_GPIO_PIN_13 	


/* outputs key*/
/* GPS ON */
#define PORT_SEG_ENB           GPIOA 
#define SEG_ENB                LL_GPIO_PIN_4  //ok 

#define PORT_SEG_LATCH         GPIOB
#define SEG_LATCH              LL_GPIO_PIN_1//ok

#define PORT_SEG_CLOCK         GPIOB
#define SEG_CLOCK              LL_GPIO_PIN_0 //ok

#define PORT_SEG_DATA          GPIOB
#define SEG_DATA               LL_GPIO_PIN_5 //ok  
 
#define NET_SEG3_Pin           LL_GPIO_PIN_0
#define NET_SEG3_GPIO_Port     GPIOD

#define NET_SEG2_Pin           LL_GPIO_PIN_1
#define NET_SEG2_GPIO_Port     GPIOD

#define NET_SEG1_Pin           LL_GPIO_PIN_2
#define NET_SEG1_GPIO_Port     GPIOD

#define PORT_GPS               GPIOA
#define PIN_GPS                LL_GPIO_PIN_1

/* Mode LED Control */
#define PORT_LED_RED           GPIOB
#define LED_RED                LL_GPIO_PIN_11

#define PORT_LED_GRN           GPIOB
#define LED_GRN                LL_GPIO_PIN_12  




#define ENB_Pin LL_GPIO_PIN_4
#define ENB_GPIO_Port GPIOA

#define CLK_Pin LL_GPIO_PIN_0
#define CLK_GPIO_Port GPIOB

#define LAT_Pin LL_GPIO_PIN_1
#define LAT_GPIO_Port GPIOB

#define NET_SEGMENT_ON_Pin               LL_GPIO_PIN_0
#define NET_SEGMENT_ON_GPIO_Port         GPIOD

#define NET_SEGMENT_ON2_Pin              LL_GPIO_PIN_1
#define NET_SEGMENT_ON2_GPIO_Port        GPIOD

#define NET_SEGMENT_ON1_Pin              LL_GPIO_PIN_2
#define NET_SEGMENT_ON1_GPIO_Port        GPIOD
#endif
