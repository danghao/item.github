/*******************************************************************************************************
File name:		SIO.c
Author:			Lian_Jin
Email:			lian_jin@sonix.com.cn
Date：			2011/10/25
Description:
				串行输入输出模块，MCU与93C46通信；
				在指定位置，写入数据；再读取该数，并存入ReadBuf里；
【注意】：
				由于命令字不是8bit，而SIOB只有 8bit	，多出来的位要使用IO口模拟时序来实现发送，
				不要忘记I/O口在GPIO功能与SIO功能之间的切换。
*******************************************************************************************************/

//------------------------------------------------------------------------------------------------------

#include	"User.h"
#include	"SIO.h"

uint	ReadDataBuf_;
uint	_ReadDataBuf_;
uint	ReadDataBuf;
uint	ReadDataBuf_0;
uint	ReadDataBuf_1;
uint	ReadDataBuf_2;
bit		FirstOP;			//第一位操作数
uint	StartCommand;		//开始
uint	TransmitData;		//要发送的数据
uint	TransmitAddress;	//存放的地址
uint	ReadAddress;
uint	DisableCommand;
//------------------------------------------------------------------------------------------------------

/*******************************************************************************************************
程序名称：	Serial_Trs_Rec(void) 
程序功能：	串行输入输出
			Trs = Transmit    Rec = Receive
*******************************************************************************************************/
void	Serial_Trs_Rec(void)
{
//------------------------------------------------------------------------------------------------------
//	写允许 
//------------------------------------------------------------------------------------------------------
	FirstOP = 0;
	StartCommand = 0X60;			
	EW_EN_Or_DS(FirstOP ,StartCommand);

	FirstOP = 0;
	TransmitAddress = 0X8F;
	TransmitData = 0X11;
	SIO_WRITE(FirstOP,TransmitAddress,TransmitData);		//写入

	FirstOP =  1;
	ReadAddress = 0X0F;
	ReadDataBuf = SIO_READ(FirstOP,ReadAddress);			//读取
//------------------------------------------------------------------------------------------------------
//	全写验证
//------------------------------------------------------------------------------------------------------
	FirstOP =  1;
	ReadAddress = 0X05;
	ReadDataBuf_0 = SIO_READ(FirstOP,ReadAddress);			//先读取

	FirstOP = 0;
	TransmitAddress = 0X20;
	TransmitData = 0X22;
	WRAL(FirstOP,TransmitAddress,TransmitData);				

	FirstOP =  1;
	ReadAddress = 0X05;                     
	ReadDataBuf_1 = SIO_READ(FirstOP,ReadAddress);          //读取
//------------------------------------------------------------------------------------------------------
//	全擦出验证
//------------------------------------------------------------------------------------------------------	
	FirstOP = 0;
	StartCommand = 0X40;
	ERAL(FirstOP,StartCommand);								//全擦

	FirstOP =  1;
	ReadAddress = 0X0F;
	ReadDataBuf_2 = SIO_READ(FirstOP,ReadAddress);			//读取

//------------------------------------------------------------------------------------------------------
//	写禁止验证
//------------------------------------------------------------------------------------------------------
	FirstOP = 0 ;
	DisableCommand = 0X00;
	EW_EN_Or_DS(FirstOP,DisableCommand);//写禁止

	FirstOP = 0;
	TransmitAddress = 0X8F;
	TransmitData = 0X99;
	SIO_WRITE(FirstOP,TransmitAddress,TransmitData);		//写入 

	FirstOP =  1;
	ReadAddress = 0X0F;
	_ReadDataBuf_ = SIO_READ(FirstOP,ReadAddress);			//读取

}

