/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __Configure_CPU_H
#define __Configure_CPU_H

void INIT_GPIO(void);
void INIT_RCC(void);
void INIT_SLAVE_RTC(void);
void INIT_TIMER(void);
void INIT_NVIC(void);
void INIT_RTC(void);
void INIT_USART(void);
void INIT_DMA(void);
void INIT_EXTI(void);
void INIT_IWGD(void);
void INIT_SysTick(void);

#endif

