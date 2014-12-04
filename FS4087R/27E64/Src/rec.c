#include	"rec.h"

bit f_01ms;					

bit tb_flag; 				
bit wx_sta; 				
bit FFFC;
bit wx_ok;

u8 wx_data,wx_data1,wx_data2; 	
u8 wx_count; 			
u8 llcount_buf;
u8 hlcount_buf;
u8 wx_bit; 			
u8 temp3,temp4;

void rec(void)
{
	if(f_01ms)
	{
		f_01ms = 0;	
		if(!wx_ok)
		{
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
						if(++wx_bit==11)
						{
							tb_flag=0;
							wx_bit=0;
							if((wx_data2&0x07)==0x01)
							{
								wx_ok = 1;
								switch(wx_data1)
								{
									case 0x3f : KeyFIFO = 5; key_on = 1; break;
									case 0x3e : KeyFIFO = 1; key_on = 1; break;
									case 0x3b : KeyFIFO = 3; key_on = 1; break;
									case 0x19 : KeyFIFO = 5; key_on_3s = 1; break;
									default : {KeyFIFO = 0;}
								}
//								if(DSP_OFF && KeyFIFO!=0)
								{
									key_on = 0;
									key_on_3s=0;
							//		DSP_OFF	= 0;
							//		BUZZER1_ON = 1;
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
		else
		{
			temp3++;
			if(temp3 == 100)
			{
				temp4++;
				if(temp4 == 10)
				{
					temp4=0;
					wx_ok = 0;
				}
			}
		}
	}
}
