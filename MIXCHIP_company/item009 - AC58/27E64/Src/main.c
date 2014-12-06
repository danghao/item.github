#include "main.h"

#include "init.h"
#include "timeflag.h"
#include "rxdata.h"
#include "txdata.h"

u8  RX_buf;
bit RX_ok;
bit f_t0;	// 125us

void main(void)
{
	WDTR = 0x5A;
	IO_Init();
	T0_Init();
	Uart_Init();
	while(1)
	{
		WDTR = 0x5A;
		Rx_Data();
		Tx_Data();
		TimeFlag();
	}
}

void __interrupt [0x13] isr_uart_rx (void)
{
	if(FURXIRQ)
	{
		FURXIRQ = 0;
		RX_buf  = 	URXD;
		RX_ok	= 	1;
	}
}

void __interrupt [0x0B] isr_t0 (void)	//125us
{
	FT0IRQ = 0;
	T0C = 200;
	f_t0 = 1;
}
