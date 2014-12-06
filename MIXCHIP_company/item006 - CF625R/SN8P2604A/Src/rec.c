/**************************************************************
*    rec.c 
*    红外遥控功能
*    读取红外信号，得到有效按键值
**************************************************************/

#include "user.h"
#include <stdlib.h>

bit key_out;
bit L_key_in;
bit key_onf_in;
u8 L_key_num;
u8 key_num_ok;
u8 num_onf;
u8 num_onf2;

u8 num_10ms_cnt;			
bit tb_flag; 				
bit wx_sta; 				
bit FFFC;
u8 wx_data;
u8 wx_data1;
u8 wx_data2; 
u8 wx_count; 			
u8 llcount_buf;
u8 hlcount_buf;
u8 wx_bit; 			
u8 temp3;
u8 temp4;

/**************************************************************
*    rec() 函数声明
*    红外遥控检测
*    读取红外信号，并解码得出有效按键值
**************************************************************/
void rec(void)
{
	if(F_125us)
	{
		F_125us = 0;	
		if(!REC)			
		{  
			if(wx_sta)		
			{  
				wx_sta=0; 
				hlcount_buf=wx_count; 
				wx_count=0; 	
				if(tb_flag) 	
				{ 
					if(abs(llcount_buf/3-hlcount_buf)<=2)		
					{ 
						FFFC=0;
					}
					else if(abs(hlcount_buf/3-llcount_buf)<=2)	
					{ 
						FFFC=1;
					}
					else		
					{
loop2:
						wx_count=0;
						wx_bit=0;
						llcount_buf=0;
						hlcount_buf=0;
						tb_flag=0;
						wx_data1=0;
						wx_data2=0;
						return;
					}
					wx_data2<<=1;
					if(wx_data1&0x80)
					{
						wx_data2|=0X01;
					}
					wx_data1<<=1;
					if(FFFC)
					{
						wx_data1|=0X01;
					}
					if(++wx_bit==13)
					{
						tb_flag=0;
						wx_bit=0;
						wx_data2<<=1;
						if(wx_data1&0x80)
						{
							wx_data2 |= 0X01;
						}
						if((wx_data2 & 0x3f)==0x1f)
						{
							wx_data = wx_data1 & 0x7f;
							key_num_ok = 1;
							switch(wx_data)
							{
								case 0x01 :
								{
									L_key_num = 1; 
									break;
								}
								case 0x02 :
								{
									L_key_num = 4; 
									break;
								}
								case 0x04 :
								{
									L_key_num = 3; 
									break;
								}
								case 0x08 :
								{
									L_key_num = 5; 
									break;
								}
								case 0x10 :
								{
									L_key_num = 6; 
									break;
								}
								case 0x20 :
								{
									L_key_num = 7; 
									break;
								}
								case 0x43 :
								{
									L_key_num = 8; 
									break;
								}
								case 0x46 :
								{
									L_key_num = 2; 
									break;
								}
								default : {L_key_num = 0;}
							}
						}
					}
				} 
				else 
				{
					if((hlcount_buf>60)&&(hlcount_buf<90)&&(llcount_buf>2)&&(llcount_buf<20))
					tb_flag=1;
				}
			} 
			else 
			wx_count++; 				
		}
		else  //	REC = 1;
		{ 
			if(!wx_sta)
			{
				wx_sta=1;
				llcount_buf=wx_count;
				wx_count=0;
			}
			else
			{
				wx_count++;
			}
		}
	}
	L_key_process();
}

/**************************************************************
*    L_key_process() 函数声明
*    对读取的遥控按键值进行处理
*    得出有效的按键值，并传递给key()函数
**************************************************************/
void L_key_process(void)
{
	if(key_num_ok)
	{
		key_num_ok = 0;
		num_10ms_cnt = 0;
		if(key_out)
		{
			if(L_key_num != 0)
			{
				key_out = 0;
				if(L_key_num == 1)
				{	
					key_onf_in = 1;
				}
				else
				{
					L_key_in = 1;
					key_on = 1;	
					KeyFIFO = L_key_num; 
				}
			}
		}
	}
	if(f4_10ms)
	{
		f4_10ms = 0;
		if((L_key_in || key_onf_in) && key_out == 0)
		{
			num_10ms_cnt ++;
			if(num_10ms_cnt >= 20)	// 若连续200ms没有收到有效键值，则判定为 key_out
			{
				num_10ms_cnt = 0;
				key_out = 1;
			}
		}
		if(key_onf_in)
		{
			num_onf++;
			if(num_onf == 100)
			{
				num_onf = 0;
				num_onf2++;
				if(num_onf2 == 3)
				{
					num_onf2 = 0;
					key_on_3s = 1;	
					KeyFIFO = L_key_num; 
					key_onf_in = 0;
				}
			}
		}
	}
}
