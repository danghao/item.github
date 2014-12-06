//==============================================================================
//	task  : UART Interrupt interface
//==============================================================================

#define      MyDef       extern         //
#include	"Global.h"			        //

/*
//------------------------------------------------------------------------------
//    UART Special Function Register define 
//
//      P30 / TX
//      P31 / RX
//------------------------------------------------------------------------------
      UARTCR1           = 0x06
            UPM(54)     = 00:no parity 
            USUZE(321)  = 011:8bit 
 
      UARTCR2           = 0x6E
            UDRIE(7)    = 1:when buffer empty, request interrupt 
            TXCIE(6)    = 1:when TX finish, request interrupt 
            RXCIE(5)    = 1:when RX finish, request interrupt 
            WEKEIE(4)   = 1:wakeup STOP mode 
            TXE(3)      = 1:TX enable 
            RXE(2)      = 1:RX enable 
            USARTEN(1)  = 1:USART module enable 
            U2X(0)      = 0:normal speed, 1:double speed 

      UARTCR3           = 0x00
            LOOPS(6)    = 0:normal, 1:loop back mode enable 
            USBS(2)     = 0:single STOP, 1:double stop 
            TX8(1)      = ?:msb 9th bit in TX 
            RX8(0)      = ?:msb 9th bit in RX

      UARTST
            UDRE(7)     = 1:TX buffer empty 
            TXC(6)      = 1:TX complete 
            RXC(5)      = 1:RX complete 
            WAKE(4)     = 1:Wake 
            SOFTRST(3)  = 1:Reset Uart
            DOR(2)      = 1:Data Over RUN 
            FE(1)       = 1:Frame Error 
            RE(0)       = 1:Parity Error 

      UARTBD            = 25:9600bps@4MHz, 12:19200bps@4MHz, 12:38400bps@8MHz
      UARTDR            = 
*/
/******************************************************************************/
//    task  : UART communication full-duplex protocol
//
//    format:
//            STX LEN D0  D1  D2  D3 ....Dn  SUM ETX
//            02h n+1 xxh xxh xxh xxh ...xxh xxh 03h
/******************************************************************************/
//------------------------------------------------------------------------------
//    UART Constant define
//------------------------------------------------------------------------------
#define     STX         0x02            //
#define     ETX         0x03            //

#define   BAUD_9600     23              //fx = 3.6864 MHz,  (8.68us)
#define   BAUD_19200    11              //
#define   BAUD_38400    5               //
#define   BAUD_115200   1               //
//------------------------------------------------------------------------------
//    Variabl define
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	task	: Uart initialize
//	input	:
//------------------------------------------------------------------------------

void Uart_Initialize(void)
{
    unsigned char k;
                                        // b7   b6   b5   b4   b3   b2   b1   b0
                                        //                RXD  TXD
	P3IO    = 0x0F;              	    // -    -    -    in   out  out  out  out
	P3      = 0x1F;              	    // -    -    -    1    1    P32  P31  P30
    P3OD    = 0x18;                     // -    -    -    OD   OD   pp   pp   pp
	P3PU    = 0x18;              	    // -    -    -    on   on   off  off  off
    
    UARTCR1 = 0x06;                     //
    UARTCR2 = 0x6E;                     //
    UARTCR3 = 0x00;                     //
    UARTBD  = BAUD_115200;			    //
    UARTST  = 0x00;                     //
    
    f_New_Packet= 0;                    //
    
	k	  = UARTDR;				        // clear overrun error !!!
}
//------------------------------------------------------------------------------
//    UART0 transmission start
//------------------------------------------------------------------------------

void Uart_Tx_Start(void)
{
    rTx_Ptr = 1;                        //
	UARTDR  = xTx_Buffer[0];		    // the first data byte out
}

//------------------------------------------------------------------------------
//	task	: Uart packet transmit
//------------------------------------------------------------------------------
void Uart_Transmit(void)
{
    Byte  k,m;

    rLength       = 5;                  // 5 byte transmit
    xTx_Buffer[0] = 0x02;               // STX
    xTx_Buffer[1] = rLength;            // LEN
    
    xTx_Buffer[2] = 0x98;               //
    xTx_Buffer[3] = 0x76;               //
    xTx_Buffer[4] = 0x54;               //
    xTx_Buffer[5] = 0x32;               //
    xTx_Buffer[6] = 0x10;               // payloader 5byte
    
    m = 0;                              //
    for(k=0;k<rLength+2;k++)            //
        m ^= xTx_Buffer[k];             // 
    xTx_Buffer[rLength+2] = m;          // BCC
    xTx_Buffer[rLength+3] = 0x03;       // ETX 
    rTx_Count = rLength+4;              //
    
    Uart_Tx_Start();                    //
}

//------------------------------------------------------------------------------
//	Uart TX interrupt 
//------------------------------------------------------------------------------
void Uart_Tx_Int_Handler(void) interrupt 10    using 1
{
    if(rTx_Count)					    //
    {	UARTDR = xTx_Buffer[rTx_Ptr];	//
    	rTx_Ptr++;					    //
    	rTx_Count--;				    //
    }
}
//------------------------------------------------------------------------------
//	Uart RX interrupt 
//------------------------------------------------------------------------------
void Uart_Rx_Int_Handler(void) interrupt 9    using 1
{
    unsigned char itemp;
    
	if(UARTST & 0x07)			            //
	{	UARTST = 0x08;                      //software reset
	    Uart_Initialize();			        //
            return;                         //
    }
    itemp = UARTDR;                         //
    if((itemp == STX)&&(f_New_Packet==0))   //
    {   rRx_Ptr = 0x00;                     //
        f_New_Packet = 1;                   //
    }
    else 
    {   if((itemp == ETX)&&(rRx_Ptr==(xRx_Buffer[1]+3)))//
        {     f_New_Packet = 0;                         //
              f_Req_Decode = 1;                         //
        }
    }
    xRx_Buffer[rRx_Ptr] = itemp;            //
    rRx_Ptr++;                              //
}

//------------------------------------------------------------------------------
//	task	: Uart receive packet decode
//------------------------------------------------------------------------------
void Uart_Packet_Decode(void)
{
    Byte  k,sum=0;
    
    if(f_Req_Decode)
    {   f_Req_Decode = 0;                   //
    
        for(k=0;k<xRx_Buffer[1]+2;k++)      //checksum Calculate
             sum ^= xRx_Buffer[k];          // 
        
        k = xRx_Buffer[1]+3;                //checksum post
        if(sum == xRx_Buffer[k])            //
        {                                   //checksum ok ... 
            
            
            
        }
    }
}

//==============================================================================
