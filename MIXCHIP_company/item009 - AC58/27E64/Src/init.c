#include "init.h"


void IO_Init(void) // IO�ڳ�ʼ��
{
	P0M		&= 	0xFB;
	P0M 	|= 	0x7B;
	P0UR	|= 	0x00;

	P1M 	|= 	0x7B;
	P1UR	|= 	0x00;
	
}
void T0_Init(void)	// T0��ʱ����ʼ��
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
	FUTXPEN = 0;	//��ֹUART TX��żУ��λ����
	FURXPEN = 0;	//��ֹUART RX��żУ��λ����
	
	URRX &= 0XFD;	//����UART������ 9600
	URRX |= 0X05;
	URCR = 0XE6;

	FUTXEN = 1;		//ʹ��UART TX���ܺ�����
	FURXEN = 1;		//ʹ��UART RX���ܺ�����

	FUTXIRQ = 0;	//��UART TX�жϱ�־
	FURXIRQ = 0;	//��UART RX�жϱ�־

	FUTXIEN = 0;	//��ֹUART TX�жϹ���
	FURXIEN = 1;	//ʹ��UART RX�жϹ���
	
	FGIE = 1;
}
