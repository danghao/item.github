#include"user.h"

extern uchar Rx_Buffer;
extern bit RX_OK;	 
extern bit tx_data_on;	 
extern uchar rTx_Ptr;
bit		f_1s;
bit		f_10ms;
bit		f2_10ms;
uchar	num_10ms;

void main(void)
{
	RSTSTAT = 0X02;	   // 256 ms
	init();
	while(1)
	{
		RSTSTAT = 0X02;	   // 256 ms
		key();
		lcd();
		tx_pack();
		rx_pack();
		timer();
	}
}
void T0_Int(void) interrupt 1 using 1
{
	TF0 = 0;
	TL0 = 0x09;	   	// 10 ms
	TH0 = 0x36; 
	f_10ms = 1;
	f2_10ms = 1;
	num_10ms ++;
	if(num_10ms == 100)
	f_1s = 1;
}
void Uart_Int(void) interrupt 4 using 1
{
	if(RI)
	{
		RI = 0;
		Rx_Buffer = SBUF;
		RX_OK = 1;
	}
	if(TI)
	{
		TI = 0;
		tx_data_on = 0;
		rTx_Ptr++;
	}
}
