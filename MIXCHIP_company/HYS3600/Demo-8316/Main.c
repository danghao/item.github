/*==============================================================================
//	Project     : MC96F8316 Demo Program
//	Date	    : 2012.08.03~
//	Author      : B	J Lim

//	Device      : MC96F8316(32SOP)
//	Voltage     : 3.3V
//	Frequency	: internal 16 MHz RC oscillator
//  ADC range   : 3.3V (Vdd)
//  edit tool   : 4 character tab.
//==============================================================================
//	History :

    2012-08-03	1. FND Display Program	Start

//==============================================================================

                              MC86F8316 (32SOP)
                  ____________________  ____________________
         0V --> 1|VSS                                   VDD|32 <-- 5V
    4.19MHz <-- 2|P37/XOUT                     DSDA/AN0/P00|31 <-- OCD interface
    4.19MHz --> 3|P36/XIN                      DSCL/AN1/P01|30 <-- OCD interface
     Melody <-- 4|R35/EINT10/PWM0/T0O   AN2/AVREF/EINT0/P02|29 <-- 5V
   32.7KHz  --> 5|P34/SXIN                    AN3/EINT1/P03|28 <-- Switch2
   32.7KHz  <-- 6|P33/SXOUT                   AN4/EINT2/P04|27 <-- Switch3
            <-- 7|P32/RESETB                  AN5/EINT3/P05|26 <-- Switch4
        RX  --> 8|P31/RXD/(SCL)               AN6/EINT4/P06|25 <-- Switch5
        TX  <-- 9|P30/TXD/(SDA)               AN7/EINT5/P10|24 --> a_segment
       LED5 -->10|P26/EC0               AN8/BUZO/EINT11/P11|23 --> b_segment
       LED4 -->11|P25/SCL               AN9/PWM1/EINT11/P12|22 --> c_segment
       LED3 -->12|P24/SDA              AN10/PWM2/EINT12/P13|21 --> d_segment
       FND4 -->13|P23/EINTA                   AN11/MISO/P14|20 --> e_segment
       FND3 -->14|P22/EINT9                   AN12/MOSI/P15|19 --> f_segment
       FND2 -->15|P21/EINT8                    AN13/SCK/P16|18 --> g_segment
       FND1 -->16|P20/EINT7                 AN14/EC2/SS/P17|17 --> h_segment
                 -------------------------------------------
*/
//------------------------------------------------------------------------------
//	Include file and variable
//------------------------------------------------------------------------------

#define     MyDef					    // MyDef(space) means proto-type variable
#include    "Global.h"				    //


#define     CRYSTAL     0               //
//------------------------------------------------------------------------------
//	external prototype function
//------------------------------------------------------------------------------

extern void	Process_Key();			    // Key.c
extern void	Process_Time();			    // Time.c
extern void	Wait_uSec(Word);		    //

extern void	Process_Led();              // Led.c
extern void RTC_DIsplay();              //

extern void	I2C_Initialize();           // I2C.c

extern void	Uart_Initialize();          // Uart.c

extern void Process_Melody();			//

void Port_Initial();				    //
void Timer_Start();				        //
void Process_Power();                   //

//==============================================================================
//	Main Program
//==============================================================================

