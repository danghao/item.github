//==============================================================================
//      project     : Demo Program
//      Device      : MC97F1204 (20SOP)
//	    file name	: Main.c
//	    author      : BJ Lim
//	    date	    : 2013.07.02
// 	    tool	    : uVision C51 Compiler ( Version 4.0 )
// 	    MDS	        : OCD 2
//
//      frequency   : internal 8MHz oscillator
//      reset       : built-in 2.5V
//==============================================================================
/*
        History 
        2013-07-02  Program Coding start
*/
//==============================================================================

//------------------------------------------------------------------------------
//	    include files and System mode define
//------------------------------------------------------------------------------

#define      MyDef                  // prototype
#include	"Global.h"			    //

//------------------------------------------------------------------------------
//	    Project include function code
//------------------------------------------------------------------------------

extern void Process_Key();          // Key.c
extern Word Get_ADC(Byte);          //

extern void Process_Time();         // Time.c
extern void Wait_uSec(Word);        //

extern void Process_Led();          // Led.c

extern void Process_Melody();		// Buzzer.c

extern void Process_SPI();          //
extern void SPI_Initial();          //

void Process_Power();               //

//==============================================================================
//      task  : Input/output port selection
//==============================================================================
//------------------------------------------------------------------------------
//      Main Board I/O initialize
//------------------------------------------------------------------------------
void Port_Initial(void)
{                                   // b7   b6   b5   b4   b3   b2   b1   b0
                                    // Key  Key  Key  Key  AN2  Ext0 DSCL DSDA      OCD and key scan strobe
	P0IO        = 0x00;             // in   in   in   in   in   in   in   in
	P0          = 0xFF;             // 1    1    1    1    1    1    1    1
    P0OD        = 0xF7;             // OD   OD   OD   OD   PP   OD   OD   OD
	P0PU        = 0xF7;             // on   on   on   on   off  on   on   on
	P0DB        = 0xF0;		        // on   on   on   on   off  off  off  off

                                    // b7   b6   b5   b4   b3   b2   b1   b0
                                    // AN12 PWM1 PWM0 AN9  VREF nc   nc   LED 
	P1IO        = 0xE7;             // out  out  out  in   in   out  out  out
	P1          = 0x18;             // 0    0    0    1    1    0    0    0
    P1OD        = 0x00;             // pp   PP   PP   PP   PP   PP   PP   PP
	P1PU        = 0x00;             // off  off  off  off  off  off  off  off
    P1DB        = 0x00;             // 0    0    0    0    0    0    0    0

                                    // b7   b6   b5   b4   b3   b2   b1   b0
                                    // -    -    -    -    -    -    AN14 AN13
	P2IO        = 0xFF;             // -    -    -    -    -    -    in   in
	P2          = 0x00;             // -    -    -    -    -    -    0    0
    P2OD        = 0x00;             // -    -    -    -    -    -    PP   PP
	P2PU        = 0x00;             // -    -    -    -    -    -    off  off
    P2DB        = 0x00;             // -    -    -    -    -    -    0    0

                                    // b7   b6   b5   b4   b3   b2   b1   b0
    PSR0        = 0x0F;             // -    -    -    -   (reset DB) (IO DB)    64/32/16/8; 8/4/2/1
    PSR2        = 0x04;             // ADC input(7~0)  0=I/O,  1=ADC input      AIN2
    PSR3        = 0x00;             // ADC input(14~8) 0=I/O,  1=ADC input
}
//------------------------------------------------------------------------------
//      Timer interval set
//------------------------------------------------------------------------------
void Timer_Start(void)
{
    T0DR        = 3999;             // 1us x 4000 = 4ms interval
    T0CR        = 0x8B;             // pcs = 8MHz/8 = 1us
    T0CR1       = 0x00;             // 

    T2DR        = 4999;             // 2us x 50 = 100us interval
    T2CR        = 0x8F;             // pcs = 8us
    T2CR1       = 0x00;             //
    
//------------------------------------------------------------------------------
//      Interrupt priority select
//------------------------------------------------------------------------------
//    IP0H        = 0x00;             // RX     SPI   PCI   Ext2  Ext1  Ext0
//    IP0L        = 0x00;             // 
//    IP1H        = 0x0A;             // ADC    T3    T2    T1    T0    TX
//    IP1L        = 0x18;             // 
//    IP2H        = 0x00;             // -      -     SCM   BOD   BIT   WDT
//    IP2L        = 0x00;             //
//------------------------------------------------------------------------------
//      external Interrupt condition set
//------------------------------------------------------------------------------
    PCI         = 0x00;             // PCI7, .....................,PCI0
    EIENAB      = 0x00;             //         Ext2[2], Ext1[1], Ext0[0]
    EIBOTH      = 0x00;             //         Ext2[2], Ext1[1], Ext0[0]
    EIEDGE      = 0x00;             //         Ext2[2], Ext1[1], Ext0[0]
    EIPOLA      = 0x00;             //         Ext2[2], Ext1[1], Ext0[0]
    EIFLAG      = 0x00;             // PCI[3], Ext2[2], Ext1[1], Ext0[0]

//------------------------------------------------------------------------------
//      every interrupt enable set
//------------------------------------------------------------------------------
                                    // b7   b6   b5     b4    b3    b2    b1    b0
    IE          = 0x80;             // EA   -    RX     SPI   PCI   Ext2  Ext1  Ext0
    IE1         = 0x02;             // -    -    ADC    T3    T2    T1    T0    TX
    IE2         = 0x00;             // -    -    -      -     SCM   BOD   BIT   WDT
    
    EA          = ON;               // Global Interrupt Enable
}
//==============================================================================
//      task  : System SFR Initialize
//      input : none
//      output: none
//==============================================================================
void Main( void )
{

//------------------------------------------------------------------------------
//      8MHz IRC System Clock Select & builtin reset level select
//------------------------------------------------------------------------------
//  SCCR    = 0x00;
    BODR    = 0x89;                 // LVR[7] off, BOD[3] enable, 2.1V[001],2.3V[010], 2.5V[011]

    Wait_uSec(30000);               // 30ms wait 

    BCCR    = 0x05;                 // 16.384ms default
//------------------------------------------------------------------------------
//	    Input, output port initial
//------------------------------------------------------------------------------
    Port_Initial();                 // Main board port initialize
//------------------------------------------------------------------------------
//      System Stabilize Delay
//------------------------------------------------------------------------------
    Wait_uSec(30000);               // 30ms wait 

    SPI_Initial();                  // SPI initialize

    rStop_Count = 5;                // 5 sec

    Timer_Start();                  //

//------------------------------------------------------------------------------
	while(1)
	{
        Process_Key();              //
        Process_Time();             //
        Process_SPI();              //
        Process_Power();            //
	}
}
//==============================================================================
//    task  : Power Saving Process 
//    input : rStop_Count
//    output: 
//            -Stop mode in 
//            -Wakeup by Ext8 interrupt
//==============================================================================

