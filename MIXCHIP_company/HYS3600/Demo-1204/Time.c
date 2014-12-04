//==============================================================================
//	file name	: Time.c
//==============================================================================

#define      MyDef       extern         //
#include	"Global.h"			        //

//==============================================================================
//    task  : N uSec delay by  16 MHz Oscillator
//    input : count data 3 ~ 56000 uSec max.
//	output: none
//==============================================================================
void	Wait_uSec(Word DELAY)
{
      Word jj;                            //

//    jj= (DELAY/18)*7;                   //
      jj= DELAY;                          // by 16MHz IRC OSC
      
      while(jj)  jj--;                    //
}

//==============================================================================
//    task  : 4ms x 255 ms delay
//==============================================================================
/*
void Wait_mSec(Word CNT)
{
      r2mS_SEC = CNT/4;                     //
      while(r2mS_SEC)
           _nop_();                         //
}
*/
//==============================================================================
// 	task  : T0 match Interrupt
//          4msec Interval Interrupt by Timer0
//
//==============================================================================
void T0_Int_Handler(void) interrupt 7 using 1
{
    if(r4mS_KEY)    r4mS_KEY--;         // 4ms timetick downcounter
    if(r4mS_WAIT)   r4mS_WAIT--;        //
    if(r4mS_LED)    r4mS_LED--;         //
    if(r4mS_ADC)    r4mS_ADC--;         //
    if(r4mS_STOP)   r4mS_STOP--;        //
}

//==============================================================================
//  task  : interval Interrupt by Timer1
//==============================================================================

void T1_Int_Handler(void) interrupt 8    using 1
{

      _nop_();

}

//==============================================================================
//  task  : Timer2 Interrupt
//          10ms interval Interrupt by T2
//==============================================================================
void T2_Int_Handler(void) interrupt 9    using 1
{
    EA = ON;
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
}
//==============================================================================
//    task  : RC Watchdog Timer Interrupt
//==============================================================================
void WDT_Int_Handler(void) interrupt 12 using 1
{
    _nop_();
}
//==============================================================================
//    task  : Basic Interval Timer Interrupt
//==============================================================================
void BIT_Int_Handler(void) interrupt 13    using 1
{


}

//==============================================================================
//    task  : BrownOut Detect Interrupt
//==============================================================================
void BOD_Int_Handler(void)    interrupt 14    using 1
{
    _nop_();
}
//==============================================================================
//      External Pin Interrupt
//==============================================================================
//------------------------------------------------------------------------------
//void Ext0_Int_Handler(void)   interrupt 0     using 1
//{
//    _nop_();
//}
//------------------------------------------------------------------------------
//void Ext1_Int_Handler(void)   interrupt 1     using 1
//{
//    _nop_();
//}
//==============================================================================
//    task  : 
//==============================================================================
void Process_Time(void)
{
    if(r4mS_LED)    return;     //
    
    r4mS_LED = 125;             //
    
    p_LED = ~p_LED;             //
}
/*
//==============================================================================
//      Appendix
//==============================================================================
//void Ext0_Int_Handler(void)   interrupt 0     using 1
//void Ext1_Int_Handler(void)   interrupt 1     using 1
//void PCI_Int_Handler(void)    interrupt 3     using 1
//void SPI_Int_Handler(void)    interrupt 4     using 1
//void T0_Int_Handler(void)     interrupt 7     using 1
//void T1_Int_Handler(void)     interrupt 8     using 1
//void T2_Int_Handler(void)     interrupt 9     using 1
//void ADC_Int_Handler(void)    interrupt 11    using 1
//void WDT_Int_Handler(void)    interrupt 12    using 1
//void BIT_Int_Handler(void)    interrupt 13    using 1
//void BOD_Int_Handler(void)    interrupt 14    using 1
//==============================================================================
*/
