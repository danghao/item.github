#include "user.h"

void initial(void)
{
	/*************** IO������ ****************/
		P0M		=	0x07;
		P0UR	=	0x07;

		P1M 	=	0xFB;
		P1UR	=	0xF2;

		P2M 	=	0xFF;
		P2UR	=	0xff;

		P5M 	=	0x0F;
		P5UR	=	0x0F;

	/*************** int T0���� ****************/
		FT0IEN=0;
		FT0ENB=0;
		T0M=0x70;	//T0ʱ��=Fcpu/2  0x60->Fcpu/4  0x50->Fcpu/8
		T0C=0xb7;	//T0C��ֵ 1ms
		FT0IRQ=0;
		FT0IEN=1;
		FT0ENB=1;
		FGIE=1;

			speed = 8;				// �ϵ�7��
			mode = 4;
}
