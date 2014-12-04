#include"user.h"

extern	bit 	f_10ms;
extern	uint 	code 	a_dsp;
extern	uchar 	counter;
extern 	bit		AUTO_ON;
		bit		lcd_en;
		bit		Fkeyin;
		bit		KEY_ON;
		bit		KEY_ON2;
		uchar	KeyChkbuf;
		uchar	KeyInbuf = 9;	
		uchar	KeyChat;
		uchar	KeyFIFO;  
		uchar	data_ctr[3];

void key(void)
{
	uchar 	temp;
	uchar 	num;
	if(f_10ms)
	{
		f_10ms = 0;
		KeyInbuf = 9;
		P1IO	=	0x0f;  
		for(num=5;num>0;num--) ;
		P1		=	0xf1;
		for(num=5;num>0;num--) ;
		temp	=	P1;
		temp	&=	0x70;
		if(temp != 0X70)
		{
			P1IO=	0xf0; 
			for(num=5;num>0;num--) ;
			if(temp == 0x60)
			{
				P1	=	0xef;
				for(num=5;num>0;num--) ;
				temp=	P1&0x0e;
				if(temp == 0X0c)
				KeyInbuf = 3;
				else if(temp == 0X0a)
				KeyInbuf = 6;
			}
			else if(temp == 0x50)
			{
				P1	=	0xdf;
				for(num=5;num>0;num--) ;
				temp=	P1&0x0e;
				if(temp == 0X0c)
				KeyInbuf = 2;
				else if(temp == 0X0a)
				KeyInbuf=5;
				else if(temp == 0X06)
				KeyInbuf=8;
			}
			else if(temp == 0x30)
			{
				P1	=	0xbf;
				for(num=5;num>0;num--) ;
				temp=	P1&0x0e;
				if(temp == 0X0c)
				KeyInbuf=1;
				else if(temp == 0X0a)
				KeyInbuf=4;
				else if(temp == 0X06)
				KeyInbuf=7;
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
				data_ctr[2] += 5;
				if(data_ctr[2] > 30 || data_ctr[2] < 15)
				data_ctr[2] = 15;
				break;
			}
			case 3 :			//语音开关
			{
				data_ctr[1] ^= 0x80;
				break;
			}
			case 4 :			//幅度+
			{
				if((data_ctr[1] & 0x0f) != 0x0f)
				data_ctr[1] += 1;
				break;
			}
			case 5 :			//幅度-
			{
				if((data_ctr[1] & 0x0f) != 0x00)
				data_ctr[1] -= 1;
				break;
			}
			case 6 :			/* 红外热灸 off L M H */
			{					
				if((data_ctr[1] & 0x30) == 0x30)
				data_ctr[1] &= 0xcf;
				else
				data_ctr[1] += 0x10;
				break;
			}
			case 7 :			//自动
			{
				data_ctr[0] ^= 0x08;
				break;
			}
			case 8 :			//手动
			{
				if(!AUTO_ON)
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