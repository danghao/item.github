#include	"key.h"

//*************************************************************
//! \brief       key函数
//! \Call        10ms
//*************************************************************

bit key_on;
bit key_on_3s;
bit Fkeyin;
bit key_0s_in;
bit key_3s_in;
u8 	key_ns;
u8  KeyChat;
u8  key_num;
u8 	Keybuf;
u8 	KeyFIFO;

void Key(void)
{
	u8 temp = ((P5 & 0x0e)<<4)|(P0 & 0x05);
	if(temp != 0xff)
	{
		switch(temp)
		{
			case 0xfe : key_num = 1; break;	// onf
			case 0xfd : key_num = 2; break;	// mode
			case 0xfb : key_num = 3; break;	// speed
			case 0xf7 : key_num = 4; break;	// timer
			case 0xef : key_num = 5; break;	// sw
			case 0xdf : key_num = 6; break;	// ion
			case 0xbf : key_num = 7; break;	// hum
			case 0x7f : key_num = 8; break;	// sil
			default : key_num = 0;
		}
	}
	else
	{
		key_num = 0;
	}
	if(Keybuf != key_num)
	{	
		if(key_num == 0)
		{
			Fkeyin = 0;
			if(key_3s_in)
			{
				key_3s_in = 0;
			}
			else
			{
				if(key_ns > 0 || KeyChat >= 6)
				key_on = 1;	
				KeyFIFO = Keybuf; 
			}
		}
		else
		{
			Fkeyin = 1;
			KeyChat = 0;
			key_ns = 0;
		}
		Keybuf = key_num;
	}
	if(Fkeyin)							 
	{
		KeyChat++;
		if(KeyChat == 5)
		{
			if(Keybuf != 1)	// 排除需要判定3s的按键
			{
				Fkeyin = 0;
				key_on = 1;			// key ok
				KeyFIFO = Keybuf; 
			}
		}
		else if(KeyChat == 100)
		{
			key_ns ++;
			if(key_ns == 3)
			{
				Fkeyin = 0;
				key_3s_in = 1;
				key_on_3s = 1;		// key3s ok
				KeyFIFO = Keybuf; 
			}
			else
			{
				KeyChat = 0;
			}
		}
	}
	if(key_on)
	{
		key_on = 0;
		switch(KeyFIFO)
		{
			case 1 :	// ******************************** onf
			{
				break;
			}
			case 2 :	// ******************************** mode
			{
				break;
			}
			case 3 :	// ******************************** speed
			{
				break;
			}
			case 4 :	// ******************************** timer
			{
				break;
			}
			case 5 :	// ******************************** sw
			{
				break;
			}
			case 6 :	// ******************************** ion
			{
				break;
			}
			case 7 :	// ******************************** hum
			{
				break;
			}
			case 8 :	// ******************************** sil
			{
				break;
			}
			default : {}
		}
	}
	else if(key_on_3s)
	{
		key_on_3s = 0;
		switch(KeyFIFO)
		{
			case 1 :	// ******************************** onf
			{
				break;
			}
			case 2 :	// ******************************** mode
			{
				break;
			}
			case 3 :	// ******************************** speed
			{
				break;
			}
			case 4 :	// ******************************** timer
			{
				break;
			}
			case 5 :	// ******************************** sw
			{
				break;
			}
			case 6 :	// ******************************** ion
			{
				break;
			}
			case 7 :	// ******************************** hum
			{
				break;
			}
			case 8 :	// ******************************** sil
			{
				break;
			}
			default : {}
		}
	}
}
