#include "user.h"

extern  bit buzzer_on;
extern  bit buzzer3_on;
extern  bit f1s;
extern 	bit shan;
extern 	bit key_dis;
extern 	bit dump_sta;

void initial(void)
{
	/*************** IO口设置 ****************/
		P0M	=	0x01;	//P0.0设为输入模式
		P0UR=	0x01;

		P1M =	0x9b;	// P1.4 P1.5设为输入模式
		P1UR=	0x5F;
		P1 	=	0x00;

		P5M =	0xFF;
		P5UR=	0xFF;
		P5  =   0XFF;
	/*************** pwm TC0设置 ****************/
		FTC0ENB	=	0;
		TC0M	=	0x70;	// TC0 时钟＝Fcpu/8
		TC0C	=	0x80;	// 
		TC0R	=	0x80;
		FTC0OUT	=	1;
		FALOAD0	=	1;
	/*************** int T0设置 ****************/
		FT0IEN=0;
		FT0ENB=0;
		T0M=0x50;	//设置T0时钟= Fcpu/16
		T0C=0x84;	//T0C初值 1ms
		FT0IRQ=0;
		FT0IEN=1;
		FT0ENB=1;
		FGIE=1;

		if(dump_sta != FP12)
		dump_sta = FP12;
		if(!dump_sta)
		key_dis = 1;
		buzzer_on = 1;
		shan = 1;

//		buzzer3_on = 1;
}
