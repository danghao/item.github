#include "initial.h"

/****************************************************************************
 * \brief       系统初始化函数
 *				IO口 定时器 初始化
 * \param       无
 * \return      无
 * *************************************************************************/
void SYS_Init(void)
{
	P0M 	|=	0x6E;
	P0UR	|=	0x6E;

	P1M 	|=	0x78;
	P1M 	&=	0xfd;
	P1UR	|=	0x78;
	P1UR 	&=	0xfd;

	P4M 	|=	0xfa;
	P4M 	&=	0xfb;
	P4UR	|=	0xfa;
	P4UR	&=	0xfb;

	P5M 	=	0x0F;
	P5UR	=	0x0F;

	T0M		=	0x60;	// T0定时器初始化
	T0C		=	200;
	FT0IRQ	=	0;
	FT0IEN	=	1;
	FT0ENB	=	1;
	FGIE	= 	1;
}
