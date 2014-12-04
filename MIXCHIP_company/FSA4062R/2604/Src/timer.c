#include "user.h"

	    uint num_10ms;
	    uint num2_10ms;
	    uint num_1s;
		bit f_display;
		uint time_cnt1;
		uint time_cnt2;
		uint time_cnt3;

void timer(void) 
{
	if(f3_10ms)
	{
		f3_10ms = 0;
		f_10ms = 1;
		f2_10ms = 1;
		if(sys_on || timer_on)
		{
			num_10ms++;
			if(num_10ms == 100)
			{
				num_10ms = 0;
				num_1s++;
				if(num_1s == 3)		// display <-->
				{
					num_1s = 0;
					f_display = ~f_display;
					if(f_display)
					{
						if(timer_keyin)	timer_keyin = 0;
						led_data[1] = LED_CODE[speed/10];
						led_data[0] = LED_CODE[speed%10];
					}
					else
					{
						time_dsp();
					}
					led_data_ok = 1;
				}
			}
		}
		num2_10ms++;
		if(num2_10ms == 100)
		{
			num2_10ms = 0;
			if(timer_on)	// timer
			{
				time_cnt1 ++;
				if(time_cnt1 == 60/time_dec)
				{
					time_cnt1 = 0;
					time_cnt2 ++;
					if((time_cnt3 >= 6 && time_cnt2 == 60)||(time_cnt3 < 6 && time_cnt2 == 30))
					{
						time_cnt2 = 0;
						time_to --;
						if(time_to == 0)
						{
							timer_on = 0;
							sys_on = ~sys_on;
							if(sys_on)
							{
								
							}
							else 
							{
								
							}
						}
					}
				}
			}
		}
	}
}