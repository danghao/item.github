//==============================================================================
//    file name   : Variable.h
//==============================================================================

#define     SOP_32          0           // MC97F1316 32 pin Package

//------------------------------------------------------------------------------
//    constant define
//------------------------------------------------------------------------------
#define     ON                1           //
#define     OFF               0           //

#define     HIGH              1           //
#define     LOW               0           //

#define     LED_ON            0           //sink
#define     LED_OFF           1           //

#define     EXT_OSC           OFF         // 0=internal 8MHz oscillator option
#define     MASTER            ON          // Main Master MCU option

//------------------------------------------------------------------------------
//    I/O Port define
//------------------------------------------------------------------------------
#define     p_LED             P10         //

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

typedef union 
{	unsigned char byte;
	BYTE_FIELD 	b;
} TYPE_BYTE;

typedef struct
{	Byte  b8	:1;
	Byte  b9	:1;
	Byte  b10	:1;
	Byte  b11	:1;
	Byte  b12	:1;
	Byte  b13	:1;
	Byte  b14	:1;
	Byte  b15  :1;

	Byte  b0	:1;
	Byte  b1	:1;
	Byte  b2	:1;
	Byte  b3	:1;
	Byte  b4	:1;
	Byte  b5	:1;
	Byte  b6	:1;
	Byte  b7	:1;
} WORD_FIELD;

typedef union 
{
	Word	      word;
	Byte	      byte[2];
	WORD_FIELD 	b;
} TYPE_WORD;

//==============================================================================
//    Data define             0x30 ~ 0xFF
//==============================================================================
MyDef   Bool    f_Flicker;              // 
MyDef   Bool    f_Speed;                // 

MyDef	Byte    r4mS_SEC;               // Time Tick
MyDef	Byte    r4mS_LED;               //
MyDef	Byte    r4mS_I2C;               //
MyDef	Byte    r4mS_KEY;               //
MyDef	Byte    r4mS_STOP;              //
MyDef	Byte    r4mS_WAIT;              //
MyDef	Byte    r4mS_ADC;               //

MyDef   Byte    rStop_Count;            // Power saving mode check time
MyDef   Byte    rCapture_Mode;          // 
//MyDef   Byte    wCapture_Buf[16];       //
//------------------------------------------------------------------------------
//    RTC Control
//------------------------------------------------------------------------------
MyDef	XDATA   Byte    rHour;          //
MyDef	XDATA   Byte    rMinute;        //
MyDef	Byte    rSecond;                //
MyDef	XDATA   Byte    rAlarm_Hour;    //
MyDef	XDATA   Byte    rAlarm_Minute;  //

//------------------------------------------------------------------------------
//    Key Control
//------------------------------------------------------------------------------
MyDef   Bool    f_KeyOk;                // 
MyDef   Bool    f_CmdOk;                //key command in
MyDef   Bool    f_Repeat;               // 

MyDef	Byte    rScan_Count;            //
MyDef	Byte    rCmd_Count;             //
MyDef	Byte    rKey_Data;              //
MyDef	Byte    rKey_Buf;               //
MyDef	Byte    rKey_Cmd;               //
MyDef	Byte    rSpd_Mode;              //

//------------------------------------------------------------------------------
//   SPI Control
//------------------------------------------------------------------------------
MyDef   Bool    f_SPI_TX;               // SPI transmit mode
MyDef   Bool    f_Page_Read;            //

MyDef	Word    rTx_Count;             // SPI data count
MyDef	Word    wSrc_Addr;              // SPI soure data address
MyDef	Word    wDst_Addr;              // SPI destination data address
MyDef	Byte    *wRX_Post;              // Uart Data Pointer
MyDef	Byte    *wTX_Post;              // Uart Data Pointer
MyDef	Byte    rTX_Data[16];           //
MyDef	Byte    rRX_Data[16];           //

//------------------------------------------------------------------------------
//    ADC Control
//------------------------------------------------------------------------------
MyDef	Word    wAdc_Data;              // ADC data address

//==============================================================================
//	End of Variable.h