main(void)
{                                       // System Clock Select & builtin reset level select
#if CRYSTAL
    P3FSR  = 0xC0;                      // 7=1:P37_XOUT, 6=1:P36_XIN
    OSCCR  = 0x02;                      // external OSC enable start
    
    Wait_uSec(16000);                   // 16ms
    
    SCCR   = 0x01;                      // external 8MHz main OSC (fxin) for System clock
    OSCCR  = 0x06;                      // internal RC OSC disable, external main OSC enable
#else
    OSCCR  = 0x18;                      // internal RC OSC 8MHz
    BITCR  = 0x4E;                      // BIT = 8MHz/128/128 = 16.384ms

    Wait_uSec(16000);                   // 16ms

#endif
    
    LVRCR  = 0x0A;                      // builtin reset 2.44V set, LVRCR.0=0 enable !!!
    
    Port_Initial();                     // Input, output port initialize
    
    Wait_uSec(60000);                   // 60ms System Stabilize Delay
    
    I2C_Initialize();                   // I2C Block initialize
    
    Uart_Initialize();                  // Uart Block initialize
    
    rHour   = 12;                       //
    rMinute = 0;                        //
    RTC_DIsplay();                      //
    
    WTCR  = 0x8C;                       // 1 minute watch timer
    WTDR  = 0x80+119;                   //
    
    Timer_Start();                      // Timer & Interrupt start
    
//------------------------------------------------------------------------------
//  main loop
//------------------------------------------------------------------------------
    
	while (1)					        //
	{
     // WDTCR = 0xE0;                   // WDT refresh
    
		Process_Key();			        // key scan & execute
    
		Process_Led();			        // LED Display Update
    
		Process_Time();			        // Clock count up and measurement
	
		Process_Melody();               //
    
    //  Process_Power();                // Icc=0.8uA@3.3V STOP mode in
	}
}

//==============================================================================
//	Prototype Function
//==============================================================================
//------------------------------------------------------------------------------
//  task    : I/O Port Initialize
//------------------------------------------------------------------------------
void Port_Initial(void)
{                           // b7     b6     b5     b4     b3     b2     b1     b0
                            // -      SW5    SW4    SW3    SW2    AN2    DSCL   DSDA
    P0IO    = 0x03;         // -      in     in     in     in     in     out    out
    P0OD    = 0x78;         // -      OD     OD     OD     OD     PP     OD     OD
	P0PU    = 0x7B;         // -      on     on     on     on     off    on     on
 	P0		= 0x7F;		    // -      1      1      1      1      1      1      1
    P03DB   = 0x5E;         // 0      1      P35DB  P06DB  P05DB  P04DB  P03DB  P02DB  76=01: fx/4 = 1us noise filtering
 	P0FSR   = 0x08;		    // 0      0      0      0      1      0      0      0

                            // b7     b6     b5     b4     b3     b2     b1     b0
                            // h      g      f      e      d      c      b      a
    P1IO    = 0xFF;         // out    out    out    out    out    out    out    out
    P1OD    = 0x00;         // PP     PP     PP     PP     PP     PP     PP     PP
	P1PU    = 0x00;         // off    off    off    off    off    off    off    off
 	P1		= 0x00;		    // 0      0      0      0      0      0      1      0
    P12DB   = 0x00;         // P23DB  P22DB  P21DB  P20DB  P13DB  P12DB  P11DB  P10DB
 	P1FSRH  = 0x00;		    // 0      0      0      0      0      0      0      0
 	P1FSRL  = 0x00;		    // 0      0      0      0      0      0      0      0
    
                            // b7     b6     b5     b4     b3     b2     b1     b0
                            // -      LED5   LED4   LED3   COM4   COM3   COM2   COM1
    P2IO    = 0x7F;         // -      out    out    out    out    out    out    out
    P2OD    = 0x7F;         // -      OD     OD     OD     OD     OD     OD     OD
	P2PU    = 0x00;         // -      off    on     on     off    off    off    off
 	P2		= 0xFF;		    // -      1      1      1      1      1      1      1
 	P2FSR   = 0x00;		    // -      -      -      -      -      -      SCL    SDA
    
                            // b7     b6     b5     b4     b3     b2     b1     b0
                            // XOUT   XIN    T0O    SXOUT  SXIN   nc     RX     TX
    P3IO    = 0x24;         // in     in     out    in     in     out    in     in
    P3OD    = 0x03;         // PP     PP     PP     PP     PP     PP     OD     OD
	P3PU    = 0x03;         // off    off    off    off    off    off    on     on
 	P3		= 0x03;		    // 0      0      0      0      0      0      1      1
 	P3FSR   = 0xF9;		    // 1      1      1      1      1      0      0      1
}

