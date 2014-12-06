#include	"user.h"

extern bit f_01ms;					
bit f_5s;
bit f_1s;
bit f2_1s;
bit f3_1s;
bit f_1ms;
bit f_4ms;
bit ADC_56;
bit ADC_OK;
bit BUZZER_ON;
bit BUZZER1_ON;
bit BUZZER2_ON;
bit BUZZER3_ON;
uint num_1s;
uint num_4ms;
uint num_01ms;
uint Adc_dat;
uint buz_cnt;
uint buz_cnt2;
uint buz_cnt3;
uint temp;
void delay_100ms(void)
{
	uint temp1,temp2,temp3;
	for(temp1=0;temp1<30;temp1++)
	{
		WDTR	=	0x5A;
		for(temp2=0;temp2<50;temp2++)
		{
			for(temp3=0;temp3<100;temp3++)
			;
		}
	}
}
void	main	(void)
{
	WDTR	=	0x5A;
	delay_100ms();
	initial();
	while(1)
	{
		WDTR	=	0x5A;
		hwjc();
		key();
		keyprocess();
		adc();
		led();
		rst();
	}		
}	
void __interrupt [0x0B] isr_t0 (void)
{
	FT0IRQ	=	0;
	T0C		=	5;
	f_4ms	=	1;
	num_4ms++	;
	if(num_4ms >= 250)
	{
		num_4ms	=	0;
		f_1s	=	1;
		f2_1s	=	1;
		f3_1s	=	1;
	}
}
void __interrupt [0x0C] isr_tc0 (void)
{
	FTC0IRQ	=	0;
	TC0C	=	156;
	num_01ms++;
	f_01ms = 1;					
	if(num_01ms == 4)
	{
		FP44	=	1;
	}
	else if(num_01ms == 100)
	{
		num_01ms	=	0;
		FP44	=	0;
	}
	if(num_01ms%10==0 && num_01ms!=0)
	{
		FADS	=	1; 
	}
}
void __interrupt [0x0E] isr_tc2 (void)
{
	FTC2IRQ	=	0;
	TC2C	=	131; 
	if(BUZZER_ON)
	{
		BUZZER = ~BUZZER; 
	}
	if(BUZZER3_ON || BUZZER2_ON || BUZZER1_ON)	
	{
		buz_cnt++;
		if(buz_cnt == 100)
		{
			buz_cnt = 0;
			buz_cnt2 ++;
			if(buz_cnt2 == 1)
			{
				BUZZER_ON = 1;
			}
			else if(buz_cnt2 == 15) 
			{
				if(BUZZER2_ON || BUZZER1_ON)
				{
				 	BUZZER_ON = 0;
				 	BUZZER = 0;
					if(BUZZER1_ON)
					{
						buz_cnt2 = 0;
						BUZZER1_ON=0;
					}
				}
			}
			else if(buz_cnt2 == 20)
			{
				if(BUZZER2_ON)
				{
					BUZZER_ON = 1;
				}
			}
			else if(buz_cnt2 >= 34)
			{
				buz_cnt2 = 0;
				BUZZER_ON = 0;
				BUZZER2_ON = 0;
				BUZZER3_ON = 0;
				BUZZER	=	0;
			}
		}
	}	
}
void __interrupt [0x10] isr_adc (void)
{
	FADCIRQ	=	0;
	Adc_dat	=	ADB;
	ADC_OK	=	1;
}