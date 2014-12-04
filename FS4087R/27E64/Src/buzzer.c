#include "buzzer.h"

bit buzzer0_on;
bit buzzer1_on;
bit buzzer2_on;
bit BUZ_EN;
u8 buz_cnt;
bit f2_10ms;

/****************************************************************************
 * \brief       Buzzer输出函数
 * \param       无
 * \return      无
 * *************************************************************************/
void buzzer(void)
{
	if(f2_10ms)
	{
		f2_10ms = 0;
		if(buzzer0_on || buzzer1_on || buzzer2_on)
		{
			if(buz_cnt == 1)
			{
				BUZ_EN = 1;
			}
			else if(buz_cnt == 14)
			{
				if(!buzzer1_on)
				{
					BUZ_EN = 0;
					if(buzzer0_on)
					{
						buzzer0_on = 0;
					}
				}
			}
			else if(buz_cnt == 19)
			{
				if(buzzer2_on)
				{
					BUZ_EN = 1;
				}
			}
			else if(buz_cnt == 32)
			{
				BUZ_EN = 0;
				buzzer1_on = 0;
				buzzer2_on = 0;
			}
			buz_cnt++;
		}
	}
}
