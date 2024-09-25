#include "main.h"

static uint32_t GetBank(uint32_t Addr);

/*******************************************************************************
* Function Name  : Key Scan
* Description    : Scan Telephonic Key Board
* Input          : None
* Output         : Key Pressed
* Return         : None
*******************************************************************************/
unsigned char Key_Scan(void)
{
  unsigned char key_press = 0;
  // Keys for Single Press
  if(LL_GPIO_IsInputPinSet(PORT_KPRG,KEY_PRG) == RESET && Key.PRG == RESET && Flag_KeyPrg == RESET)
  {
    Flag_KeyPrg = SET;
    Key.PRG = SET;
    key_press = PRG_KEY;
    
  };
  if(LL_GPIO_IsInputPinSet(PORT_KPRG,KEY_PRG) == SET)Flag_KeyPrg = RESET;
  
  if(LL_GPIO_IsInputPinSet(K12_24_GPIO_Port,K12_24_Pin) == RESET && Key.K1224 == RESET && Flag_Key1224 == RESET)
  {
    Flag_Key1224 = SET;
    Key.K1224 = SET;
    key_press = K1224_KEY;
    
  };
  if(LL_GPIO_IsInputPinSet(K12_24_GPIO_Port,K12_24_Pin) == SET)Flag_Key1224 = RESET;
  
  // Keys for Multi Press
  if(LL_GPIO_IsInputPinSet(PORT_KINC,KEY_INC) == RESET && Key.INC == RESET)
  {
    Key.INC = SET;
    key_press = INC_KEY;  
  }
  
  else if(LL_GPIO_IsInputPinSet(PORT_KDEC,KEY_DEC) == RESET && Key.DEC == 0)
  {
    Key.DEC = SET;
    key_press = DEC_KEY;
    
  }
  
  else if(LL_GPIO_IsInputPinSet(PORT_KINT,KEY_INT) == RESET && Key.INT == 0)
  {
    Key.INT = SET;
    key_press = INT_KEY;
    
  };
  return(key_press);
  
}
/*******************************************************************************
* Function Name  : Program Clock
* Description    : Program Master & Slave Clock
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Program_Clock(unsigned char Hour, unsigned char Min, unsigned char Sec)
{
 // Prograsm Master Clock
  Write_RTC(RTC_SS_REG,Sec);
  Write_RTC(RTC_MM_REG,Min);
  Write_RTC(RTC_HH_REG,Hour);

 }
/*******************************************************************************
* Function Name  : Program_Mode
* Description    : Programming fo Master Clock
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Program_Mode(void)
{
  ModeCounter = 0;
  if(LL_GPIO_IsInputPinSet(PORT_LED_GRN,LED_GRN) == SET){RST_GRN;SET_RED;}
  else {RST_RED;SET_GRN;};
  switch (Prog_State)
   {
    case HOUR : switch(Key_Entry)
                 {
                  case INC_KEY : Key_Entry = NONE; PRG_HH++;
		                 if(PRG_HH > 23)PRG_HH = 0;
		                 break;
		  case DEC_KEY : Key_Entry = NONE; PRG_HH--;
		                 if(PRG_HH > 23)PRG_HH = 23;
		                 break;
                  case PRG_KEY : Key_Entry = NONE;Prog_State = MIN;
		                 break;
		  case INT_KEY : Key_Entry = NONE;Prog_State = INT_DAY;
                                 DayInt = (4 - DayInt)*25;
                                 NightInt = (4 - NightInt)*25;
                                 if(DayInt == 0)DayInt = 100;
                                 if(NightInt == 0)NightInt = 100;
		                 break;
                  default      : break;				
		  };
                 Flag_Toggle = SET;
                 Display_RAM[0] = PRG_HH/10;Display_RAM[1] = PRG_HH%10;
		 Display_RAM[2] = Display_RAM[3] = BLANK;
                 break;
     case MIN : switch(Key_Entry)
                 {
                  case INC_KEY : Key_Entry = NONE; PRG_MM++;
		                 if(PRG_MM > 59)PRG_MM = 0;
		                 break;
		  case DEC_KEY : Key_Entry = NONE; PRG_MM--;
		                 if(PRG_MM > 59)PRG_MM = 59;
		                 break;
                  case PRG_KEY : Key_Entry = NONE;Prog_State = HOLD;
		                 break;
		  default      : break;		
		  };
                 Flag_Toggle = SET;
                 Display_RAM[2] = PRG_MM/10;Display_RAM[3] = PRG_MM%10;
		         break;

    case HOLD : if(Flag_Toggle == SET)
                   {
		    Display_RAM[0] = PRG_HH/10;Display_RAM[1] = PRG_HH%10;
		    Display_RAM[2] = PRG_MM/10;Display_RAM[3] = PRG_MM%10;
		   }
		else
		   {
                    Display_RAM[0] = Display_RAM[1] = BLANK;
		    Display_RAM[2] = Display_RAM[3] = BLANK;
		   };
		
		if(Key_Entry == PRG_KEY){Program_Clock(PRG_HH,PRG_MM,0);Flag_Prog = RESET;Key_Entry = NONE;}
		
		break;

 case INT_DAY : switch(Key_Entry)
                 {
                  case INC_KEY : Key_Entry = NONE; DayInt += 25;
		                 if(DayInt > 100)DayInt = 25;
				 break;
		  case DEC_KEY : Key_Entry = NONE; DayInt -= 25;
		                 if(DayInt > 100 || DayInt == 0)DayInt = 100;
				 break;
                  case PRG_KEY : Key_Entry = NONE;Prog_State = INT_NIGHT;
		                 break;
		  default      : break;		
		  };
                 Flag_Toggle = SET;
                 if(DayInt == 100){Display_RAM[2] = 9;Display_RAM[3] = 9; }
		   else {Display_RAM[2] = DayInt/10;Display_RAM[3] = DayInt%10; }
                 Display_RAM[0] = I, Display_RAM[1] = d;

                 break;		
		
case INT_NIGHT : switch(Key_Entry)
                 {
                  case INC_KEY : Key_Entry = NONE; NightInt += 25;
		                 if(NightInt > 100)NightInt = 25;
				 break;
		  case DEC_KEY : Key_Entry = NONE; NightInt -= 25;
		                 if(NightInt > 100 || NightInt == 0)NightInt = 100;
				 break;
                  case PRG_KEY : Key_Entry = NONE;
		                 
		
				 DayInt = (100 - DayInt)/25;
				 NightInt = (100 - NightInt)/25;
				
				 	
				 if(PRG_HH > 7 && PRG_HH < 19)DutyCycle = DayInt;
				 else DutyCycle = NightInt;
				 Flag_Intensity = SET;				
				 Flag_Prog = RESET;
                                 
                                 DayInt_self = DayInt;
                                 NightInt_self = NightInt;
                                 Save_Time = 5;
		                 break;
		   default      : break;		
		  };
                 Flag_Toggle = SET;
                 if(NightInt == 100){Display_RAM[2] = 9;Display_RAM[3] = 9; }
		  else {Display_RAM[2] = NightInt/10;Display_RAM[3] = NightInt%10; }
		 Display_RAM[0] = I, Display_RAM[1] = n;
                 
                
	          break;	
   };

}

/*******************************************************************************
* Function Name  : Manage_RcvData
* Description    : Manage recieved data
* Input          : none
* Output         : None
* Return         : None
*******************************************************************************/