/*******************************************************************************************************
程序名称：	void	EW_EN_Or_DS(bit FirstOP_Reg,uint StartCommand_Reg) 
程序功能：	写允许或写禁止, 					11：写允许   00：写禁止
			FirstOP_Reg: 第一位操作数			StartCommand_Reg: 开始命令
*******************************************************************************************************/
void	EW_EN_Or_DS(bit FirstOP_Reg,uint StartCommand_Reg)
{
	SCS = 1;

	SCK = 0;
	SDO = BEGIN_BIT;
	SCK = 1;
					
	SCK = 0;
	SDO = FirstOP_Reg;
	SCK = 1;
	SCK = 0;

	FSENB = 1;
	SIOB = StartCommand_Reg;
	FSTART = 1;												//传输完毕，FSTART由系统自动清零
	while(FSIOBZ);

	FSENB = 0;
	SCS = 0;
}
/*******************************************************************************************************
程序名称：	void	SIO_WRITE(bit FirstOP_Reg, uint TransmitAddress_Reg, uint TransmitData_Reg)
程序功能：	发送数据给93C46
			FirstOP_Reg ：第一个操作数       TransmitAddress_Reg：要写入的地址
			TransmitData_Reg：要写入的数据
*******************************************************************************************************/
void	SIO_WRITE(bit FirstOP_Reg,uint TransmitAddress_Reg,uint TransmitData_Reg)
{	
	ulong	i;
	SCS = 1;

	SCK = 0;
	SDO = BEGIN_BIT;
	SCK = 1;

	SCK = 0;
	SDO = FirstOP_Reg;
	SCK = 1;
	SCK = 0;

	FSENB = 1;
	SIOB = TransmitAddress_Reg;
	FSTART = 1;
	while(FSIOBZ);			

	SIOB = TransmitData_Reg;		//需要发送的数据
	FSTART = 1;
	while(FSIOBZ);					//等待MCU数据传输完毕
//------------------------------------------------------------------------------------------------------
	SCS = 0;						// 根据93C46时序
	SCS = 1;						// 必须有CS线低电平信号 93C46 才开始写入
			


//	while(!SDI);					如果有故障，使用while有可能导致看门狗溢出
	for(i=0;i<0X0D05;i++)			//检测93C46的DO位Busy/Ready状态,最长时间为5ms
	{
		if(SDI == 1)
		break;
	}

	SCS = 0;
	FSENB = 0;	
}
/*******************************************************************************************************
程序名称：	uint	SIO_READ(bit FirstOP_Reg,uint ReceiveAddress_Reg)
程序功能：	从93C46读取数据
			FirstOP_Reg：第一个操作数		ReceiveAddress_Reg：所读取的地址
*******************************************************************************************************/
uint	SIO_READ(bit FirstOP_Reg,uint ReceiveAddress_Reg)
{
	SCS = 1;	

	SCK = 0;
	SDO = BEGIN_BIT;
	SCK = 1;

	SCK = 0;
	SDO = FirstOP_Reg;
	SCK = 1;
	SCK = 0;

	FSENB = 1;
	SIOB = ReceiveAddress_Reg;
	FSTART = 1;
	while(FSIOBZ);
//-----------------------------------------------------------------------------------------------------
// 	送完读命令后，需要继续CLK，才会传数据
//-----------------------------------------------------------------------------------------------------
	FCPHA = 1;				//在下降沿读取数据
	FSTART = 1;
	while(FSIOBZ);

	FCPHA = 0;				//MCU在上升沿正确读取数据
	SCS = 0;
	FSENB = 0;

	return(SIOB);
}
/*******************************************************************************************************
程序名称：	uint	WRAL(bit FirstOP_Reg,uint ReceiveAddress_Reg)
程序功能：	从93C46读取数据
			FirstOP_Reg：第一个操作数		ReceiveAddress_Reg：所读取的地址
*******************************************************************************************************/
void	WRAL(bit FirstOP_Reg,uint StartCommand_Reg,uint TransmitData_Reg)
{
	ulong	i;	

	SCS = 1;

	SCK = 0;
	SDO = BEGIN_BIT;
	SCK = 1;

	SCK = 0;
	SDO = FirstOP_Reg;
	SCK = 1;
	SCK = 0;

	FSENB = 1;
	SIOB = StartCommand_Reg;
	FSTART = 1;
	while(FSIOBZ);			

	SIOB = TransmitData_Reg;
	FSTART = 1;	
	while(FSIOBZ);

	SCS = 0;			// 根据93C46时序
	SCS = 1;			// 必须有CS线低电平信号 93C46 才开始写入
			
 	for(i=0;i<0X0D05;i++)	//检测93C46的DO位Busy/Ready状态,最长时间为5ms
	{
		if(SDI == 1)
		break;
	}

	SCS = 0;
	FSENB = 0;	
}
/*******************************************************************************************************
程序名称：	uint	ERASE_AL(bit FirstOP_Reg,uint StartCommand_Reg)
程序功能：	从93C46读取数据
			FirstOP_Reg：第一个操作数		StartCommand_Reg：开始命令
*******************************************************************************************************/

void	ERAL(bit FirstOP_Reg,uint StartCommand_Reg)
{
	ulong	i;
	SCS = 1;

	SCK = 0;
	SDO = BEGIN_BIT;
	SCK = 1;
					
	SCK = 0;
	SDO = FirstOP_Reg;
	SCK = 1;
	SCK = 0;

	FSENB = 1;
	SIOB = StartCommand_Reg;
	FSTART = 1;					//传输完毕，FSTART由系统自动清零
	while(FSIOBZ);

	SCS = 0;
	SCS = 1;

	for(i=0;i<0X0D05;i++)	
	{
		if(SDI == 1)
		break;
	}

	FSENB = 0;
	SCS = 0;
}
