#include	"user.h"

extern uint rst_rev;
extern uint __RAM * Ptr; 
extern bit FUN_SP;
extern bit BUZZER1_ON;
extern bit BUZZER2_ON;
extern bit BUZZER3_ON;
extern bit 		xiping2;
extern bit		KEY_ON;
extern bit		KEY_ON_3s;
extern bit		KEY_ON_5s;
extern uint		KeyFIFO;
extern bit 		wx_ok;
extern uint 	rst_rev;
extern bit		RST_LED;  
extern bit  	LOCK_LED; 
extern uint  	TIME_LED; 
extern bit  	SYS_LED; 
extern uint  	POWER_LED; 
extern long	 	x4; 
bit DSP_OFF;
bit LOCK_T;
bit RST_T;
bit RST_ON;         
bit SYS_ON;     
bit LOCK_ON;        
uint TIME;
uint POWER;
bit model;
uint t_cnt1;
uint t_cnt2;
uint t_cnt3;

void keyprocess (void)
{
	uint temp;
	if(KEY_ON || KEY_ON_3s || KEY_ON_5s)
	{
		if(KeyFIFO == 7 && !LOCK_ON)
		{					
			if(KEY_ON && SYS_ON)	
			{
				SYS_ON=0;
				BUZZER3_ON = 1;
				POWER = 0;
				TIME = 0;
			}
		}
		else if(KeyFIFO == 5 && !LOCK_ON)
		{					
			if(KEY_ON)	
			{
				SYS_ON=~SYS_ON;
				if(SYS_ON)
				{
					xiping2 = 1;
					BUZZER2_ON = 1;
					if(FUN_SP)
					POWER = 0;
					else if(TIME == 0)
					POWER = 1;
					else
					TIME = 0;
				}
				else
				{
					BUZZER3_ON = 1;
					POWER = 0;
					TIME = 0;
				}
			}
			if(KEY_ON_3s)
			{
				if(SYS_ON && !xiping2)
				{
					BUZZER1_ON = 1;
					DSP_OFF = 1;
				}
			}
		}
		else if(FUN_SP)
		{
			if(KeyFIFO == 4 && !LOCK_ON)
			{
				if(RST_ON)			
				{
					if(KEY_ON)
					{
						RST_T = 1;
					}
					else if(KEY_ON_5s)
					{
						BUZZER1_ON = 1;
						RST_ON = 0;
						RST_T  = 0;
						FUN_SP = 0;
						t_cnt1 = 0;
						t_cnt2 = 0;
						t_cnt3 = 0;
						rst_rev= 0x00;

						PEROML		=	0x00;
						PEROMH		=	0x0A;
						WDTR 		=	0X5A;
						PECMD 		=	0XC3;
						for(temp=0;temp<5;temp++);
						Ptr = &rst_rev;
						x4  = (long)Ptr;
						PERAML		=	(x4 % 0x0100);
						PERAMCNT	=	(x4 / 0x0100);
						PERAMCNT	|=	0X08;
						PEROML		=	0x05;
						PEROMH		=	0x0A;
						WDTR 		=	0X5A;
						PECMD 		=	0X5A;
						for(temp=0;temp<5;temp++);
					}
				}
			}
		}
		else if(KeyFIFO == 2)
		{
			if(LOCK_ON)
			{
				if(KEY_ON)
				{
					LOCK_T = 1; 
					LOCK_LED  = 1;
				}
				if(KEY_ON_3s)
				{
					BUZZER1_ON = 1;	
					LOCK_T    = 0;
					LOCK_ON   = 0;
					LOCK_LED  = 0;
				}
			}
			else if(SYS_ON || TIME)		
			{
				if(KEY_ON)
				{
					LOCK_T = 1; 
					LOCK_LED   = 1;
				}
				else if(KEY_ON_3s)
				{
					BUZZER1_ON = 1;
					LOCK_T    = 0;
					LOCK_ON   = 1;
					LOCK_LED  = 1;
				}
			}
		}
		else if(!LOCK_ON && (KeyFIFO == 3))
		{
			if(KEY_ON)
			{
				TIME++;
				if(TIME >= 5)
				{
					TIME = 0;
				}
				BUZZER1_ON = 1;
			}
		}
		else if(!LOCK_ON && (KeyFIFO == 1))
		{
			if(KEY_ON)
			{
				if(SYS_ON || TIME)		
				{
					POWER++;
					if(POWER == 5)
					{
						POWER = 1;
					}
					BUZZER1_ON = 1;
				}
			}
		}
		else if(!LOCK_ON && (KeyFIFO == 6) && model!=1)
		{
			if(KEY_ON_3s)
			{
				if(SYS_ON)	
				{
				
					BUZZER1_ON = 1;
					model  = 1;	
					t_cnt1 = 0;
					t_cnt2 = 0;
					t_cnt3 = 0;
				}
			}
		}
		SYS_LED		=	SYS_ON;  
		TIME_LED	=	TIME;
		POWER_LED	=	POWER;
		LOCK_LED 	=	LOCK_ON; 
		RST_LED 	=	RST_ON;
		KEY_ON_5s = 0;
		KEY_ON_3s = 0;
		KEY_ON = 0;
	}
}