void Manage_RcvData(void)
 {

   switch(RcvInput.Code)
	 {
	  case LNK_CHK :  memset(TxBuffer,0,10);
                          //SET_RxTx;
	                  TxBuffer[0] = 0xAA;TxBuffer[1] = 0xCC;                    // Header
			  TxBuffer[2] = 4;TxBuffer[3] = BoardAddress;               // Length & Source
			  TxBuffer[4] = 0x00;                                       // Destination Master Clock
			  TxBuffer[5] = LNK_CHK;                                    // Code - Link Check
			  TxBuffer[6] = 0x80 | (DutyCycle + 1);                     // Link & Duty Cycle
			  /* DMA Buffer Size */
			  //DMA1_Channel7->CNDTR = 7;
			  /* Enable DMA1 Channel7 */
			 // DMA_Cmd(DMA1_Channel7, ENABLE);
			  break;
			
	  case SET_CFG  : DayInt = Rcv_DataIn[0];
                          if(DayInt > 3)DayInt_Com = 0;
			  NightInt = Rcv_DataIn[1];
                          if(NightInt > 3)NightInt_Com = 2;

			  
                           
			  if(Clock_Mode == MASTER)
			   {
			    if(MST_HH > 7 && MST_HH < 19)DutyCycle = DayInt;
			    else DutyCycle = NightInt;
			   }
			  else if(Clock_Mode == SLAVE)
			   {
			    if(SLV_HH > 7 && SLV_HH < 19)DutyCycle = DayInt;
			      else DutyCycle = NightInt;
			   }
                          
                           DayInt_Com = DayInt;
                           NightInt_Com = NightInt;
                            Save_Time = 5;
			  Flag_Intensity = SET;	
			  break;
	
			
     };// End of Switch
 }

