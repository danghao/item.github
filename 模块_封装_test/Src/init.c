#include	"init.h"

void Init(void)
{
// *******************************	
// \brief    IO init	
// *******************************	
	P0M  	|=	0x00;
	P0UR	|=	0x00;
	P0		|=	0x00;

// *******************************	
// \brief    TIMER init	
// *******************************
	FT0IEN	=	0;
	FT0ENB	=	0;
	T0M		=	0x70;
	T0C		=	200;
	FT0IRQ	=	0;
	FT0IEN	=	1;
	FT0ENB	=	1;
}
