#include"user.h"

uchar	t0_num,t0_cnt;
uchar CHARGRA_PWM;
bit f_16ms;

void T0_Int_Handler(void) interrupt 13 using 1
{
	if(t0_cnt==0)
	{
		IO_B=0;
	}
	else if((t0_cnt<5)||((t0_cnt>15)&&(t0_cnt<20)))
	{
		IO_B=~IO_B;
		IO_C=~IO_C;
	}
	else if(t0_cnt==5 || t0_cnt==20)
	{
		IO_B=1;
		IO_C=1;
	}
	else if(t0_cnt==15)
	{
		IO_C=0;
	}
	if(t0_num==0)
	{
		IO_A=1;
	}
	if(t0_num==CHARGRA_PWM)
	{
		IO_A=0;				// duty CHARGR_PWM
	}
	t0_num++;
	if(t0_num == 91)	
	f_16ms = 1;
	else if(t0_num >= 100)		// period 160us*100=16ms
	{
		t0_num=0;
	}
	t0_cnt++;
	if(t0_cnt>=30)
	{
		t0_cnt=0;
	}
}