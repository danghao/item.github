#include "user.h"

	    u8 num_10ms;
	    u8 num2_10ms;
	    u8 num_1s;
		bit f_display;
		bit f_1s;
		bit f2_1s;
		u8 time_cnt1;
		u8 time_cnt2;
		u8 time_cnt3;
		bit f4_10ms;

void timer(void) 
{
	if(f3_10ms)
	{
		f3_10ms = 0;
		f_10ms = 1;
		f2_10ms = 1;
		f4_10ms = 1;
		if(sys_on || timer_on)
		{
			num_10ms++;
			if(num_10ms == 100)
			{
				num_10ms = 0;
				f_1s = 1;
				f2_1s = 1;
				num_1s++;
				if(num_1s == 3)		// display <-->
				{
					num_1s = 0;
					time_speed_dsp(2);
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
				if(time_cnt1 == testmode_timer)
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
							led_data[2] &= 0xfc;
							if(!sys_on)
							{
								led_data[0] = 0;					
								led_data[1] = 0;					
								led_data[2] = 0;					
								led_data[3] = 0;

								buzzer_on = 0;
								buzzer2_on = 0;
								buzzer1_on = 1;
								BUZ_CNT = 0;
								buz_en = 0;
							}
							else
							{
								num_10ms = 0;
								num_1s = 0;
								if(!timer_on)
								{
									led_data[2] &= 0xeb;
									if(SIL)	
									{
										speed = 0;
										led_data[2] |= 0x04;	
									}
									else if(speed == 5)
									led_data[2] |= 0x10;
									time_speed_dsp(1);

									led_data[2] &= 0xf7;
									led_data[3] &= 0xe7;
									if(mode == 1)
									led_data[3] |= 0x10;
									else if(mode == 2)
									mode = 0;
									else if(mode == 0)
									led_data[2] |= 0x08;

									if(sw)		led_data[3] |= 0x01;
									else		led_data[3] &= 0xfe;

									if(HUM)		led_data[2] |= 0x20;
									else		led_data[2] &= 0xdf;

									if(ion)		led_data[3] |= 0x04;
									else 		led_data[3] &= 0xfb;
								}
								buzzer_on = 0;
								buzzer1_on = 0;
								buzzer2_on = 1;
								BUZ_CNT = 0;
								buz_en = 0;
							}
							led_data_ok = 1;
						}
					}
				}
			}
		}
	}
}