#include "key.h"

	bit f_10ms;

	bit key_on;
	bit key_on_3s;
	bit key_in;
	u8 KeyChat;
	u8 key_num;
	u8 KeyChkbuf;
	u8 KeyInbuf;
	u8 KeyFIFO;
	bit Fkeyin;
	u8 seconds;
	bit quiet;
	bit sw;
	u8 mode = 4;		// 上电初始 普通模式
	u8 speed = 7+1;		// 上电初始 7档运行3s
	bit ion;
	bit sys_on;
	u8 time_to;
	bit	delay_15s_in;
	bit key_3s_in;
	bit key_0s_in;

void key(void)
{
	u8 	temp;
	u8 	temp2;
	if(f_10ms)
	{
		f_10ms = 0;
		LED_10 = 0;
		LED_11 = 0;
		LED_5 = 0;
		P4M &= 0xE7;
		P0M &= 0x91;
		for(temp2=0;temp2<5;temp2++) ;
		temp = P0 & 0x6e;
		temp2 = P4M & 0x18;
		P4M |= 0x18;
		P0M |= 0x67;
		if(temp != 0x6e)
		{
			switch(temp)
			{
				case (0x6c) : key_num = 7; break;
				case (0x6a) : key_num = 6; break;
				case (0x66) : key_num = 5; break;
				case (0x4e) : key_num = 4; break;
				case (0x2e) : key_num = 3; break;
				default : 	key_num = 0XFF; break;
			}
		}
		else if(temp2 != 0x18)
		{
			if(temp2 == 0x10)
			{
				key_num = 2;
			}
			else if(temp2 == 0x08)
			{
				key_num = 1;
			}
			else
			{
				key_num = 0XFF;
			}
		}
		else
		{
			key_num = 0;
		}
		if(KeyChkbuf != key_num)
		{	
			if(key_num == 0)
			{
				Fkeyin = 0;
				if(KeyChkbuf == 4 || (KeyChkbuf == 5 && !key_0s_in))
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
				if(KeyChkbuf != 4 && KeyChkbuf != 5)
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
///////////////////////////////////////////////////////////////////////////
	if(key_on || key_on_3s)
	{
		if(sys_on && (mode == 2))
		{
			delay_15s_in = 0;
			t_cnt1 = 0;
			t_cnt2 = 0;
		}
		if(un_display)
		{
			un_display = 0;
		}
		else
		switch(KeyFIFO)
		{
			case 1 : 	// SPD
			{
				if(sys_on || timer_on)
				{
					speed ++;
					if(speed >8)
					speed = 2;
					if(quiet)
					{
						quiet = 0;
						led_buf[1] &= 0xef;
					}
					if(mode != 3)
					led_buf[2] = LED_CODE[speed-1];

					buzzer1_on = 0;
					buzzer2_on = 0;
					buzzer0_on = 1;
					buz_cnt = 0;
					BUZ_EN = 0;
				}
				break;
			}
			case 2 :	// QUITE
			{
				if((sys_on || timer_on))
				{
					if(!quiet)
					{
						quiet = 1;
						speed = 2;
						led_buf[1] |= 0x10;
						if(mode != 3)
						led_buf[2] = LED_CODE[10];

						buzzer1_on = 0;
						buzzer2_on = 0;
						buzzer0_on = 1;
						buz_cnt = 0;
						BUZ_EN = 0;
					}
					else
					{
						quiet = 0;
						speed = 2;
						led_buf[1] &= 0xef;
						if(mode != 3)
						led_buf[2] = LED_CODE[1];

						buzzer1_on = 0;
						buzzer2_on = 0;
						buzzer0_on = 1;
						buz_cnt = 0;
						BUZ_EN = 0;
					}
				}
				break;
			}
			case 3 :	// SW
			{
				if(sys_on || timer_on)
				{
					sw = ~sw;
					if(sw)
					{
						led_buf[0] |= 0x01;
					}
					else 
					{
						led_buf[0] &= 0xfe;
					}

					buzzer1_on = 0;
					buzzer2_on = 0;
					buzzer0_on = 1;
					buz_cnt = 0;
					BUZ_EN = 0;
				}
				break;
			}
			case 4 :	// TIMER
			{
				if(key_on)
				{
					if(!timer_on)
					timer_on = 1;
					time_to++;
					if(time_to == 16)
					time_to = 0;
					t_cnt1 = 0;
					t_cnt1 = 0;
				}
				else if(key_on_3s)
				{
					if(!timer_on)
					timer_on = 1;
					time_to = 1;
				}
				led_buf[0] &= 0x1e;
				led_buf[0] |= time_to << 1;
				
				buzzer1_on = 0;
				buzzer2_on = 0;
				buzzer0_on = 1;
				buz_cnt = 0;
				BUZ_EN = 0;
				break;
			}
			case 5 :	// ON/OFF
			{
				if(key_on)
				{
					timer_on = 0;
					time_to = 0;
					if(sys_on)
					{
						sys_on = 0;
						led_buf[0] = 0;					
						led_buf[1] = 0;					
						led_buf[2] = 0;	
						
						sys_3s_ok = 0;				
						num2_1s = 0;

						buzzer0_on = 0;
						buzzer2_on = 0;
						buzzer1_on = 1;
						buz_cnt = 0;
						BUZ_EN = 0;
					}
					else
					{
						sys_on = 1;
						led_buf[0] &= 0xe1;	
						led_buf[2] = LED_CODE[7];

							led_buf[1] &= 0xf1;
							switch(mode)
							{
								case 1 :	led_buf[1] |= 0x01;	break;
								case 2 :	mode = 4;	break;
								case 3 :	led_buf[1] |= 0x04;	break;
								default : {}
							}

							if(quiet)	led_buf[1] |= 0x10;
							else		led_buf[1] &= 0xef;

							if(sw)		led_buf[0] |= 0x01;
							else		led_buf[0] &= 0xfe;

							if(ion)		led_buf[1] |= 0x08;
							else		led_buf[1] &= 0xf7;

						buzzer0_on = 0;
						buzzer1_on = 0;
						buzzer2_on = 1;
						buz_cnt = 0;
						BUZ_EN = 0;
					}				
				}
				else if(key_on_3s)
				{
					un_display = 1;

					buzzer1_on = 0;
					buzzer2_on = 0;
					buzzer0_on = 1;
					buz_cnt = 0;
					BUZ_EN = 0;
				}
				break;
			}
			case 6 :	// MODE
			{
				if(sys_on || timer_on)
				{
					mode++;
					if(mode>4)
					{
						mode = 1;
					}
					led_buf[1] &= 0xf1;
					switch(mode)
					{
						case 1 :	// 自然风
						{
							led_buf[1] |= 0x01;
							break;
						}
						case 2 :	// 睡眠风
						{
							led_buf[1] |= 0x02;
							break;
						}
						case 3 :	// 冷房风
						{
							led_buf[1] |= 0x04;
							led_buf[2] = LED_CODE[11]; // A 
							break;
						}
						case 4 :	// 标准风
						{
							if(quiet)
							led_buf[2] = LED_CODE[10];
							else
							led_buf[2] = LED_CODE[speed - 1];
							break;
						}
						default : { }
					}

					buzzer1_on = 0;
					buzzer2_on = 0;
					buzzer0_on = 1;
					buz_cnt = 0;
					BUZ_EN = 0;
				}
				break;
			}
			case 7 :	// ION
			{
				if(sys_on || timer_on)
				{
					ion = ~ion;
					if(ion)
					{
						led_buf[1] |= 0x08;
					}
					else
					{
						led_buf[1] &= 0xf7;
					}

					buzzer1_on = 0;
					buzzer2_on = 0;
					buzzer0_on = 1;
					buz_cnt = 0;
					BUZ_EN = 0;
				}
				break;
			}
			default : {}
		}
		key_on = 0;
		key_on_3s = 0;
	}
}