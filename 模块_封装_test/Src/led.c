#include	"led.h"

//***************************************************************************
//! \brief       LEDÏÔÊ¾º¯Êý
//! \param       
//! \Call        1 ms
//***************************************************************************

bit un_display;
bit undisplay_ok;
u8  led_cnt;
u8  led_data[3];
u8  LED_CS;

void led(void)
{
	if(!un_display)
	{
		led_cnt++;
		switch(led_cnt)
		{
			case 1 :
			{
				LED_CS = 1;
				P0 = led_data[1];
				break;
			}
			case 2 :
			{
				LED_CS = 2;
				P0 = led_data[2];
				break;
			}
			case 3 :
			{
				LED_CS = 3;
				P0 = led_data[3];
				led_cnt = 0;
				break;
			}
			default : {}
		}
	}
	else if(!undisplay_ok)
	{
		LED_CS = 0;
		undisplay_ok = 1;
	}
}
