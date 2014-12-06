#include"user.h"

uchar xTx_Buffer[6];   /* [0]读写	[1]xxx	 [2]按键标识  [3]键值  [4]修正值  [5]chk_sum */
uchar Tx_Buffer;
uchar T_count;
uchar rTx_Ptr;
bit tx_en;
bit T_start;
bit f_139us;
bit tx_data_on;	 

void tx_pack(void)
{
	if(f_139us)
	{
		f_139us = 0;
		if(tx_data_on)	/* 发送一帧数据前 tx_en = 1;   rTx_Ptr = 0;   xTx_Buffer[]; */
		{
			if(T_start) 
			{
				T_count++;
				if(T_count%3 == 0 && T_count<25)
				{
					if(Tx_Buffer & 0x01)
					TXD =	1;
					else 
					TXD =	0;
					Tx_Buffer>>=1;
				}
				else if(T_count == 27)
				{
					TXD 	=	1;
				}
				else if(T_count == 38)	  // 8ms 发出1个字节
				{
					T_count =	0;
					T_start = 0;
					tx_data_on = 0;
					rTx_Ptr++;
				}
			}
			else
			{
				TXD		=	0;
				T_start =	1;
				T_count =	0;
			}
		}
		if(tx_en && !tx_data_on)	
		{
			switch(rTx_Ptr)
			{
				case 0 :
				case 1 : Tx_Buffer = 0xaa;					tx_data_on = 1;								break;	  // 起始码
				case 3 : Tx_Buffer = 0x08;					tx_data_on = 1;	xTx_Buffer[1] ^= 0x08;		break;	  // 位数 8
				case 2 :
				case 4 :
				case 5 :
				case 6 : Tx_Buffer = xTx_Buffer[rTx_Ptr-2];	tx_data_on = 1;	xTx_Buffer[1] ^= Tx_Buffer;	break;	  // 有效数据位4位
				case 7 : Tx_Buffer = xTx_Buffer[1]; xTx_Buffer[6] = xTx_Buffer[1]; tx_data_on = 1; xTx_Buffer[1] = 0x00; break;	  // 校验 - 异或和
				default :	rTx_Ptr = 0;  tx_en = 0;	 break;	  // 一帧数据发送完成
			}
		}
	}
}