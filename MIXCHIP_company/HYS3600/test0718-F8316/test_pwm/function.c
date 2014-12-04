/************PWM output************/
#include"user.h"
uchar 	CHARGR_PWM;
uchar 	CHARGR_PWM_buf;
uchar 	CHARGRA_PWM2;
extern uchar CHARGRA_PWM;
extern bit f_New_Packet;
extern uchar xRx_Buffer[];
uchar temp_1,temp_2;
			//xRx_Buffer[1]   xRx_Buffer[2]
			//[x000   0xxx] [ x0   xx  xxxx] 
			//[开关   模式] [语音 红外 幅度]

bit SYS_on_off = 1;	 //系统开关
bit SPK_on_off;	 //语音开关
bit SYS_on_off_buf = 1;	 //系统开关
bit SPK_on_off_buf;	 //语音开关
uchar HW_power;	 //红外档级	0 1 2 3

uint	num_16ms,num2_16ms,num3_16ms;
enum	MODEL_1{TN,CJ,HG,ZJ,GS,AM,ER1,ER2} model,model_buf;	 //模式

uchar	temp1=20,temp2=16,temp3=8,temp4=20,temp5=1,temp6=1;
bit up_dn;					// 0 up 1 dn
bit kp;	   					// 1 kp
//uchar code PWM_TABLE[]=
//{0,36,37,38,40,41,42,45,47,50,53,55,59,62,65,70,90};	
uchar code PWM_TABLE[]=
{0,24,26,28,30,32,35,38,40,42,44,47,52,62,75,90,90,55,58,61,64,67,70,73,76,79,82,85, 90,90};	
//											[15]									[28]

