#include"user.h"

extern  bit 	f_139us;
extern  bit 	f2_139us;
		bit		f_10ms;
		bit		f2_10ms;
		uchar	num_139us;

void main(void)
{
	init();
	while(1)
	{
		tx_pack();
		rx_pack();
		key();
		lcd();
		timer();
	}
}
void T0_Int_Handler(void) interrupt 7 using 1
{
	f_139us=1;		   		// 2400 bit/s
	f2_139us=1;
	num_139us++;
	if(num_139us >= 80)
	{
		num_139us =	0;
		f_10ms = 1;
		f2_10ms = 1;
	}
}