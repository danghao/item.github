#include "timer.h"

bit  f_display;
bit  f_1s;
u8 num_10ms;
u8 num2_10ms;
u8 num3_10ms;
u8 num_1s;
u8 time_cnt1;
u8 time_cnt2;
u8 time_cnt3;

bit F_125us;
bit f_10ms;
bit f2_10ms;
bit f3_10ms;
u8	num_125us;

//***************************************************************************
//! \brief       时间标志位处理函数
//! \param       无
//! \return      无
//***************************************************************************
void time_flag(void)
{
	if(f_t0)
	{
		f_t0 = 0;
		F_125us = 1;			//电位器
		f_01ms = 1;				//rec
		num_125us++;
		if(num_125us == 80)
		{
			num_125us = 0;
			f_10ms = 1;		//key
			f2_10ms = 1;	//buzzer
			f3_10ms = 1;	//timer
			num3_10ms ++;
			if(num3_10ms == 100)
			{
				num3_10ms = 0;
				f_1s = 1;
			}
			// Nature_Out();
			// f_1s
			// sys_3s_ok = 1;
		}
	}
}


//***************************************************************************
//! \brief       时间管理子程序
//! \param       无
//! \return      无
//***************************************************************************
void timer(void)
{
	if(f3_10ms)
	{ 
		f3_10ms = 0;
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

