//***************************************************************************
//!
//! \file    RxData.c
//! \brief   型号:HCA22090R(WiFi) MCU:27E62
//! \version V1.0
//! \author  D.H.
//! \date    2014-11-01
//! \email   danghao0815@163.com
//!
//***************************************************************************

#include	"rxdata.h"

	u8 temp;
	bit rx_ok_f;
	bit kuaishan;

//***************************************************************************
//! \brief       串口接收处理函数
//! \param       无
//! \return      无
//***************************************************************************
void RxData (void)
{
	if(RX_pack_ok)
	{
		RX_pack_ok = 0;
		if(RX_data[3] == 0x0d)						//用户码 if(RX_data[3] == 0x0D)	
		{
			switch(RX_data[4])
			{
				case 0xA3 :		//产品关机及显示信息  熄屏模式[7 6]  显示状态[5 4]  开关机按键[3 2 1]  工作状态[0]
				{ 
					if(RX_data[5] == 0xf0)				//开显示
					{
						send_data[1] &= 0xbf;
					}
					else if(RX_data[5] == 0xc0)			//关显示
					{
						send_data[1] |= 0x40;
					}
					else if(RX_data[5] == 0x08)			//关机  模式清零
					{
						send_data[1] 	&= 0xc0;
						send_data[2]	= 0x00;			//档位清零
						send_data[3] 	= 0x00;			//定时关机时间清零
						send_data[4] 	= 0x00;
						receive_data[3] 	= 0x00;			//定时关机时间清零
						receive_data[4] 	= 0x00;
					send_data[1] 	|= 0x08;
					}
					else if(RX_data[5] == 0x09)			//开机
					{
						send_data[1] &= 0xcf;
						send_data[1] |= 0x20;
						send_data[5] = 0x00;			//预约开机时间清零
						send_data[6] = 0x00;
						receive_data[5] = 0x00;			//预约开机时间清零
						receive_data[6] = 0x00;
					send_data[1] 	|= 0x08;
					}
					break;
				}
				case 0xA5 :
				{	
					if(RX_ptr_buf<=9)
					{
						if(RX_data[5]==0xD1)				//定时关机
						{
							send_data[3] = RX_data[6]&0x3f;
							send_data[4] = RX_data[7]&0x3f;
						}
						else if(RX_data[5]==0xe1)			//预约开机
						{
							send_data[5] = RX_data[6]&0x3f;
							send_data[6] = RX_data[7]&0x3f;
						}
					}
					else if(RX_ptr_buf <= 13) 
					{
						if(RX_data[5]==0xD1 || RX_data[9]==0xD2)		//定时关机
						{
							send_data[3] = RX_data[6]&0x3f;
							send_data[4] = RX_data[7]&0x3f;
						}
						else if(RX_data[5]==0xe1 || RX_data[9]==0xe2)	//预约开机
						{
							send_data[5] = RX_data[6]&0x3f;
							send_data[6] = RX_data[7]&0x3f;
						}
					}
					send_data[1] 	|= 0x08;
					break;
				}
				case 0xA4 :	//产品风类(模式)信息  风类种类[7~4]1011  当前风类(模式)[3~0] 0000标准 0001高温 0010中温 0011低温
				{
					if(RX_data[5] == 0xb0)					//设定档位
					{
						if(RX_data[6] == 0x01)
						{
							send_data[2] = RX_data[6] - 1;						
						}
						else if(RX_data[6] == 0x02)
						{
							send_data[2] = RX_data[6] - 1;						
						}
						else if(RX_data[6] == 0x03)
						{
							send_data[2] = RX_data[6] - 1;						
						}
						send_data[1] &= 0xf8;
					}
					else if(RX_data[5] == 0xb1)				//设定智能模式下的温度
					{
						if(RX_data[6] == 0x01)
						{
							send_data[2] = 3 - RX_data[6];						
						}
						else if(RX_data[6] == 0x02)
						{
							send_data[2] = 3 - RX_data[6];						
						}
						else if(RX_data[6] == 0x03)
						{
							send_data[2] = 3 - RX_data[6];						
						}
						send_data[1] &= 0xf8;
						send_data[1] |= (RX_data[6] & 0x07);
					}
					break;
				}
				default : {}
			}
			In_send			=	1;
			data_ptr		=	0;
			send_data_buf	=	0xa1;
			chksum_send 	=	0xa1;
		}
		else if(RX_data[3] == 0x01)
		{
			if(RX_data[4] == 0x02)
			kuaishan = 1;
		}
	}
}
