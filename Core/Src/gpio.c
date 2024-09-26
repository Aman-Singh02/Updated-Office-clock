/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  
  /*GPIO Ports for Clock Enable*/
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOF);
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOD);
  
  /**----------------------------------Output---------------------------------*/
  
  /*GPIO Ports for GPS ON*/
  GPIO_InitStruct.Pin = PIN_GPS;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PORT_GPS, &GPIO_InitStruct);
  
  /*GPIO Ports for SS-TEN*/
  GPIO_InitStruct.Pin = LED_GRN;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PORT_LED_GRN, &GPIO_InitStruct);
  
  /*GPIO Ports for NET SEG ON*/
  GPIO_InitStruct.Pin = NET_SEG3_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(NET_SEG3_GPIO_Port, &GPIO_InitStruct);
  
  /*GPIO Ports for NET SEG2 ON*/
  GPIO_InitStruct.Pin = NET_SEG2_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(NET_SEG2_GPIO_Port, &GPIO_InitStruct);
  
  /*GPIO Ports for NET SEG1 ON*/
  GPIO_InitStruct.Pin = NET_SEG1_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(NET_SEG1_GPIO_Port, &GPIO_InitStruct);

  /*GPIO Ports for SS-UNIT*/
  GPIO_InitStruct.Pin = LED_RED;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull =LL_GPIO_PULL_NO;
  LL_GPIO_Init(PORT_LED_RED, &GPIO_InitStruct);
  
  /*-------------------------------DRIVER IC----------------------------------*/
  
  /*GPIO Ports for CLK*/
  GPIO_InitStruct.Pin = SEG_CLOCK;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PORT_SEG_CLOCK, &GPIO_InitStruct);
  
  /*GPIO Ports for LAT*/
  GPIO_InitStruct.Pin = SEG_LATCH;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PORT_SEG_LATCH, &GPIO_InitStruct);

  /*GPIO Ports for ENB*/
  GPIO_InitStruct.Pin = SEG_ENB;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PORT_SEG_ENB, &GPIO_InitStruct);
  
  /*GPIO Ports for DATA*/
  GPIO_InitStruct.Pin = SEG_DATA;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PORT_SEG_DATA, &GPIO_InitStruct);

  /**----------------------------------input----------------------------------*/
  
  /*GPIO Ports for DEC*/
  GPIO_InitStruct.Pin = KEY_DEC;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(PORT_KDEC, &GPIO_InitStruct);
  
  /*GPIO Ports for INC*/
  GPIO_InitStruct.Pin = KEY_INC;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(PORT_KINC, &GPIO_InitStruct);
 
  /*GPIO Ports for INT*/
  GPIO_InitStruct.Pin = KEY_INT;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(PORT_KINT, &GPIO_InitStruct);
  
  /*GPIO Ports for K12_24*/
  GPIO_InitStruct.Pin = K12_24_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(K12_24_GPIO_Port, &GPIO_InitStruct);
  
  /*GPIO Ports for PRG*/
  GPIO_InitStruct.Pin = KEY_PRG;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(PORT_KPRG, &GPIO_InitStruct);
  
  /*--------------------------------------------------------------------------*/
 
 }

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
