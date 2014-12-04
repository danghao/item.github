#include	"sdio.h"

		bit f_dt;
		bit f_dt3;
		bit f_2dt;
		bit f1s;
		u8 T0CNT;
	    u8 num_10ms;
		u8 num_cnt;
		u8 num_buf;
		u8 temp_x;
						
		bit DI_sta;
		u8 U_count;
		u8 L_count_buf;
		u8 H_count_buf;
		bit FFFC2;
		bit tb_in;
		bit tb_flag2; 
		u8 DI_bit;
		u8 DI_byte;
		u8 receive_byte;
		bit wx_ok2;

		bit In_send;
		bit f_h_l;
		u8 send_data_buf;
		u8 chksum_send;
		u8 bit_cnt;
		u8 data_ptr;

		u8 send_data[13];	
		u8 receive_data[13];	

void send (void)
{
	if(f_dt3)
	{
		f_dt3 = 0;
		T0CNT++;
		if((T0CNT&0x01)==0x01)
		{
			f_2dt = 1;
		}
		else if((T0CNT&0x0f)==0x02)
		{
			f_2ms = 1;
		}
		else if(T0CNT == 0x50)
		{
			T0CNT = 0x00;
			f_10ms = 1;
			f2_10ms = 1;
			num_10ms++;
			if(num_10ms == 100)
			{
				num_10ms = 0;
				f1s = 1;
				f_1s = 1;
			}
		}
	}
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

void receive (void)
{
	if(f_dt)
	{
		f_dt = 0;
		f_dt3 = 1;
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
error:					U_count=0;
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
						goto error;
					}
				}
			}
		}
	}
}
