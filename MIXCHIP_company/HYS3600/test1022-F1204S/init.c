#include"user.h"


void init(void)
{
/******IO init******/
	P0IO	=	0xFF;  
	P0PU	=	0xFF;  
	P1IO	=	0xfe;
	P1PU	=	0xff;

/******T0 init******/
    T0DR	=	138;        // 1us x 139 = 139us interval
    T0CR	=	0x8B;       // pcs = 8MHz/8 = 1us	fX/16
    T0CR1	=	0x00;  
	IE1		|=	0x02; 		// -  -  ADC  T3  T2  T1  T0  TX	
	EA		=	1;	

/******LCD init*****/
	LED		=	1;
	CS		=	1;
	WR		=	1;
	DATA	=	1;
	Lcd_Init(0x00);
	LED = 0;
}