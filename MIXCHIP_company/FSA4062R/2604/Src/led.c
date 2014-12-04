#include	"user.h"

uint led_data[4] = {0xda,0x81};
bit led_data_ok = 1;
uint temp2;
uint led_cnt;
uint LED_CODE[12] = { 0xeb,0x81,0xda,0xd9,0xb1,0x79,0x7b,0xc1,0xfb,0xf9 };  // 0~9 
bit	undis_ok;

/************************ led ctrl ************************/
void led(void)
{
	if(led_data_ok && !un_display)
	{
		led_cnt ++;
		switch(led_cnt)
		{
			case 1 :
			{
				led_wr(0xc0);		// led0
				led_wrDATA(led_data[0]);
				break;
			}
			case 2 :
			{
				led_wr(0xc2);		// led1
				led_wrDATA(led_data[1]);
				break;
			}
			case 3 :
			{
				led_wr(0xc8);		// led2 SW RHY SLP
				led_wrDATA(led_data[2]);
				break;
			}
			case 4 :
			{
				led_wr(0xca);		// led2 ECO TIMER
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
	else if(un_display && !undis_ok)
	{
		__asm("nop")
		led_wr(0xc0);		led_wrDATA(0);
		led_wr(0xc2);		led_wrDATA(0);
		led_wr(0xc8);		led_wrDATA(0);
		led_wr(0xca);		led_wrDATA(0);
		__asm("nop")
		undis_ok = 1;
	}
}
/************************ time dsp ************************/
void time_dsp(void)
{
	if(time_to < 6)
	{
		led_data[1] = LED_CODE[time_to/2] | 0x04;
		led_data[0] = LED_CODE[5*(time_to%2)];
	}
	else if((time_to-3)<10)
	{
		led_data[1] = LED_CODE[time_to-3] | 0x04;
		led_data[0] = 0xeb;
	}
	else
	{
		led_data[1] = LED_CODE[(time_to-3)/10];
		led_data[0] = LED_CODE[(time_to-3)%10] | 0x04;
	}
}
/************************ led 写指令 ************************/
void led_wr(uint com)
{
	uchar i;
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
void led_wrDATA(uint com)
{
	uchar i;
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
void delay(uint x)
{
	uint i;
	for(i=0;i<x;i++) {__asm("nop")}
}