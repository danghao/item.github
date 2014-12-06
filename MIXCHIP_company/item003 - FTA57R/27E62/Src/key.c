#include	"key.h"

	bit      key_on;
	bit   key_on_3s;

	bit      Fkeyin;
	bit   key_0s_in;
	bit   key_3s_in;
	u8 		seconds;
	u8      KeyChat;
	u8      key_num;
	u8 	  KeyChkbuf;
	u8 	    KeyFIFO;


	bit 	 sys_on;
	bit 	  sw_on;
	u8 		time_to;		// 定时时间
	u8 	   mode = 1;		// 上电初始 普通模式 
	u8 	  speed = 2;		// 上电初始 中档运行 3s

	bit	 un_display;
	bit	   timer_on;

//***************************************************************************
//! \brief       函数 读取键值
//! \param       无
//! \return      无
//***************************************************************************
void Key_Read(void)
{
	u8 	temp;
	u8 	temp2;
	if(f_10ms)
	{
		f_10ms = 0;
		P5M &= 0xf1;
		P0M &= 0xfa;
		for(temp=0;temp<5;temp++) ;
		temp = P0 & 0x05;
		temp2 = P5 & 0x0e;
		P5M |= 0x0e;
		P0M |= 0x05;
		if(temp != 0x05)
		{
			if(temp == 0x04)
			{
				key_num = 1;
			}
			else if(temp == 0x01)
			{
				key_num = 2;
			}
			else
			{
				key_num = 0;
			}
		}
		else if(temp2 != 0x0e)
		{
			if(temp2 == 0x06)
			{
				key_num = 3;
			}
			else if(temp2 == 0x0a)
			{
				key_num = 4;
			}
			else if(temp2 == 0x0c)
			{
				key_num = 5;
			}
			else
			{
				key_num = 0;
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
				if(key_0s_in)
				{
					key_0s_in = 0;
					if(!key_3s_in)
					{
						if(seconds > 0 || KeyChat >= 6)
						key_on = 1;				/* key ok */
						KeyFIFO = KeyChkbuf; 
					}
					else
					{
						key_3s_in = 0;
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
					undis_in = 0;
					Fkeyin = 0;
				}
				else
				{
					if(KeyChkbuf != 1)
					{
						Fkeyin = 0;
						key_on = 1;				/* key ok */
						KeyFIFO = KeyChkbuf; 
					}
					else
					{
						key_0s_in = 1;
					}
				}
			}
			else if(KeyChat == 103)
			{
				seconds ++;
				if(seconds == 3)
				{
					key_3s_in = 1;
					Fkeyin = 0;
					un_display = 1;
					// buzzer_on
				}
				else
				KeyChat = 5;
			}
			KeyChat++;
		}
	}
}

//***************************************************************************
//! \brief       函数 按键功能处理
//! \param       无
//! \return      无
//***************************************************************************
void Key_Process(void)
{
	if(key_on)
	{
		key_on = 0;
		switch(KeyFIFO)
		{
	//led_buf[0]  [8H 4H 2H 1H] [-- H    M   L  ]
	//led_buf[1]  [-- -- -- --] [SW WIFI SLP RHY]
			case 1 :	// ON/OFF
			{
				sys_on = ~sys_on;
				if(sys_on)	// 开机
				{
					
				}
				else		// 关机
				{
					
				}
				break;
			}
			case 2 :	// SW
			{
				if(sys_on || timer_on)
				{
					sw_on = ~sw_on;
				}
				break;
			}
			case 3 :	// MODE
			{
				if(sys_on || timer_on)
				{
					mode++;
				}
				break;
			}
			case 4 :	// TIMER
			{
				break;
			}
			case 5 : 	// SPD
			{
				if(sys_on || timer_on)
				{
				}
				break;
			}
			default : {}
		}
	}
}