void pwm_output(void)
{
	num_16ms++;
	if(CHARGRA_PWM2 && SYS_on_off)
	switch(model)
	{
		case CJ:	 //0
		{
			if(num_16ms >= 55)
			{
				num_16ms = 0;
				CHARGRA_PWM = CHARGRA_PWM2;
			}
			else if(num_16ms == 10)	 // *((CHARGR_PWM/5)+1)
			{
				CHARGRA_PWM = 0;
			}
			break;
		}
		case TN:	 //1
		{
			if(!up_dn)
			{
				if(CHARGRA_PWM < 20)
				CHARGRA_PWM += 10;
				else if(CHARGRA_PWM<CHARGRA_PWM2)
				CHARGRA_PWM ++;
				else
				{
					num2_16ms = num_16ms*1.5;
					up_dn = 1;
					kp = 1;
				}
			}
			if(kp)
			{
				if(num2_16ms > 0)
				num2_16ms --;
				else 
				{
					kp = 0;
				}
			}
			if(up_dn && !kp)
			{
				
				if(CHARGRA_PWM%5 == 0 && CHARGRA_PWM > 0)
				CHARGRA_PWM -= 5;
				else if((CHARGRA_PWM%5))
				CHARGRA_PWM -= CHARGRA_PWM%5;
				else
				{
					up_dn = 0;
					num_16ms = 0;
				}
			}
			break;
		}
		case AM:	 //2
		{
			if(num3_16ms)
			{
				num3_16ms--;
			}
			else
			{
				if(!up_dn)
				{
					if(CHARGRA_PWM < temp1)
					CHARGRA_PWM = temp1;
					//else 
					else if(CHARGRA_PWM < CHARGRA_PWM2)	// &&(num_16ms & 0x01) 
					{
						if(CHARGRA_PWM+5 >= CHARGRA_PWM2)	// &&(num_16ms & 0x01) 
						{
							if((num_16ms%temp2==0))
							CHARGRA_PWM ++;
						}
						else if((num_16ms%temp3==0))
						CHARGRA_PWM ++;
					}
					else
					{
						up_dn = 1;
					}
				}
				if(up_dn)
				{
					
					if(CHARGRA_PWM > temp1)//	 && (num_16ms%2)
					{
						if(CHARGRA_PWM+5 >= CHARGRA_PWM2)	// &&(num_16ms & 0x01) 
						{
							if((num_16ms%temp2==0))
							CHARGRA_PWM --;
						}
						else if((num_16ms%temp3==0))
						CHARGRA_PWM --;
					}
					else if(CHARGRA_PWM > temp4)
					CHARGRA_PWM = temp4;
					else
					{
						up_dn = 0;
						num_16ms = 0;
						num2_16ms++;
						if(num2_16ms == 1)
						{
							temp1=CHARGRA_PWM2-10;
							temp2=2;
							temp3=1;
							temp4=CHARGRA_PWM2-12;
						}
						else if(num2_16ms == 101)
						{
							num2_16ms=0;
							temp1=20;
							temp2=16;
							temp3=8;
							temp4=0;
						}
						else if(num2_16ms%10 == 1)
						{
							CHARGRA_PWM=0;
							num3_16ms=10;
						}
					}
				}
			}
			break;
		}
		case HG:	 //3
		{
			if(!up_dn)
			{
				if(CHARGRA_PWM < 25)
				CHARGRA_PWM += 5;
				else if(CHARGRA_PWM < CHARGRA_PWM2)
				CHARGRA_PWM += 2;
				else
				{
					CHARGRA_PWM = CHARGRA_PWM2;
					num2_16ms = num_16ms*5 + 300;
					up_dn = 1;
					kp = 1;
				}
			}
			if(kp)
			{
				if(num2_16ms > 0)
				num2_16ms --;
				else 
				{
					kp = 0;
				}
			}
			if(up_dn && !kp)
			{
				
				if(CHARGRA_PWM > 28)
				CHARGRA_PWM -= 4;
				else if(CHARGRA_PWM > 25)
				CHARGRA_PWM = 25;
				else if(CHARGRA_PWM > 0)
				CHARGRA_PWM -= 5;
				else
				{
					up_dn = 0;
					num_16ms = 0;
				}
			}
			break;
		}
		case ZJ:	 //4
		{
			if(num3_16ms)
			{
				num3_16ms--;
			}
			else
			{
				if(!up_dn)
				{
					if(CHARGRA_PWM < temp1)
					CHARGRA_PWM = temp1;
					//else 
					else if(CHARGRA_PWM < CHARGRA_PWM2)	// &&(num_16ms & 0x01) 
					{
						if(CHARGRA_PWM+5 >= CHARGRA_PWM2)	// &&(num_16ms & 0x01) 
						{
							if((num_16ms%temp2==0))
							CHARGRA_PWM ++;
						}
						else if((num_16ms%temp3==0))
						CHARGRA_PWM ++;
					}
					else
					{
						up_dn = 1;
						if(num2_16ms < 1)
						num3_16ms=300;
					}
				}
				if(up_dn)
				{
					
					if(CHARGRA_PWM > temp1)//	 && (num_16ms%2)
					{
						if(CHARGRA_PWM+5 >= CHARGRA_PWM2)	// &&(num_16ms & 0x01) 
						{
							if((num_16ms%temp5==0))
							CHARGRA_PWM --;
						}
						else if((num_16ms%temp6==0))
						CHARGRA_PWM --;
					}
					else if(CHARGRA_PWM > temp4)
					CHARGRA_PWM = temp4;
					else
					{
						up_dn = 0;
						num_16ms = 0;
						num2_16ms++;
						if(num2_16ms == 1)
						{
							num3_16ms=50;
							temp1=CHARGRA_PWM2-10;
							temp2=2;
							temp3=1;
							temp4=CHARGRA_PWM2-12;
							temp5=2;
							temp6=1;
						}
						else if(num2_16ms == 19)
						{
							num2_16ms=0;
							CHARGRA_PWM=0;
							num3_16ms=50;
							temp1=20;
							temp2=16;
							temp3=8;
							temp4=0;
							temp5=1;
							temp6=1;
						}
						else if(num2_16ms%3 == 1)
						{
							CHARGRA_PWM=0;
							num3_16ms=5;
						}
					}
				}
			}
			break;
		}
		case GS:	 //5
		{
			if(!up_dn)
			{
				if(CHARGRA_PWM < 25)
				CHARGRA_PWM += 5;
				else if(CHARGRA_PWM < CHARGRA_PWM2)
				{
					if(num_16ms%10 == 0)
					CHARGRA_PWM ++;
				}
				else
				{
					CHARGRA_PWM = CHARGRA_PWM2;
					num2_16ms = num_16ms + 1000;
					up_dn = 1;
					kp = 1;
				}
			}
			if(kp)
			{
				if(num2_16ms > 0)
				num2_16ms --;
				else 
				{
					kp = 0;
				}
			}
			if(up_dn && !kp)
			{
				
				if(CHARGRA_PWM > 28)
				CHARGRA_PWM -= 4;
				else if(CHARGRA_PWM > 25)
				CHARGRA_PWM = 25;
				else if(CHARGRA_PWM > 0)
				CHARGRA_PWM -= 5;
				else
				{
					up_dn = 0;
					num_16ms = 0;
				}
			}
			break;
		}
		default:{}
	}
	else 
	{
		CHARGRA_PWM = 0;
	}
	if(f_New_Packet == 1)
	{
		if(xRx_Buffer[0]==0x18 && xRx_Buffer[3]==0x38)
		{
			temp_1 = xRx_Buffer[1];
			temp_2 = xRx_Buffer[2];
			f_New_Packet = 0;
			model = (enum MODEL_1)(temp_1&0x07);		 //模式
			CHARGR_PWM = temp_2&0x0F;	 //强度
			SYS_on_off = temp_1/0x80;	 //开关
			SPK_on_off = temp_2/0x80;	 //语音
			HW_power = (temp_2>>4)%4;	 //红外
				if(model_buf != model)
				{
					model_buf = model;
					CHARGRA_PWM = 0;
					num_16ms = 0;
					num2_16ms = 0;
					up_dn=0; 		//up
					kp = 0;
				}
				if(CHARGR_PWM != CHARGR_PWM_buf)
				{
					CHARGR_PWM_buf = CHARGR_PWM;
					CHARGRA_PWM2 = PWM_TABLE[CHARGR_PWM];
					CHARGRA_PWM = 0;
					num_16ms = 0;
					up_dn = 0; 		
					kp = 0;
				}
				if(SYS_on_off != SYS_on_off_buf)
				{
					SYS_on_off_buf = SYS_on_off;
		
				}
				if(SPK_on_off != SPK_on_off_buf)
				{
					SPK_on_off_buf = SPK_on_off;	
				}
		}
		f_New_Packet = 0;
	}
}