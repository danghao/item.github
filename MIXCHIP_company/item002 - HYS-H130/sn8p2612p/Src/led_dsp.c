#include "user.h"

extern uint time;
extern bit buzzer_on;
extern uint BUZ_CNT;
extern uint BUZ_CNT1;
extern uint num_10ms;
extern bit buzzer1_on;

	   bit f_50ms;
	   bit f_250ms;
	   bit f2_10ms;
	   bit f3_10ms;
	   bit f_leddsp;
	   bit buzzer_on;

uint __ROM LED_CODE[10] = { 0x80,0xE9,0x44,0x60,0x29,0x22,0x02,0xe8,0x00,0x20 };//

void led_dsp(void)
{
	uint temp;
		f_leddsp = ~f_leddsp;
			FP11 = 1;		
			FP10 = 1;
		if(f_leddsp)
		{
			P5 &= 0x10;
			P5 |= LED_CODE[time/10];
			FP11 = 0;		// 十位显示
			FP10 = 1;
			for(temp=0;temp<5;temp++);
		}
		else 
		{
			P5 &= 0x10;
			P5 |= LED_CODE[time%10];
			FP10 = 0;		// 个位显示
			FP11 = 1;
			for(temp=0;temp<5;temp++);
		}

	if(f3_10ms)	//100ms
	{
		f3_10ms = 0;
		if(buzzer_on)
		{
			BUZ_CNT++;
			if(BUZ_CNT == 4 || BUZ_CNT == 14 || BUZ_CNT == 24)
			{
				FP16 = 0;
			}
			else if(BUZ_CNT == 10)
			{
				FTC0ENB = 0;
				TC0C=0x91;	//  2.25k
				TC0R=0x91;
				FTC0ENB = 1;
				FP16 = 1;
			}
			else if(BUZ_CNT == 20)
			{
				FTC0ENB = 0;
				TC0C=0x9A;	//  2.4k
				TC0R=0x9A;
				FTC0ENB = 1;
				FP16 = 1;
			}
			else if(BUZ_CNT == 120)
			{
				BUZ_CNT = 0;
				buzzer_on = 0;
				FP16 = 0;
				FTC0ENB = 0;
				TC0C=0x8A;	//  2.1k
				TC0R=0x8A;
			}
		}
		if(buzzer1_on)
		{
			BUZ_CNT++;
			if(BUZ_CNT == 13)
			{
				BUZ_CNT = 0;
				FTC0ENB = 0;
				buzzer1_on = 0;
			}
			else if(BUZ_CNT == 4)
			{
				FP16 = 0;
			}
		}
	}
	if(f2_10ms)
	{
		f2_10ms = 0;
		if(num_10ms % 5 == 0) //50ms
		{
			f_50ms = 1;
		}
		if(num_10ms == 25) //250ms
		{
			num_10ms = 0;
			f_250ms = 1;
		}
	}
}
