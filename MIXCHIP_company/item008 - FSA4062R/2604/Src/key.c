#include "user.h"

		bit key_on;
		bit key_on_3s;
		bit key_in;
		bit key_3s_in;
		uint KeyChat;
		uint key_num;
		uint KeyChkbuf;
		uint KeyInbuf;
		uint KeyFIFO;
		bit Fkeyin;
		bit ffp13;
		bit ffp14;
		bit timer_on;
		bit key_0s_in;
		uint seconds;
		bit un_display;
		uint time_to;

		bit key_add;
		bit key_dec;

		bit sys_on;
		bit quiet;
		uint sw;
		uint mode;
		bit ion;
		uint speed = 12;
		bit timer_keyin;

void key(void)
{
	uint temp;
	if(f_10ms)
	{
		f_10ms = 0;
		temp = P2 & 0xb4;
		if(temp != 0xb4)
		{
			switch(temp)
			{
				case 0xb0 : key_num = 2; break;
				case 0xa4 : key_num = 4; break;
				case 0x94 : key_num = 5; break;
				case 0x34 : key_num = 7; break;
				default : 	key_num = 0; break;
			}
		}
		else
		{
			key_num = 0;
		}
		if(KeyChkbuf != key_num)
		{	
//////////////////////////////////////////////////////////////
			if(key_num == 0)
			{
				Fkeyin = 0;
				if(KeyChkbuf == 7 && !key_0s_in)
				{
					if(!key_3s_in && (seconds > 0 || KeyChat >= 6))
					{
						key_on = 1;				/* key ok */
						KeyFIFO = KeyChkbuf; 
					}
					else if(key_3s_in)
					key_3s_in = 0;
				}
				else if(key_0s_in && KeyChkbuf == 5)
				{
					key_0s_in = 0;
				}
			}
			else
			{
				Fkeyin = 1;
				KeyChat = 0;
				seconds = 0;
			}
			KeyChkbuf = key_num;
		}
		if(Fkeyin)							 
		{
			if(KeyChat == 5)
			{
				if(KeyChkbuf != 7)
				{
					Fkeyin = 0;
					key_on = 1;				/* key ok */
					KeyFIFO = KeyChkbuf; 
				}
				else if(timer_on && KeyChkbuf == 5)
				{
					key_0s_in = 1;
					Fkeyin = 0;
					key_on = 1;				/* key ok */
					KeyFIFO = KeyChkbuf; 
				}
			}
			else if(KeyChat == 100)
			{
				seconds ++;
				if(seconds == 3)
				{
					key_3s_in = 1;
					seconds = 0;
					Fkeyin = 0;
					key_on_3s = 1;				/* key ok */
					KeyFIFO = KeyChkbuf; 
				}
				else
				KeyChat = 0;
			}
			KeyChat++;
		}
	}
	if(F_125us)
	{
		F_125us = 0;
		if(ffp13 != FP13)
		{
			ffp13 = FP13;
			if(ffp13 == ffp14)		// 顺时针ok
			{
				key_add = 1;
			}
		}
		if(ffp14 != FP14)
		{
			ffp14 = FP14;
			if(ffp13 == ffp14)		// 逆时针ok
			{
				key_dec = 1;
			}
		}
	}
///////////////////////////////////////////////////////////////////////////
	if(key_on || key_on_3s)	// led数据准备 led_data_ok = 1; led_data[4]
	{
		if(un_display)
		{
			un_display = 0;
		}
		else
		switch(KeyFIFO)
		{
			case 7 : 		// on/off
			{
				if(key_on)
				{
					if(sys_on)
					{
						sys_on = 0;
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
						sys_on = 1;
						num_10ms = 0;
						num_1s = 0;
						f_display = 1;
						led_data[0] = LED_CODE[speed%10];
						led_data[1] = LED_CODE[speed/10];
						if(!timer_on)
						{
							if(sw)		led_data[2] |= 0x08;
							else		led_data[2] &= 0xf7;
							led_data[2] &= 0xcf;
							led_data[3] &= 0xdf;
							if(mode == 1)
							{
								led_data[2] |= 0x10;
							}
							else if(mode == 3)
							{
								led_data[3] |= 0x20;
							}
							else if(mode == 2)
							{
								mode = 0;
							}
						} 
						buzzer_on = 0;
						buzzer1_on = 0;
						buzzer2_on = 1;
						BUZ_CNT = 0;
						buz_en = 0;
					}
					if(timer_on)
					{
						timer_on = 0;
						time_to = 0;
						led_data[3] &= 0xef;
					}
					led_data_ok = 1;
				}
				else if(key_on_3s)
				{
					un_display = 1;
					undis_ok = 0;

					buzzer1_on = 0;
					buzzer2_on = 0;
					buzzer_on = 1;
					BUZ_CNT = 0;
					buz_en = 0;
				}
				break;
			}
			case 5 : 		// MODE
			{
				if(sys_on || timer_on) 
				{
					mode ++;
					if(mode == 4)
					mode = 0;
					led_data[2] &= 0xcf;
					led_data[3] &= 0xdf;
					switch(mode)
					{
						case 0 : //普通风
						{
							break;
						}
						case 1 : //自然风
						{
							led_data[2] |= 0x10;
							break;
						}
						case 2 : //睡眠风
						{
							led_data[2] |= 0x20;
							break;
						}
						case 3 : //经济风
						{
							led_data[3] |= 0x20;
							break;
						}
						default : {}
					}
					led_data_ok = 1;
					buzzer1_on = 0;
					buzzer2_on = 0;
					buzzer_on = 1;
					BUZ_CNT = 0;
					buz_en = 0;
				}
				break;
			}
			case 4 : 		// sw
			{
				if(sys_on || timer_on)
				{
					sw = ~sw;
					if(sw)
					led_data[2] |= 0x08;
					else 
					led_data[2] &= 0xf7;
					led_data_ok = 1;

					buzzer1_on = 0;
					buzzer2_on = 0;
					buzzer_on = 1;
					BUZ_CNT = 0;
					buz_en = 0;
				}
				break;
			}
			case 2 : 		// TIMER
			{
				timer_keyin = 1;
				num_10ms = 0;
				num_1s = 0;
				f_display = 0;
				time_dsp();
				led_data_ok = 1;
				buzzer1_on = 0;
				buzzer2_on = 0;
				buzzer_on = 1;
				BUZ_CNT = 0;
				buz_en = 0;
				break;
			}
			default : break;
		}
		if(key_on)	key_on = 0;
		else		key_on_3s = 0;
	}
	else if(key_add)//////////////////////////////////////////////////////////////////////////////////
	{
		key_add = 0;
		if(!timer_keyin && (sys_on || timer_on))
		{
			speed ++;
			if(speed == 25)
			speed = 1;
			led_data[1] = LED_CODE[speed/10];
			led_data[0] = LED_CODE[speed%10];
		}
		else if(timer_keyin)
		{
			time_to ++;
			if(time_to == 19)
			{
				time_to = 0;
				timer_on = 0;
				led_data[3] &= 0xef;
			}
			else
			{
				timer_on = 1;
				led_data[3] |= 0x10;
				time_cnt1 = 0;
				time_cnt2 = 0;
				time_cnt3 = 0;
			}
			time_dsp();
		}
		led_data_ok = 1;
		buzzer1_on = 0;
		buzzer2_on = 0;
		buzzer_on = 1;
		BUZ_CNT = 0;
		buz_en = 0;
	}
	else if(key_dec)
	{
		key_dec = 0;
		if(!timer_keyin && (sys_on || timer_on))
		{
			if(speed > 1)	speed --;
			else 			speed = 24;
			led_data[1] = LED_CODE[speed/10];
			led_data[0] = LED_CODE[speed%10];
		}
		else if(timer_keyin)
		{
			if(time_to > 0)	time_to --;
			else 			time_to = 18;
			if(time_to == 0)
			{
				timer_on = 0;
				led_data[3] &= 0xef;
			}
			else
			{
				timer_on = 1;
				led_data[3] |= 0x10;
				time_cnt1 = 0;
				time_cnt2 = 0;
				time_cnt3 = 0;
			}
			time_dsp();
		}
		led_data_ok = 1;
		buzzer1_on = 0;
		buzzer2_on = 0;
		buzzer_on = 1;
		BUZ_CNT = 0;
		buz_en = 0;
	}
}