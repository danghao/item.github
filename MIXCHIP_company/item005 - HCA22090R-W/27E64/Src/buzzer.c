#include	"user.h"

	bit BUZZER1_ON;
	bit BUZZER2_ON;
	bit BUZZER3_ON;
	u8	buz_cnt;

void buzzer(void )
{
	if(f10ms)
	{
		f10ms = 0;
		if(BUZZER3_ON || BUZZER2_ON || BUZZER1_ON)	
		{
			buz_cnt++;
			if(buz_cnt == 1)
			{
				BUZZER_ON = 1;
			}
			else if(buz_cnt == 14) 
			{
				if(BUZZER2_ON || BUZZER1_ON)
				{
				 	BUZZER_ON = 0;
				 	FP16 = 0;
					if(BUZZER1_ON)
					{
						buz_cnt = 0;
						BUZZER1_ON=0;
					}
				}
			}
			else if(buz_cnt == 18)
			{
				if(BUZZER2_ON)
				{
					BUZZER_ON = 1;
				}
			}
			else if(buz_cnt == 31)
			{
				buz_cnt = 0;
				BUZZER_ON = 0;
				BUZZER2_ON = 0;
				BUZZER3_ON = 0;
				FP16	=	0;
			}
		}
	}
}
