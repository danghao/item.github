#include"user.h"

extern	uchar 	f_10ms;
extern	uchar 	a_dsp;
extern 	uchar		AUTO_ON;
extern	uchar		SYS_ON;
extern	uchar		t_dsp;
		uchar		lcd_en;
		uchar		Fkeyin;
		uchar		KEY_ON;
		uchar		KEY_ON2;
		uchar	KeyChkbuf;
		uchar	KeyInbuf = 9;	
		uchar	KeyChat;
		uchar	KeyFIFO;  
		uchar	data_ctr[3];
		uchar	key_num_1;

void key(void)
{
	uchar 	temp;
	uchar 	num;
	if(f_10ms)
	{
		f_10ms = 0;
		KeyInbuf = 9;
		PB_ODR &= ~0x30;
		PC_ODR &= ~0x08;
		for(num=5;num>0;num--) ;
		temp	=	PC_IDR & 0x70;
		if(temp != 0x70)
		{
			switch(temp)
			{
				case 0x30 : key_num_1 = 1; break;
				case 0x50 : key_num_1 = 2; break;
				case 0x60 : key_num_1 = 3; break;
				default : key_num_1 = 0; break;
			}
			PB_ODR |= 0x10;
			PC_ODR |= 0x08;
			for(num=5;num>0;num--) ;
			temp	=	PC_IDR & 0x70;
			if(temp != 0x70)
			{
				KeyInbuf = 0;
			}
			PB_ODR &= ~0x10;
			PB_ODR |= 0x20;
			for(num=5;num>0;num--) ;
			temp	=	PC_IDR & 0x70;
			if(temp != 0x70)
			{
				KeyInbuf = 1;
			}
			PB_ODR |= 0x10;
			PC_ODR &= ~0x08;
			for(num=5;num>0;num--) ;
			temp	=	PC_IDR & 0x70;
			if(temp != 0x70)
			{
				KeyInbuf = 2;
			}
			if(KeyInbuf != 9 && key_num_1 != 0)
			{
				KeyInbuf = KeyInbuf * 3 + key_num_1;
			}
			else
			{
				KeyInbuf = 9;
			}
		}
		if(KeyInbuf != KeyChkbuf)
		{	
			Fkeyin = 1;
			KeyChkbuf = KeyInbuf;
			KeyChat = 5;
		}
		if(Fkeyin && (KeyChat==0))							 
		{
			Fkeyin = 0;
			if(KeyChkbuf != 9)
			{
				KeyFIFO = KeyChkbuf; 
				KEY_ON=1;				/* key ok */
			}
		}
		if(Fkeyin && (KeyChat>0))
		{
			KeyChat--;
		}
	}
	if(KEY_ON)			/* 发送一帧数据前 tx_en = 1;   rTx_Ptr = 0;   xTx_Buffer[5]; */
	{
		KEY_ON = 0;
		KEY_ON2 = 1;
		switch(KeyFIFO)
		{
			case 1 :			// 开关
			{
				LED_ON;
				data_ctr[0] ^= 0x80;
				break;
			}
			case 2 :			//定时
			{
				if(SYS_ON)
				{
					data_ctr[2] += 5;
					if(data_ctr[2] > 30 || data_ctr[2] < 15)
					data_ctr[2] = 15;
				}
				break;
			}
			case 3 :			//语音开关
			{
					LED_OFF;
				if(SYS_ON)
				{
					data_ctr[1] ^= 0x80;
				}
				break;
			}
			case 4 :			//幅度+
			{
				if(SYS_ON && t_dsp != 0)
				{
					if((data_ctr[1] & 0x0f) != 0x0f)
					data_ctr[1] += 1;
				}
				break;
			}
			case 5 :			//幅度-
			{
				if(SYS_ON && t_dsp != 0)
				{
					if((data_ctr[1] & 0x0f) != 0x00)
					data_ctr[1] -= 1;
				}
				break;
			}
			case 6 :			/* 红外热灸 off L M H */
			{					
				if(SYS_ON && t_dsp != 0)
				{
					if((data_ctr[1] & 0x30) == 0x30)
					data_ctr[1] &= 0xcf;
					else
					data_ctr[1] += 0x10;
				}
				break;
			}
			case 7 :			//自动
			{
				if(SYS_ON && t_dsp != 0)
				{
					data_ctr[0] ^= 0x08;
				}
				break;
			}
			case 8 :			//手动
			{
				if(SYS_ON && t_dsp != 0 && !AUTO_ON)
				{
					if((data_ctr[0] & 0x07) == 0x06)
					{
						data_ctr[0] &= 0xf8;
						data_ctr[0] |= 0x01;
					}
					else
					{
						data_ctr[0] += 1;
					}
				}
				break;
			}
			default : {}
		}
	}
} 