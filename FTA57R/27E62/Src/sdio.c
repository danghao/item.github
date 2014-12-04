#include	"sdio.h"

		bit f2_dt;
		bit f_2dt;
		u8 num_dt;
		u8 num_cnt;
		u8 num_buf;
		bit DI_sta;
		bit FFFC2;
		u8 U_count;
		u8 L_count_buf;
		u8 H_count_buf;
		bit tb_in;
		bit tb_flag2; 
		u8 DI_bit;
		u8 DI_byte;
		u8 receive_byte;
		bit In_send;
		bit f_h_l;
		u8 send_data_buf;
		u8 chksum_send;
		u8 bit_cnt;
		u8 data_ptr;
		bit wx_ok2;				// 接收完成Flag
		u8 send_data[13];		// 发送缓存
		u8 receive_data[13];	// 接收缓存

//***************************************************************************
//! \brief       向WiFi模块发送数据
//! \param       无
//! \return      无
//***************************************************************************
void send (void)
{
	if(f_2dt)
	{
		f_2dt = 0;
 		if(In_send)	
		{
			num_cnt++;
			if(num_cnt == 1)
			DO = 0;
			else if(num_cnt==21)
			DO = 1; 
			else if(num_cnt > 21)
			{
				if(f_h_l)
				{
					if((send_data_buf & 0x01) == 0x01)
					{
						DO		=	1;
						f_h_l	=	0;
						send_data_buf	>>=	1;	
						bit_cnt	++;
					}
					else if(num_cnt == (num_buf+3))
					{
						DO		=	1; 
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
							send_data_buf = chksum_send;
						}
						else
						{
							num_cnt = 0; 
							In_send = 0; 
							data_ptr = 0;
							send_data[1] &= 0xf7;
						}
					}
				}
				else 
				{ 
					DO=0;	
					f_h_l=1; 
					num_buf=num_cnt;
				}
			}
		}
	}
}

//***************************************************************************
//! \brief       接收WiFi模块传来的数据
//! \param       无
//! \return      无
//***************************************************************************
void receive (void)
{
	if(f2_dt)
	{
		f2_dt = 0;
		if(++num_dt == 2)
		{
			num_dt = 0;
			f_2dt = 1;
		}
		if(!DI)
		{  
			if(DI_sta)	// H to L
			{  
				DI_sta = 0; 
				H_count_buf = U_count; 
				U_count = 0; 	
			} 
			else 	// L
			{
				U_count++; 	
			}
		}
		else // H
		{ 
			if(!DI_sta) // L to H
			{
				DI_sta = 1; 
				L_count_buf = U_count; 
				U_count = 0;
				if(tb_flag2)
				{ 
					if(L_count_buf < 3)			FFFC2=1;
					else if(L_count_buf >= 3)	FFFC2=0;
					else
					{
L_Error:				U_count=0;
						DI_bit=0;
						DI_byte=0;
						tb_flag2=0;
						return;
					}
					receive_data[DI_byte] >>= 1;
					if(FFFC2) receive_data[DI_byte] |= 0X80;
					DI_bit++;
					if(DI_bit == 8)	{DI_bit = 0; DI_byte ++;}
				} 
				else if(L_count_buf > 25 && L_count_buf < 45) 
				{ 
					tb_flag2 = 1; 
					tb_in = 1; 
				}
			}
			else
			{
				U_count++;
				if(U_count >= 40 && tb_in)
				{
					if(DI_bit == 0 && DI_byte != 0)
					{
						receive_byte = DI_byte;
						DI_byte = 0;
						tb_flag2 = 0;
						wx_ok2 = 1;
						tb_in = 0;
					}
					else
					{
						goto L_Error;
					}
				}
			}
		}
	}
}
