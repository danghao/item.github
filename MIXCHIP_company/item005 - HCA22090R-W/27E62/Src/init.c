//***************************************************************************
//!
//! \file    init.c
//! \brief   型号:HCA22090R(WiFi) MCU:27E62
//! \version V1.0
//! \author  D.H.
//! \date    2014-11-01
//! \email   danghao0815@163.com
//!
//***************************************************************************

#include	"init.h"

#include	"delay.h"

//***************************************************************************
//! \brief       系统初始化函数
//! \			 IO引脚、定时器、串口初始化
//! \param       无
//! \return      无
//***************************************************************************
void SYS_Init(void)
{
	Delay_ms(250);

	P0M  	&=	0xbb;
	P0M  	|=	0x28;
	P0UR	=	0x40;
	FP05 	=	0;

	P4M  	|=	0x60;
	P4UR	=	0x00;
	P4 		|=	0x60;

	P5M  	&=	0xFB;
	P5M  	|=	0x08;
	P5UR	=	0x04;
	FP53 	=	1;

	FGIE	=	0;
	FUTXPEN	=	0;
	FURXPEN	=	0;
	if(BodeRate-9 == 0)			// 9600
	{
		URRX	&=	0XFd;
		URRX	|=	0X05;
		URCR	=	0Xe6;								
	}
	else if(BodeRate-11 == 0)	// 115200
	{
		URRX	&=	0XF8;
		URCR	=	0Xbb;
	}
	FURXEN 	=	1;
	FUTXEN	=	1;
	FURXIEN = 	1;
	FURXIRQ = 	0;

	FT0IEN	=	0;
	FT0ENB	=	0;
	T0M		=	0x70;
	T0C		=	130;
	FT0IEN	=	1;
	FT0IRQ	=	0;
	FT0ENB	=	1;
	FGIE	= 	1;
	Delay_ms(250);
}

//***************************************************************************
//! \brief       WiFi复位函数
//! \			 送给WiFi模块复位引脚一个低脉冲，使其复位
//! \param       无
//! \return      无
//***************************************************************************
void Wifi_Rest(void)
{
	FP45 = 0;
	Delay_ms(250);
	FP45 = 1;
	Delay_ms(250);
}
