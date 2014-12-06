//***************************************************************************
//!
//! \file    LinkCheck.c
//! \brief   型号:HCA22090R(WiFi) MCU:27E62
//! \version V1.0
//! \author  D.H.
//! \date    2014-11-01
//! \email   danghao0815@163.com
//!
//***************************************************************************

#include	"linkcheck.h"

#include	"delay.h"

	u8  num_0;
	u8 	num_1;
	u8  num_2;
	bit TX_product_OK;
	bit FP52_buf;
	bit kuaishan_in;


//***************************************************************************
//! \brief       WiFi连接状态检测函数
//! \param       无
//! \return      无
//***************************************************************************
void LinkCheck(void)
{
	if(FP52_buf != FP52)
	{
		FP52_buf = FP52;
		if(FP52)
		{
			In_send 		=	1;
			data_ptr 		=	0;
			send_data_buf	=	0xa3;
			chksum_send		=	0xa3;
			send_data[1]	&=	0x7F;
		}
		else
		{
			num_0			=	0;
			FP53			=	0;	

			In_send			=	1;
			data_ptr		=	0;
			send_data_buf	=	0xa3;
			chksum_send		=	0xa3;
			send_data[1]	|=	0x80;
		}
	}
	if(f2_50ms)
	{
		f2_50ms = 0;
		if(FP52)
		{
			num_0 ++;
			if(num_0 == 20)			num_0	=	0;
			if(num_0 == 0)			FP53	=	0;
			else if(num_0 == 5)		FP53	=	1;
		}
		if(key_link)
		{
			num_2 ++;
			if(num_2 == 5)
			{
				num_2		=	0;
				FP46 		=	1;
				key_link	=	0;
			}
		}
	}

	if(kuaishan)
	{
		if(f1_50ms)
		{
			f1_50ms = 0;
			num_1 ++;
			switch(num_1)
			{
				case 1 : 
				case 7 : 
				case 13 :   FP53 = 0; 
							break;
				case 19 : 	FP53 = 0; 
							kuaishan = 0; 
							kuaishan_in = 1; 
							break;
				case 4 : 
				case 10 : 
				case 16 : FP53 = 1; break;
				default : {}
			}
		}
		return;
	}
	else if(!kuaishan_in)
	{
		if(f_500ms)
		{
			f_500ms = 0;
			Delay_ms(5);
				UTXD = 0xaa;
			Delay_ms(5);
				UTXD = 0xaa;
			Delay_ms(5);
				UTXD = 0x01;
			Delay_ms(5);
				UTXD = 0x02;
			Delay_ms(5);
				UTXD = 0x03;
			Delay_ms(5);
				UTXD = 0x55;
			Delay_ms(5);
				UTXD = 0x55;
			Delay_ms(5);
		}
	}


}
