#include"user.h"

void init(void)
{
/******IO init******/
		P1M0 &= ~0X03;		//P10 P11 out
		P1M1 |= 0X03;

		P3M0 &= ~0X80;		//P37 out
		P3M0 |= 0X1c;		//P32 P33 P34 in
		P3M1 |= 0X80;
		P3M1 &= ~0X1c;

		P4M0 = 0X00;
		P4M1 = 0X00;
/******T0 init******/
	TMOD	=	0x01;
	TL0  	= 	0x00;		//中断中重装值
	TH0  	= 	0x01; 		//中断中清TF0标志位
	TR0		=	1;
	IE0		=	1;
	ET0		=	1;	  	
/******uart init******/
	SBUF	=   0;
	SCON	|=	0X40;
	RI 		= 	0;
	REN		=	1;
	TCLK	=	1;		 // T2 波特率发生
	RCLK	=	1;
	RCAP2L	=	18;		 // 2400 bit/s
	RCAP2H	=	0;


	TR2		=	1;
	ES0		=	1;
	EA		=	1;	
/******LCD init*****/
	LED		=	1;
	CS		=	1;
	WR		=	1;
	DATA	=	1;
	Lcd_Init(0xFF);
	LED = 0;
}