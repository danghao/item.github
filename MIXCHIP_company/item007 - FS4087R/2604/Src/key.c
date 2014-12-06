#include "user.h"

		bit f_10ms;
		bit key_on;
		bit key_on_3s;
		bit key_in;
		uint KeyChat;
		uint key_num;
		uint KeyChkbuf;
		uint KeyInbuf;
		uint KeyFIFO;
		bit Fkeyin;
		uint seconds;
		bit quiet;
		uint sw;
		uint mode;
		bit ion;
		bit sys_on;
		uint buz_cnt;
		uint time_to;
		uint speed;
		bit SLP;
		bit	delay_15s_in;
		bit key_3s_in;
		bit key_0s_in;
void key(void)
{
	uchar 	temp;
	uchar 	num;
	if(f_10ms)
	{
		f_10ms = 0;
		FP17 = 0;
		FP16 = 0;
		FP20 = 0;
		P2M = 0x01;
		for(num=0;num<5;num++) ;
		temp = P2&0xfe;
		P2M = 0xff;
		if(temp != 0xfe)
		{
			switch(temp)
			{
				case (0xfc) : key_num = 1; break;
				case (0xfa) : key_num = 2; break;
				case (0xf6) : key_num = 3; break;
				case (0xee) : key_num = 4; break;
				case (0xde) : key_num = 5; break;
				case (0xbe) : key_num = 6; break;
				case (0x7e) : key_num = 7; break;
				default : 	key_num = 0; break;
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
		if(sys_on && SLP)
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
/////////////////////////////////////////////////////
						send_data_buf = 0x55;
						send_data[1] = 0x55;
						send_data[2] = 0x55;
						send_data[3] = 0x55;
						send_data[4] = 0x55;
						send_data[5] = 0x55;
						send_data[6] = 0x55;
						chksum_send = 0x55;
						data_ptr = 0;
						In_send = 1;
/////////////////////////////////////////////////////
				if(sys_on || timer_on)
				{
					speed ++;
					if(speed >8)
					speed = 2;
					if(quiet)
					{
						quiet = 0;
						led_buf[1] &= 0xf7;
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
/////////////////////////////////////////////////////
						send_data_buf = 0xaa;
						send_data[1] = 0xaa;
						send_data[2] = 0xaa;
						send_data[3] = 0xaa;
						send_data[4] = 0xaa;
						send_data[5] = 0xaa;
						send_data[6] = 0xaa;
						chksum_send = 0xaa;
						data_ptr = 0;
						In_send = 1;
/////////////////////////////////////////////////////
				if((sys_on || timer_on))
				{
					if(!quiet)
					{
						quiet = 1;
						speed = 2;
						led_buf[1] |= 0x08;
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
						led_buf[1] &= 0xf7;
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
					sw ++;
					if(sw > 3)
					{
						sw = 0;
					}
					else 
					{
					}
					switch(sw)
					{
						case 0 : 
						{
							led_buf[0] &= 0xf7;
							break; 
						}
						case 1 : // 水平摆
						{
							led_buf[0] |= 0x08;
							break; 
						}
						case 2 : // 垂直摆
						{
							led_buf[0] |= 0x08;
							break; 
						}
						case 3 : // 水平+垂直摆
						{
							led_buf[0] |= 0x08;
							break; 
						}
						default : {}
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
				led_buf[0] &= 0x0f;
				led_buf[0] |= time_to << 4;
				
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
					
						buzzer0_on = 0;
						buzzer2_on = 0;
						buzzer1_on = 1;
						buz_cnt = 0;
						BUZ_EN = 0;
					}
					else
					{
						sys_on = 1;
						led_buf[0] &= 0x0f;	
						led_buf[2] = LED_CODE[7];
							if(quiet)
							{
								led_buf[1] |= 0x08;
							}
							else
							{
								led_buf[1] &= 0xf7;
							}
							switch(sw)
							{
								case 0 : led_buf[0] &= 0xf7; break; 
								case 1 :
								case 2 :
								case 3 : led_buf[0] |= 0x08; break; 
								default : {}
							}
							led_buf[1] &= 0x1f;
							switch(mode)
							{
								case 1 :	led_buf[1] |= 0x80;	break;
								case 2 :	mode = 4;	break;
								case 3 :	led_buf[1] |= 0x20;	break;
								default : {}
							}
							if(ion)		led_buf[1] |= 0x10;
							else		led_buf[1] &= 0xef;
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
					led_buf[1] &= 0x1f;
					switch(mode)
					{
						case 1 :	// 自然风
						{
							SLP = 0;
							led_buf[1] |= 0x80;
							break;
						}
						case 2 :	// 睡眠风
						{
							SLP = 1;
							led_buf[1] |= 0x40;
							break;
						}
						case 3 :	// 冷房风
						{
							SLP = 0;
							led_buf[1] |= 0x20;
							led_buf[2] = LED_CODE[11]; // A 
							break;
						}
						case 4 :	// 标准风
						{
							SLP = 0;
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
						led_buf[1] |= 0x10;
					}
					else
					{
						led_buf[1] &= 0xef;
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
///////////////////////////////// function //////////////////////////////////
	if(sys_on)
	{
		
		//
	}
}