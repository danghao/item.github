#include "user.h"

extern uint time;
	   bit f_leddsp;
	   uint __ROM LED_CODE[10] = { 0x80,0xE9,0x44,0x60,0x29,0x22,0x02,0xe8,0x00,0x20 };//

extern  bit f1s;
extern 	bit shan;
bit led_on_off;
uint num_shan;
extern   uint num4_10ms;
extern   bit Standby;
extern   bit timer_on;

	extern 	bit key_dis;

void led_dsp(void)
{
	uint temp;
	f_leddsp = ~f_leddsp;
	FP11 = 1;		
	FP10 = 1;
	if(led_on_off)
	{
		if(f_leddsp)
		{
			P5 &= 0x10;
			P5 |= LED_CODE[time/10];
			FP10 = 0;
			FP11 = 1;
			for(temp=0;temp<5;temp++);
		}
		else 
		{
			P5 &= 0x10;
			P5 |= LED_CODE[time%10];
			FP11 = 0;
			FP10 = 1;
			for(temp=0;temp<5;temp++);
		}
	}
	if(f1s && shan)
	{
		f1s = 0;
		led_on_off = ~led_on_off;
		if(!key_dis)	// 没倒下
		{
			if(FP16 == 0)  //有键按下
			{
				led_on_off = 1;
				num4_10ms = 0;
			}
			else if(time != 0)
			{
				num_shan++;
				if(num_shan == 6)
				{
					num_shan = 0;
						shan = 0;
						led_on_off = 1;
						timer_on = 1;
						if(FP12 == 1)
						{
							RLY_CTL = 1;
							FAN_CTL = 1;
						}
				}
			}
		}
	}
	if(key_dis == 1 || time == 0)
	RLY_CTL = 0;

}
