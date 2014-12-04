#include	"init.h"

//***************************************************************************
//! \brief      系统初始化函数 
//! 			IO引脚、定时器初始化
//! \param      无
//! \return     无
//***************************************************************************
void SYS_Init(void)
{
	P0M  	&=	0xef;	// in REC
	P0M  	|=	0x6d;	// out
	P0UR	|=	0x6d;
	P0		|=	0x68;

	P4M  	|=	0xB8;	// out DO
	P4M  	&=	0xBF;	// in DI
	P4UR	|=	0xB8;	// up
	P4		|=	0xB8;	

	P5M  	|=	0x0f;
	P5UR	=	0x0f;
	P5		|=	0x05;

	FT0IEN	=	0;
	FT0ENB	=	0;
	T0M		=	0x70;
	T0C		=	130;
	FT0IEN	=	1;
	FT0IRQ	=	0;
	FT0ENB	=	1;
	FGIE	= 	1;

}

