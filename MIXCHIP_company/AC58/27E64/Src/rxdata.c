#include "rxdata.h"

bit RX_com_in;
bit RX_dat_in;

u8 RX_data[65];
u8 RX_ptr;
u8 RX_byte;
bit RX_pack_ok;
u16 RX_data_add;

u8 TX_data[65];

void Rx_Data(void)
{
	if(RX_ok)
	{
		RX_ok = 0;
		if(RX_com_in)
		{
			RX_ptr ++;
			RX_data[RX_ptr] = RX_buf;
			RX_data_add += RX_buf;	//chk sum
			if(RX_ptr > 10)
			{
				if(RX_data[6] == 0xE9 && RX_ptr == 11)		// 网络配置复位时 响应
				{
					// If_Ack = 1;
					RX_com_in = 0;
				}
				else if(RX_ptr == 15 && RX_data[6] == 0xEC)	// WiFi模块 状态改变，发送到控制器的命令
				{
					switch(RX_data[12])
					{
						case 0 :		// 设备进入配置状态
						{
							break;
						}
						case 1 :		// 设备进入连接AP状态
						{
							break;
						}
						case 2 :		// 已经连接到AP,可以本地控制
						{
							break;
						}
						case 3 :		// 已经正常连到云服务,可远程控制
						{
							break;
						}
						default :
						{
							;
						}
					}
					RX_com_in = 0;
				}
				else if(RX_ptr == 19 && RX_data[6] == 0xEE)	// WiFi模块 返回的当前网络时间值
				{
	/*
					RX_data[12] // 年低字节
					RX_data[13] // 年高字节
					RX_data[14] // 秒
					RX_data[15] // 分钟
					RX_data[16] // 小时
					RX_data[17] // 星期
					RX_data[18] // 日
					RX_data[19] // 月
	*/
					RX_com_in = 0;
	 			}
				else if(RX_ptr > 19)
				{
					RX_com_in = 0;
				}
			}
		}
		else if(RX_dat_in)
		{
			RX_ptr ++;
			RX_data[RX_ptr] = RX_buf;
			if(RX_ptr < 61)
			{
				RX_data_add += RX_buf;
			}
			else if(RX_ptr==62 && RX_data[61] == (1+~RX_data_add) && RX_data[62]==0x44)
			{
				// 一帧数据结束
				RX_dat_in = 0;
			}
			else if(RX_ptr > 62)
			{
				RX_dat_in = 0;
			}
		}
		else
		{
			if(RX_buf == 0xbb)
			{
				RX_data[0] = 0xbb;
				RX_ptr = 0;
				RX_dat_in = 1;
				RX_data_add = 0x0000;	//chk sum
			}
			else
			{
				RX_data[0] = RX_data[1];
				RX_data[1] = RX_data[2];
				RX_data[2] = RX_data[3];
				RX_data[3] = RX_buf;
				if(RX_data[3] == 0x5a && RX_data[2] == 0x5a && RX_data[1] == 0xa5 && RX_data[0] == 0xa5)
				{
					RX_ptr = 3;
					RX_com_in = 1;
					RX_data_add = 0xc0ad;	//chk sum
				}
			}
		}
	}
}
