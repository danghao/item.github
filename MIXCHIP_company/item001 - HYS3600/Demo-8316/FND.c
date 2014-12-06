//==============================================================================
//	file name   : Led.c
//==============================================================================
#define  MyDef  extern					// MyDef means external variable
#include "Global.h"				        //

//------------------------------------------------------------------------------
//	external prototype function
//------------------------------------------------------------------------------

extern void	Wait_uSec(Word);		    //

//==============================================================================
//  FND font map
//==============================================================================
/*
     aaaaaaa
    f       b
    f       b
    f       b
     ggggggg
    e       c
    e       c
    e       c
     ddddddd    hh
*/
//------------------------------------------------------------------------------
//  numeric digit font
//------------------------------------------------------------------------------
code Byte FND_font_table[] =
{               // hgfe_dcba
    0x3F,       // 0011_1111    0
    0x06,       // 0000_0110    1
    0x5B,       // 0101_1011    2
    0x4F,       // 0100_1111    3
    0x66,       // 0110_0110    4
    0x6D,       // 0110_1101    5
    0x7D,       // 0111_1101    6
    0x27,       // 0010_0111    7
    0x7F,       // 0111_1111    8
    0x67,       // 0110_0111    9
    0x77,       // 0111_0111    A
    0x7C,       // 0111_1100    b
    0x39,       // 0011_1001    C
    0x5E,       // 0101_1110    d
    0x79,       // 0111_1001    E
    0x71,       // 0111_0001    F

    0x00,       // 0000_0000    chr_Space   ( )
    0x40,       // 0100_0000    chr_Bar     (=)
    0x73,       // 0111_0011    chr_P       (P)
    0x76        // 0111_0110    chr_H       (H)
};


#define chr_Space   (0x10)              //
#define chr_Bar     (0x11)              //
#define chr_P       (0x12)              //
#define chr_H       (0x13)              //

//==============================================================================
//	task	: Clock Display Update
//	input	: rHour, rMinute
//	output  : rFont_Buf[4]
//==============================================================================
void RTC_DIsplay(void)
{
    Byte k;
    
    k = rHour/10;                       //
//  if(k==0) k = 0x10;                  //chr_Space
    rFont_Buf[0] = FND_font_table[k];   //Hour_10digit
    k = rHour%10;                       //
    rFont_Buf[2] = FND_font_table[k];   //Hour_1digit
    if(f_Flicker)
        rFont_Buf[2] |= 0x80;           //
    
    k = rMinute/10;                     //
    rFont_Buf[1] = FND_font_table[k];   //Minute_10digit
    k = rMinute%10;                     //
    rFont_Buf[3] = FND_font_table[k];   //Minute_1digit
}
//==============================================================================
//	task	: Alarm Display Update
//	input	: rAlarm_Hour, rAlarm_Minute
//	output  : rFont_Buf[4]
//==============================================================================
void Alarm_DIsplay(void)
{
    Byte k;
    
    k = rAlarm_Hour/10;                 //
//  if(k==0) k = 0x10;                  //chr_Space
    rFont_Buf[0] = FND_font_table[k];   //Alarm Hour_10digit
    k = rAlarm_Hour%10;                 //
    rFont_Buf[2] = FND_font_table[k];   //Alarm Hour_1digit
    
    k = rAlarm_Minute/10;               //
    rFont_Buf[1] = FND_font_table[k];   //Alarm Minute_10digit
    k = rAlarm_Minute%10;               //
    rFont_Buf[3] = FND_font_table[k];   //Alarm Minute_1digit
}
//==============================================================================
//	task	: ADC Data Display Update
//	input	: wAdc_Data
//	output  : rFont_Buf[4]
//==============================================================================
void ADC_Display(void)
{
    Byte k,j;

    k = chr_Bar;                        //
    rFont_Buf[0] = FND_font_table[k];   //
    k = wAdc_Data/0x0100;               //
    rFont_Buf[2] = FND_font_table[k];   //

    j = wAdc_Data%0x0100;               //
    k = j/0x10;                         //
    rFont_Buf[1] = FND_font_table[k];   //
    k = j%0x10;                         //
    rFont_Buf[3] = FND_font_table[k];   //
}

//==============================================================================
//	task	: Key Data Display Update
//	input	: rKey_Cmd
//	output  : rFont_Buf[4]
//==============================================================================
void Key_Display(void)
{
    rFont_Buf[0] = FND_font_table[rKey_Cmd];   //
    rFont_Buf[1] = FND_font_table[rKey_Cmd];   //
    rFont_Buf[2] = FND_font_table[rKey_Cmd];   //
    rFont_Buf[3] = FND_font_table[rKey_Cmd];   //
}
//==============================================================================
//	task	: Process FND (Figurable Numeric Display)
//	input	: rCook_Menu, rCook_Recipe
//	output  : rDisp_Buf[ ]
//==============================================================================

void Process_Led(void)
{
    if(f_Req_Display)               //
        f_Req_Display = OFF;        //
    else
    {   if(r2mS_LED)                //
            return;                 //
        r2mS_LED = 250;             // 500ms cycle
        rSecond++;                  // 임시 Test 용도임.
        p_LED3 = ~p_LED3;           //
        f_Flicker = ~f_Flicker;     //
    }
    
    switch (rFND_Menu)
    {   case RTC:
            RTC_DIsplay();          //
        break;
    
        case ALARM:
            Alarm_DIsplay();        //
        break;
    
        case ADC:
            ADC_Display();          //
        break;
    
        case KEY:
            Key_Display();          //
        break;
    }
    
}
//==============================================================================
