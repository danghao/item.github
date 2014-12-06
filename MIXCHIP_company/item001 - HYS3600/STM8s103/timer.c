#include"user.h"

extern	uchar 	f2_10ms;
extern	uchar		KEY_ON2;
extern	uchar 	tx_en;
extern	uchar 	RX_pack_ok;	 
extern	uchar		data_ctr[3];
extern	uchar 	xRx_Buffer[6];	 // [0]读写 [1]位数 [2]按键标识  [3]键值  [4]修正值  [5]chk_sum
extern	uchar		xTx_Buffer[6];	 // [0]读写	[1]xxxx [2]按键标识  [3]键值  [4]修正值  [5]chk_sum
extern	uchar 	rTx_Ptr;
extern	uchar 	counter;
extern	uchar		no_ack_times;
extern	uchar		data_fa_times;

extern	uchar		t_dsp;
extern	uchar		power_dsp;
extern	uchar		model;
extern	uchar		hwrj;
extern	uchar		SPEEKER_ON;
extern	uchar		AUTO_ON;
extern	uchar		SYS_ON;


void TIM2_Init(void)
{
  _asm("sim");       //sim是禁止中断
  TIM2_IER  = 0x00;  //禁止中断
 
  TIM2_EGR  =0x01;   // 允许产生更新标志
  TIM2_PSCR =0x01;   // 设置时钟分频 2M/2=1MHz---1us
  TIM2_ARRH = 0x27;  // 0x2710=10000;  每10ms复位一次定时器2
  TIM2_ARRL = 0x10;  // ARR自动装载值，每1us递减1          
 
  TIM2_CNTRH=0x00;   //初值
  TIM2_CNTRL=0x00;
 
  TIM2_CR1 |= 0x81;  //开启定时器
  TIM2_IER |= 0x01;  //允许中断 
  _asm("rim");       //rim使能中断
 
}

void timer(void)
{
	if(f2_10ms)
	{
		f2_10ms	= 0;
		counter	++;
		if(counter == 100)		 // 查询码	 
		{
			counter	= 0;
			xTx_Buffer[0] = 0x52;
			xTx_Buffer[2] = 0x01;
			xTx_Buffer[3] = 0x01;
			xTx_Buffer[4] = 0x55;
			tx_en = 1;
			rTx_Ptr = 0;
			no_ack_times ++;
			if(no_ack_times > 5) 
			{
				no_ack_times = 0;
				///////////////////////////////////////////////////init////////////////////////////////////////////////
			}
		}
	}
	if(KEY_ON2)
	{
		KEY_ON2	= 0;
		xTx_Buffer[0] = 0x57;
		xTx_Buffer[4] = 0x01;
		tx_en = 1;
		rTx_Ptr = 0;
		counter	= 0;
		if(((data_ctr[1]&0x80)>>7) != SPEEKER_ON)
		{
			xTx_Buffer[2] = 0x02;
			if(SPEEKER_ON)	  		xTx_Buffer[3] = 0x01;
			else 					xTx_Buffer[3] = 0x02;
		}
		else if(((data_ctr[0]&0x08)>>3) != AUTO_ON)
		{
			xTx_Buffer[2] = 0x04;
			if(AUTO_ON)	  			xTx_Buffer[3] = 0x01;
			else 					xTx_Buffer[3] = 0x07;
		}
		else if(((data_ctr[0]&0x80)>>7) != SYS_ON)
		{
			xTx_Buffer[2] = 0x01;
			if(SYS_ON)				xTx_Buffer[3] = 0x01;
			else 					xTx_Buffer[3] = 0x02;
		}
		else if(data_ctr[2] != t_dsp)
		{
			xTx_Buffer[2] = 0x03;
			xTx_Buffer[3] = data_ctr[2];
		}
		else if((data_ctr[1]&0x0f) != power_dsp)
		{
			xTx_Buffer[2] = 0x05;
			xTx_Buffer[3] = data_ctr[1]&0x0f;
		}
		else if((data_ctr[0]&0x07) != model)
		{
			xTx_Buffer[2] = 0x04;
			xTx_Buffer[3] = data_ctr[0]&0x07;
		}
		else if(((data_ctr[1]&0x30)>>4) != hwrj)
		{
			xTx_Buffer[2] = 0x06;
			xTx_Buffer[3] = ((data_ctr[1]&0x30)>>4) + 1;
		}
		else
		{
			tx_en = 0;
		}
	}
}