//------------------------------------------------------------------------------
//  task    : Timer and Interrupt start
//------------------------------------------------------------------------------
void Timer_Start(void)
{
#if  CRYSTAL
    T1CRH       = 0x80;                 // Timer 1 enable
    T1ADR       = 130;                  // 15.258789us x 131   = 1.9989ms interval
    T1CRL       = 0x40;                 // pcs= 4.194304MHz/64 = 65.536KHz (15.258789us)
    T1CRH       = 0x81;                 // Timer 1 start
#else
    T1CRH       = 0x80;                 // Timer 1 enable
    T1ADR       = 1999;                 // 1us x 2000   = 2ms interval
    T1CRL       = 0x80;                 // pcs= 4MHz/4 = 1us
    T1CRH       = 0x81;                 // Timer 1 start
#endif

//  BITCR       = 0x4E;                 // BIT = 4.19MHz/128/128 = 32.768ms
//  WDTDR       = 60;                   // 32.768 x 61 = 1.998848 sec watchdog refresh cycle
//  WDTCR       = 0xE0;                 // WDT enable and refresh
    
//  IP          = 0x00;                 // Interrupt Priority Register 0
//  IP1         = 0x00;                 // Interrupt Priority Register 1
    
//  EIPOL1      = 0x00;                 // Ext Int8 falling edge trigger
//  EIPOL0L     = 0xA8;                 // Ext Int 3~0 Polarity Register Low
//  EIPOL0H     = 0x02;                 // Ext Int 7~4 Polarity Register High
    EIFLAG0     = 0x00;                 // Ext Int Flag Register0
    EIFLAG1     = 0x00;                 // Ext Int Flag Register1

                                        // b7    b6    b5    b4    b3    b2    b1    b0
    IE          = 0x80;                 //(EA)   -     ExG0  -     -     Ex12  Ex11  Ex10
    IE1         = 0x18;                 // -     -     -    (TX)  (RX)   I2C   Ex6   Ex5
    IE2         = 0x04;                 // -     -     ExG1  -     T2   (T1)   T0    T0V
    IE3         = 0x04;                 // -     -     -     BIT   WDT   WT    SPI   ADC
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
    if(r2mS_STOP ) return;              //
    
    r2mS_STOP = 250;                    // 500ms
    if(rStop_Count)                     //
    {     rStop_Count--;                //
        return;                         //
    }
    
    rStop_Count = 20;                   // 10sec
    P1  = 0x00;                         // all segment off
    P2 |= 0x3F;                         // all grid off
    
    T1CRH       = 0x00;                 // Timer 1 enable

    EIPOL1      = 0x00;                 // Ext Int8 falling edge trigger
    EIPOL0L     = 0xA8;                 // Ext Int 3~0 falling edge wakeup
    EIPOL0H     = 0x02;                 // Ext Int 7~4 Polarity Register High
    EIFLAG0     = 0x00;                 // Ext Int Flag Register0
    EIFLAG1     = 0x00;                 // Ext Int Flag Register1

                                        // b7    b6    b5    b4    b3    b2    b1    b0
    IE          = 0xA0;                 //(EA)   -    (ExG0)  -     -    Ex12  Ex11  Ex10
    IE1         = 0x00;                 // -     -     -     TX    RX    I2C   Ex6   Ex5
    IE2         = 0x00;                 // -     -     ExG1  -     T2    T1    T0    T0V
    IE3         = 0x00;                 // -     -     -     BIT   WDT   WT    SPI   ADC

    PCON   = 0x03;                      // stop mode in !!!
    _nop_();                            //
    _nop_();                            // 0.8uA@3.3V ±¸Çö Ok
    _nop_();                            // wakeup by Ext0~EINT3

    Timer_Start();                      //
}
//==============================================================================
