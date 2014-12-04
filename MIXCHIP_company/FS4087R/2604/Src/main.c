#include "user.h"

		bit f2_10ms;
	    uint num_5ms;
	
		bit f1s;
		bit shan;

void main(void)
{
	WDTR = 0x5A;
	initial();
	while(1)
	{
		WDTR = 0x5A;
		key();
		led();
//		buzzer();
		timer();
//		rec();
		receive();
		send();
	}
}

void __interrupt [0x08] isr(void)
{
	FT0IRQ = 0;
	T0C = 0xcc;		// 125us
	if(BUZ_EN)
	{
		BUZ = ~BUZ;
	}
	f_01ms = 1;
	f_dt = 1;
}

