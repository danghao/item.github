#include "user.h"

bit sys_3s_ok;
bit water_3s_ok;
u8	modebuf;
u8	speedbuf;
bit swbuf;
bit ionbuf;
bit sysbuf;
bit HUMbuf;
bit HUM_in;
bit water_less;
u8 num2_1s;
u8 num3_1s;
u8 num4_1s;
u8 nature_cnt;
u8 slp_cnt;

void fun(void)
{
	if(sys_on)
	{
	 	if(sysbuf != sys_on)
		sysbuf = sys_on;
		if(!sys_3s_ok)
		{
			if(f_1s)
			{
				f_1s = 0;
				num2_1s++;
				if(num2_1s == 1)
				{
					BT_OUT = 0;
				 	L_OUT = 1;
				 	H_OUT = 1;
				 	M_OUT = 0;
					BT_OUT = 1;
					speedbuf = 4;
				}
				else if(num2_1s == 3)
				{
					sys_3s_ok = 1;
				}
			}
		}
		else
		{
			if(mode == 1 || mode == 2)
			{
				if(f2_1s)
				{
					f2_1s = 0;
					num4_1s++;
					if(num4_1s == 5)
					{
						num4_1s = 0;
						nature_cnt++;
						if(nature_cnt >= 17)
						{
							nature_cnt = 0;
							slp_cnt ++;
							if(slp_cnt > testmode_slp)	
							{
								slp_cnt = 0;
								if(mode == 2 && speed > 1)
								{
									speed -= 2;
									time_speed_dsp(1);
								}
							}
						}
					}
					if(speed>3)
					switch(nature_cnt)
					{
						case 0 :
						case 3 :
						case 5 :
						case 8 :
						case 10 :
						case 12 :
						case 15 :
						{
							H_L_M_out(5);
							break;
						}
						case 1 :
						case 4 :
						case 7 :
						case 11 :
						case 14 :
						{
							H_L_M_out(3);
							break;
						}
						case 2 :
						case 9 :
						case 16 :
						{
							H_L_M_out(1);
							break;
						}
						case 6 :
						case 13 :
						{
							BT_OUT = 0;
						 	L_OUT = 1;
						 	M_OUT = 1;
						 	H_OUT = 1;
							break;
						}
						default : {}
					}
					else if(speed>1)
					switch(nature_cnt)
					{
						case 2 :
						case 6 :
						case 9 :
						case 13 :
						{
							H_L_M_out(5);
							break;
						}
						case 0 :
						case 4 :
						case 8 :
						case 11 :
						case 15 :
						{
							H_L_M_out(3);
							break;
						}
						case 1 :
						case 5 :
						case 10 :
						case 12 :
						case 16 :
						{
							H_L_M_out(1);
							break;
						}
						case 3 :
						case 7 :
						case 14 :
						{
							BT_OUT = 0;
						 	L_OUT = 1;
						 	M_OUT = 1;
						 	H_OUT = 1;
							break;
						}
						default : {}
					}
					else				
					switch(nature_cnt)
					{
						case 5 :
						case 14 :
						{
							H_L_M_out(5);
							break;
						}
						case 0 :
						case 2 :
						case 7 :
						case 10 :
						case 12 :
						case 16 :
						{
							H_L_M_out(3);
							break;
						}
						case 1 :
						case 3 :
						case 6 :
						case 8 :
						case 15 :
						case 11 :
						{
							H_L_M_out(1);
							break;
						}
						case 4 :
						case 9 :
						case 13 :
						{
							BT_OUT = 0;
						 	L_OUT = 1;
						 	M_OUT = 1;
						 	H_OUT = 1;
							break;
						}
						default : {}
					}
				}
				if(mode ==2)
				{
				}
			}
			else if(speedbuf != speed && mode == 0)
			{
				speedbuf = speed;
				H_L_M_out(speed);
			}
		}
		if(HUMbuf != HUM)
		{
			HUMbuf = HUM;
			if(HUM)
			{
				HUM_in = 1;
			}
			else 
			{
				HUM_in = 0;
				num2_1s = 0;
				HUMbuf = 0;
				led_data[3] &= 0xfd;  // water_led 状态改变
				led_data_ok = 1;
				water_less = 0;
			}

		}
		if(HUM_in)
		{
			if(f_1s)
			{
				f_1s = 0;
				num2_1s++;
				if(!water_less)
				{
					if(num2_1s == 1)			HUM_OUT = 0;
					else if(num2_1s == 4) 		HUM_OUT = 1;
					else if(num2_1s == 6) 		HUM_OUT = 0;
					else if(num2_1s == 9) 		HUM_OUT = 1;
					else if(num2_1s == 11) 		{HUM_OUT = 0; num3_1s = 0;}
					else if(num2_1s > 11)
					{
						if(WATER_F)
						{
							num3_1s ++;
						}
						else
						{
							num3_1s = 0; 
						}
						if(num3_1s == 4)
						{
							num3_1s = 0;
							HUM_OUT = 1;
							water_less = 1;
						}
						if(num2_1s > 0xff)	num2_1s = 12;
					}
				}
				else
				{
					led_data[3] ^= 0x02;  // water_led 状态改变
					led_data_ok = 1;
				}
			}
		}
		if(swbuf != sw)
		{
			swbuf = sw;
			if(!sw)		SW_OUT = 1;
			else		SW_OUT = 0;
		}
		if(ionbuf != ion)
		{
			ionbuf = ion;
			if(!ion)	ION_OUT = 1;
			else 		ION_OUT = 0;
		}
	}
	else if(sysbuf != sys_on)
	{
	 	sysbuf = sys_on;
		BT_OUT	=	0;	// 1有效
	 	L_OUT	=	1;	// 0有效
	 	M_OUT	=	1;	// 0有效
	 	H_OUT	=	1;	// 0有效
	 	HUM_OUT	=	1;	// 0有效
	 	SW_OUT	=	1;	// 0有效
	 	ION_OUT	=	1;	// 0有效
	}
}

void H_L_M_out(u8 x)
{
	if(x<3)
	BT_OUT = 0;
	else
	BT_OUT = 1;
 	L_OUT = 1;
 	M_OUT = 1;
 	H_OUT = 1;
	switch(x)
	{
		case 0 :
		case 3 :
		{
		 	L_OUT = 0;
			break;
		}
		case 1 :
		case 4 :
		{
		 	M_OUT = 0;
			break;
		}
		case 2 :
		case 5 :
		{
		 	H_OUT = 0;
			break;
		}
		default : {}
	}
}
