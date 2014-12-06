#include "user.h"

extern uint BUZ_CNT;
extern uint BUZ_CNT1;
extern bit sys_on;
extern bit buzzer_on;
extern bit buzzer2_on;
extern bit BUZ_CNT1_in;
extern bit delay_500ms_in;
extern uint time;
extern bit buzzer1_on;
extern bit buzzer3_on;
extern uint num_10ms;
	   bit delay_10s_in;
	   bit timer_on;
	   bit Standby = 1;
	   bit led_on_wait;
	   uint t_cnt1;
	   uint t_cnt2;
	   bit f_50ms;
	   bit f_250ms;
	   bit f2_10ms;

extern  bit f1s;
extern 	bit shan;
extern  bit led_on_off;
extern  bit key_dis;

void timer(void) 
{
	if(f2_10ms)
	{
		f2_10ms = 0;
		if(num_10ms % 5 == 0)
		{
			f_50ms = 1;
		}
		if(num_10ms == 25)
		{
			num_10ms = 0;
			f_250ms = 1;
		}
	}
	if(delay_500ms_in && f_50ms)
	{
		f_50ms = 0;
		t_cnt1++;
		if(t_cnt1 == 10)
		{
			t_cnt1 = 0;
			delay_500ms_in = 0;
			Standby = 0;
//			timer_on = 1;
			led_on_wait = 1;
		}
	}
	else if(delay_10s_in && f_50ms)
	{
		f_50ms = 0;
		t_cnt1++;
		if(t_cnt1 == 20)
		{
			t_cnt1 = 0;
			t_cnt2++;
			if(t_cnt2 == 30)
			{
				t_cnt2 = 0;
				delay_10s_in = 0;
				FAN_CTL = 0;
			}
		}
	}
	else if(!key_dis && time && timer_on && f_250ms)
	{
		f_250ms = 0;
		t_cnt1++;
		if(led_on_wait && t_cnt1 == 12)
		{
			led_on_wait = 0;
		}
		if(t_cnt1 == 240)
		{
			t_cnt1 = 0;
			time--;
			if(time == 0)
			{
				timer_on = 0;
				buzzer3_on = 1;

					FTC0ENB = 0;
					FP14 = 0;
	   				buzzer_on = 0;
	   				buzzer1_on = 0;
	   				buzzer2_on = 0;
					BUZ_CNT = 0;
					BUZ_CNT1 = 0;
					BUZ_CNT1_in = 0;

				delay_10s_in = 1;
				RLY_CTL = 0;
				timer_on = 0;
				Standby = 1;
				shan = 1;

			}
		}
	}

}