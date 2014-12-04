#include "user.h"

extern	bit f_10ms;
extern	bit f2_10ms;
extern	bit f4_10ms;
		bit f_3ms;
	    uint num_1ms;
	    uint num2_1ms;
	    uint num_10ms;
	    uint num4_10ms;
bit s;
		bit f1s;
		bit shan;

void main(void)
{
	WDTR = 0x5A;
	STKP |= 0x07;
	initial();
	if(!FP12)
	s = 1;
	while(1)
	{
		WDTR = 0x5A;
		key();
		timer();
		led_dsp();
		buzzer();
	}
}

void __interrupt [0x08] isr(void)
{
	if(FT0IEN)
	{
		if(FT0IRQ)
		{
			FT0IRQ = 0;
			T0C=0x84;
			num_1ms++;
			if(num_1ms == 3)
			{
				num_1ms = 0;
				f_3ms = 1;
			}
			num2_1ms++;
			if(num2_1ms == 10)
			{
				num2_1ms = 0;
				f_10ms = 1;
				f2_10ms = 1;
				f4_10ms = 1;
				num_10ms++;
				num4_10ms++;
				if(num4_10ms == 50)
				{
					num4_10ms = 0;
					f1s = 1;
				}
			}
		}
	}
}

