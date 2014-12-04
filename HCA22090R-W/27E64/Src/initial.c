#include	"user.h"

void	initial	(void)
{
	u8 temp,temp1;
	P0M  	=	0xfb;	//[P0] 0 1 2 3
	P1M  	=	0xff;	//[P1] 0 1 2 3 4 5 6
	P1UR	=	0xbf;
/****************  设置 T0 中断  ****************/
	T0M		=	0x60;
	T0C		=	200;
	FT0IRQ	=	0;
	FT0IEN	=	1;
	FT0ENB	=	1;
	FGIE	= 	1;
/****************  led 初始化  ****************/
	led_wr(0x80);		//关显示
	led_wr(0x00);
	led_wr(0x40);
	led_wr(0xc0);
	for(temp=0;temp<7;temp++)
	led_wrDATA(0x00);
	led_wr(0x8f);		//开显示
/****************  key 初始化  ****************/
	for(temp=0;temp<20;temp++)		// 500ms
	{
		for(temp1=0;temp1<100;temp1++)
		{
			WDTR = 0x5A;
			delay(250);
		}
	}
	WDTR = 0x5A;
	P4M  	|=	0x80;	//[P4]7 sda
	P5M  	|=	0x01;	//[P5] 0 1 2 3
	P4		|=	0x80;
	P5		|=	0x01;
	delay(10);
	write(0x40,0x8A);
	delay(20);
	read(0x40);
}