/*******************************************************************************
* Function Name  : Delay_Cycles
* Description    : Insert Delay of cycles
* Input          : val Number of cycle
* Output         : None
* Return         : None
*******************************************************************************/

void Delay_Cycles(unsigned int val)
{
  while(val)
    {
     __NOP();
     val--;
    };
}

/*******************************************************************************
* Function Name  : DISABLE_ROW
* Description    : Disable All Rows
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DISABLE_CLOCK(void)
{
  NET_SEGMENT_ON_GPIO_Port ->BSRR  = (uint32_t)NET_SEGMENT_ON_Pin; 
  NET_SEGMENT_ON2_GPIO_Port->BSRR  = (uint32_t)NET_SEGMENT_ON2_Pin;
  NET_SEGMENT_ON1_GPIO_Port->BSRR  = (uint32_t)NET_SEGMENT_ON1_Pin;

}

/*******************************************************************************
* Function Name  : GP_Timer
* Description    : General Purpose TImer Decrements every 1 second
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GP_Timer(void)
 { 
   if(Save_Time)Save_Time--;
   if(Save_Time == 1) Write_Config();
   
  if(ReCheck_Time)ReCheck_Time--;                                               // Re check for Mode
  else
   {
    if(Flag_Init == SET)
    {
      Flag_Init = RESET;
      Flag_Intensity = SET;
    };
 
    ReCheck_Time = 5;
    Flag_GPSActive = RESET;Flag_RCVActive = RESET;
    if(Flag_GPSDataReady == SET)
     {
      Flag_GPSDataReady = RESET;

      GPS_HH = (GPS_DataIn[0]  -'0')*10 + GPS_DataIn[1] - '0';
      GPS_MM = (GPS_DataIn[2] - '0')*10 + GPS_DataIn[3] - '0';
      GPS_SS = (GPS_DataIn[4] - '0')*10 + GPS_DataIn[5] - '0';
      
           if((Flag_1224_Com == RESET) && (Rcv_DataIn[6] == 'U')){Flag_1224_Com = SET;   Save_Time = 5;}
      else if((Flag_1224_Com ==   SET) && (Rcv_DataIn[6] != 'U')){Flag_1224_Com = RESET; Save_Time = 5;}
      
      /* Formating Time in india standard */
       if (GPS_HH < 24 && GPS_MM < 60)
	{
	 GPS_HH += 5;GPS_MM += 30;                                              /* adding 5:30 in GPS time */
         if(GPS_MM > 59){GPS_MM -= 60;GPS_HH++;};                               /* maintening minute       */                   
         if(GPS_HH > 23)GPS_HH -= 24;                                           /* maintening hour         */
         if(Clock_Mode == MASTER)
         {
           MST_MM = Read_RTC(RTC_MM_REG);                                        /* Reading minute from external RTC */
           MST_HH = Read_RTC(RTC_HH_REG);                                        /* Reading hour from external RTC   */
           MST_SS = Read_RTC(RTC_SS_REG);
           
           /* Checking if gps time and external rtc time doesn't match then programming external clock */
           if(GPS_HH != MST_HH || GPS_MM != MST_MM)
           {
             /* programming the external RTC */
             Program_Clock(GPS_HH,GPS_MM,GPS_SS);
           }
         }
         else
          {
           /* getting time */
           HAL_RTC_GetTime(&hrtc,&gTime,RTC_FORMAT_BIN);
           
           /* inserting time */
           SLV_HH = gTime.Hours;
           SLV_MM = gTime.Minutes;
           SLV_SS = gTime.Seconds;

           /* Checking GPS time and internal rtc time  */
           if(GPS_HH != SLV_HH || GPS_MM != SLV_MM)Program_Clock(GPS_HH,GPS_MM,GPS_SS);
           Clock_Mode = MASTER;
          };
          Flag_GPSActive = SET;
          GPS_DataIn[11] = 'V';
        };
     }
    
    /**------------- Recieve Data through Uart Configuration UART1 -----------------*/
    else if(Flag_RCVDataReady == SET)
     {
      Flag_RCVDataReady = RESET;
      RCV_HH = Rcv_DataIn[0]*10 + Rcv_DataIn[1];
      RCV_MM = Rcv_DataIn[2]*10 + Rcv_DataIn[3];
      RCV_SS = Rcv_DataIn[4]*10 + Rcv_DataIn[5];
      
         if((Flag_1224_Com == RESET) && (Rcv_DataIn[6] == 'U')){Flag_1224_Com = SET; Save_Time = 5;}
      else if((Flag_1224_Com == SET) && (Rcv_DataIn[6] != 'U')){Flag_1224_Com = RESET; Save_Time = 5;}
      
      if (RCV_HH < 24 && RCV_MM < 60)
	{
	 if(Clock_Mode == MASTER)
          {
          MST_MM = Read_RTC(RTC_MM_REG);
          MST_HH = Read_RTC(RTC_HH_REG);
          if(RCV_HH != MST_HH || RCV_MM != MST_MM)Program_Clock(RCV_HH,RCV_MM,RCV_SS);
	  }
         else
          {
            /* getting time */
           HAL_RTC_GetTime(&hrtc,&gTime,RTC_FORMAT_BIN);
           
           /* inserting time */
           SLV_HH = gTime.Hours;
           SLV_MM = gTime.Minutes;
           SLV_SS = gTime.Seconds;
           
           /* Checking slave hour and receive hour doesn't match then program external clock */
           if(RCV_HH != SLV_HH || RCV_MM != SLV_MM)Program_Clock(RCV_HH,RCV_MM,RCV_SS);
           Clock_Mode = MASTER;
          };
         Flag_RCVActive = SET;
        };
     };
   };


 ModeCounter++;                                                                // Check Mode of Clock
  if(ModeCounter > 5)                                                           // If not reset by clock mode for 6 times
     {
      if(Clock_Mode < SLAVE)Clock_Mode = SLAVE;
      ModeCounter = 0;                                                          //  Reset Mode Counter
     };
 }

