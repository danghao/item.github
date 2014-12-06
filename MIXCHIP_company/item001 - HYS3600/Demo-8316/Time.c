//==============================================================================
//  	File name : Time.C 
//==============================================================================

#define  MyDef  extern					// MyDef means external variable
#include "Global.h"				        //


void Cook_Start();                      // cook procedure start

//==============================================================================
//  task    : N uSec delay by  4.19 MHz Crystal Oscillator
//  input   : count data 65000 uSec max.
//==============================================================================
void Wait_uSec(Word DELAY)
{
    Word jj;                            //
    
    jj= (DELAY/18)*7;                   //
    while(jj)  jj--;                    //
}
//==============================================================================
// 	task  : 2 msec Interval Interrupt by Timer1
//==============================================================================
code Byte Grid_Table[] =
{
    0xFE,               // 1111_1110b   P20
    0xFB,               // 1111_1101b   P21
    0xFD,               // 1111_1011b   P22
    0xF7                // 1111_0111b   P23
};
//------------------------------------------------------------------------------
//      Timer1 Interrupt Handler by 2ms interval
//------------------------------------------------------------------------------
void T1_Int_Handler(void) interrupt 14 using 1
{
    P1  = 0x00;                         // all segment off

    if(r2mS_Key)    r2mS_Key--;         //
    if(r2mS_WAIT)   r2mS_WAIT--;        //
    if(r2mS_LED)    r2mS_LED--;         //
    if(r2mS_Buzz)   r2mS_Buzz--;        //
    if(r2mS_STOP)   r2mS_STOP--;        //

    P2 |= 0x0F;                         // all FND off
    rFND_Mode++;                       //
    if(rFND_Mode>3)                    //
        rFND_Mode = 0;                 // 2ms x 4 = 8 ms  Display Frame Frequency = 125Hz 
    P1  = rFont_Buf[rFND_Mode];        // segment data out (P10~P17)
    P2 &= Grid_Table[rFND_Mode];       // grid switch on   (P20~P23)
}
//==============================================================================
//  task    : 1 Sec interval Real Time Clock Interval by Watch Timer
//==============================================================================
void WT_Int_Handler(void) interrupt 20
{
    f_Minute = ON;                      //
}

//------------------------------------------------------------------------------
//      task    : Buzzer out
//------------------------------------------------------------------------------
void Buzzer_Out(void)
{
    P1FSRL  |= 0x02;                    //[2:1]= 01
    BUZDR   =  0x40;                    //
    BUZCR   =  0x05;                    //
}
//------------------------------------------------------------------------------
//      task    : Buzzer stop
//------------------------------------------------------------------------------
void Buzzer_Stop(void)
{
    P1FSRL  &= ~0x06;                   //[2:1]= 00
    BUZCR   =  0x04;                    //
}
//==============================================================================
//	task	: Time cyclic process
//==============================================================================
void Process_Time(void)				        //
{
    if(f_Minute)                            //
    {   rMinute++;                          //
        if(rMinute>59)                      //
        {   rMinute = 0;                    //
            rHour++;                        //
            if(rHour>23)                    //
                rHour = 0;                  // 00:00 ~ 23:59
        }
    
        if((rHour == rAlarm_Hour)           //
            &&(rMinute == rAlarm_Minute))   //
        {
            rMelody_Mode = BEEP_Home;       //
        }
    }
}

//==============================================================================
//  Appindix :  interrupt vector
//==============================================================================
//void Ext10_Int_Handler(void)  interrupt 0     using 1
//void Ext11_Int_Handler(void)  interrupt 1     using 1
//void Ext12_Int_Handler(void)  interrupt 2     using 1

void ExtG0_Int_Handler(void)  interrupt 5     using 1     //Ext0~Ext4
{
    EIFLAG0 = 0;                        // for key wakep (EINT0 ~ EINT3)
}

//void Ext5_Int_Handler(void)   interrupt 6     using 1
//void Ext6_Int_Handler(void)   interrupt 7     using 1
//void I2C_Int_Handler(void)    interrupt 8     using 1
//void TX_Int_Handler(void)     interrupt 9     using 1
//void RX_Int_Handler(void)     interrupt 10    using 1

//void T0V_Int_Handler(void)    interrupt 12    using 1
//void T0_Int_Handler(void)     interrupt 13    using 1
//void T1_Int_Handler(void)     interrupt 14    using 1
//void T2_Int_Handler(void)     interrupt 15    using 1

//void ExtG7_Int_Handler(void)  interrupt 17    using 1     //Ext7~ExtA
//void ADC_Int_Handler(void)    interrupt 18    using 1
//void SPI_Int_Handler(void)    interrupt 19    using 1
//void WT_Int_Handler(void)     interrupt 20    using 1
//void WDT_Int_Handler(void)    interrupt 21    using 1
//void BIT_Int_Handler(void)    interrupt 22    using 1
//==============================================================================
