/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

/* prototype */
void SystemClock_Config(void);
 
int main(void)
{
  SYSTEM_INIT();                                                                /* Peripheral initialization */
  INIT_APP();                                                                   /* configuration pin when power up */
  
  while(1)
  {
    if(Flag_Second)                                                             /* General Purpose Timer for timing event*/
    { 
      Flag_Second = RESET;                                                      /* Reset Flag*/
      GP_Timer();                                                               /* Every Second Activity*/  
   
    }; 
    if(Flag_DataReady == SET){                                                  /*/ Processign Recieved Data*/
      Flag_Communication = SET;
      Comm_TimeOut = 5;
      Flag_DataReady = RESET;				                        // Reset Flag
      if(RcvInput.Code == DATA_TFR)Flag_RCVDataReady = SET;
      else Manage_RcvData();
    };/* End of Data Ready */
    
    /* Sense button and perform functionality */
    KeyPad_Functionality();
    
    /* Scan Display */
    Scan_Display();
    LL_IWDG_ReloadCounter(IWDG);
    
  }; // End of Infinite Loop
}


void SYSTEM_INIT(void)
{
  HAL_Init();                                                                   //Intialization of all pheripheral
  SystemClock_Config();                                                         //Intialization the system clock
  MX_GPIO_Init();                                                               //Intialization of GPIO
  INIT_SW_I2C();
  INIT_RTC();                                                                   //Intialization of External RTC
  MX_RTC_Init();                                                                //Intialization of Internal RTC
  //MX_USART1_UART_Init();
  MX_USART2_UART_Init();                                                        //Intialization of USART 2
  MX_TIM3_Init();                                                               //Intialization of Timer
  
  MX_IWDG_Init();
}
/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
  while(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_2)
  {
  }

  /* HSE configuration and activation */
  LL_RCC_HSE_Enable();
  while(LL_RCC_HSE_IsReady() != 1)
  {
  }

  /* LSI configuration and activation */
  LL_RCC_LSI_Enable();
  while(LL_RCC_LSI_IsReady() != 1)
  {
  }
  LL_PWR_EnableBkUpAccess();
  /* Main PLL configuration and activation */
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_1, 16, LL_RCC_PLLR_DIV_3);
  LL_RCC_PLL_Enable();
  LL_RCC_PLL_EnableDomain_SYS();
  while(LL_RCC_PLL_IsReady() != 1)
  {
  }

  /* Set AHB prescaler*/
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /* Sysclk activation on the main PLL */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  }

  /* Set APB1 prescaler*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(64000000);

   /* Update the time base */
  if (HAL_InitTick (TICK_INT_PRIORITY) != HAL_OK)
  {
    Error_Handler();
  }
}
 
/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