/*******************************************************************************
* Function Name  : Key_Function
* Description    : perform Keypad functionality 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Key_Function(void)
{
  /* If the PRG_KEY is pressed and the programming flag is not set */
  if (Key_Entry == PRG_KEY && Flag_Prog == RESET)
  {
    /* Set the program hour and minute based on the clock mode (MASTER/SLAVE) */
    if(Clock_Mode == MASTER)
    {
      PRG_HH = MST_HH; 
      PRG_MM = MST_MM;
    }
    else 
    {
      PRG_HH = SLV_HH; 
      PRG_MM = SLV_MM;
    }
    
    /* Set the programming state to HOUR and enable the programming flag */
    Prog_State = HOUR;
    Flag_Prog = SET;
    
    /* Reset the key entry and other related flags/variables */
    Key_Entry = NONE;
    Key.RST = SET;
    Sec_Tick = 0;
  }
  /* If the K1224_KEY is pressed */
  else if(Key_Entry == K1224_KEY)
  {
    /* Toggle the 12/24-hour mode if the key is pressed */
    if(LL_GPIO_IsInputPinSet(K12_24_GPIO_Port, K12_24_Pin) == RESET)
    { 
      /* Toggle the 12/24-hour mode flag */
      if(Flag_1224_self == SET)
        Flag_1224_self = RESET;
      else 
        Flag_1224_self = SET; 
      
      /* Set the save time to 5 and reset key and seconds tick */
      Save_Time = 5;
      Key.RST = SET;
      Sec_Tick = 0;
    }
  }
  /*Check if the INT_KEY is pressed and the programming flag is not set */
  else if(Key_Entry == INT_KEY && Flag_Prog == RESET)
  {
    /* Increment the duty cycle, reset if it exceeds 3 */
    DutyCycle++;
    if(DutyCycle > 3)
      DutyCycle = 0;
    
    /* Adjust intensity based on the clock mode and time of day */
    if(Clock_Mode == MASTER)
    {
      if(MST_HH > 7 && MST_HH < 19)
        DayInt = DutyCycle;
      else 
        NightInt = DutyCycle;
    }
    else if(Clock_Mode == SLAVE)
    {
      if(SLV_HH > 7 && SLV_HH < 19)
        DayInt = DutyCycle;
      else 
        NightInt = DutyCycle;
    }
    
    /* Update self intensity values */
    DayInt_self = DayInt;
    NightInt_self = NightInt;
    
    /* Set the save time, intensity flag, and reset key and seconds tick */
    Save_Time = 5; 
    Flag_Intensity = SET;
    Key.RST = SET;
    Sec_Tick = 0;
  }
}

