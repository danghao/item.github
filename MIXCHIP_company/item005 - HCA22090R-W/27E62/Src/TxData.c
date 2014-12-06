//***************************************************************************
//!
//! \file    TxData.c
//! \brief   型号:HCA22090R(WiFi) MCU:27E62
//! \version V1.0
//! \author  D.H.
//! \date    2014-11-01
//! \email   danghao0815@163.com
//!
//***************************************************************************

#include	"txdata.h"

u8 TX_ptr;
u8 wx_num;
u16 TX_data_add;
u8 TX_product[20];			// 上传给模块的 型号缓存
u8 receive_data1_0_buf;
u8 receive_data1_1_buf;
u8 receive_data1_2_buf;
u8 receive_data1_3_buf;
u8 receive_data1_4_buf;
u8 receive_data1_5_buf;
u8 receive_data1_6_buf;
u8 receive_data1_7_buf;
u8 TX_bytes;
u8 TX_data[20];				// 上传给模块的 数据缓存
bit  TX_data_ok;
bit key_link;
bit TX__product;
u8 temp_0;
u8 temp_1;

//***************************************************************************
//! \brief       串口发送处理函数
//! \param       无
//! \return      无
//***************************************************************************
void TxData (void)
{
	if(f10ms)
	{
		f10ms = 0;
		if(TX_data_ok)
		{
 			TX_ptr++;
			if(TX_ptr - 4 == TX_bytes)	TX_ptr = 30;
			if(TX_ptr < (TX_bytes + 4) && TX_ptr > 3)
			{
				if(!TX__product)
				{
					UTXD = TX_data[TX_ptr-4];
					TX_data_add += TX_data[TX_ptr-4];
				}
				else
				{
					UTXD = TX_product[TX_ptr-4];
					TX_data_add += TX_product[TX_ptr-4];
				}
			}
			else if(TX_ptr == 1 || TX_ptr == 2)	UTXD = 0xaa;
			else if(TX_ptr == 3)	{UTXD = 0x0d; TX_data_add = 0x0d;}
			else if(TX_ptr == 30)	{UTXD = (TX_data_add & 0x00ff); }
			else if((TX_ptr == 31)||(TX_ptr == 32))	{UTXD = 0x55;}
			else if(TX_ptr == 33)
			{
				TX_data_ok = 0;		//上传完一组数据给模块 可设断点观察上传的数据
				if(TX__product)
				TX__product = 0;
			}
		}
	}
	if(wx_ok && !TX_data_ok)
	{
		if(receive_data[0] == 0xa1)
		{
			wx_num ++;
			switch(wx_num)
			{
				case 2 : 
				case 4 : 
				case 6 : 
				case 8 : 
				{
					if(f10ms_2)
					{
						f10ms_2 = 0;
						temp_0 ++;
					}
					if(temp_0 == 2)
					{
						temp_0 = 0;
						if(rx_again)
						{
							wx_num --;
							rx_again = 0;
							TX_data_ok = 1;
							TX_ptr = 0;
						}
					}
					else
					{
						wx_num --;
					}
					break;
				}
				case 1 :
				{
					if((receive_data[3] != receive_data1_4_buf)||(receive_data[4] != receive_data1_5_buf))
					{
						receive_data1_4_buf = receive_data[3];
						receive_data1_5_buf = receive_data[4];
						TX_data[0] = 0x55; 
						wx_num = 7;
						goto branch3; 
					}
					else if((receive_data[5] != receive_data1_6_buf)||(receive_data[6] != receive_data1_7_buf))
					{
						receive_data1_6_buf = receive_data[5];
						receive_data1_7_buf = receive_data[6];
						TX_data[0] = 0x55; 
						wx_num = 7;	
						goto branch3_2;
					}
					else if(receive_data[2] != receive_data1_3_buf)
					{
						receive_data1_3_buf = receive_data[2];
						send_data[2] = receive_data[2];
						TX_data[0] = 0x54;
						wx_num = 7;
						if((receive_data[1] & 0x0f) == 0x00)	goto branch1_1;
					}
					else if((receive_data[1] & 0x0f) != receive_data1_2_buf)
					{
						receive_data1_2_buf = receive_data[1]&0x0f;
						send_data[1] &= 0xf0;
						send_data[1] |= receive_data[1]&0x0f;
						TX_data[0] = 0x54;
						wx_num = 7;	
						if((receive_data[1] & 0x0f) != 0x00)	goto branch1;
						else									goto branch1_1;
					}
					else if((receive_data[1] & 0x70) != (receive_data1_0_buf + receive_data1_1_buf))
					{
						receive_data1_1_buf = receive_data[1]&0x30;
						receive_data1_0_buf = receive_data[1]&0x40;
						send_data[1] &= 0x8f;
						send_data[1] |= receive_data[1]&0x70;
						TX_data[0] = 0x53;
						wx_num = 7;
						goto branch2;
					}
					else if((!FP52)&&(!key_link))
					{
						if(TX_product_OK)
						{
							TX_product_OK	=	0;
							TX__product		=	1;
							TX_bytes 		=	12;
							TX_data_ok		=	1;
							TX_ptr			=	0;
							wx_num = 8;
						}
					}
					break;
				}
				case 3 :
				{
					TX_data[0] = 0xd3;

branch2:			if(receive_data1_1_buf == 0x00)		//f开显示c关显示9开机8关机
					{
						if(receive_data1_0_buf == 0x00)	//关机开显示
						{
							TX_data[1] = 0xf8; 
							TX_bytes = 2; 
							TX_data_ok = 1; 
							TX_ptr = 0;
						}
						else							//关机关显示
						{
							TX_data[1] = 0xc8; 
							TX_bytes = 2; 
							TX_data_ok = 1; 
							TX_ptr = 0;
						}
					}
					else if(receive_data1_1_buf == 0x20)
					{
						if(receive_data1_0_buf == 0x00)	//开机开显示
						{
							TX_data[1] = 0xf9; 
							TX_bytes = 2; 
							TX_data_ok = 1; 
							TX_ptr = 0;
						}
						else							//开机关显示
						{
							TX_data[1] = 0xc9; 
							TX_bytes = 2; 
							TX_data_ok = 1; 
							TX_ptr = 0;
						}
					}
					break;
				}
				case 5 : 
				{
					TX_data[0] = 0xd4;

branch1:			if(receive_data1_2_buf==0)
					goto branch1_1;
					TX_data[1] = 0xb1; 
					TX_data[2] = 0x03;
					TX_data[3] = receive_data1_2_buf;
					TX_bytes   = 4; 
					TX_data_ok = 1; 
					TX_ptr 	   = 0;
					break;

branch1_1:			TX_data[1] 	= 0xb0; 
					TX_data[2] 	= 0x03;
					TX_data[3] 	= 1+(receive_data1_3_buf & 0x03); 
					TX_bytes 	= 4; 
					TX_data_ok 	= 1; 
					TX_ptr 		= 0;
					break;
				}
				case 7 : 
				{
					TX_data[0] = 0xd5; 
					if((receive_data[1]&0x30) != 0x20)	goto branch3_2; 

branch3:			TX_data[1] = 0xd1;
					TX_data[2] = 0x40 | receive_data1_4_buf; 
					TX_data[3] = 0x80 | receive_data1_5_buf;; 
					TX_data[4] = 0xc0; 
					TX_data[5] = 0xC1;
					TX_data[6] = 0x40 | receive_data1_4_buf; 
					TX_data[7] = 0x80 | receive_data1_5_buf; 
					TX_data[8] = 0xc0; 
					TX_bytes = 9; 
					TX_data_ok = 1; 
					TX_ptr = 0;
					break;

branch3_2:			TX_data[1] = 0xe1;
					TX_data[2] = 0x40 | receive_data1_6_buf; 
					TX_data[3] = 0x80 | receive_data1_7_buf; 
					TX_data[4] = 0xc0; 
					TX_data[5] = 0xC1;
					TX_data[6] = 0x40 | receive_data1_6_buf; 
					TX_data[7] = 0x80 | receive_data1_7_buf; 
					TX_data[8] = 0xc0; 
					TX_bytes = 9; 
					TX_data_ok = 1; 
					TX_ptr = 0;
					break;
				}
				default : 
				{
f_default:			wx_ok = 0;
					wx_num = 0;
				}
			}
		}
		else if(receive_data[0] == 0xa0)		//型号
		{
			TX_product[0] = 0x52;
			for(TX_ptr = 1;TX_ptr < 12;TX_ptr ++)
			TX_product[TX_ptr] = receive_data[TX_ptr];
			wx_ok = 0;
		}
		else if(receive_data[0] == 0xa2)		//模拟按键；
		{
			key_link = 1;
			FP46 = 0;
			num_2 = 0;
			wx_ok = 0; 
		}
	}
}
