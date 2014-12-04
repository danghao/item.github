#include"user.h"

extern	bit 	f2_10ms;
extern	bit		KEY_ON2;
extern	bit 	tx_en;
extern	bit 	RX_pack_ok;	 
extern	uchar	data_ctr[3];
extern	uchar 	xTx_Buffer[];
extern	uchar 	xRx_Buffer[6];	 // [0]读写 [1]位数 [2]按键标识  [3]键值  [4]修正值  [5]chk_sum
extern	uchar	xTx_Buffer[6];	 // [0]读写	[1]xxxx [2]按键标识  [3]键值  [4]修正值  [5]chk_sum
extern	uchar 	rTx_Ptr;
extern	uchar 	counter;
extern	uchar	no_ack_times;
extern	uchar	data_fa_times;

		uchar	t_dsp;
		uchar	power_dsp;
		uchar	model;
		uchar	hwrj;
		bit		SPEEKER_ON;
		bit		AUTO_ON;
		bit		SYS_ON;

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
	if(RX_pack_ok)
	{
		RX_pack_ok = 0;
		no_ack_times = 0;
		if(xRx_Buffer[5] == (xRx_Buffer[0]^xRx_Buffer[1]^xRx_Buffer[2]^xRx_Buffer[3]^xRx_Buffer[4]))	  // chk_sum 无误
		{
			data_fa_times = 0;
			switch(xRx_Buffer[0])
			{
				case 0x52 :	
				{// 数据接收误码判定
					if(((xRx_Buffer[2]&0x7f)==xTx_Buffer[2])&&((xRx_Buffer[3]&0x7f)==xTx_Buffer[3])) break;
					else	xTx_Buffer[4] = 0x02;
				} 
				case 0x91 :
				case 0x92 :
				case 0x93 :
				{// 数据发送误码重传
					tx_en = 1; rTx_Ptr = 0; counter	= 0; break;
				}
				case 0x80 :
				case 0x81 :
				case 0xA0 :
				case 0xA1 :
				{/******************** SYS_ON 如何界定 *********************/
					if((xRx_Buffer[2]&0x80)==0x80) SPEEKER_ON = 1;	else  SPEEKER_ON = 0;
					if((xRx_Buffer[2]&0x40)==0x40) AUTO_ON = 1;		else  AUTO_ON = 0;
					model =	(xRx_Buffer[2]&0x38)>>3;
					hwrj = (xRx_Buffer[2] & 0x07) - 1;
					power_dsp = xRx_Buffer[3];
					t_dsp = xRx_Buffer[4];
					break;
				}
				case 0x82 :
				case 0xA2 :
				{
					//////////////////////////////////////////////强度=E2////////////////////////////////////////////////////
					break;
				}
				case 0x83 : break;
				case 0x84 :
				{
					//////////////////////////////////////////////强度=E3////////////////////////////////////////////////////
					break;
				}
				default : {}
			}
		}
		else
		{
			data_fa_times++;
			if(data_fa_times<5)
			counter = 99; 
			else
			{
				//////////////////////////////////////////////////init 强度=E1/////////////////////////////////////////////////////
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