/*******************************************************************************
* Function Name  : Get_Config
* Description    : Get The Configuration Values
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Get_Config(void)
  {
     uint64_t FlashAddress = 0,FlashData = 0;
    /****** FLASH READING *****************************************************/
    FlashAddress = ADDR_FLASH_PAGE_15; 
    FlashData = (*(uint64_t*) FlashAddress);                      // VERIFY FLASH DATA 
   
    FlashData =  (FlashData >> 24) & 0xff;
    if(FlashData == 0xED)                                                     // Signature Byte
    { 
      FlashData =(*(uint64_t*) FlashAddress);FlashAddress += 8; 
      DutyCycle = (FlashData >> 16) & 0xff;
      if(FlashData & 0x02 == 1)Flag_1224_Com  = SET; else Flag_1224_Com  = RESET;
      if(FlashData & 0x01 == 1)Flag_1224_self = SET; else Flag_1224_self = RESET;
 
      
        FlashData    = (*(uint64_t*) FlashAddress);FlashAddress += 8; 
        DayInt_Com   =  FlashData >> 24;
        NightInt_Com = (FlashData >> 16) & 0xff;
        DayInt_self  = (FlashData >>  8) & 0xff;
        NightInt_self = FlashData & 0xff;
    }
    else 
    {
      DayInt = 0; 
      NightInt = 2; 
      Flag_1224 = RESET;
        
      DayInt_Com        = 0;
      NightInt_Com      = 2;
      Flag_1224_Com     = RESET;
      
      DayInt_self        = 0;
      NightInt_self      = 2;
      Flag_1224_self     = RESET;
      
      Write_Config();
    }
  }
  
