#include"user.h"

uchar xRx_Buffer[6]; /* [0]读写	[1]位数	 [2]按键标识  [3]键值  [4]修正值  [5]chk_sum */
uchar Rx_Buffer;
uchar R_count;
uchar RX_ptr;
uchar no_ack_times;
uchar data_fa_times;
uchar counter;
bit f2_139us;
bit R_start;
bit RX_pack_ok;	 
bit RX_in;

void rx_pack(void)
{
	if(f2_139us)	 
	{
		f2_139us = 0;
		if(!R_start)
		{
			if(!RXD)	// IO口 0
			{  
				R_start	= 1;
				R_count = 0;
			}
		}
		else
		{
			R_count ++;
			switch(R_count)
			{
				case 1 : if(RXD) R_start = 0; break;
				case 4 : 
				case 7 : 
				case 10 : 
				case 13 : 
				case 16 : 
				case 19 : 
				case 22 : 
				case 25 : Rx_Buffer>>=1; if(RXD)Rx_Buffer |= 0x80; else Rx_Buffer &= 0x7f; break;
				case 28 : if(RXD)
						  {
							if(RX_in)
							{
								xRx_Buffer[RX_ptr-2] = Rx_Buffer;
								RX_ptr ++;
								if(RX_ptr > 7)
								{
									RX_ptr = 0;
									RX_in = 0;
									RX_pack_ok = 1;	 //接收成功 存于xRx_Buffer[6]：[0]读写 [1]位数 [2]按键标识 [3]键值 [4]修正值 [5]chk_sum
								}
							}
							else
							{
								if(Rx_Buffer == 0xaa)
								{
									RX_ptr ++;
									if(RX_ptr == 2)
									{
										RX_in = 1;
									}
								}
								else
								{
									RX_ptr = 0;
								/*	data_fa_times ++;
									if(data_fa_times<5)
									counter = 99; 
									else
									{
										////////////////////////////////////////////init 强度=E1////////////////////////////////////////////
									}  				*/
								}
							}
						  }
						  R_start = 0;
						  break;	
				default : {}
			}
		}
	}
}