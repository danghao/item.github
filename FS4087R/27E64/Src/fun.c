#include "fun.h"

bit f_1s;
u8 num2_1s;
u8 num3_1s;

bit sys_3s_ok;
u8	modebuf;
u8	speedbuf;
bit swbuf;
bit ionbuf;
bit sysbuf;
u8 nature_cnt;
u8 slp_cnt;
u8 testmode_slp;
u8 testmode_timer;

/****************************************************************************
 * \brief       输出控制函数
 *        		风量 ION SW MODE
 * \param       无
 * \return      无
 * *************************************************************************/
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
					H_L_M_out(8);
					speedbuf = 8;
				}
				else if(num2_1s == 3)
				{
					sys_3s_ok = 1;
					num2_1s = 0;
				}
			}
		}
		else
		{
			if(mode == 1 || mode == 2)
			{
				Nature_Out();
			}
			else if(mode == 3)
			{
			}
			else if(mode == 4)
			{
				if(speedbuf != speed)
				{
					speedbuf = speed;

					H_L_M_out(speed);

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
	else
	{
		if(sysbuf != sys_on)
		{
			sysbuf = sys_on;
			H_L_M_out(0);
		}
	}
}

/****************************************************************************
 * \brief       风量输出控制函数
 * \param       spd 风量的大小0 2~8 
 * \return      无
 * *************************************************************************/
void H_L_M_out(u8 spd)
{
 	LL_OUT = 1;
 	L_OUT = 1;
 	M_OUT = 1;
 	H_OUT = 1;
	if(spd <= 4)
	BT_OUT = 0;
	if(spd == 0)
	{
		SW_OUT	=	1;
		ION_OUT	=	1;
	}
	else
	{
		if(spd > 4)
		BT_OUT = 1;
		switch(spd)
		{
			case 1 :
			case 5 :
			{
			 	LL_OUT = 0;
				break;
			}
			case 2 :
			case 6 :
			{
			 	L_OUT = 0;
				break;
			}
			case 3 :
			case 7 :
			{
			 	M_OUT = 0;
				break;
			}
			case 4 :
			case 8 :
			{
			 	H_OUT = 0;
				break;
			}
			default : {}
		}
	}
}

/****************************************************************************
 * \brief       自然风输出函数
 * \param       无
 * \return      无
 * *************************************************************************/
void Nature_Out(void)
{
	if(f_1s)
	{
		f_1s = 0;
		num2_1s++;
		if(num2_1s == 25)
		{
			num2_1s = 0;
			nature_cnt++;
			if(nature_cnt >= 32)	// 25s * 32 = 800s
			{
				nature_cnt = 0;
				slp_cnt ++;
				if(slp_cnt > 1)	
				{
					slp_cnt = 0;
					if(mode == 2 && speed > 1)
					{
						speed -= 1;
						////////////////////////////////////////time_speed_dsp(1);
					}
				}
			}
				if(speed>6)
				switch(nature_cnt)
				{
					case 0 :
					case 6 :
					case 10 :
					case 15 :
					case 19 :
					case 22 :
					case 27 :
					{
						H_L_M_out(8);
						break;
					}
					case 2 :
					case 8 :
					case 12 :
					case 24 :
					{
						H_L_M_out(5);
						break;
					}
					case 4 :
					case 17 :
					case 20 :
					case 30 :
					{
						H_L_M_out(2);
						break;
					}
					default : {}
				}
				else if(speed>3)
				switch(nature_cnt)
				{
					case 4 :
					case 10 :
					case 15 :
					case 23 :
					{
						H_L_M_out(8);
						break;
					}
					case 0 :
					case 5 :
					case 12 :
					case 19 :
					case 24 :
					case 29 :
					{
						H_L_M_out(5);
						break;
					}
					case 2 :
					case 8 :
					case 17 :
					case 22 :
					case 27 :
					case 31 :
					{
						H_L_M_out(2);
						break;
					}
					default : {}
				}
				else if(!quiet)			
				switch(nature_cnt)
				{
					case 6 :
					case 22 :
					{
						H_L_M_out(8);
						break;
					}
					case 2 :
					case 10 :
					case 14 :
					case 20 :
					case 27 :
					case 31 :
					{
						H_L_M_out(5);
						break;
					}
					case 0 :
					case 4 :
					case 8 :
					case 12 :
					case 17 :
					case 24 :
					case 29 :
					{
						H_L_M_out(2);
						break;
					}
					default : {}
				}
		}
	}
}