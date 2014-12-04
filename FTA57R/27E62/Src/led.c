#include	"led.h"

bit 	undis_in;
u8 		 led_cnt;
u8 	  led_buf[2];

//***************************************************************************
//! \brief       LED显示函数
//! \param       无
//! \return      无
//***************************************************************************
void led(void)
{
	if(f_1ms)
	{
		f_1ms = 0;
		if(!un_display)
		{
			led_cnt++;
			if(led_cnt > 3)
			led_cnt = 1;
			switch(led_cnt)
			{
				case 1 :
				{
					LED_CS3 =	1;
					P5 &= 0xf5; P0 &= 0xfa;
					switch(led_buf[0] & 0xf0)
					{
						case 0x10 : FP51 = 1; break;
						case 0x20 : FP02 = 1; break;
						case 0x40 : FP00 = 1; break;
						case 0x80 : FP53 = 1; break;
						default : {}
					}
					LED_CS1 =	0;
					break;
				}
				case 2 :
				{
					LED_CS1 =	1;
					if((led_buf[1] & 0x04))			// WIFI
					{
						P0 |= 0x01;
					}
					else
					{
						P0 &= 0xfe;
					}
					P0 &= 0xfb;
					P5 &= 0xfd;
					if((led_buf[1] & 0x02))			// SLP	
					{
						P0 |= 0x04;
					}
					else if((led_buf[1] & 0x01))	// RHY
					{
						P5 |= 0x02;
					}
					LED_CS2 =	0;
					break;
				}
				case 3 :
				{
					LED_CS2 =	1;
					if((led_buf[0] & 0x08))
					{
						FP51 = 1;
					}
					else
					{
						FP51 = 0;
					}
					FP02 = 0; FP00 = 0; FP53 = 0;
					switch(led_buf[0] & 0x07)
					{
						case 0x01 : FP02 = 1; break;
						case 0x02 : FP00 = 1; break;
						case 0x04 : FP53 = 1; break;
						default : {}
					}
					LED_CS3 =	0;
					break;
				}
				default : {}
			}
		}
		else if(!undis_in)
		{
			LED_CS1 =	1;
			LED_CS2 =	1;
			LED_CS3 =	1;
			undis_in = 1;
		}
	}
}