void Process_Power(void)
{
    if(r4mS_STOP ) return;          //
    r4mS_STOP = 250;                // 1000ms
    if(rStop_Count) 
    {   rStop_Count--;
        return;
    }
    rStop_Count = 5;


    return;             // for test !!!!!


    
    T0CR        = 0x00;             // timer0 disable
    
    BODR        = 0x80;             // LVR/BOD disable
//  BODR        = 0x08;             // LVR/BOD enable
    
    EIENAB      = 0x01;
    EIBOTH      = 0x00;
    EIEDGE      = 0x01;
    EIPOLA      = 0x01;             // Ext0  
    EIFLAG      = 0;                //
    ;
//------------------------------------------------------------------------------
//      every interrupt enable set
//------------------------------------------------------------------------------
                                    // b7   b6   b5     b4    b3    b2    b1    b0
    IE          = 0x81;             // EA   -    RX     SPI   PCI   Ext2  Ext1  Ext0
    IE1         = 0x00;             // -    -    ADC    T3    T2    T1    T0    TX
    IE2         = 0x00;             // -    -    -      -     SCM   BOD   BIT   WDT
    
//------------------------------------------------------------------------------
    PCON   = 0x03;                  // stop mode in !!!
//  PCON   = 0x01;                  // idle mode in !!!
    _nop_();                        //
    _nop_();                        //
    _nop_();                        //
//------------------------------------------------------------------------------
    Port_Initial();                 //
    
    Timer_Start();                  //
    
}
//==============================================================================
