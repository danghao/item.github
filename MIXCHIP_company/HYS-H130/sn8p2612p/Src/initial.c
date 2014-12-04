#include "user.h"


void initial(void)
{
	/*************** IO口设置 ****************/
		P0M	=	0x00;	//P0.0设为输入模式
		P0UR=	0x01;

		P1M =	0xCF;	// P1.4 P1.5设为输入模式
		P1UR=	0xCF;
		P1 	=	0x00;

		P5M =	0xFF;
		P5UR=	0xFF;
		P5  =   0XFF;
	/*************** pwm TC0设置 ****************/
		FTC0ENB	=	0;
		TC0M	=	0x50;	// TC0 时钟＝Fcpu/2
		TC0C	=	0x8A;	// 
		TC0R	=	0x8A;
		FTC0OUT	=	1;
		FALOAD0	=	1;
	/*************** int T0设置 ****************/
		FT0IEN=0;
		FT0ENB=0;
		T0M=0x00;	//设置T0时钟= Fcpu/256
		T0C=0x64;	//T0C初值 10ms
		FT0IRQ=0;
		FT0IEN=1;
		FT0ENB=1;
}
