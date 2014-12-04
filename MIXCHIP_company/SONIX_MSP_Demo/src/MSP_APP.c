/*******************************************************************************************************
File name:		MSP_APP.c
Author:			Lian_Jin
Email:			lian_jin@sonix.com.cn
Date：			2011/10/25
Description:	Byte Write,Byte Read;	Page Write,Page	Read
*******************************************************************************************************/

//------------------------------------------------------------------------------------------------------
#include	"User.h"
#include	"Msp_TX_RX.h"

#define	Wr_cmd	0XA0		//write command
#define	Rd_cmd	0XA1		//read command
#define	Addr1	0X05		//data1 address
#define	Addr2	0X00		//【注意】：Page Write 地址要适当，不然会出错
#define	Data1	0X58		// Addr2取00H、08H、10H、18H、20H即8的倍数，	
							// 24C01页写最多8Bytes
//------------------------------------------------------------------------------------------------------

/*******************************************************************************************************
功能描述：读写应用程序
【注意】：读写之间要有一定的延时（10ms）；
*******************************************************************************************************/
void	MSP_APP(void)
{
//------------------------------------------------------
//	Word Write and Word Read
//------------------------------------------------------

//	MSP_Byte_TX(Wr_cmd,Addr1,Data1);				 //TX_Command，TX_Address，TX_Data
//	MSP_Byte_RX(Wr_cmd,Addr1,Rd_cmd);				 //RX_Command1,RX_Data,RX_Command2

//------------------------------------------------------
//	Page Write and Page Read
//------------------------------------------------------

//	MSP_Page_TX(Wr_cmd,Addr2);						//TX_Command,TX_Address
	MSP_Page_RX(Wr_cmd,Addr2,Rd_cmd);				//TX_Command1,TX_Address,RX_Command2
}