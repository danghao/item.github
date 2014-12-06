#include "init.h"


void IO_Init(void) // IO口初始化
{
	P0M		&= 	0xFB;
	P0M 	|= 	0x7B;
	P0UR	|= 	0x00;

	P1M 	|= 	0x7B;
	P1UR	|= 	0x00;
	
}
void T0_Init(void)	// T0定时器初始化
{
	T0M		=	0x60;
	T0C		=	200;
	FT0IRQ	=	0;
	FT0IEN	=	1;
	FT0ENB	=	1;

	FGIE	= 	1;
}

void Uart_Init(void)
{
	FUTXPEN = 0;	//禁止UART TX奇偶校验位功能
	FURXPEN = 0;	//禁止UART RX奇偶校验位功能
	
	URRX &= 0XFD;	//设置UART波特率 9600
	URRX |= 0X05;
	URCR = 0XE6;

	FUTXEN = 1;		//使能UART TX功能和引脚
	FURXEN = 1;		//使能UART RX功能和引脚

	FUTXIRQ = 0;	//清UART TX中断标志
	FURXIRQ = 0;	//清UART RX中断标志

	FUTXIEN = 0;	//禁止UART TX中断功能
	FURXIEN = 1;	//使能UART RX中断功能
	
	FGIE = 1;
}
