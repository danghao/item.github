#include"user.h"

uchar xTx_Buffer[6];   /* [0]读写	[1]xxx	 [2]按键标识  [3]键值  [4]修正值  [5]chk_sum */
uchar Tx_Buffer;
uchar T_count;
uchar rTx_Ptr;
uchar tx_en;
uchar f_139us;
uchar tx_data_en;	 

void tx_pack(void)
{
	if(tx_en && tx_data_en)	
	{
		tx_data_en = 0;
		switch(rTx_Ptr)
		{
			case 0 :
			case 1 :	Tx_Buffer = 0xaa;	  // 起始码
								break;
			case 3 : 	Tx_Buffer = 0x08;	  // 位数 8
								xTx_Buffer[1] ^= 0x08;
								break;
			case 2 :
			case 4 :
			case 5 :
			case 6 :	Tx_Buffer = xTx_Buffer[rTx_Ptr-2];	// 有效 数据位 4位
								xTx_Buffer[1] ^= Tx_Buffer;	
								break;
			case 7 : 	Tx_Buffer = xTx_Buffer[1]; 				  // 校验 - 异或和
								xTx_Buffer[6] = xTx_Buffer[1]; 
								xTx_Buffer[1] = 0x00; 
								break;
			default :	rTx_Ptr = 0;	  // 一帧数据发送完成
								tx_en = 0;
								break;
		}
	}
}