//***************************************************************************
//!
//! \file    main.c
//! \brief   型号:HCA22090R(WiFi) MCU:27E62
//! \version V1.0
//! \author  D.H.
//! \date    2014-11-01
//! \email   danghao0815@163.com
//!
//***************************************************************************

#include	"main.h"

#include	"init.h"
#include	"linkcheck.h"
#include	"rxdata.h"
#include	"sdio.h"
#include	"timeflag.h"
#include	"txdata.h"


bit  f125us;
bit  f025ms;
bit  bit_125us;
bit  f_send;
bit  RX_ok; 
bit  RX_in; 
bit  RX_pack_ok; 
bit  rx_again;
u8   RX_data[20];
u8   RX_ptr_buf;
u8   RX_ptr;
u16  RX_data_add;


//***************************************************************************
//! \brief       主函数
//***************************************************************************
void main (void)
{
	WDTR = 0x5A;
	SYS_Init();				//
	Wifi_Rest();			//
	while(1)
	{
		WDTR = 0x5A;
		LinkCheck ();		// WiFi连接断开 检测
		RxData ();		// 串口接收数据处理
		TxData ();		// 串口数据发送
		TimeFlag ();			// 时间标志位处理
		Sd_Send ();			// 与主机通信 发送处理函数
		Sd_Receive ();			// 与主机通信 接受处理函数
	}
}

//***************************************************************************
//! \brief       定时器T0中断函数
//***************************************************************************
void __interrupt [0x0B] isr_t0(void)
{
	FT0IRQ	=	0;
	T0C		=	200;
	f125us	=	1;
	bit_125us	=	~bit_125us;
	if(!bit_125us)
	{
		f_send	=	1;
		f025ms	=	1;
	}
}

//***************************************************************************
//! \brief       串口 rx 中断函数
//***************************************************************************
void __interrupt [0x13] uart_rx(void)
{
	FURXIRQ = 0;
	if(FUFMER)
	{
		FUFMER = 0;
	}
	else
	{
		RX_data[0] = URXD;
		if(RX_in)
		{
			RX_ptr ++;
			RX_data[RX_ptr] = RX_data[0];
			RX_data_add += RX_data[0];
			if(RX_data[0] == 0x55 && RX_ptr>4)
			{
				if(RX_data[RX_ptr-1] == 0x55)
				{
					RX_data_add -= 0xaa;
					if(((RX_data_add-RX_data[RX_ptr-2])&0x00ff) == RX_data[RX_ptr-2])
					{
						RX_ptr_buf = RX_ptr-2;
						RX_pack_ok = 1;
					}
					else if((RX_data_add & 0x00ff) == 0x55)
					{
						RX_ptr_buf = RX_ptr-1;
						RX_pack_ok = 1;
					}
					else
					{
						UTXD = 0xE1;
					}
					RX_data_add = 0;
					RX_in = 0;
					RX_ptr = 0;
				}
			}
			if(RX_ptr > 20)
			{
				RX_ptr = 0;
				RX_in = 0;
			}
		}
		else
		{
			if(RX_data[0] == 0xaa)
			{
				RX_ptr ++;
				RX_data[RX_ptr] = 0xaa;
				if(RX_ptr == 2)
				{
					RX_in = 1;
				}
			}
			else
			{
				RX_ptr = 0;
				if(RX_data[0] == 0xe1)
				rx_again = 1;
			}
		}
	}
}