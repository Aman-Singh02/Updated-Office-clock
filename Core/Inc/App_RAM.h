
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __Application_RAM_H
#define __Application_RAM_H

extern RTC_DateTypeDef gDate; 
extern RTC_TimeTypeDef gTime;


#define GPS_BufferSize  100
#define DATA_BufferSize 100
/* USART Base Registors for DMA Transfer */
#define USART1_DR_Base  0x40013804
#define USART2_DR_Base  0x40004404

/************************************/
/* DEFINATION FOR GPS COMM Packet   */
/************************************/
#define Init_GPS           0
#define Get_Str_G          1
#define Get_Str_P          2
#define Get_Str_R          3
#define Get_Str_M          4
#define Get_Str_C          5
#define Get_Str_CMA        6
#define Get_GPS_DATA       7

/************************************/
/* DEFINATION FOR Comm. Packet      */
/************************************/
#define Init_RCV          0
#define Get_ADD           1
#define Get_Length        2
#define Get_Source        3
#define Get_Desti         4
#define Get_Code          5
#define Get_Data          6

/************************************/
/* DEFINATION FOR DataTransfer      */
/************************************/
#define LNK_CHK           0x80
#define DATA_TFR          0x81
#define SET_CFG           0x82

/************************************/
/* DEFINATION Clock Progmming       */
/************************************/

#define HOUR              1
#define MIN               2
#define HOLD              3
#define INT_DAY           4
#define INT_NIGHT         5



/************************************/
/* DEFINATION FOR LED Inidcator     */
/************************************/
#define RED_BLK           3                                                     //reverse
#define RED_STB           2
#define GREEN_BLK         1
#define GREEN_STB         0


/************************************/
/* DEFINATION FOR Digit Display     */
/************************************/
#define BLANK		  10
#define I		  11
#define d		  12
#define n		  13

/************************************/
/* DEFINATION FOR Clock Modes       */
/************************************/
#define MASTER            0
#define SLAVE             1

/************************************/
/* KEY DEFINATION FOR Programming   */
/************************************/
#define NONE              0
#define PRG_KEY           1
#define INC_KEY           2
#define DEC_KEY		  3
#define K1224_KEY         4
#define INT_KEY           5

/************************************/
/* DEFINATION FOR Programming Mode  */
/************************************/
#define CLK               0
#define COM               1
#define US		  2
#define INI               3

#define RED_TOG      PORT_LED_RED->ODR ^= LED_RED;
#define GRN_TOG      PORT_LED_GRN->ODR ^= LED_GRN;

/*----- FLASH PROGRAMMING FOR WRITTING CONFIG TABLE --------------------------*/
#define StartAddr           ((uint32_t)0x08004C00)                                   // MICRO FLASH START ADDRESS
#define EndAddr             ((uint32_t)0x08020000)                                   // MICRO FLASH LAST ADDRESS BUT ONE PAGE 
//#define FLASH_PAGE_SIZE     ((u16)0x400)                                        // MICRO FLASH PAGE SIZE

typedef struct
  {
    uint8_t Length;
    uint8_t Source;
    uint8_t Desti;
    uint8_t Code;
  }RCVR_InitTypeDef;


typedef union Key_Status
  {
   unsigned char KeyStatus;
   struct Bits {
                char PRG   : 1;						// Program Key
                char INC   : 1;						// Increment Key
                char DEC   : 1;						// Decrement Key
                char K1224 : 1;						// 1224 Key
                char INT   : 1;						// Intensity Programming
                char NC1    : 1;					// Not Used
                char NC2    : 1;					// Not Used
                char RST   : 1;						// Reset Key State
                };
  }Status;

extern Status 		    Key;
extern RCVR_InitTypeDef     RcvInput;


extern const int BitMap_DATA[16];

// Working Flags
extern FlagStatus
Flag_TGL,
Flag_mTick,
Flag_Tim_tick,
Flag_Communication,
Flag_GPSFix,
Flag_Keyscan,
Flag_mSick,
Flag_KeyPrg,            // Programming Key Debounce
Flag_Key1224,           // 12/24 Key Debounce
Flag_1224_self,
Flag_1224_Com,
Flag_Second,		// Flag @ predefined time Interval
Flag_Toggle,            // Flag to toggle LED
Flag_SegReady,          // Segment data Ready for display
Flag_DigitScan,	        // Scan Column for next data
Flag_SegUpdate,         // Update Segemnt with Next Data
Flag_SLAVE,             // Flag to access Slave
Flag_MASTER,            // Flag to access Master
Flag_Prog,              // Flag for Programming Mode
Flag_1224,              // Flag for 12/14 mode
Flag_Intensity,         // Flag for setting Intensity
Flag_GPSActive,         // GPS Data Valid
Flag_RCVActive,         // Master Dat Valid
Flag_DataReady,         // New Data Arrived
Flag_GPSDataReady,      // GPS Data Avilable
Flag_CheckTime,         // Check Time of Master Clock
Flag_Init,              // Initalization Flag
Flag_RCVDataReady;   	// MAster Clock Data Avilable

// Variables Defination
extern unsigned char
GNSS_Buffer[150],
Comm_TimeOut,
Save_Time,

GPS_DataIn[GPS_BufferSize],  // GPS Input Buffer
Rcv_DataIn[DATA_BufferSize], // Reciever Buffer
TxBuffer[25],                // Transmit Data buffer

Clock_Mode,             // Clock Mode
ModeCounter,            // Counter to check clock status
ReCheck_Time,           // Recheck GPS avalibility

LED_Color,              // Mode LED indicator

Display_RAM[7],         // Data to be displayed

DISP_HH,		// For displaying Hour

GPS_HH,			// GPS Hour
GPS_MM,			// GPS Minute
GPS_SS,			// GPS Second

RCV_HH,                 // Recieved Data Hour
RCV_MM,                 // Recieved Data Min
RCV_SS,                 // Recieved Data Second

MST_HH,			// Master Hour
MST_MM,			// Master Minute
MST_SS,			// Master Second

SLV_HH,			// Slave Hour
SLV_MM,			// Slave Minute
SLV_SS,			// Slave Second

PRG_HH,                 // Program Hour
PRG_MM,                 // Program Minute

Old_SS,			// Previous Second Value

Key_State,              // Variable for Key Scan
Key_Entry,              // Key Entred by User

Prog_State,             // Program Mode

DayInt,                 // Day Time Intensity
DayInt_self,
DayInt_Com,

NightInt,               // Night Time Intensity
NightInt_self,
NightInt_Com,

DutyCycle,              // Intensity Duty Cycle

RcvState_GPS,		// GPS Reciever State
RcvState,               // Clock Reciever State

NextDigit,              //  Next Digit to be scaned


BoardAddress,		// Board Physical Address

RcvCnt_GPS,		// Reciever Counter for Recieving GPS Data
RcvCnt,			// Reciever Counter for recieving data

DigitCount;		// Didit Scan Count



extern unsigned short
Tick,                                                                           // 1 MILI SECOND TICK
SegMult,                // Segment multiplier for scanning
DigitDisplay[2],        // Data to be displayed

Key_Time[4],             // Key String Input

crc,                    // CRC for verifiation
Sec_Tick,               // Second Tick Counter
DisplayData,            // Data to Be displayed

Scan_Time,              // Key Scan Time


GP_Counter;		// General Purpose Counter

extern unsigned long
RTC_Count;              // Counter for Slave RTC

extern uint8_t Duty_Count;
extern uint16_t Toggle_Counter;
#endif
