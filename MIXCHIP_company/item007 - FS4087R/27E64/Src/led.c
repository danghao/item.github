#include	"led.h"

	bit f_2ms;

	u8 LED_CODE[12] = { 0x7d,0x30,0x6e,0x7a,0x33,0x5b,0x5f,0x70,0x7f,0x7b,0x4a,0x77 };  // 0~9 Èý A
	u8 led_cnt;
	bit undis_in;

	u8 led_buf[3];
	//led_buf[0]  [bit 4~0] 8H 4H 2H 1H sw
	//led_buf[1]  [bit 5~0] WIFI QUIT ION AIR SLP RHY
	//led_buf[2]  LED_CODE[12]

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
				case 1 :
				{
					LED_11 = 0;
					P0 &= 0x91;
					if((led_buf[0] & 0x01) == 0x01)
					P0 |= 0x40;
					if((led_buf[0] & 0x02) == 0x02)
					P0 |= 0x20;
					if((led_buf[0] & 0x04) == 0x04)
					P0 |= 0x08;
					if((led_buf[0] & 0x08) == 0x08)
					P0 |= 0x04;
					if((led_buf[0] & 0x10) == 0x10)
					P0 |= 0x02;
					LED_5 = 1;
					break;
				}
				case 2 :
				{
					LED_5 = 0;
					if((led_buf[1] & 0x20) == 0x20)
					P4 |= 0x08;
					else
					P4 &= 0xf7;
					P0 &= 0x91;
					P0 |= (led_buf[1]&0x07)<<1;
					P0 |= (led_buf[1]&0x18)<<2;
					LED_10 = 1;
					break;
				}
				case 3 :		//led_buf[2]  [bit 6~0] 
				{
					LED_10 = 0;
					P4 &= 0xe7;
					P0 &= 0x91;
					P4 |= (led_buf[2] & 0x60)>>2;
					P0 |= (led_buf[1]&0x18)<<2;
					P0 |= (led_buf[1]&0x07)<<1;
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
