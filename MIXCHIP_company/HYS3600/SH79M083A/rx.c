#include"user.h"

uchar xRx_Buffer[6]; /* [0]��д	[1]λ��	 [2]������ʶ  [3]��ֵ  [4]����ֵ  [5]chk_sum */
uchar Rx_Buffer;
uchar R_count;
uchar RX_ptr;
uchar no_ack_times;
uchar data_fa_times;
uchar counter;
bit f2_139us;
bit R_start;
bit RX_OK;	 
bit RX_pack_ok;	 
bit RX_in;

void rx_pack(void)
{
	if(RX_OK)
	{
		RX_OK = 0;
		if(RX_in)
		{
			xRx_Buffer[RX_ptr-2] = Rx_Buffer;
			RX_ptr ++;
			if(RX_ptr > 7)
			{
				RX_ptr = 0;
				RX_in = 0;
				RX_pack_ok = 1;	 //���ճɹ� ����xRx_Buffer[6]��[0]��д [1]λ�� [2]������ʶ [3]��ֵ [4]����ֵ [5]chk_sum
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
					////////////////////////////////////////////init ǿ��=E1////////////////////////////////////////////
				}  				*/
			}
		}
	}

}