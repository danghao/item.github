/*******************************************************************************************************
File name:	EmbededASM_Main.c
Author:		Lian_Jin

Email:		lian_jin@sonix.com.cn
Description:
			SN8C 嵌汇编例程 ：
			1，嵌汇编RAM的调用；
			2，嵌汇编RAM BANK的切换；
			3，嵌汇编函数的调用；
			4，嵌汇编数组的调用；
_______________________________________________________________________________________________________
-------------------------------------------------------------------------------------------------------
			EXT_V00						Date: 2011/9/20

			Compiler Version：			V141
_______________________________________________________________________________________________________
-------------------------------------------------------------------------------------------------------
Copyright (C) 2008
Sonix RomConverter - Version 2.00.001
----------------------------------------
EPROM Check Sum   : 17750 [0x4556] 
Security Check Sum: 9157 [0x23C5] 
----------------------------------------
Rom total size : 4092 [0xFFC] words
Rom has  used  : 142 [0x8E] words			[composed by: all segments size]
Rom Remains    : 3950 [0xF6E] words
---------------------------------------
Ram total size    : 256 [0x100] bytes
RamBank0 has used :  19 [0x13 ] bytes			[composed by: Ram hole + all data segments size]
RamBank0 remains  : 109 [0x6d ] bytes
RamBank1 has used :   1 [0x01 ] bytes			[composed by: Ram hole + all data segments size]
RamBank1 remains  : 127 [0x7f ] bytes
---------------------------------------
--------------------------------------------------------------------------------------------------------
*******************************************************************************************************/

//------------------------------------------------------------------------------------------------------
#include	<SN8P2708A.h>
#include	"Other.h"

#define		uint	unsigned int	
#define		uchar	unsigned char	
#define		ulong	unsigned long 	

uint	Data1;
uint	Data2;
uint	AddResult;
uint	NewAddResult;
uint	table_1;
uint	table_2;

uint	table[3] = {0X01,0X03,0X05};

extern void DelayTime_New(void);

#pragma  rambank  1
uint	 AddResultBank1;
#pragma  rambank off

void	DelayTime(void);
void	Premain(void);
//-----------------------------------------------------------------------------------------------------

/*******************************************************************************************************
*****************************************主  程  序*****************************************************
*******************************************************************************************************/
void	main(void)
{
	Premain();
	
	while(1)
	{
		WDTR = 0X5A;
		__asm
		{

//调用C变量时可用“_”加变量来调用全局变量，用CNameToAsmLabel来调用全局变量或局部变量		
		
			MOV		A,CNameToAsmLabel(Data1)			
			MOV		CNameToAsmLabel(AddResult),A			
			MOV		A,CNameToAsmLabel(Data2)
			ADD		CNameToAsmLabel(AddResult),A		
		
			MOV		A,CNameToAsmLabel(AddResult)		// Data1 + Data2 => AddResult;

			SelectBank(AddResultBank1);					// Bank0 --> Bank1;
			MOV		CNameToAsmLabel(AddResultBank1),A

	
		  	CALLTREE	_main invoke _DelayTime			//调用DelayTime()的格式,暂时不支持有参函数的调用
		    CALL	CNameToAsmLabel(DelayTime)
		
			CALLTREE	_main invoke _DelayTime_New		//调用Other.c文件中的函数，需要如下声明
		    CALL	CNameToAsmLabel(DelayTime_New)      // 即：extern void DelayTime_New(void)
		
			MOV 	A,_table             		   	//调用数组的第一个元素
			MOV		_table_1,A
	        MOV 	A,_table+1                			//调用数组的第二个元素
			MOV		_table_2,A	

	   	}		
	}	
}
/*******************************************************************************************************
		系统寄存器预设
*******************************************************************************************************/
void	Premain(void)
{
		Data1 = 0X32;
		Data2 = 0X7A; 
}
/*******************************************************************************************************
子 程 序：	void	DelayTime(void)
程序功能：	起到被调用的作用
*******************************************************************************************************/
void	DelayTime(void)
{
	uint	i,j;
	for(i=0;i<20;i++)
		for(j=0;j<30;j++);
}


