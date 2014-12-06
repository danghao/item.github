#include"user.h"

extern	uchar 	tx_en;
extern	uchar		xTx_Buffer[6];	 // [0]读写	[1]xxxx [2]按键标识  [3]键值  [4]修正值  [5]chk_sum
extern	uchar 	rTx_Ptr;
				uchar xRx_Buffer[6]; /* [0]读写	[1]位数	 [2]按键标识  [3]键值  [4]修正值  [5]chk_sum */
				uchar Rx_Buffer;
				uchar R_count;
				uchar RX_ptr;
				uchar no_ack_times;
				uchar data_fa_times;
				uchar counter;
				uchar f2_139us;
				uchar R_start;
				uchar RX_OK;	 
				uchar RX_pack_ok;	 
				uchar RX_in;
				uchar	t_dsp;
				uchar	power_dsp;
				uchar	model;
				uchar	hwrj;
				uchar	SPEEKER_ON;
				uchar	AUTO_ON;
				uchar	SYS_ON;
				uchar chk_sum;

void UART1_Init(void)
{
	UART1_CR2	&=	~0x08;	//使发送使能 TEN=1；
	UART1_CR2 &= 	~0x24;	//使接收使能 REN=1; RIEN=1;		
	
	UART1_CR1	=		0x00;	//设置M字长，8位数据位
	UART1_CR3	=		0x00;	//1位停止位
	
	UART1_BRR2=		0x00;	//00-0d:9600（fcpu=fmaster=2MHz)
	UART1_BRR1=		0x0d;	//00-1a:4800; 01-34:2400
	
	UART1_CR2	|=	0x48;	//使发送使能 TEN=1；TCIEN=1;
	UART1_CR2 |= 	0x24;	//使接收使能 REN=1; RIEN=1;
}

void rx_pack(void)
{
	if(RX_OK)
	{
		RX_OK = 0;
		if(RX_in)
		{
			xRx_Buffer[RX_ptr] = Rx_Buffer;
			chk_sum ^= Rx_Buffer;
			RX_ptr ++;
			if(RX_ptr > 5)
			{
				RX_ptr = 0;
				RX_in = 0;
				RX_pack_ok = 1;	 //接收成功 存于xRx_Buffer[6]：[0]读写 [1]位数 [2]按键标识 [3]键值 [4]修正值 [5]chk_sum
			}
		}
		else if(Rx_Buffer == 0xaa)
		{
			RX_ptr ++;
			if(RX_ptr == 2)
			{
				RX_in = 1;
				RX_ptr = 0;
				chk_sum= 0;
			}
		}
		else
		{
			RX_ptr = 0;
			/*data_fa_times ++;
			if(data_fa_times<5)
			counter = 99; 
			else
			{
				////////////////////////////////////////////init  E1////////////////////////////////////////////
			}  				*/
		}
	}
	if(RX_pack_ok)
	{
		RX_pack_ok = 0;
		no_ack_times = 0;
		if(chk_sum == 0)	  // chk_sum 无误
		{
			data_fa_times = 0;
			switch(xRx_Buffer[0])
			{
				case 0x52 :	
				{// 数据接收误码判定
					if(((xRx_Buffer[2]&0x7f)==xTx_Buffer[2])&&((xRx_Buffer[3]&0x7f)==xTx_Buffer[3])) break;
					else	xTx_Buffer[4] = 0x02;
				} 
				case 0x91 :
				case 0x92 :
				case 0x93 :
				{// 数据发送误码重传
					tx_en = 1; rTx_Ptr = 0; counter	= 0; break;
				}
				case 0x80 :
				case 0x81 :
				case 0xA0 :
				case 0xA1 :
				{/******************** SYS_ON 如何界定 *********************/
					if((xRx_Buffer[2]&0x80)==0x80) SPEEKER_ON = 1;	else  SPEEKER_ON = 0;
					if((xRx_Buffer[2]&0x40)==0x40) AUTO_ON = 1;		else  AUTO_ON = 0;
					model =	(xRx_Buffer[2]&0x38)>>3;
					hwrj = (xRx_Buffer[2] & 0x07) - 1;
					power_dsp = xRx_Buffer[3];
					t_dsp = xRx_Buffer[4];
					break;
				}
				case 0x82 :
				case 0xA2 :
				{
					//////////////////////////////////////////////强度=E2////////////////////////////////////////////////////
					break;
				}
				case 0x83 : break;
				case 0x84 :
				{
					//////////////////////////////////////////////强度=E3////////////////////////////////////////////////////
					break;
				}
				default : {}
			}
		}
		else
		{
			data_fa_times++;
			if(data_fa_times<5)
			counter = 99; 
			else
			{
				//////////////////////////////////////////////////init 强度=E1/////////////////////////////////////////////////////
			}		
		}
	}
}