/*******************************************************************************
* Function Name  : Write_Default
* Description    : Write Default Data in Flash Memory
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Write_Config(void)
{
  uint32_t FirstPage = 0, NbOfPages = 0;
  uint32_t FlashAddress = 0, PageError = 0,FlashData = 0;
  __IO uint32_t MemoryProgramStatus = 0;
  __IO uint32_t data32 = 0;
  
  FLASH_EraseInitTypeDef EraseInitStruct;
  /* Unlock the Flash to enable the flash control register access *************/
  HAL_FLASH_Unlock();
  
  /* Clear OPTVERR bit set on virgin samples */
  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);
  /* Get the 1st page to erase */
  FirstPage = GetPage(ADDR_FLASH_PAGE_15);
  
  /* Get the number of pages to erase from 1st page */
  NbOfPages = GetPage(FLASH_USER_END_ADDR) - FirstPage + 1;
  
  /* Fill EraseInit structure*/
  EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
  EraseInitStruct.Page        = FirstPage;
  EraseInitStruct.NbPages     = NbOfPages;
  EraseInitStruct.Banks       = FLASH_BANK_1;
  
  /* Note: If an erase operation in Flash memory also concerns data in the data or instruction cache,
  you have to make sure that these data are rewritten before they are accessed during code
  execution. If this cannot be done safely, it is recommended to flush the caches by setting the
  DCRST and ICRST bits in the FLASH_CR register. */
  if (HAL_FLASHEx_Erase(&EraseInitStruct, &PageError) != HAL_OK)
  {}
  FlashAddress = ADDR_FLASH_PAGE_15;
  /*----- FLASH HALFWORD PROGRAM ----------------------------------------------*/
  
  FlashData = 0xED << 24|DutyCycle << 16|Flag_1224_Com << 1|Flag_1224_self;
  HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,FlashAddress,FlashData);FlashAddress += 8;	             // SIGNATURE 
  
  FlashData = DayInt_Com << 24|NightInt_Com << 16|DayInt_self << 8|NightInt_self;
  HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,FlashAddress,FlashData);FlashAddress += 8;               // DAY TIME INTENSITY OF MASTER COMMUNICATION 
  
  /*Lock Flash memory*/
  HAL_FLASH_OB_Lock();
  HAL_FLASH_Lock();    
}

