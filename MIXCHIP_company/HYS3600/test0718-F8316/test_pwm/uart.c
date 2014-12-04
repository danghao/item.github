#include"user.h"
uchar xRx_Buffer[]={0x00,0x00,0x00,0x00};

uchar rRx_Count = 2;
uchar rRx_Ptr;
uchar itemp;
bit f_In_Packet;
bit f_New_Packet;

	uchar xTx_Buffer[]={0x18,0xf7,0xf8,0x38};
	uchar rTx_Count = 2;
	uchar rTx_Ptr;

void Uart_Initialize(void)
{
    uchar		k;
    UARTCR1 = 	0x06;                
    UARTCR2 = 	0x6E;                 
    UARTCR3 = 	0x00;                   
    UARTBD  =	12;			// fx=1MHz BAUD_4800 208us
    UARTST  =	0x00;                    
    IE1		|=	0x18;		// -     -     -    (TX)  (RX)   I2C   Ex6   Ex5
	IE		|=	0x80;		//(EA)   -    ExG0  -     -     Ex12  Ex11  Ex10
	k		=	UARTDR;		// clear overrun error!
}

/********************接收***********************/

void Uart_Rx_Int_Handler(void) interrupt 9    using 1
{
	if((UARTST&0x07))						//判断是否有错误发生
	{										//若有错，复位并重新初始化
	    UARTST = 0x08;
	    Uart_Initialize();
        return;								
    }
	itemp = UARTDR;                         //读接收数据寄存器/识别接收到的数据
    if((itemp == 0x18))  //&&(f_In_Packet == 0)若为开始码，指针归零，新数据包标志 置1
    {   
		f_In_Packet=	1;                
		rRx_Ptr 	=	0;
    }
    else if((itemp == 0x38)&&(rRx_Ptr == 3))
	{										 //若为结束码且指针已指向结束码，则新数据包标志清0 接收结束
		f_In_Packet=	0;
		f_New_Packet=	1;
		LED = ~LED;
    }
	if(rRx_Ptr < 4)
	{
	    xRx_Buffer[rRx_Ptr] = itemp;      
		rRx_Ptr++;
	}
}

/********************发送***********************/

void Uart_Tx_Int_Handler(void) interrupt 10    using 1
{
	if(rTx_Count>0 && rTx_Ptr>0)					   
    {	
		UARTDR	=	xTx_Buffer[rTx_Ptr];	//发送数据 '**'
    	rTx_Count--;
		rTx_Ptr++;				   
    }
	else if(rTx_Ptr == 3)
	{
		UARTDR	=	xTx_Buffer[rTx_Ptr];	//发送结束校验码 '0x38'
		rTx_Ptr	=	0;
		rTx_Count=	2;
	}
}