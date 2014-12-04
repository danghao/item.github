#include "user.h"

extern uchar Rx_Buffer;
extern uchar RX_OK;	 
extern uchar tx_data_en;	 
extern uchar rTx_Ptr;
uchar		f_1s;
uchar		f_10ms;
uchar		f_10s;
uchar		f2_10ms;
uchar	num_10ms;
uchar	num_1s;


void main(void)
{
	 //fmaster=fcpu=2MHz
   CLK_ECKR=0x00;
   CLK_ICKR=0x01;
   CLK_CMSR=0xe1;
 
   CLK_SWR=0xe1;
   CLK_CKDIVR=0x18;
	 
	init();
	while(1)
	{
		
//		UART1_DR = 0xaa;
		
		key();
		lcd();
		tx_pack();
		rx_pack();
		timer();
	}	
}

@far @interrupt void TIM2_UPD_IRQHandler(void)	// 10 ms
{
	TIM2_SR1 &=~(0x01);  //=0x0e; 清楚中断标志位
	f_10ms = 1;
	f2_10ms = 1;
	num_10ms ++;
	if(num_10ms == 100)
	{
		num_10ms = 0;
		f_1s = 1;
		num_1s++;
		if(num_1s == 10)
		{
			num_1s = 0;
			f_10s = 1;
		}	
	}
}

@far @interrupt void UART1_RX_IRQHandler (void)
{
   Rx_Buffer = UART1_DR; //Store the received byte in 
   RX_OK = 1;
}

@far @interrupt void UART1_TX_IRQHandler (void)
{
	UART1_CR2 &= ~0X40;
	tx_data_en = 1;
	rTx_Ptr++;
}
