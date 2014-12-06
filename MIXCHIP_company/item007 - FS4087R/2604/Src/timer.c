#include "user.h"

		bit  timer_on;
		uint t_cnt1;
		uint t_cnt2;
		uint time;

		bit un_display;
		bit delay_3s_ok;

void timer(void)
{
	if(f1s)	// && 
	{
		f1s = 0;
		t_cnt1++;
			if(t_cnt1 == 60)
			{
				t_cnt1 = 0;
				t_cnt2++;
				if((SLP)&&(t_cnt2==30 || t_cnt2==60))	// 30 min
				{
					if(speed > 2)
					speed --;
					led_buf[2] = LED_CODE[speed-1];
				}
				if(t_cnt2 == 60 )						// 1 hour
				{
					t_cnt2 = 0;
					if(timer_on)
					{
						time_to --;
						if(time_to == 0)
						{
							timer_on = 0;
							sys_on = ~sys_on;
							if(sys_on)
							{
								// open
							}
							else
							{
								delay_3s_ok = 0;
			
								buzzer0_on = 0;
								buzzer2_on = 0;
								buzzer1_on = 1;
								buz_cnt = 0;
								BUZ_EN = 0;
							}
						}
					}
				}
			}
			else if(sys_on)
			{
				if(SLP && !un_display)
				{
					if(!delay_15s_in)
					{
						delay_15s_in = 1;
						t_cnt1 = 0;
						t_cnt2 = 0;
					}
					else if((t_cnt1 == 15)&&(t_cnt2 == 0))
					{
						un_display = 1;
					}
				}
				if(!delay_3s_ok)
				{
					if(t_cnt1 == 3)
					delay_3s_ok = 1;
					led_buf[2] = LED_CODE[speed-1];
					//////////////////////////////////////////
				}
			}
	}
}