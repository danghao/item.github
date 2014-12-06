#include"user.h"

uchar xTx_Buffer[6];   /* [0]��д	[1]xxx	 [2]������ʶ  [3]��ֵ  [4]����ֵ  [5]chk_sum */
uchar Tx_Buffer;
uchar T_count;
uchar rTx_Ptr;
bit tx_en;
bit f_139us;
bit tx_data_on;	 

void tx_pack(void)
{
	if(tx_en && !tx_data_on)	
	{
		switch(rTx_Ptr)
		{
			case 0 :
			case 1 : Tx_Buffer = 0xaa;					tx_data_on = 1;								break;	  // ��ʼ��
			case 3 : Tx_Buffer = 0x08;					tx_data_on = 1;	xTx_Buffer[1] ^= 0x08;		break;	  // λ�� 8
			case 2 :
			case 4 :
			case 5 :
			case 6 : Tx_Buffer = xTx_Buffer[rTx_Ptr-2];	tx_data_on = 1;	xTx_Buffer[1] ^= Tx_Buffer;	break;	  // ��Ч����λ4λ
			case 7 : Tx_Buffer = xTx_Buffer[1]; xTx_Buffer[6] = xTx_Buffer[1]; tx_data_on = 1; xTx_Buffer[1] = 0x00; break;	  // У�� - ����
			default :	rTx_Ptr = 0;  tx_en = 0;	 break;	  // һ֡���ݷ������
		}
	}
}