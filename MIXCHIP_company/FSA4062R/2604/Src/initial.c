#include "user.h"

void initial(void)
{
	uint temp1;
	/*************** IO口设置 ****************/
		P0M		&=	0xfb;
		P0UR	=	0x04;

		P1M 	=	0x87;
	//	P1UR	=	0xa7;
		P1		=	0x07;

		P2M 	&=	0x4b;
		P2UR	=	0xb4;

		P5M 	|=	0x0C;
		P5UR	=	0x00;
	/*************** int T0设置 ****************/
		FT0IEN=0;
		FT0ENB=0;
		T0M=0x70;	//T0时钟=Fcpu/8  0x60->Fcpu/4  0x70->Fcpu/2
		T0C=0xCC;	//T0C初值 0xC2 125us
		FT0IRQ=0;
		FT0IEN=1;
		FT0ENB=1;
		FGIE=1;
/****************  led 初始化  ****************/
		led_wr(0x02);
		led_wr(0x40);	// 0x44 固定地址
		led_wr(0xc0);
		for(temp1=0;temp1<14;temp1++)
		led_wrDATA(0x00);
		led_wr(0x8b);		// 88开显示  80关显示   +1~7调节亮度
/****************  旋转电位器  ****************/
		ffp13 = FP13;
		ffp14 = FP14;
}
