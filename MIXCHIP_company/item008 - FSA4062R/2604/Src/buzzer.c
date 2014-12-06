#include "user.h"

		bit buzzer_on;
		bit buzzer1_on;
		bit buzzer2_on;
		uint BUZ_CNT;

void buzzer(void)
{
	if(f2_10ms)
	{
		f2_10ms = 0;
		if(buzzer_on || buzzer1_on || buzzer2_on)
		{
			BUZ_CNT++;
			if(BUZ_CNT == 1)
			{
				buz_en = 1;
			}
			else if(BUZ_CNT == 14)
			{
				if(!buzzer1_on)
				{
					buz_en = 0;
					if(buzzer_on)
					{
						buzzer_on = 0;
					}
				}
			}
			else if(BUZ_CNT == 19)
			{
				if(buzzer2_on)
				{
					buz_en = 1;
				}
			}
			else if(BUZ_CNT == 32)
			{
				BUZ_CNT = 0;
				buz_en = 0;
				if(buzzer1_on)
				{
					buzzer1_on = 0;
				}
				else if(buzzer2_on)
				{
					buzzer2_on = 0;
				}
			}
		}
	}
}
