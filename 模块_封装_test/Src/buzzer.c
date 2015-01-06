#include "buzzer.h"

bit buz_en;
u8	BUZ_CNT;
u8  buzzer_sel;

//*************************************************************
//! \brief       Buzzer函数
//! \参数        [buzzer_sel] 1 bi 2 bibi 3 bi-
//! \Call        10ms
//*************************************************************
void buzzer(void)
{
	if(buzzer_sel)	
	{
		BUZ_CNT++;
		switch(BUZ_CNT)
		{
			case 1 :
			{
				buz_en = 0;
				break;
			}
			case 2 :
			{
				buz_en = 1;			//	使能buzzer 开始发声
				break;
			}
			case 15 :
			{
				if(buzzer_sel != 3)
				{
					buz_en = 0;		//	禁止buzzer 停止发声
					if(buzzer_sel == 1)
					{
						buzzer_sel = 0;
					}
				}
				break;
			}
			case 20 :
			{
				if(buzzer_sel == 2)
				{
					buz_en = 1;
				}
				break;
			}
			case 33 :
			{
				BUZ_CNT = 0;
				buz_en = 0;
				buzzer_sel = 0;
				break;
			}
			default : {}
		}
	}
}
