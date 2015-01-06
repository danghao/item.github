#include	"sdio.h"

//***************************************************************************
//! \brief       向WiFi模块发送数据
//! \para        send_data[]  send_bytes  DO_data_ok = 1
//! \Call        250 us
//***************************************************************************

bit DO_data_ok;
u8  send_bytes;
u8  send_data[13];

bit f_h_l;
u8  send_data_buf;
u8  chksum_out;
u8  do1_cnt;
u8  do1_buf;
u8  DO_bit_cnt;
u8  data_out_ptr;

void Data_Out (void)
{
	if(DO_data_ok)	
	{
		do1_cnt ++;
		switch(do1_cnt)
		{
			case 1 :
			{
				DO = 0;
				send_data_buf = send_data[0];
				chksum_out = 0;
				break;
			}
			case 21 :
			{
				DO = 1;
				break;
			}
			default :
			{
				if(do1_cnt > 21)
				{
					if(f_h_l)
					{
						if((send_data_buf & 0x01) == 0x01)
						{
							DO		=	1;
							f_h_l	=	0;
							send_data_buf	>>=	1;	
							DO_bit_cnt	++;
						}
						else if(do1_cnt == (do1_buf + 3))
						{
							DO		=	1; 
							f_h_l	=	0;
							send_data_buf >>= 1;	
							DO_bit_cnt ++;
						}
						if(DO_bit_cnt == 8)
						{
							DO_bit_cnt	=	0;
							data_out_ptr ++;
							if(data_out_ptr < send_bytes)
							{
								do1_cnt = 21;
								chksum_out	+= send_data[data_out_ptr - 1];
								if(data_out_ptr < send_bytes - 1) 
								{ 
									send_data_buf = send_data[data_out_ptr];
								}
								else
								{
									send_data_buf = chksum_out;
								}
							}
							else
							{
								DO_data_ok = 0; 
								do1_cnt = 0; 
								data_out_ptr = 0;
							}
						}
					}
					else 
					{ 
						DO = 0;	
						f_h_l = 1; 
						do1_buf = do1_cnt;
					}
				}
			}
		}
	}
}

//***************************************************************************
//! \brief       接收WiFi模块传来的数据
//! \para        DI_data_ok  receive_byte  receive_data[]
//! \Call        125 us
//***************************************************************************

bit DI_data_ok;	
u8  receive_byte;
u8  receive_data[13];

bit DI_tb;
bit DI_sta;
bit BIT_di_chk;
u8  DI_count;
u8  L_count_buf;
u8  H_count_buf;
u8  DI_bit;
u8  DI_byte;

void Data_In (void)
{
	if(!DI)
	{  
		if(DI_sta)	// H to L
		{  
			DI_sta = 0; 
			H_count_buf = DI_count; 
			DI_count = 0; 	
		} 
		else 	// L
		{
			DI_count++; 	
		}
	}
	else // H
	{ 
		if(!DI_sta) // L to H
		{
			DI_sta = 1; 
			L_count_buf = DI_count; 
			DI_count = 0;
			if(DI_tb)
			{ 
				if(L_count_buf < 3)
				{
					BIT_di_chk = 1;
				}
				else if(L_count_buf >= 3)
				{
					BIT_di_chk = 0;
				}
				else
				{
L_Error:			DI_bit = 0;
					DI_byte = 0;
					DI_tb = 0;
					return;
				}
				receive_data[DI_byte] >>= 1;
				if(BIT_di_chk) receive_data[DI_byte] |= 0X80;
				DI_bit++;
				if(DI_bit == 8)
				{
					DI_bit = 0; 
					DI_byte ++;
				}
			} 
			else if(L_count_buf > 25 && L_count_buf < 45) 
			{ 
				DI_tb = 1; 
			}
		}
		else
		{
			DI_count++;
			if(DI_count >= 40 && DI_tb)	// 5 ms 超时
			{
				if(DI_bit == 0)
				{
					DI_data_ok = 1;
				}
				else
				{
					DI_bit = 0;
				}
				receive_byte = DI_byte;
				DI_byte = 0;
				DI_tb = 0;
			}
		}
	}
}
