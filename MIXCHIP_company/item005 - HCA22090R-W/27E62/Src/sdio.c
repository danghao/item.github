//***************************************************************************
//!
//! \file    sdio.c
//! \brief   型号:HCA22090R(WiFi) MCU:27E62
//! \version V1.0
//! \author  D.H.
//! \date    2014-11-01
//! \email   danghao0815@163.com
//!
//***************************************************************************

#include	"sdio.h"

bit In_send;
bit tb_flag; 				
bit SDO_sta; 				
bit FFFC;
bit wx_ok;
bit f_h_l;
bit tb_in;
bit f200ms;	

u8 send_data_buf;
u8 num_cnt;
u8 num_buf;
u8 data_ptr;
u8 wx_byte;
u8 receive_byte;
u8 U_count;
u8 llcount_buf;
u8 hlcount_buf;
u8 wx_bit;
u8 bit_cnt;
u8 chksum_send;
u8 temp_x;
u8 send_data[13] = {0xa1,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
u8 receive_data[13];

//***************************************************************************
//! \brief       SD数据发送函数
//! \param       无
//! \return      无
//***************************************************************************
void Sd_Send (void)
{
	if(f_send)
	{
		f_send = 0;
 		if(In_send)	
		{
			num_cnt++;
			if(num_cnt == 1)			SDI = 0;
			else if(num_cnt==21)		SDI = 1; 
			else if(num_cnt > 21)	
			{
				if(f_h_l)
				{
					if((send_data_buf & 0x01) == 0x01)
					{
						SDI		=	1;
						f_h_l	=	0;
						send_data_buf	>>=	1;	
						bit_cnt	++;
					}
					else if(num_cnt == (num_buf+3))
					{
						SDI		=	1; 
						f_h_l	=	0;
						send_data_buf >>= 1;	
						bit_cnt ++;
					}
					if(bit_cnt == 8)
					{
						bit_cnt	=	0;
						data_ptr	++;
						if(data_ptr < 7) 
						{ 
							num_cnt = 21;
							send_data_buf	=	send_data[data_ptr];
							chksum_send		+=	send_data_buf;
						}
						else if(data_ptr < 8)
						{
							num_cnt=21;
							send_data_buf=chksum_send;
						}
						else
						{
							num_cnt=0; 
							In_send=0; 
							data_ptr=0;
							send_data[1] &= 0xf7;
						}
					}
				}
				else{SDI=0;	f_h_l=1; num_buf=num_cnt;}
			}
		}
	}
}

//***************************************************************************
//! \brief       SD数据接收函数
//! \param       无
//! \return      无
//***************************************************************************
void Sd_Receive (void)
{
	if(f125us)
	{
		f125us = 0;	
		if(!SDO)
		{  
			if(SDO_sta)	
			{  
				SDO_sta = 0; 
				hlcount_buf = U_count; 
				U_count = 0; 	
				if(tb_flag)
				{ 
					if(hlcount_buf < 3)			FFFC=1;
					else if(hlcount_buf > 3)	FFFC=0;
					else
					{
wx_init:				U_count=0;
						wx_bit=0;
						wx_byte=0;
						tb_flag=0;
						return;
					}
					receive_data[wx_byte] >>= 1;
					if(FFFC) receive_data[wx_byte] |= 0X80;
					wx_bit++;
					if(wx_bit == 8)	{wx_bit = 0; wx_byte ++;}
				} 
				else if(hlcount_buf > 35 && hlcount_buf < 45) { tb_flag=1; tb_in = 1; }
			} 
			else 
			{
				U_count++; 	
				if(U_count >= 40 && tb_in)
				{
					if(receive_data[0] == 0xa0)
					{
						send_data_buf = 0xa0;
						send_data[1] |= receive_data[1];
					}
					else if(receive_data[0] == 0xa1)
					{
						send_data_buf=0xa3;
						send_data[1] &= 0xc0;
						send_data[1] |= receive_data[1]&0x3f;
					}
						for(temp_x=2;temp_x<13;temp_x++)
						{
							send_data[temp_x] = receive_data[temp_x];
						}
						receive_byte = wx_byte;
						wx_byte = 0;
						tb_flag = 0;
						wx_ok = 1;
						tb_in = 0;
						In_send = 1;
						chksum_send = send_data_buf;
						data_ptr = 0;
				}
			}
		}
		else 
		{ 
			if(!SDO_sta) {  SDO_sta = 1; llcount_buf = U_count; U_count = 0;}
			else { U_count++; }
		}
	}
}
