/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __Functions_H
#define __Functions_H
 
void Scan_Display(void);
void KeyPad_Functionality(void);
unsigned char Key_Scan(void);
void Program_Clock(unsigned char,unsigned char,unsigned char);
void Program_Mode(void);
void Manage_RcvData(void);
void Delay_Cycles(unsigned int);
void DISABLE_CLOCK(void);
void GP_Timer(void);
void Key_Function(void);
void Get_Config(void);
void Write_Config(void);
uint32_t GetPage(uint32_t Addr);
#endif
