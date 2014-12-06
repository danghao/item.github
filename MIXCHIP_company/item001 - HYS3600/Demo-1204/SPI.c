//==============================================================================
//	file name   : SPI.c
//==============================================================================

#define     MyDef       extern              //
#include	"Global.h"			            //

//------------------------------------------------------------------------------
//	External function	assignment
//------------------------------------------------------------------------------
//extern void	Wait_uSec(Word);            //timer.c

extern Word Get_ADC12(Byte);

//==============================================================================
//    P00/SO
//    P01/SCK
//    P02/SI
//    P03/SS
//
//    SPICR       0xD2  SPI Control
//    SPIEN[7]    = 1   SPI enable
//    FLSB[6]     = 1   LSB first
//    MS[5]       = 0   Slave mode
//    CPOL:CPHA   = 00  rising sample, falling setup
//    DSCR[2:0]   = 000 SCK frequency fx/4)
//
//    SPIDR       0xD3  SPI data

//    SPISR       0xD4  SPI Status
//    TCIR[7]     = 1   Transmission complete
//    WCOL[6]     = 1   Write collision
//    SS_HIGH[5]  = 1   SS pin is high
//    SSENA[2]    = 1   SS pin enaable
//    TXENA[1]    = 1   data transfer enable 
//    RXENA[0]    = 1   data reception enable
//==============================================================================
void SPI_Initial(void)
{
	SPICR =  (1<<7)	            // spien
		    |(0<<6)		        // 0:MSB first, 1:LSB first
		    |(1<<5)		        // 0:slave, 1:master
//		    |(0<<4)		        // pol
		    |(1<<4)		        // pol
		    |(0<<3)		        // pha
		    |(3<<0);		    // clock setting  8MHz/128 MHz

	SPISR =  (1<<1)             // txena
		    |(1<<0)             // rxena
		    |(0<<2);            // ssena

	IE      |= 0x10;            //IE.4 = 1 SPI interrupt enable
}


//==============================================================================
//    task  : SPI Interrupt Handler
//    input : wSrc_Addr (A20~A9)
//            wDst_Addr (A11~A9) (A8~A0)
//==============================================================================
void SPI_Int_Handler(void) interrupt 4    using 1
{
    if(f_SPI_TX)                            //
    {   if(rTx_Count)                       //
        {   SPIDR = *wTX_Post++;            //
            rTx_Count--;                    //
        }
        else f_SPI_TX = OFF;                //
    }
    else
    {   *wRX_Post = SPIDR;                  //
        wRX_Post++;                         //
    }
}
//==============================================================================
//    task  : Serial Flash AT45DB161D (16Mbit)  Interface
//
//    input : command
//            wSrc_Addr  Flash Page Address    A23~A8(4096page)
//            wDst_Addr  VRAM address          A11~A8(12page),A7~A0(256 byte)
//==============================================================================

void SPI_Start(void)
{
    rTX_Data[0] = wAdc_Data >> 8;       // STX
    rTX_Data[1] = wAdc_Data%0x100;;     // 

    rTx_Count  = 2;                     //
    f_SPI_TX   = ON;                    //

    wTX_Post = &rTX_Data[0];            //
    wRX_Post = &rRX_Data[0];            //
    SPIDR    = *wTX_Post++;             // continuous array read command  upto 33MHz
}
//==============================================================================
//    task  : Process SPI
//==============================================================================

void Process_SPI(void)
{
    if(r4mS_ADC) return;
    
    r4mS_ADC = 250;
    wAdc_Data = Get_ADC12(0x02);        // AN2

    SPI_Start();
}

//==============================================================================
