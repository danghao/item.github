//==============================================================================
//    type define
//==============================================================================
typedef struct
{	Byte  b0	:1;
	Byte  b1	:1;
	Byte  b2	:1;
	Byte  b3	:1;
	Byte  b4	:1;
	Byte  b5	:1;
	Byte  b6	:1;
	Byte  b7	:1;
} BYTE_FIELD;
//------------------------------------------------------------------------------
typedef union 
{	unsigned char byte;
	BYTE_FIELD 	b;
} TYPE_BYTE;
//------------------------------------------------------------------------------
typedef struct
{	Byte  b8	:1;
	Byte  b9	:1;
	Byte  b10	:1;
	Byte  b11	:1;
	Byte  b12	:1;
	Byte  b13	:1;
	Byte  b14	:1;
	Byte  b15   :1;

	Byte  b0	:1;
	Byte  b1	:1;
	Byte  b2	:1;
	Byte  b3	:1;
	Byte  b4	:1;
	Byte  b5	:1;
	Byte  b6	:1;
	Byte  b7	:1;
} WORD_FIELD;
//------------------------------------------------------------------------------
typedef union 
{
	Word        word;
	Byte	    byte[2];
	WORD_FIELD 	b;
} TYPE_WORD;
//==============================================================================
//      Constant  Define
//==============================================================================

//------------------------------------------------------------------------------
//	    bit define
//------------------------------------------------------------------------------
#define     ON          1               //
#define  	OFF         0               //
#define     HIGH        1               //
#define  	LOW         0               //
#define  	OK          1               //
#define  	FAIL		0               //

#define  	OPENED      1               //
#define  	CLOSED      0               //

#define  	LAMP_OFF	1               //
#define  	LAMP_ON     0               //

//------------------------------------------------------------------------------
// 	    I/O Port define
//------------------------------------------------------------------------------
#define     p_LED3	    P24             //
#define     p_LED4	    P25             //
#define     p_LED5      P26             //
#define     p_Flash_CS  P27             //
//==============================================================================
//     IRAM Assignment
//==============================================================================
//------------------------------------------------------------------------------
//      2 ms Time Tick variable define
//------------------------------------------------------------------------------
MyDef Byte  r2mS_Key;                   //
MyDef Byte  r2mS_WAIT;                  //
MyDef Byte  r2mS_LED;                   //
MyDef Byte  r2mS_Buzz;                  //
MyDef Byte  r2mS_STOP;                  //

MyDef Byte  rStop_Count;                //
//------------------------------------------------------------------------------
//	    Local Key control variable define
//------------------------------------------------------------------------------
MyDef TYPE_BYTE Key_Flag;               //
#define rKey_Flag	    Key_Flag.byte   //byte
#define f_Repeat	    Key_Flag.b.b1   //
#define f_Key_Ok	    Key_Flag.b.b2   //

MyDef Byte  rKey_Count;                 //
MyDef Byte  rKey_Data;                  //
MyDef Byte  rKey_Chat;                  //key chattering check
MyDef Byte  rDebounce;                  //key release check
MyDef Byte  rKey_Cmd;                   //key command
MyDef Byte  rCmd_Back;                  //
MyDef Byte  rKey_Speed;                 //Repeat Key speed

MyDef Byte  rKey_Buf[3]; 	            //key scan raw data buffer

//------------------------------------------------------------------------------
//  Buzzer sound control
//------------------------------------------------------------------------------
MyDef Byte  *wBuzz_Ptr;                 //
MyDef Byte  rBuzz_Count;                //

//------------------------------------------------------------------------------
//      Real Time Clock variable define
//------------------------------------------------------------------------------
MyDef Bool  f_Minute;                   //
MyDef Bool  f_Hour_Set;                 //
MyDef Bool  f_Reserve;                  //

MyDef Byte  rSecond;                    //
MyDef Byte  rMinute;                    // RTC 분 down counter
MyDef Byte  rHour;                      // RTC 시간 down counter
MyDef Byte  rAlarm_Minute;              // Alarm 분 down counter
MyDef Byte  rAlarm_Hour;                // Alarm 시간 down counter

//------------------------------------------------------------------------------
//      ADC variable define
//------------------------------------------------------------------------------
MyDef Word  wAdc_Data;                  //

//------------------------------------------------------------------------------
//      FND Display variable define
//------------------------------------------------------------------------------
MyDef Bool  f_Req_Display;              //
MyDef Bool  f_Flicker;                  //
MyDef Bool  f_Tx;                       // spi transmit

MyDef Byte  rFND_Menu;                  // LED display menu
enum {
    RTC = 0,                            //
    ALARM,                              //
    ADC,                                //
    KEY                                 //
};

MyDef Byte  rFND_Mode;                  // FND refresh mode
MyDef Byte  rFont_Buf[4];               //
//------------------------------------------------------------------------------
//      SPI variable define
//------------------------------------------------------------------------------
MyDef Bool  f_SPI_TX;                   //
MyDef Bool  f_Page_Read;                //

MyDef Word  wSPI_Count;                 //
MyDef Word  wSrc_Addr;                  //
MyDef Word  wDst_Addr;                  //

MyDef XDATA Byte  xSPI_Data[16];        //

//------------------------------------------------------------------------------
//      I2C variable define
//------------------------------------------------------------------------------
MyDef Bool  f_I2C_Read;                 //
MyDef Bool  f_I2C_Sad;                  //
MyDef Bool  f_Touch;                    //


MyDef Byte  rI2C_Mad;                   //
MyDef Byte  rI2C_Sad;                   //
MyDef Byte  rI2C_Byte;                  //
MyDef Byte  *wI2C_Post;                 //
MyDef XDATA Byte  xI2C_Data[16];        //

//------------------------------------------------------------------------------
//      UART variable define
//------------------------------------------------------------------------------
MyDef Byte  rTx_Count;                  //
MyDef Byte  rTx_Ptr;                    //
MyDef XDATA Byte  xTx_Buffer[20];       //
MyDef Byte  rLength;                    //

MyDef Byte  rRx_Ptr;                    //
MyDef XDATA Byte  xRx_Buffer[16];       //

MyDef Bool  f_Req_Decode;               //
MyDef Bool  f_New_Packet;               //

//------------------------------------------------------------------------------
//      Melody Control variable define
//------------------------------------------------------------------------------
MyDef Byte  rMelody_Mode;               //
enum {
    BEEP_NONE = 0,
    BEEP_OFF,
    BEEP_ALARM,
    BEEP_JJangGa,
    BEEP_ERROR,
    BEEP_LOW,
    BEEP_Home,
    BEEP_Chamm,
    BEEP_HappyBD
};
MyDef Byte  *wMelody_Ptr;               //
MyDef Byte  rMelody_cnt;                //
MyDef Byte  rMelody_Mode;               //

//------------------------------------------------------------------------------
//      FlashData variable define
//------------------------------------------------------------------------------

MyDef XDATA Byte  Backup_Info[8];       //
MyDef XDATA Byte  Flash_Buf[32];        //
//==============================================================================
