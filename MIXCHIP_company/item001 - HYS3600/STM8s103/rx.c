#include"user.h"

extern	uchar 	tx_en;
extern	uchar		xTx_Buffer[6];	 // [0]��д	[1]xxxx [2]������ʶ  [3]��ֵ  [4]����ֵ  [5]chk_sum
extern	uchar 	rTx_Ptr;
				uchar xRx_Buffer[6]; /* [0]��д	[1]λ��	 [2]������ʶ  [3]��ֵ  [4]����ֵ  [5]chk_sum */
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
	UART1_CR2	&=	~0x08;	//ʹ����ʹ�� TEN=1��
	UART1_CR2 &= 	~0x24;	//ʹ����ʹ�� REN=1; RIEN=1;		
	
	UART1_CR1	=		0x00;	//����M�ֳ���8λ����λ
	UART1_CR3	=		0x00;	//1λֹͣλ
	
	UART1_BRR2=		0x00;	//00-0d:9600��fcpu=fmaster=2MHz)
	UART1_BRR1=		0x0d;	//00-1a:4800; 01-34:2400
	
	UART1_CR2	|=	0x48;	//ʹ����ʹ�� TEN=1��TCIEN=1;
	UART1_CR2 |= 	0x24;	//ʹ����ʹ�� REN=1; RIEN=1;
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
				RX_pack_ok = 1;	 //���ճɹ� ����xRx_Buffer[6]��[0]��д [1]λ�� [2]������ʶ [3]��ֵ [4]����ֵ [5]chk_sum
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
		if(chk_sum == 0)	  // chk_sum ����
		{
			data_fa_times = 0;
			switch(xRx_Buffer[0])
			{
				case 0x52 :	
				{// ���ݽ��������ж�
					if(((xRx_Buffer[2]&0x7f)==xTx_Buffer[2])&&((xRx_Buffer[3]&0x7f)==xTx_Buffer[3])) break;
					else	xTx_Buffer[4] = 0x02;
				} 
				case 0x91 :
				case 0x92 :
				case 0x93 :
				{// ���ݷ��������ش�
					tx_en = 1; rTx_Ptr = 0; counter	= 0; break;
				}
				case 0x80 :
				case 0x81 :
				case 0xA0 :
				case 0xA1 :
				{/******************** SYS_ON ��ν綨 *********************/
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
					//////////////////////////////////////////////ǿ��=E2////////////////////////////////////////////////////
					break;
				}
				case 0x83 : break;
				case 0x84 :
				{
					//////////////////////////////////////////////ǿ��=E3////////////////////////////////////////////////////
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
				//////////////////////////////////////////////////init ǿ��=E1/////////////////////////////////////////////////////
			}		
		}
	}
}