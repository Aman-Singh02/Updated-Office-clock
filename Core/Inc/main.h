/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_bus.h"
#include "stm32g0xx_ll_system.h"
#include "stm32g0xx_ll_exti.h"
#include "stm32g0xx_ll_cortex.h"
#include "stm32g0xx_ll_utils.h"
#include "stm32g0xx_ll_pwr.h"
#include "stm32g0xx_ll_dma.h"
#include "stm32g0xx_ll_usart.h"
#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_ll_iwdg.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE BEGIN Includes */
#include "App_init.h"
#include "SW_I2C.h"
#include "I2C_RTC.h"
#include "Misc_Functions.h"
#include "Configure_STM32.h"
#include "App_RAM.h"
#include "HW_Config.h"
#include <stdio.h>
#include <string.h>
#include "rtc.h"
#include "usart.h"
#include "tim.h"
#include "gpio.h"
#include "iwdg.h"  
//#include "App_Include.h"
/* USER CODE END Includes */
#define Flash_ADD 0x800ff00
#define ADDR_FLASH_PAGE_0     ((uint32_t)0x08000000) /* Base @ of Page 0, 2 Kbytes */
#define ADDR_FLASH_PAGE_1     ((uint32_t)0x08000800) /* Base @ of Page 1, 2 Kbytes */
#define ADDR_FLASH_PAGE_2     ((uint32_t)0x08001000) /* Base @ of Page 2, 2 Kbytes */
#define ADDR_FLASH_PAGE_3     ((uint32_t)0x08001800) /* Base @ of Page 3, 2 Kbytes */
#define ADDR_FLASH_PAGE_4     ((uint32_t)0x08002000) /* Base @ of Page 4, 2 Kbytes */
#define ADDR_FLASH_PAGE_5     ((uint32_t)0x08002800) /* Base @ of Page 5, 2 Kbytes */
#define ADDR_FLASH_PAGE_6     ((uint32_t)0x08003000) /* Base @ of Page 6, 2 Kbytes */
#define ADDR_FLASH_PAGE_7     ((uint32_t)0x08003800) /* Base @ of Page 7, 2 Kbytes */
#define ADDR_FLASH_PAGE_8     ((uint32_t)0x08004000) /* Base @ of Page 8, 2 Kbytes */
#define ADDR_FLASH_PAGE_9     ((uint32_t)0x08004800) /* Base @ of Page 9, 2 Kbytes */
#define ADDR_FLASH_PAGE_10    ((uint32_t)0x08005000) /* Base @ of Page 10, 2 Kbytes */
#define ADDR_FLASH_PAGE_11    ((uint32_t)0x08005800) /* Base @ of Page 11, 2 Kbytes */
#define ADDR_FLASH_PAGE_12    ((uint32_t)0x08006000) /* Base @ of Page 12, 2 Kbytes */
#define ADDR_FLASH_PAGE_13    ((uint32_t)0x08006800) /* Base @ of Page 13, 2 Kbytes */
#define ADDR_FLASH_PAGE_14    ((uint32_t)0x08007000) /* Base @ of Page 14, 2 Kbytes */
#define ADDR_FLASH_PAGE_15    ((uint32_t)0x08007800) /* Base @ of Page 15, 2 Kbytes */
  
#define FLASH_USER_START_ADDR   ADDR_FLASH_PAGE_5   /* Start @ of user Flash area */
#define FLASH_USER_END_ADDR     (ADDR_FLASH_PAGE_15 + FLASH_PAGE_SIZE - 1)   /* End @ of user Flash area */
  
#define DATA_32                 ((uint32_t)0x12345678)
#define DATA_64                 ((uint64_t)0x1234567812345678)
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
 

#define GPS_ON           PORT_GPS->BRR    = (uint32_t)PIN_GPS                    // INVERSE LOGIC TRANSISTOR
#define GPS_OFF          PORT_GPS->BSRR   = (uint32_t)PIN_GPS                    // INVERSE LOGIC TRANSISTOR

#define SET_CLOCK         PORT_SEG_CLOCK->BSRR = (uint32_t)SEG_CLOCK
#define RST_CLOCK         PORT_SEG_CLOCK->BRR  = (uint32_t)SEG_CLOCK

#define SET_LATCH         PORT_SEG_LATCH->BSRR = (uint32_t)SEG_LATCH
#define RST_LATCH         PORT_SEG_LATCH->BRR  = (uint32_t)SEG_LATCH

#define DISPLAY_DISABLE   PORT_SEG_ENB->BSRR   = (uint32_t)SEG_ENB
#define DISPLAY_ENABLE    PORT_SEG_ENB->BRR    = (uint32_t)SEG_ENB

#define SET_DATA          PORT_SEG_DATA->BSRR  = (uint32_t)SEG_DATA
#define RST_DATA          PORT_SEG_DATA->BRR   = (uint32_t)SEG_DATA
 
// Mode LED
#define SET_RED           PORT_LED_RED->BSRR        = (uint32_t)LED_RED
#define RST_RED           PORT_LED_RED->BRR         = (uint32_t)LED_RED

#define SET_GRN           PORT_LED_GRN->BSRR        = (uint32_t)LED_GRN
#define RST_GRN           PORT_LED_GRN->BRR         = (uint32_t)LED_GRN

#define SET_SEG3          NET_SEG3_GPIO_Port ->BRR   =  (uint32_t)NET_SEG3_Pin
#define RST_SEG3          NET_SEG3_GPIO_Port ->BSRR  =  (uint32_t)NET_SEG3_Pin
  
#define SET_SEG2          NET_SEG2_GPIO_Port ->BRR   =  (uint32_t)NET_SEG2_Pin
#define RST_SEG2          NET_SEG2_GPIO_Port ->BSRR  =  (uint32_t)NET_SEG2_Pin
  
#define SET_SEG1          NET_SEG1_GPIO_Port ->BRR   =  (uint32_t)NET_SEG1_Pin
#define RST_SEG1          NET_SEG1_GPIO_Port ->BSRR  =  (uint32_t)NET_SEG1_Pin
  
#define GRD_LED_ON        PORT_LED_RED -> BSRR      = (uint32_t)LED_RED;
#define GRD_LED_OFF       PORT_LED_RED -> BRR       = (uint32_t)LED_RED;
  
#define GRN_LED_ON        PORT_LED_GRN -> BSRR      = (uint32_t)LED_GRN;
#define GRN_LED_OFF       PORT_LED_GRN -> BRR       = (uint32_t)LED_GRN;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);
void SYSTEM_INIT(void);
/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
 
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
