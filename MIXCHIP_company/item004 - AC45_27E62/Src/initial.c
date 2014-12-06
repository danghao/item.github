#include	"user.h"

extern void rst_set(void);
extern uint t_cnt2;
extern uint t_cnt3;



extern bit BUZZER2_ON;
extern bit  	SYS_LED; 
extern uint  	POWER_LED; 
extern bit  	LOCK_LED; 
extern bit SYS_ON;     
extern bit LOCK_ON;        
extern uint POWER;

uint rst_rev;

uint __RAM * Ptr;
uint __ROM * Ptr2; 

void	initial		(void)
{
	WDTR	=	0x5A;

	P0M  	=	0xff;
	P0UR	=	0xFF;
	P0		=	0x00;
	P0OC	=	0x00;

	P1M  	=	0xff;
	P1UR	=	0xFF;
	P1		=	0x00;
	P1OC	=	0x00;

	P4M  	=	0x5f;
	P4UR	=	0x5F;
	P4		=	0x10;
	P4CON	=	0x20;		

	P5M  	=	0xff;
	P5UR	=	0xFF;
	P5		=	0x00;
	P5CON	=	0x00;

	L_outp = 0;
	M_outp = 0; 	
	H_outp = 0; 

	FGIE	=	0;
	FT0IEN	=	0;
	FT0ENB	=	0;

	T0M		=	0x00;
	T0C		=	100;

	FT0IEN	=	1;
	FT0IRQ	=	0;
	FT0ENB	=	1;
	FGIE	=	1;	

 	TC0M	=	0;		
	TC0M	=	0x30;	

	TC0C	=	156;	
	TC0R	=	156;	

	FTC0IRQ	=	0;		

	FTC0IEN=	1;		
	FTC0ENB	=	1;		

 	TC2M	=	0;		
	TC2M	=	0x30;	

	TC2C	=	236;	
	TC2R	=	236;

	FTC2IRQ	=	0;		

	FTC2IEN=	1;		
	FTC2ENB	=	1;		

	FADCIEN = 0;		

	ADM 	= 0xb5;		

	ADR 	= 0;		
	FADCIRQ	= 0;		

	FADCIEN = 1; 		
	FGIE	= 1; 		

	Ptr2 = (uint __ROM *)0x0A05;
	rst_rev	=	*Ptr2;
	if(rst_rev == 0x01)
	{
		rst_set();
	}
	else
	{
		Ptr2 = (uint __ROM *)0x0A01;
		t_cnt2	=	*Ptr2;
		Ptr2 = (uint __ROM *)0x0A03;
		t_cnt3	=	*Ptr2;
	}
}

