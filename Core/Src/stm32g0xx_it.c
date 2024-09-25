/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32g0xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "stm32g0xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */
   char GPS_Buffer[100];
   FlagStatus Flag_LinkRST;
   unsigned short GPS_FailTime;
   unsigned char Key_ScanTime;
/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim3;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M0+ Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
   while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
 if(Key_ScanTime)Key_ScanTime--;
  else
  {
    Key_ScanTime = 200; 
    Flag_Keyscan = SET;
    Key.RST = 0; Key.KeyStatus = 0;
  }
  
  /* increase toggle count */
  Toggle_Counter++;
  
  /* Checking the Toggle Count*/
  if(Toggle_Counter > 500)
  {
    
    Toggle_Counter = 0;
    
    /* Toggle Flag*/
    Flag_TGL ^= 1;
  }

  /* Scan Time */
  if(Scan_Time)Scan_Time--;
  else
    {
      Scan_Time = 499;
      
      if(Flag_Toggle == SET)Flag_Toggle = RESET;
      else Flag_Toggle = SET;

        
      if(Flag_Prog == RESET)
      {
      switch(LED_Color)
       {
        case RED_BLK    : SET_RED;
                          if(Flag_Toggle == SET){RST_GRN;}
                          else SET_GRN;
                          break;
        case RED_STB    : SET_RED;RST_GRN;
                          break;				
        case GREEN_BLK  : SET_GRN;
                          if(Flag_Toggle == SET){RST_RED;} else SET_RED;
                          break;
        case GREEN_STB :  SET_GRN;RST_RED;
                          break;
                  
       };
      };
    };
    
  Flag_mTick = SET;
 
  if(Tick)Tick--;
  else
  {
    Tick = 999;
    Flag_Second = SET; 
       
 
   
    if(Flag_GPSFix == RESET)GPS_FailTime++;
    else GPS_FailTime = 0;
    if(GPS_FailTime == 2)GPS_ON;
    if(GPS_FailTime >= 3600){GPS_FailTime = 0; GPS_OFF;}
    
    if(Comm_TimeOut)Comm_TimeOut--;
    else 
    {
      if(Flag_Communication)Flag_Communication = RESET;
    }
  }
  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32G0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32g0xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles TIM3 global interrupt.
  */
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */
  Flag_Tim_tick = SET;
  /* USER CODE END TIM3_IRQn 0 */
  HAL_TIM_IRQHandler(&htim3);
  /* USER CODE BEGIN TIM3_IRQn 1 */

  /* USER CODE END TIM3_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt / USART1 wake-up interrupt through EXTI line 25.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

  /* USER CODE END USART1_IRQn 0 */
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/**
  * @brief This function handles USART2 global interrupt / USART2 wake-up interrupt through EXTI line 26.
  */
void USART2_IRQHandler(void)
{
  char *GNSSPtr;
  uint8_t Gnss_RcvIn;
  static uint8_t RcvCnt_GNSS;                                                   // BUFFER COUNTER FOR GNSS
  
  GNSSPtr = NULL;
  if(LL_USART_IsActiveFlag_RXNE(USART2) == SET)                                 //Checking for UART2 interrupt has occurred or not.
  {
    Gnss_RcvIn = (unsigned short)(USART2->RDR & (unsigned short)0x01FF);
    if(Gnss_RcvIn == 10)
    {
      GNSS_Buffer[RcvCnt_GNSS] = 0;
      
      if((GNSSPtr = strstr((char*)GNSS_Buffer,"RMC,")) != NULL)
        {
         GNSSPtr += 4;
         strcpy((char *)GPS_DataIn,GNSSPtr);
         RcvCnt_GNSS = 0;
         if(GPS_DataIn[11] == 'A'){Flag_GPSDataReady = SET; Flag_GPSFix = SET;}
         else Flag_GPSFix = RESET;
        }
    }
    else
    {
      GNSS_Buffer[RcvCnt_GNSS] = Gnss_RcvIn;
      RcvCnt_GNSS++;if(RcvCnt_GNSS > 99)RcvCnt_GNSS = 0;
    };
  }
  else 
  {
    LL_USART_ClearFlag_TC(USART2);
    LL_USART_ClearFlag_ORE(USART2);
    LL_USART_ClearFlag_FE(USART2);
    //LL_USART_ClearFlag_NE(USART3);
    LL_USART_ClearFlag_PE(USART2);
    LL_USART_ClearFlag_IDLE(USART2);
    //LL_USART_ClearFlag_EOB(USART3);
    Gnss_RcvIn = (unsigned short)(USART2->RDR & (unsigned short)0x01FF);
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
