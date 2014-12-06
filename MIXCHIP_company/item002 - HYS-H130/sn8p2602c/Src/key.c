#include "user.h"

extern bit sys_on;
extern bit f_50ms;
extern bit f_250ms;
extern bit buzzer_on;
extern bit buzzer2_on;
extern bit BUZ_CNT1_in;
extern bit Standby;
extern bit timer_on;
extern uint t_cnt1;
extern  uint t_cnt2;
extern  bit led_on_wait;
extern  bit delay_10s_in;
	   bit buzzer1_on;
	   bit buzzer2_on;
	   bit buzzer3_on;
		bit f_dump_in;
		bit f_dump_out;
	   bit key_on;
	   bit sta;
	   bit key_in;
	   bit f_10ms;
	   bit delay_500ms_in;
	   uint KeyChat;
	   uint time;
		bit f_dump_ok;
		bit f4_10ms;
		bit key_dis;
		bit dump_sta;
		uint BUZ_CNT;
		uint BUZ_CNT1;
		uint num2_10ms;
		uint num3_10ms;
		uint temp1s;
uint num5_10ms;
extern  bit f1s;
extern 	bit shan;
extern  bit led_on_off;
extern  uint num4_10ms;
extern  uint num_shan;
extern  bit s;
//bit dumpin;
void key(void)
{
		if(FP16)
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
		if(key_in && (KeyChat>0) && f_10ms)	
		{
			f_10ms = 0;
			KeyChat--;
		}
///////////////////////////////////////////////////////////////////////////
			if(Standby || timer_on)
			{
			}
		if(key_on)
		{
			key_on = 0;		//( && !key_dis)dumpin
			if(!key_dis)
			{
				num4_10ms = 0;
				led_on_off = 1;
	  			num_shan = 0;
				shan = 1;

				if(time > 1)
				{
					time--;
				}
				else
				{
					time = 15;
				}
				buzzer1_on = 1;

					FTC0ENB = 0;
					FP14 = 0;
	   				buzzer_on = 0;
	   				buzzer2_on = 0;
	   				buzzer3_on = 0;
					BUZ_CNT = 0;
					BUZ_CNT1 = 0;
					BUZ_CNT1_in = 0;

				delay_500ms_in = 1;
				delay_10s_in = 0;
				Standby = 1;
				timer_on = 0;
				t_cnt1 = 0;
				t_cnt2 = 0;
//				f_dump_in = 0;
//				f_dump_ok = 0;
			}
			else
			{
				buzzer2_on = 1;

					FTC0ENB = 0;
					FP14 = 0;
	   				buzzer_on = 0;
	   				buzzer1_on = 0;
	   				buzzer3_on = 0;
					BUZ_CNT = 0;
					BUZ_CNT1 = 0;
					BUZ_CNT1_in = 0;
			}
		}
////////////////////////////////////////////////////////////
	if(dump_sta != FP12)
	{
		dump_sta = FP12;
		if(FP12)		//on
		{
			s = 0;
			if(f_dump_in)
			{
				f_dump_in = 0;
			}
			else if(key_dis)
			{
				f_dump_out = 1;
				num3_10ms = 0;
//				temp1s = 0;
			}	

		}
		else		//dump
		{
			if(f_dump_out)
			{
				f_dump_out = 0;
			}
			else if(!key_dis)
			{
				f_dump_in = 1;
				num2_10ms = 0;
				temp1s = 0;
			}
		}
	}
////////////////////////////////////////////////////////////
	if(f4_10ms)
	{
		f4_10ms = 0;
		if(f_dump_in)
		{
			num2_10ms++;
			if(num2_10ms == 100)			//200
			{
				num2_10ms = 0;
				f_dump_in = 0;
				f_dump_ok = 1;
				time = 0;
				timer_on = 0;
				key_dis = 1;
				RLY_CTL = 0;
				t_cnt1 = 0;
				t_cnt2 = 0;
				Standby = 0;
				shan = 1;
				if(!s)
				{
		   			buzzer2_on = 1;
					FTC0ENB = 0;
					FP14 = 0;
					buzzer_on = 0;
					buzzer1_on = 0;
					buzzer3_on = 0;
					BUZ_CNT = 0;
					BUZ_CNT1 = 0;
					BUZ_CNT1_in = 0;
				}
			}
		}
		if(f_dump_out)
		{
			num3_10ms++;
			if(num3_10ms == 200)
			{
				num3_10ms = 0;
				f_dump_out = 0;
				key_dis = 0;
				Standby = 1;
				delay_500ms_in = 0;
				delay_10s_in = 0;
			}
		}
		if(f_dump_ok)
		{
			num5_10ms ++;
			if(num5_10ms == 100)
			{
				num5_10ms = 0;
				temp1s++;
				if(temp1s == 30)
				{
					temp1s = 0;
					if(timer_on == 0)
					FAN_CTL = 0;
					f_dump_ok = 0;
				}
			}
		}
	}
}