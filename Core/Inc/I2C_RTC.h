

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RTC_H
#define __RTC_H

#define RTC_ADDRESS_Wr  0xD0
#define RTC_ADDRESS_Rd  0xD1


#define RTC_SS_REG      0x01
#define RTC_MM_REG      0x02
#define RTC_HH_REG      0x03
#define RTC_DD_REG      0x04
#define RTC_DT_REG      0x05
#define RTC_MH_REG      0x06
#define RTC_YY_REG      0x07
#define RTC_DC_REG      0x08
#define RTC_WD_REG      0x09
#define RTC_A1MH_REG    0x0A
#define RTC_A1DT_REG    0x0B
#define RTC_A1HH_REG    0x0C
#define RTC_A1MM_REG    0x0D
#define RTC_A1SS_REG    0x0E
#define RTC_FLAG_REG    0x0F
#define RTC_TmrV_REG    0x10
#define RTC_TmrC_REG    0x11
#define RTC_AC_REG      0x12
#define RTC_SQW_REG     0x13
#define RTC_A2MH_REG    0x14
#define RTC_A2DT_REG    0x15
#define RTC_A2HH_REG    0x16
#define RTC_A2MM_REG    0x17
#define RTC_A2SS_REG    0x18
#define RTC_RAM0_REG    0x19
#define RTC_RAM1_REG    0x1A
#define RTC_RAM2_REG    0x1B
#define RTC_RAM3_REG    0x1C
#define RTC_RAM4_REG    0x1D
#define RTC_RAM5_REG    0x1E
#define RTC_RAM6_REG    0x1F

void INIT_RTC(void);
void Write_RTC(unsigned char,unsigned char);
unsigned char Read_RTC(unsigned char);

#endif


