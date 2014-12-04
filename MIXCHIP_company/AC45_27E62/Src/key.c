#include	"user.h"

extern bit f_4ms;
extern bit BUZZER1_ON;
extern bit DSP_OFF;
extern bit LOCK_T;
extern bit LOCK_LED;
extern bit LOCK_ON;
extern bit RST_T;
extern bit RST_LED;
extern bit RST_ON;
extern bit SYS_ON;
uint 	key_buf;
uint	KeyChkbuf;
uint	KeyChat;
uint	KeyChat2;
uint	KeyFIFO;
bit		Fkeyin;
bit		KEY_ON;
bit		KEY_ON_3s;
bit		KEY_ON_5s;
bit     xiping;
bit     xiping2;
bit     xiping3;
void	key		(void)
{
	uint temp1,temp2;
	if(f_4ms)
	{
		f_4ms = 0;
		FP43 = 1;
		FP05 = 1;
		FP06 = 1;
		P0M  &=	0xe2;
		P5M  &=	0xf7;
		for(temp1=0;temp1<20;temp1++);
		temp1 = P0 & 0x1d;
		temp2 = P5 & 0x08;
		if(temp1 != 0x1d)
		{
			switch(temp1)
			{
				case 0x0d 	: key_buf=1; break;
				case 0x15 	: key_buf=2; break;
				case 0x19 	: key_buf=3; break;
				case 0x1C 	: key_buf=4; break;
				case 0x09 	: key_buf=6; break;
				default		: {}
			}
			if(temp2 != 0x08)
			key_buf = 7;
		}
		else if(temp2 != 0x08)
		key_buf = 5;
		else 
		key_buf = 0;

		if(KeyChkbuf != key_buf)
		{	
			if(key_buf == 0)
			{
				Fkeyin = 0;
				xiping2 = 0;
				LOCK_T = 0;
				LOCK_LED = LOCK_ON;
				RST_T = 0;
				RST_LED = RST_ON;
				if(xiping)
				{
					xiping = 0;
					if( KeyChkbuf == 5 && KeyChat2 < 150 && KeyChat2 > 2 )
					KEY_ON = 1;
					KeyFIFO = 5;
				}
			}
			else
			{
				Fkeyin = 1;
				xiping3 = 0;
				KeyChat = 0;
				KeyChat2 = 0;
			}
			KeyChkbuf = key_buf;
		}
		if(Fkeyin && !xiping3)
		{
			KeyChat++;		
			if(KeyChat >= 5) 
			{
				KeyChat = 0;
				KeyChat2 ++;
				if((KeyChat2 == 4) && Fkeyin)				 
				{
					KeyFIFO = KeyChkbuf;
					KEY_ON=1;
					if(DSP_OFF && KeyFIFO!=0)
					{
						DSP_OFF	=	0;
						KEY_ON = 0;
						BUZZER1_ON = 1;
						if(KeyFIFO == 5)
						{
							xiping3 = 1;
						}
					}
					else if(SYS_ON && KeyFIFO == 5)
					{
						xiping = 1;
						KEY_ON=0;
					}
				}
				else if((KeyChkbuf==2 || KeyChkbuf==5 || KeyChkbuf==6) && (KeyChat2==150) && Fkeyin)				 
				{
					KeyFIFO = KeyChkbuf;
					KEY_ON_3s=1;
				}
				else if((KeyChkbuf==4) && (KeyChat2==250) && Fkeyin)				 
				{
					Fkeyin = 0;
					KeyFIFO = KeyChkbuf;
					KEY_ON_5s=1;
				}
				else if(KeyChat2 >= 255)
				{
					KeyChat2 = 251;
				}
			}
		}
	}
}