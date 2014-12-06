#include "user.h"

	    bit F_125us;
		bit f_10ms;
		bit f2_10ms;
		bit f3_10ms;
		bit buz_en;
	    u8 num_125us;

void main(void)
{
	WDTR = 0x5A;
	STKP |= 0x07;
	initial();
	while(1)
	{
		WDTR = 0x5A;
		timer();
		key();
		led();
		buzzer();
		fun();
	}
}

void __interrupt [0x08] isr(void)
{
	FT0IRQ = 0;
	T0C=0xCC;
	if(buz_en)
	FP50 = ~FP50;
	F_125us = 1;
	num_125us++;
	if(num_125us == 80)
	{
		num_125us = 0;
		f3_10ms = 1;
	}
}

