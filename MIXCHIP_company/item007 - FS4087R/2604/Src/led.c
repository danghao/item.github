#include	"user.h"

	uint LED_CODE[12] = { 0xbe,0x0c,0x76,0x5e,0xcc,0xda,0xfa,0x0e,0xfe,0xde,0x52,0xee };  // 0~9 Èý A
	uint led_cnt;
	bit f_2ms;
	bit undis_in;
	uint led_buf[3] = {0,0,0/*LED_CODE[0]*/};	// [0]led 12345  [1]led 678910  [2]led 11

void led(void)
{
	if(f_2ms)
	{
		f_2ms = 0;
		if(!un_display)
		{
			led_cnt++;
			if(led_cnt > 3)
			led_cnt = 1;
			switch(led_cnt)
			{
				case 1 :		//led 1~5  	p2.[7~3]
				{
					LED_11 = 0;
					P2 &= 0x07;
					P2 |= led_buf[0];
					LED_5 = 1;
					break;
				}
				case 2 :		//led 6~10	p2.[7~3]
				{
					LED_5 = 0;
					P2 &= 0x07;
					P2 |= led_buf[1];
					LED_10 = 1;
					break;
				}
				case 3 :		//led 11	p2.[7~1]
				{
					LED_10 = 0;
					P2 &= 0x01;
					P2 |= led_buf[2];
					LED_11 = 1;
					break;
				}
				default : {}
			}
			if(undis_in)
			undis_in = 0;
		}
		else if(!undis_in)
		{
			LED_5 = 0;
			LED_10 = 0;
			LED_11 = 0;
			undis_in = 1;
		}
	}
}
