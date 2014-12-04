#include "user.h"

extern bit sys_on;
extern bit f_50ms;
extern bit f_250ms;
extern bit buzzer_on;

	   bit buzzer1_on;
	   bit key_on;
	   bit sta;
	   bit key_in;
	   bit f_10ms;
	   bit delay_500ms_in;
	   bit led_on_wait;
	   bit delay_10s_in;
	   bit timer_on;
	   bit Standby = 1;
	   uint KeyChat;
	   uint time;
	   uint t_cnt1;
	   uint t_cnt2;

void key(void)
{
	if(Standby || timer_on)
	{
		if(FP14)
		{
			if(sta != 1)
			{
				sta = 1;
				key_in=0;
			}
		}
		else
		{
			if(sta != 0)
			{
				sta = 0;
				key_in=1;
				KeyChat=5;
			}
		}
		if(key_in && (KeyChat==0))							 
		{
			key_in = 0;
			key_on = 1;
		}
		if(key_in && (KeyChat>0) && f_10ms)	//
		{
			f_10ms = 0;
			KeyChat--;
		}
		if(key_on)
		{
			key_on = 0;
				if(time > 1)
				{
					time--;
				}
				else
				{
					time = 15;
				}
				buzzer1_on = 1;
				FP16 = 1;
				FTC0ENB	=	1;
				delay_500ms_in = 1;
				Standby = 1;
				timer_on = 0;
				t_cnt1 = 0;
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
			timer_on = 1;
			led_on_wait = 1;
			FAN_CTL = 1;
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
				Standby = 1;
			}
		}
	}
	else if(time && timer_on && f_250ms)
	{
		f_250ms = 0;
		t_cnt1++;
		if(led_on_wait && t_cnt1 == 12)
		{
			led_on_wait = 0;
			RLY_CTL = 1;
		}
		if(t_cnt1 == 240)
		{
			t_cnt1 = 0;
			time--;
			if(time == 0)
			{
				timer_on = 0;
				buzzer_on = 1;
				FP16 = 1;
				FTC0ENB	=	1;
				delay_10s_in = 1;
				RLY_CTL = 0;
				timer_on = 0;
			}
		}
	}
}