/*******************************************************************************
* Function Name  : GetPage
* Description    : Perform Key pad functionality based on button press
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint32_t GetPage(uint32_t Addr)
{
  return (Addr - FLASH_BASE) / FLASH_PAGE_SIZE;;
}

/*******************************************************************************
* Function Name  : KeyPad_Functionality
* Description    : Perform Key pad functionality based on button press
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void KeyPad_Functionality(void)
{
    /* Sensing button input */
    if(Flag_Keyscan)
    {
        Flag_Keyscan = RESET;
        Key_Entry = Key_Scan();
        
        /* If a key is detected, call the Key_Function to handle the keypress */
        if(Key_Entry)Key_Function();
    } /* End of button sensing */ 
    
    /* Enter program mode if the programming flag is set */
    if(Flag_Prog == SET)
    {
        Program_Mode();
        Key.RST = SET;
    }
    else
    {
        /* Clock mode selection based on the current Clock_Mode */
        switch(Clock_Mode)
        {
            case MASTER:  
                /* Check and update the master clock time */
                if(Flag_CheckTime == SET)
                {
                    Flag_CheckTime = RESET;
                    MST_SS = Read_RTC(RTC_SS_REG);
                }
                
                /* Update display and intensity based on time and communication flags */
                if(MST_SS != Old_SS)
                {
                  /* making mode zero*/
                    ModeCounter = 0;
                    
                    /* Update LED color based on GPS and RCV activity */
                         if(Flag_GPSActive == SET)LED_Color = RED_BLK;       
                    else if(Flag_RCVActive == SET)LED_Color = GREEN_STB;
                    else LED_Color = GREEN_BLK;                                                              
                    
                    /* Reading time from external rtc*/
                    MST_MM = Read_RTC(RTC_MM_REG);
                    MST_HH = Read_RTC(RTC_HH_REG);
                    MST_SS = Read_RTC(RTC_SS_REG);
                    
                    /* Adjust 12/24 hour mode based on communication and self settings */
                    if(Flag_Communication)Flag_1224 = Flag_1224_Com ? SET : RESET;else Flag_1224 = Flag_1224_self ? SET : RESET;
                    
                    /* Adjust intensity based on the time of day */
                    if(MST_HH > 7 && MST_HH < 19)
                    {
                      if(Flag_Communication && (DayInt != DayInt_Com))
                      {
                        DayInt = DayInt_Com;
                        Flag_Intensity = SET;
                        DutyCycle = DayInt;
                      }
                      else if(!Flag_Communication && (DayInt != DayInt_self))
                      {
                        DayInt = DayInt_self;
                        Flag_Intensity = SET;
                        DutyCycle = DayInt;
                      }
                    }
                    else 
                    {
                      if(Flag_Communication && (NightInt != NightInt_Com))
                      {
                        NightInt = NightInt_Com;
                        Flag_Intensity = SET;
                        DutyCycle = NightInt;
                      }
                      else if(!Flag_Communication && (NightInt != NightInt_self))
                      {
                        NightInt = NightInt_self;
                        Flag_Intensity = SET;
                        DutyCycle = NightInt;
                      }
                    }
                    
                    /* Handle 12/24 hour display logic */
                    if(Flag_1224 == SET && MST_HH > 12)
                        DISP_HH = MST_HH - 12;  // Adjust for 12-hour format
                    else 
                        DISP_HH = MST_HH;
                    
                    /* Update display RAM with the current hour and minute */
                    Display_RAM[0] = DISP_HH / 10;
                    Display_RAM[1] = DISP_HH % 10;
                    Display_RAM[2] = MST_MM  / 10;
                    Display_RAM[3] = MST_MM  % 10;
                    Display_RAM[4] = MST_SS  / 10;
                    Display_RAM[5] = MST_SS  % 10;
                    
                    Old_SS = MST_SS;
                    
                    /* Adjust duty cycle at specific times */
                    if(MST_HH == 7 && MST_MM == 0 && MST_SS == 0)
                    {
                        DutyCycle = DayInt;
                        Flag_Intensity = SET;
                    }
                    
                    if(MST_HH == 19 && MST_MM == 0 && MST_SS == 0)
                    {
                        DutyCycle = NightInt;
                        Flag_Intensity = SET;
                    }
                }
                break;
            
            case SLAVE:  
                /* Check and update the slave clock time */
                if(Flag_SLAVE == SET)
                {
                    Flag_SLAVE = RESET;
                    ModeCounter = 0;
                    LED_Color = RED_STB;
                    
                    SLV_SS = (RTC_Count % 3600) % 60;
                    SLV_MM = (RTC_Count % 3600) / 60;
                    SLV_HH = RTC_Count / 3600;
                    
                    /* Adjust 12/24 hour mode based on communication and self settings */
                    if(Flag_Communication)
                        Flag_1224 = Flag_1224_Com ? SET : RESET;
                    else 
                        Flag_1224 = Flag_1224_self ? SET : RESET;
                    
                    /* Adjust intensity based on the time of day */
                    if(SLV_HH > 7 && SLV_HH < 19)
                    {
                        if(Flag_Communication && (DayInt != DayInt_Com))
                        {
                            DayInt = DayInt_Com;
                            Flag_Intensity = SET;
                            DutyCycle = DayInt;
                        }
                        else if(!Flag_Communication && (DayInt != DayInt_self))
                        {
                            DayInt = DayInt_self;
                            Flag_Intensity = SET;
                            DutyCycle = DayInt;
                        }
                    }
                    else 
                    {
                        if(Flag_Communication && (NightInt != NightInt_Com))
                        {
                            NightInt = NightInt_Com;
                            Flag_Intensity = SET;
                            DutyCycle = NightInt;
                        }
                        else if(!Flag_Communication && (NightInt != NightInt_self))
                        {
                            NightInt = NightInt_self;
                            Flag_Intensity = SET;
                            DutyCycle = NightInt;
                        }
                    }
                    
                    /* Handle 12/24 hour display logic */
                    if(Flag_1224 == SET && SLV_HH > 12)
                        DISP_HH = SLV_HH - 12;  // Adjust for 12-hour format
                    else 
                        DISP_HH = SLV_HH;
                    
                    /* Update display RAM with the current hour and minute */
                    Display_RAM[0] = DISP_HH / 10;
                    Display_RAM[1] = DISP_HH % 10;
                    Display_RAM[2] = SLV_MM / 10;
                    Display_RAM[3] = SLV_MM % 10;
                    
                    /* Adjust duty cycle at specific times */
                    if(SLV_HH == 7 && SLV_MM == 0 && SLV_SS == 0)
                    {
                        DutyCycle = DayInt;
                        Flag_Intensity = SET;
                    }
                    
                    if(SLV_HH == 19 && SLV_MM == 0 && SLV_SS == 0)
                    {
                        DutyCycle = NightInt;
                        Flag_Intensity = SET;
                    }
                }
                break;
        } // End of Switch 	
    } // End of Else Prog
}

