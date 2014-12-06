#include	"user.h"

//数据准备 led_data[8]; led_data_ok = 1;
uint led_data[8];
bit led_data_ok;

/************************ led ctrl ************************/
void led(void)
{
	uchar i;
	if(led_data_ok)
	{
		led_data_ok = 0;
		led_wr(0xc0);
		for(i=0;i<7;i++)
		led_wrDATA(led_data[i]);
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
	while(x--)
	{
		__asm("nop")
	}
}
