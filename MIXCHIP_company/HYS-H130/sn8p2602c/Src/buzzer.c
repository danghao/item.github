#include "user.h"

extern uint BUZ_CNT;
extern uint BUZ_CNT1;
extern bit buzzer_on;
extern bit buzzer1_on;
extern bit buzzer2_on;
extern bit buzzer3_on;
extern bit f_3ms;
	   bit buzzer_on;
	   bit BUZ_CNT1_in;

//		TC0R	= 0xb0;	//  3.125k
//		TC0R	= 0xb9;	//  3.571k
//		TC0R	= 0xc0;	//  4.167k

void buzzer(void)
{
	if(f_3ms)
	{
		f_3ms = 0;
		if(BUZ_CNT1_in||buzzer_on||buzzer1_on||buzzer2_on||buzzer3_on)
		{
			if(BUZ_CNT == 0 && !BUZ_CNT1_in)
			{
				FTC0ENB = 0;
				if(buzzer_on)
				{
					TC0R	= 0xb0;	//  3.125k
				}
				else if(buzzer1_on)
				{
					TC0R	= 0xb5;	//  3.571k
				}
				else if(buzzer2_on || buzzer3_on)
				{
					TC0R	= 0xBA;	//  4.167k
				}
				FTC0ENB = 1;
				FP14 	= 1;
			}
			else if(BUZ_CNT == 25 && !BUZ_CNT1_in)
			{
				if(!buzzer1_on && !buzzer3_on)
				FP14 = 0;
			}
			else if(BUZ_CNT == 45 && !BUZ_CNT1_in)
			{
					if(buzzer_on || buzzer2_on)
					{
						FTC0ENB = 0;
						TC0R	= 0xb5;	//  3.571k
						FTC0ENB = 1;
						FP14 	= 1;
					}
					else if(buzzer3_on)
					{
						FP14 = 0;
					}
				else if(buzzer1_on)
				{
					buzzer1_on = 0;
					FP14 = 0;
					BUZ_CNT = 0;
					BUZ_CNT1_in = 1;
				}
			}
			else if(BUZ_CNT == 70 && !BUZ_CNT1_in)
			{
				if(buzzer2_on || buzzer_on)
				FP14 = 0;
					FTC0ENB = 0;
					if(buzzer3_on)
					{
						TC0R	= 0xb0;	//  3.125k
					}
					FTC0ENB = 1;
					FP14 	= 1;
			}
			else if(BUZ_CNT == 90 && !BUZ_CNT1_in)
			{
				FTC0ENB = 0;
				if(buzzer_on)
				{
					TC0R	= 0xBA;	//  4.167k
				} 
				else if(buzzer2_on) 
				{
					TC0R	= 0xb0;	//  3.125k
				}
				FTC0ENB = 1;
				FP14 	= 1;
			}
			else if(BUZ_CNT == 115 && !BUZ_CNT1_in)
			{
				if(buzzer2_on || buzzer_on || buzzer3_on)
				{
					FP14 = 0;
					BUZ_CNT = 0;
					BUZ_CNT1_in = 1;
					buzzer3_on = 0;
					buzzer2_on = 0;
					buzzer_on = 0;
				}
			}
			else if(BUZ_CNT == 135 && BUZ_CNT1_in)		//100
			{
				BUZ_CNT = 0;
				BUZ_CNT1++;
				if(BUZ_CNT1 >= 7)
				{
					BUZ_CNT1_in = 0;
					FTC0ENB = 0;
				}
			}
			BUZ_CNT++;
		}
	}
}