/*******************************************************************************
* Function Name  : Scan_Display
* Description    : display time task performing
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Scan_Display(void)
{
  
  /**-----------------  SENDING DATA TO SHIFT REGISTER IC --------------------*/
    /* Start segment scanning if the segment update flag is set */
  if(Flag_SegUpdate == SET)
  {
    Flag_SegUpdate = RESET;                                                     /* Reset the segment update flag */
    
    /* Prepare the data for the next digit */
    DisplayData = BitMap_DATA[Display_RAM[NextDigit]];
    
    /* Toggle Dot */
    if(Flag_TGL){DisplayData = DisplayData ^ (1 << 1);DisplayData = DisplayData ^ (1 << 2);}
    
    /* assign 1 in segmultiplyer*/
    SegMult = 0x01;
   
    /* Transmit the segment data by shifting bits and generating clock pulses */
    for(GP_Counter = 0; GP_Counter < 16; GP_Counter++)                          /* Process 16 bits for the segment */
    {
      /* Creating Serial Data */
      if(DisplayData & SegMult)SET_DATA;else RST_DATA;
      
      /* Create Clock */
      Delay_Cycles(50);SET_CLOCK;Delay_Cycles(50);RST_CLOCK;
      
      /* bit shifting */
      SegMult = SegMult << 1;
    }
    
    SegMult = 0x01;
    /* Repeat the same process for the next digit */
    DisplayData = BitMap_DATA[Display_RAM[NextDigit + 1]];
    
    /* Toggle Dot */
    if(Flag_TGL){DisplayData = DisplayData ^ (1 << 1);DisplayData = DisplayData ^ (1 << 2);}
    
        for(GP_Counter = 0; GP_Counter < 16; GP_Counter++)                      /* Process 16 bits for the segment */
        {
          /* Creating Serial Data */
          if(DisplayData & SegMult)SET_DATA;else RST_DATA;
          
          /* Create Clock */
          Delay_Cycles(50);SET_CLOCK;Delay_Cycles(50);RST_CLOCK;
          
          /* bit shifting */
          SegMult = SegMult << 1;
        }
    
         Flag_SegReady = SET;                                                    /* Indicate that the segment data is ready for the next digit */
    } /* End of segment scanning */
    

    /**------------------------ Adjust the duty cycle  -----------------------*/
    if(Flag_Tim_tick == SET)
    {
        Flag_Tim_tick = RESET;
        Duty_Count++;
        
        /* Disable the clock if the duty count exceeds the duty cycle  */
        if(Duty_Count > DutyCycle){DISABLE_CLOCK();}
        
        /* If duty count exceeds 3, reset and prepare for the next digit scan */
        if(Duty_Count > 3){Flag_DigitScan = SET;Duty_Count = 0;}
    }
    
    /** --------------- turning segment on and off ---------------------------*/
    /* Start digit scanning if the digit scan flag is set */
    if(Flag_DigitScan == SET)
    {
        Flag_DigitScan = RESET;                                                 /* Reset the digit scan flag      */
        Flag_SegReady = RESET;                                                  /* Reset the segment ready flag   */
        DISABLE_CLOCK();                                                        /* Turn off all Segments          */
        Delay_Cycles(50);SET_LATCH;Delay_Cycles(50);  RST_LATCH;                /* Latch the next data set        */

        
        /* Select the digit to display and set the next digit */
        switch(DigitCount)
        {
            case 0: SET_SEG1; NextDigit = 2; break;                             /* Display Hour Tenth             */
            case 1: SET_SEG2; NextDigit = 4; break;                             /* Display Hour Unit              */
            case 2: SET_SEG3; NextDigit = 0; break;                             /* Display Minute Tenth           */
        }
        DigitCount++;                                                           /* Increment the digit counter    */
        
        /* If all digits have been scanned, reset the counter and set the check time flag */
        if(DigitCount > 3){DigitCount = 0;Flag_CheckTime = SET;}

        Flag_SegUpdate = SET;                                                   /* Set the flag for the next segment scan */
    }
  
}
 
/*******************************************************************************
* Function Name  : GetBank
* Description    : choosing bank based on address
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static uint32_t GetBank(uint32_t Addr)
{
  return FLASH_BANK_1;
}