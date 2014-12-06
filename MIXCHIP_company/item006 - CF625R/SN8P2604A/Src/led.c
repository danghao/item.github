#include	"user.h"

u8 led_data[4] = {0,0,0,0};
bit led_data_ok = 1;
u8 temp2;
u8 led_cnt;
u8 LED_CODE[12] = { 0x7D,0x28,0x5B,0x7A,0x2E,0x76,0x77,0x38,0x7F,0x7E };  // 0~9 
bit	undis_ok;

/************************ led ctrl ************************/
void led(void)
{
	if(un_display && !undis_ok)
	{
		led_wr(0xc6);		led_wrDATA(0);
		led_wr(0xc8);		led_wrDATA(0);
		led_wr(0xcA);		led_wrDATA(0);
		led_wr(0xcC);		led_wrDATA(0);
		undis_ok = 1;
	}
	else if(!un_display && led_data_ok)
	{
		led_cnt ++;
		switch(led_cnt)
		{
			case 1 :
			{
				led_wr(0xca);		// led0
				led_wrDATA(led_data[0]);
				break;
			}
			case 2 :
			{
				led_wr(0xcc);		// led1
				led_wrDATA(led_data[1]);
				break;
			}
			case 3 :
			{
				led_wr(0xc8);		// led2: HUM STORM NORMAL SLIENT OFF-TIME ON-TIME
				led_wrDATA(led_data[2]);
				break;
			}
			case 4 :
			{
				led_wr(0xc6);		// led3: NATURE SLEEP ION WATER SW
				led_wrDATA(led_data[3]);
				break;
			}
			default :
			{
				led_cnt = 0;
				led_data_ok = 0;
			}
		}
	}
}
/************************ time dsp ************************/
void time_dsp(void)
{
	if(time_to < 6)
	{
		led_data[1] = LED_CODE[time_to/2] | 0x80;
		led_data[0] = LED_CODE[5*(time_to%2)];
	}
	else if((time_to-3)<10)
	{
		led_data[1] = LED_CODE[time_to-3] | 0x80;
		led_data[0] = LED_CODE[0];
	}
	else
	{
		led_data[1] = LED_CODE[(time_to-3)/10];
		led_data[0] = LED_CODE[(time_to-3)%10] | 0x80;
	}
}
/************************ time dsp ************************/
void time_speed_dsp(u8 x)	// 0 time 1 speed 2 auto
{
	if((speed == 0 || speed == 5) && time_to == 0)
	{
		led_data[1] = 0;
		led_data[0] = 0;
	}
	else
	{
		if(speed == 0 || speed == 5)
		f_display = 0;
		else if(time_to == 0)
		f_display = 1;
		else
		{
			if(x == 2)
			f_display = ~f_display;
			else if(x == 1)
			f_display = 1;
			else
			f_display = 0;
		}
		if(f_display)
		{
			led_data[1] = LED_CODE[speed/10];
			led_data[0] = LED_CODE[speed%10];
		}
		else
		{
			time_dsp();
		}
	}
}
/************************ led 写指令 ************************/
void led_wr(u8 com)
{
	u8 i;
	STB=1;
		delay(4);
	STB=0;
		delay(4);
	for(i=0;i<8;i++)
	{
		CLK=0;
		if(com & 0x01)
		DIO=1;
		else
		DIO=0;
		delay(4);
		com>>=1;
		CLK=1;
		delay(4);
	}
}
/************************ led 写数据 ************************/
void led_wrDATA(u8 com)
{
	u8 i;
	delay(4);
	for(i=0;i<8;i++)
	{
		CLK=0;
		if(com & 0x01)
		DIO=1;
		else
		DIO=0;
		delay(4);
		com>>=1;
		CLK=1;
		delay(4);
	}
}
/************************ delay 函数 ************************/
void delay(u8 x)
{
	u8 i;
	for(i=0;i<x;i++) {__asm("nop")}
}/************************ delay 函数 ************************/
void delayms(u8 y)
{
	u8 i;
	for(i=0;i<y;i++)
	{
		WDTR = 0x5A;
		delay(250);
		WDTR = 0x5A;
		delay(250);
		WDTR = 0x5A;
		delay(250);
		WDTR = 0x5A;
		delay(250);
	}
}