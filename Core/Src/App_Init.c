/******************** (C) COPYRIGHT 2008 DAN ELECTRONICS ********************
* File Name          : App_init.c
* Author             : Aman Singh
* Date               : 26/09/2024
* Description        : This file provides all Application Initialization func.
*****************************************************************************/
#include "main.h"

void INIT_APP(void)
{
/* Get configuration from flash */  
Get_Config();

  while(LL_GPIO_IsInputPinSet(K12_24_GPIO_Port, K12_24_Pin) == RESET)
  {
   SegMult = 0x0001;

   DisplayData = BitMap_DATA[Display_RAM[NextDigit]];                           //Taking the data to display Selected Bitmap

   for(GP_Counter = 0;GP_Counter < 16; GP_Counter++)
      {
        if(DisplayData & SegMult)SET_DATA; else RST_DATA;
	SET_CLOCK;Delay_Cycles(200);   RST_CLOCK;Delay_Cycles(200);
        SegMult = SegMult << 1;
      };

     NextDigit++;SegMult = 0x01;   
    

    for(GP_Counter = 0;GP_Counter < 16; GP_Counter++)
      {
        if(DisplayData & SegMult)SET_DATA; else RST_DATA;
	SET_CLOCK; Delay_Cycles(200);   RST_CLOCK;Delay_Cycles(200);
        SegMult = SegMult << 1;
      };
    
      DISABLE_CLOCK();                           				// Turn OFF all ROWS First
      Delay_Cycles(10);								// Delay to remove ghost Image
      SET_LATCH;Delay_Cycles(10); RST_LATCH;					// Set Latch for nect data set
      if(Flag_Intensity == SET)
      {Flag_Intensity = RESET;Sec_Tick = 0;/*INIT_TIMER();*/};                  // Set Intensity
      switch (DigitCount)							// Select Digit & enable
          {
           case 0 : SET_SEG1; NextDigit = 1; break;			        // Display Hour Tenth
	   case 1 : SET_SEG2; NextDigit = 2; break;			        // Display Houm Unit
	   case 2 : SET_SEG3; NextDigit = 0; break;			        // Display Min Tenth
	 };

      DigitCount++;								// Increment Counter
      if(DigitCount >= 3){DigitCount = 0;Flag_CheckTime = SET;};		// if all digits scaned reset

  };                                                                            // For Address display at Startup
    
  ModeCounter = 0;
  Clock_Mode = MASTER;
  Flag_SegUpdate = SET;
  Flag_Intensity = SET;
  NextDigit = 1;
  DISPLAY_ENABLE;
}