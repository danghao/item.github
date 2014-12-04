#include "user.h"

		bit key_on;
		bit key_on_3s;
		bit key_in;
		bit key_3s_in;
		u8 KeyChat;
		u8 key_num;
		u8 KeyChkbuf;
		u8 KeyInbuf;
		u8 KeyFIFO;
		bit Fkeyin;
		bit key_0s_in;
		u8 seconds;
		bit timer_on;
		bit un_display;
		u8 time_to;
		bit sys_on;
		bit sw;
		u8 mode;
		bit ion;
		bit SIL;
		bit HUM;
		bit dis_ok;
		u8 speed = 1;
		bool timer_keyin;

		bit notest;
		u8 testmode_slp;
		u8 testmode_timer;


void key(void)
{
	u8 temp;
	if(f_10ms)
	{
		f_10ms = 0;
		temp = P2 & 0x1f;
		switch(temp)
		{
			case 0x0f : key_num = 1; break;
			case 0x17 : key_num = 2; break;
			case 0x1b : key_num = 3; break;
			case 0x1d : key_num = 4; break;
			case 0x1e : key_num = 5; break;
			default : 	key_num = 0; break;
		}
		if(key_num == 0)
		{
			temp = P1 & 0xe0;
			switch(temp)
			{
				case 0x60 : key_num = 6; break;
				case 0xa0 : key_num = 7; break;
				case 0xc0 : key_num = 8; break;
				default : 	break;
			}
		}
		if(KeyChkbuf != key_num)
		{	
			if(key_num == 0)
			{
				Fkeyin = 0;
				if(KeyChkbuf == 1)
				{
					if(key_3s_in)
					{
						key_3s_in = 0;
					}
					else if(dis_ok)
					{
						dis_ok = 0;
					}
					else if(!key_3s_in && (KeyChat >= 5 || seconds > 0))
					{
						key_on = 1;	
						KeyFIFO = KeyChkbuf; 
					}
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
				if(un_display)
				{
					un_display = 0;
					led_data_ok = 1;
					dis_ok = 1;
					Fkeyin = 0;
				}
				else if(KeyChkbuf != 1)
				{
					Fkeyin = 0;
					key_on = 1;	
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
					key_on_3s = 1;
					KeyFIFO = KeyChkbuf; 
				}
				else 
				KeyChat = 0;
			}
			KeyChat++;
		}
	}
///////////////////////////////////////////////////////////////////////////
	if(key_on||key_on_3s)		// led数据准备 led_data_ok = 1; led_data[4]
	{
		switch(KeyFIFO)
		{
			case 1 : 		// on/off
			{
				if(key_on)
				{
					sys_on = ~sys_on;
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

						if(!notest)
						{
							notest = 1;
							testmode_slp = 20;
							testmode_timer = 60;
						}
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
					if(timer_on)
					{
						timer_on = 0;
						time_to = 0;
						led_data[2] &= 0xfc;
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
			case 2 : 		// SILENT
			{
				if(sys_on || timer_on)
				{
					SIL = ~SIL;
					if(SIL)
					{
						speed = 0;
						led_data[2] |= 0x04;
						if(speed == 5)
						{
							led_data[2] &= 0xEF;
						}
					}
					else
					{
						speed = 1;
						led_data[2] &= 0xeb;
					}
					time_speed_dsp(1);
					led_data_ok = 1;
					buzzer1_on = 0;
					buzzer2_on = 0;
					buzzer_on = 1;
					BUZ_CNT = 0;
					buz_en = 0;
				}
				break;
			}
			case 3 : 		// MODE
			{
				if(sys_on || timer_on) 
				{
					mode ++;
					if(mode == 3)
					mode = 0;

					led_data[2] &= 0xf7;
					led_data[3] &= 0xe7;
					if(mode == 1)
					led_data[3] |= 0x10;
					else if(mode == 2)
					led_data[3] |= 0x08;
					else if(mode == 0)
					led_data[2] |= 0x08;

					led_data_ok = 1;
					buzzer1_on = 0;
					buzzer2_on = 0;
					buzzer_on = 1;
					BUZ_CNT = 0;
					buz_en = 0;
				}
				break;
			}
			case 4 : 		// SPEED
			{
				if(sys_on || timer_on)
				{
					speed ++;
					if(speed == 6)
					{
						speed = 1;
					}
					if(speed == 5)		led_data[2] |= 0x10;
					else				led_data[2] &= 0xef;
					if(SIL)
					{
						SIL = 0;
						led_data[2] &= 0xfb;
					}
					time_speed_dsp(1);
					led_data_ok = 1;
					buzzer1_on = 0;
					buzzer2_on = 0;
					buzzer_on = 1;
					BUZ_CNT = 0;
					buz_en = 0;
				}
				break;
			}
			case 5 : 		// TIMER
			{
				time_to ++;
				if(time_to == 19)
				{
					time_to = 0;
					timer_on = 0;
					led_data[2] &= 0xfc;
				}
				else
				{
					timer_on = 1;
					if(sys_on)
					led_data[2] |= 0x02;
					else
					{
						led_data[2] |= 0x01;
						if(time_to == 1)
						{
							led_data[2] &= 0xeb;
							if(SIL)	
							{
								speed = 0;
								led_data[2] |= 0x04;	
							}
							else if(speed == 5)
							led_data[2] |= 0x10;

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
					}
				}
				time_speed_dsp(0);
				led_data_ok = 1;
				time_cnt1 = 0;
				time_cnt2 = 0;
				time_cnt3 = 0;
				num_10ms = 0;
				num_1s = 0;
				buzzer1_on = 0;
				buzzer2_on = 0;
				buzzer_on = 1;
				BUZ_CNT = 0;
				buz_en = 0;
				break;
			}
			case 6 : 		// sw
			{
				if(sys_on || timer_on)
				{
					sw = ~sw;
					if(sw)	led_data[3] |= 0x01;
					else 	led_data[3] &= 0xfe;

					led_data_ok = 1;
					buzzer1_on = 0;
					buzzer2_on = 0;
					buzzer_on = 1;
					BUZ_CNT = 0;
					buz_en = 0;
				}
				break;
			}
			case 7 : 		// ION
			{
				if(sys_on || timer_on)
				{
					ion = ~ion;
					if(ion)		led_data[3] |= 0x04;
					else 		led_data[3] &= 0xfb;
					led_data_ok = 1;
					buzzer1_on = 0;
					buzzer2_on = 0;
					buzzer_on = 1;
					BUZ_CNT = 0;
					buz_en = 0;
				}
				break;
			}
			case 8 : 		// HUM
			{
				if(sys_on || timer_on)
				{
					HUM = ~HUM;
					if(HUM)	led_data[2] |= 0x20;
					else 	led_data[2] &= 0xdf;
					led_data_ok = 1;
					buzzer1_on = 0;
					buzzer2_on = 0;
					buzzer_on = 1;
					BUZ_CNT = 0;
					buz_en = 0;
				}
				break;
			}
			default : break;
		}
		if(key_on)	key_on = 0;
		else		key_on_3s = 0;
	}
}