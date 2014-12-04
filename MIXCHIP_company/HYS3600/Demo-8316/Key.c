//==============================================================================
//     file name  : Key.c
//==============================================================================
#define  MyDef  extern					// MyDef means external variable
#include "Global.h"				        //

//------------------------------------------------------------------------------
//	external prototype function
//------------------------------------------------------------------------------

extern void	Wait_uSec(Word);		    //
extern void Uart_Transmit();            //
extern void Buzzer_Start();             //
extern void Write_I2C();                //

extern char Flash_Erase(unsigned int, unsigned int);
extern char Flash_Write(unsigned int, unsigned char *, unsigned char);
extern char Flash_Read(unsigned int, unsigned char *, unsigned char);

//==============================================================================
//  task    : Analog to Digital Conversion
//==============================================================================
#define     STBY    (0x80)              // ADC block enable
#define     ADST    (0x40)              // ADC conversion start
#define     REFSEL  (0x20)              // bit5=1:AVref, =0:VDD
#define     AFLAG   (0x10)              // ADC conversion completed?
#define     ALIGN   (0x04)              // 1=LSB alignment

#define     AN2     (0x02)              // ADC2 input select
#define     VDD18   (0x0F)              // VDD18 input select

//------------------------------------------------------------------------------
Word Get_Adc12(Byte ADC_CH)
{
    Word    jj;

    ADCCRL = STBY+ADC_CH;               // ADST(6),   VDD Ref reference  (주)정밀ADC가 필요할 때, Pin35에 기준전압 인가 필요함.
    ADCCRH = ALIGN;                     // LSB align 11~8 7~0, 8MHz clock (7.5us conversion time)   much better !!!
    ADCCRL |= ADST;                     // conversion start
    for(jj=0;jj<20;jj++)                //
    {   if(ADCCRL & AFLAG)              //AFLAG(4)
            break;                      //
    }
    
    return ADCDR;                       //
}
//==============================================================================
//  task    : Key Function Execution
//==============================================================================
//------------------------------------------------------------------------------
//  task    : SW2_Key
//------------------------------------------------------------------------------
void SW2_Key(void)
{
    switch(rFND_Menu)
    {
        case RTC:
            rFND_Menu = ALARM;
        break;
        
        case ALARM:
            rFND_Menu = ADC;
            wAdc_Data = Get_Adc12(AN2); //
        break;
        
        case ADC:
            rFND_Menu = KEY;
        break;
        
        case KEY:
            rFND_Menu = RTC;
        break;
    }
    f_Req_Display  = ON;                //
}
//------------------------------------------------------------------------------
//  task    : SW3_Key
//
//------------------------------------------------------------------------------
void SW3_Key(void)
{
    rFND_Menu = ALARM;                  //
    f_Req_Display  = ON;                //

    rMelody_Mode = BEEP_ALARM;          //
}
//------------------------------------------------------------------------------
//  task    : SW4_Key
//------------------------------------------------------------------------------
void SW4_Key(void)
{
    if(rFND_Menu == RTC)                //
    {    rHour++;
        if(rHour>23) rHour = 0;
    }
    else
    {    rAlarm_Hour++;                 //
        if(rAlarm_Hour>23)              //
            rAlarm_Hour = 0;            //
    }
    f_Req_Display  = ON;                //
}
//------------------------------------------------------------------------------
//  task    : SW5_Key
//------------------------------------------------------------------------------
void SW5_Key(void)
{
    if(rFND_Menu == RTC)                //
    {   rMinute++;                      //
        if(rMinute>59) rMinute = 0;     //
    }
    else
    {   rAlarm_Minute++;                //
        if(rAlarm_Minute>59)            //
            rAlarm_Minute = 0;          //
    }
    f_Req_Display  = ON;                //
}
//------------------------------------------------------------------------------
//  task    : No_Key
//------------------------------------------------------------------------------
void No_Key(void)
{
    _nop_();                            //
}
//==============================================================================
//	task    : Key Function Jump Table
//==============================================================================
code void (*(Func_Pointer[]))(void)=
{
    No_Key,                             //K0
    
    SW2_Key,                            //K1
    SW3_Key,                            //K2
    SW4_Key,                            //K3
    SW5_Key,                            //K4
    
    No_Key                              //
};
//==============================================================================
//  task    : Key profile check and Filtering
//  input   : rKey_Data, Cook_Information
//  output  : 0 OK, other skip
//==============================================================================
#define     RPT     0x01                // repeat key
#define     RCP     0x02                // Recipe=Setup+Adjust 이외 상태에서도 동작하는 Key
#define     WRM     0x04                // Recipe=Warm 상태에서 동작하는 Key
#define     ENA     0x80                // Enable Key
//------------------------------------------------------------------------------
Byte Key_Filtering(void)
{
    Byte k;
    
    switch(rKey_Data)
    {   case 1:     k = ENA;        break;      //
        case 2:     k = ENA;        break;      //
        case 3:     k = ENA+RPT;    break;      //
        case 4:     k = ENA+RPT;    break;      //
    }

    if(k==0) return 1;                          // disable key ?
    
    if(rKey_Cmd == rKey_Data)                   // 1~10
    {   if(!(k&RPT)) return 1;                  // repeat key?
        else
        {   if(rCmd_Back == rKey_Cmd)           //
            {   if(rKey_Speed)                  // repeat speed chck
                {   rKey_Speed--;               //
                    return 1;                   // skip
                }
                else rKey_Speed = 1;            //
            }
        }
    }
    else
    {   rKey_Cmd  = rKey_Data;                  // new key command in
        rCmd_Back = rKey_Cmd;                   // new repeat key pass
        rKey_Speed = 8;                         // 80ms
    }

    return 0;                                   //
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
code Byte Key_Match_Table[] =
{
    0x78,           // 0111_1000b   0
    0x70,           // 0111_0000b   1
    0x68,           // 0110_1000b   2
    0x58,           // 0101_1000b   3
    0x38            // 0011_1000b   4
};
//==============================================================================
//	task    : Key matrix scan & decode
//  input   :
//==============================================================================

void Process_Key(void)
{
    Byte   buf,key;                     //
	
    if(r2mS_Key) return;			    //
    r2mS_Key = 10;                      // Key Scan by every 20ms (2ms x 10) cycle
    
    buf = P0 & 0x78;                    // P06,P05,P04,P03
    for(key=0;key<5;key++)              //
    {   if(buf==Key_Match_Table[key])   //
            break;                      //
    }
    if(key>4) key = 0;                  //
	if(key)                             // key != 0
	{	if(key == rKey_Chat)			// new key pressed?
		{	rKey_Count--;               //
			if(rKey_Count  == 0)		//
			{	rKey_Data  = key;       //
				rKey_Count = 5;		    // 20x5=100	mSec repeat	key command	in
				f_Key_Ok   = ON;        //
			}
		}
		else
		{	rKey_Chat  = key;			// 40ms chattering
			rKey_Count = 2;			    //
		}                               //
	}
	else                                // key == 0
	{	rDebounce--;				    // Key Release debounce check
		if(rDebounce) return;			//
		else
		{	rKey_Chat	= 0x00;         //
			rKey_Data	= 0x00;         //
			rKey_Cmd	= 0x00;         //
			rCmd_Back   = 0x00;         // repeat key backup
            rDebounce   = 1;            //
		}
	}
    if(f_Key_Ok)                        //
    {   f_Key_Ok = OFF;                 //
        
        if(Key_Filtering()) return;     // repeat key speed control
        
        rDebounce = 6;                  // 120ms key release time delay
        
        (*Func_Pointer[rKey_Cmd])();    // key command function pointer
    }
}
//==============================================================================
