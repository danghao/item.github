//==============================================================================
//	file name   : Key.c
//==============================================================================

#define     MyDef       extern          //
#include	"Global.h"			        //

//------------------------------------------------------------------------------
//	External function	assignment
//------------------------------------------------------------------------------
extern void	Wait_uSec(Word);            //timer.c
extern void SPI_Start();                //

//==============================================================================
//    task  : External Interrupt
//==============================================================================
void Ext0_Int_Handler(void) interrupt 0    using 1
{
    rCapture_Mode++;                    // 
    rCapture_Mode &= 0x0F;
//    wCapture_Buf[rCapture_Mode]= CDR2;

}
//------------------------------------------------------------------------------
void Ext1_Int_Handler(void) interrupt 1    using 1
{
    rStop_Count = 5;                    // 5 sec

}
//------------------------------------------------------------------------------
void PCI_Int_Handler(void) interrupt 3    using 1
{
    rStop_Count = 5;                    // 5 sec

}
//==============================================================================
//	task	: Read Time clock Interrupt
//==============================================================================
void ADC_Int_Handler(void) interrupt 11    using 1
{
    wAdc_Data = (ADCRH & 0x0F) * 0x100; //
    wAdc_Data += ADCRL;                 //

    TMISR        = 0x00;                // interrupt pending clear
}
//==============================================================================
//    task  : 12bit ADC read
//    input : ADC Channel
//    output: 12bit data return
//==============================================================================
#define     STBY    0x80                // ADC block enable
#define     ADST    0x40                // ADC conversion start
#define     REFSEL  0x20                // bit5=1:AVref, =0:VDD
#define     AFLAG   0x10                // ADC conversion completed?

Word Get_ADC12(Byte ADC_CH)
{
    Word  jj;                           //
    
//  ADCM = REFSEL+ADC_CH;               // REFSEL(5)  external reference
    ADCM = ADC_CH;                      // VDD reference
    ADCM1 = 0x05;                       // LSB align 11~8 7~0, fx/4=2MHz clock
    ADCM |= ADST;                       //  ADST(6)=1 conversion start
    for(jj=0;jj<0xFF;jj++)              //
    {   if(ADCM & AFLAG)                // AFLAG(4)
            break;                      //
    }
//    jj = (ADCRH & 0x0F) * 0x100;        //
//    jj += ADCRL;                        //
//    return jj;                          //

    return ADCR;                        //
}
//==============================================================================
//    task  : Up Key Function
//    input :
//    output:
//==============================================================================
void Menu_Key(void)	                        //
{

}
//==============================================================================
//    task  : Enter Key Function
//    input :
//    output:
//==============================================================================
void Enter_Key(void)                        //
{

}
//==============================================================================
//    task  : Up Key Function
//    input :
//    output:
//==============================================================================
void Up_Key(void)	                    //
{

}
//==============================================================================
//    task  : Dow Key Function
//    input :
//    output:
//==============================================================================
void Down_Key(void)	                    //
{
}
//==============================================================================
//    task  : Null Key Function
//==============================================================================
void No_Key(void)                           //
{
      _nop_();                              //
}

//==============================================================================
//    task  : Key Scan Process by 20ms interval
//    input :
//    output:
//==============================================================================

//------------------------------------------------------------------------------
//    task  : Key State Table
//------------------------------------------------------------------------------
#define     Ena         0x01        //key enable
#define     Off         0x02        //key enable at OFF state
#define     Rpt         0x04        //key repeat

Byte code Key_State_Table[] =
{
    0x00,                           //0
    
    Ena,                            //1
    Ena,                            //2
    Ena,                            //3
    Ena                             //4
};
//------------------------------------------------------------------------------
//    task  : Key Filtering State check
//------------------------------------------------------------------------------
Byte Chk_Key_State(void)
{
    Byte k = 0;                     //
    Byte js;                        //
    
    js = Key_State_Table[rKey_Cmd]; //
    if(js==0)                       // 할당되지 않은 Key Skip
        k = 1;                      //
    if(f_Repeat)                    //
    {   if(!(js & Rpt))             // 연속 동작 Key가 아닌 것 Skip
            k = 1;                  //

                                    // 동작속도 조절 
    }
    return k;                       //
}
//------------------------------------------------------------------------------
//    task  : Key matrix Scan
//    output: rKey_Buf
//------------------------------------------------------------------------------
Byte code Key_Scan_Table[5] =
{
    0xF0,                           // 1111_0000    0
    0xE0,                           // 1110_0000    1
    0xD0,                           // 1101_0000    2
    0xB0,                           // 1011_0000    3
    0x70                            // 0111_0000    4
};
//==============================================================================
//    task  : Key Jump Table
//==============================================================================
code void (*(Func_Pointer[]))(void)=
{
    No_Key,             //K0
    
    Menu_Key,           //K1
    Enter_Key,          //K2
    Up_Key,             //K3
    Down_Key,           //K4
};
//------------------------------------------------------------------------------
//    task  : Key Matrix scan (8 x 3 = 24 points)
//------------------------------------------------------------------------------
Byte Key_Scan(void)
{
    Byte  k,m;                          //
    
    m = P0 & 0xF0;                      //
    
    for(k=0;k<5;k++)                    //
    {   if(m == Key_Scan_Table[k])      //
            break;                      //
    }
    if(k > 4) k = 0;                   //
    
    return k;                           //
}
//==============================================================================
//      task    : Key read & execute
//      input   : P04~P07
//==============================================================================
void Process_Key( void )
{
    if(r4mS_KEY)  return;                   //
    r4mS_KEY = 10;                          //20ms interval
    
    rKey_Buf = Key_Scan();                  //
    
    if(rKey_Buf)                            //
    {   if(rKey_Buf == rKey_Data)           //
        {   rScan_Count--;                  //
            if(rScan_Count==0)              //
            {   f_KeyOk = ON;               //
                rScan_Count = 5;            // 20ms x 5 = 100ms repeat interval
            }                               //
        }
        else                                //
        {   rKey_Data   = rKey_Buf;         //new key detected
            rScan_Count = 1;                //
            r4mS_KEY = 1;                   //4ms interval
            f_Repeat    = OFF;              //
        }
    }
    else                                    //
    {   if(rCmd_Count)                      //
            rCmd_Count--;                   //
        else
        {   rSpd_Mode  = 0;                 //
            rKey_Buf   = 0x00;              //
            rKey_Data  = 0x00;              //
            rKey_Cmd   = 0x00;              //
            rCmd_Count = 1;                 //
        }
    }
    
    if(f_KeyOk == OFF) return;              //
    
    r4mS_STOP = 125;                        // 400ms 후 연속키 없으면 STOP mode 진입함.
    
    f_KeyOk = OFF;                          //
    if(rKey_Cmd == rKey_Data)               //
        f_Repeat = ON;                      //
    rKey_Cmd    = rKey_Data;                //
    rCmd_Count  = 5;                        //100ms debounce
    
    if(Chk_Key_State()) return;             //
    
    (*Func_Pointer[rKey_Cmd])();            //

}
//==============================================================================
