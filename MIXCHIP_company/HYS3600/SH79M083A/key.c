#include"user.h"

extern	bit 	f_10ms;
extern	uint 	code 	a_dsp;
extern 	bit		AUTO_ON;
extern	bit		SYS_ON;
extern	uchar	t_dsp;
		bit		lcd_en;
		bit		Fkeyin;
		bit		KEY_ON;
		bit		KEY_ON2;
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
		P1		&=	~0x03;
		P3		&=	~0x80;
		P3		|=	0x1c;
		for(num=5;num>0;num--) ;
		temp	=	P3&0x1c;
		if(temp != 0X1c)
		{
			switch(temp)
			{
				case 0x18 : key_num_1 = 1; break;
				case 0x14 : key_num_1 = 2; break;
				case 0x0c : key_num_1 = 3; break;
				default : key_num_1 = 0; break;
			}
			P1		|=	0x01;
			P3		|=	0x80;
			for(num=5;num>0;num--) ;
			temp	=	P3&0x1c;
			if(temp != 0x1c)
			{
				KeyInbuf = 0;
			}
			P1		|=	0x02;
			P1		&=	~0x01;
			for(num=5;num>0;num--) ;
			temp	=	P3&0x1c;
			if(temp != 0x1c)
			{
				KeyInbuf = 1;
			}
			P1		|=	0x01;
			P3		&=	~0x80;
			for(num=5;num>0;num--) ;
			temp	=	P3&0x1c;
			if(temp != 0x1c)
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
			KeyFIFO = KeyChkbuf; 
			KEY_ON=1;				/* key ok */
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
			default: {}
		}
	}
} 