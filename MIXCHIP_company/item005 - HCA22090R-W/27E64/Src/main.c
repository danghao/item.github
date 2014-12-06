#include	"user.h"

uint RX_data;
uint num10ms;
uint num_1s;
uint num_cnt;
bit f_1s;
bit f10ms;
bit BUZZER_ON;
bit f_100ms;
uint num_100ms;
	
void	main	(void)
{
	WDTR = 0x5A;
	initial();
	while(1)
	{
		WDTR = 0x5A;
		key();
		led();
		timer();
		buzzer();
	}		
}

void __interrupt [0x0B] isr_t0 (void)		//125us
{
	FT0IRQ	=	0;
	T0C		=	200;	// 131 139 209
	if(BUZZER_ON)
	FP16 = ~FP16;
	num_cnt++;
	if(num_cnt == 80)
	{
		num_cnt = 0;
		f10ms = 1;
		num10ms++;
		if(num10ms == 10)
		{
			num10ms = 0;
			f_100ms = 1;
			num_100ms++;
			if(num_100ms == 10)
			{
				num_100ms = 0;
				f_1s = 1;
			}
		}
	}
}