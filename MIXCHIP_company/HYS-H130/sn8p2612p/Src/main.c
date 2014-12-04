#include "user.h"

extern	bit f_10ms;
extern	bit f2_10ms;
extern	bit f3_10ms;
extern	bit f4_10ms;
extern	bit f_50ms;
extern	bit f_250ms;
extern  bit delay_10s_in;
extern	uint time;
extern  uint t_cnt1;
extern  uint t_cnt2;
extern  bit timer_on;
extern  bit Standby;
extern  bit buzzer_on;
extern  bit delay_500ms_in;
extern  bit led_on_wait;



		bit dump_sta;
		bit f_dump_in;
		bit f_dump_ok;
		bit f4_10ms;
		bit FAN_buf;
		bit RLY_buf;
		bit f_p00_in;
	    uint num_10ms;
		uint BUZ_CNT;
		uint BUZ_CNT1;
		uint num2_10ms;
		uint temp1s;

void main(void)
{
	WDTR = 0x5A;
	STKP |= 0x07;
	initial();
		while(FP00)
		{
			WDTR = 0x5A;
			led_dsp();
		}
		FGIE=1;
		buzzer_on = 1;
		FP16 = 1;
		FTC0ENB	=	1;
	while(1)
	{
		WDTR = 0x5A;
		key();
		led_dsp();
		if(dump_sta != FP00)
		{
			dump_sta = FP00;
			if(FP00)
			{
				f_dump_in = 1;
				num2_10ms = 0;
				temp1s = 0;
			}
			else
			{
				f_dump_in = 0;
				if(f_dump_ok)
				{
					f_dump_ok = 0;
					delay_10s_in = 1;
					t_cnt1 = 0;
					t_cnt2 = temp1s;
					timer_on = 0;
				}
			}
		}
		if(f_dump_in && FP00)
		{
			if(f4_10ms)
			{
				f4_10ms = 0;
				num2_10ms++;
				if(num2_10ms == 200)
				{
					num2_10ms = 0;
					time = 0;
					RLY_CTL = 0;
					FP16 = 0;
					f_dump_ok = 1;
					Standby = 0;
					timer_on = 0;
					f_dump_in = 0;
					while(FP00)
					{
						WDTR = 0x5A;
						led_dsp();
						if(f4_10ms && f_dump_ok)
						{
							f4_10ms = 0;
							num2_10ms++;
							if(num2_10ms == 100)
							{
								num2_10ms = 0;
								temp1s++;
								if(temp1s == 30)
								{
									temp1s = 0;
									FAN_CTL = 0;
									f_dump_ok = 0;
								}
							}
						}
					}
					if(!f_dump_ok)
					{
						////≥ı ºªØ////
						delay_500ms_in = 0;
						led_on_wait = 0;
						delay_10s_in = 0;
						timer_on = 0;
						Standby = 1;
						t_cnt1 = 0;
						t_cnt2 = 0;
					}
				}
			}
		}
	}
}

void __interrupt [0x08] isr(void)
{
	if(FT0IEN)
	{
		if(FT0IRQ)
		{
			FT0IRQ = 0;
			T0C=0x64;	//T0C≥ı÷µ 10ms
			f_10ms = 1;
			f2_10ms = 1;
			f3_10ms = 1;
			f4_10ms = 1;
			num_10ms++;
		}
	}
}

