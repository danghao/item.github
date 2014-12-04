#include	"fun.h"

u8 nature_cnt;
u8    slp_cnt;
bit    sysbuf;
bit sys_3s_ok;
u8 	  num2_1s;
u8 	 speedbuf;
bit     swbuf;
bit  sw_on;

/****************************************************************************
 * \brief       输出控制函数
 *        		风量 ION SW MODE
 * \param       无
 * \return      无
 * *************************************************************************/
void fun (void)
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
					H_M_L_OUT(2);
					speedbuf = 2;
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
				Nature_Out(speed);
			}
			else if(mode == 3)
			{
			}
			else if(mode == 4)
			{
				if(speedbuf != speed)
				{
					speedbuf = speed;

					H_M_L_OUT(speed);

				}
			}
		}
		if(swbuf != sw_on)
		{
			swbuf = sw_on;
			if(!sw_on)		SW_OUT = 1;
			else		SW_OUT = 0;
		}
	}
	else
	{
		if(sysbuf != sys_on)
		{
			sysbuf = sys_on;
			H_M_L_OUT(0);
		}
	}
}

//***************************************************************************
//! \brief       函数 风量输出
//! \param       spd 风量的强弱 1 - 弱 2 - 中 3 - 强 其它值 - 无输出
//! \return      无
//***************************************************************************
void H_M_L_OUT(u8 spd)
{
//	H_OUT	=	1;
//	M_OUT	=	1;
//	L_OUT	=	1;
	switch(spd)
	{
		case 1 :
		{
//			L_OUT	=	0;
			break;
		}
		case 2 :
		{
//			M_OUT	=	0;
			break;
		}
		case 3 :
		{
//			H_OUT	=	0;
			break;
		}
		default :
		{
			;
		}
	}
}

//***************************************************************************
//! \brief       函数 自然风输出函数
//! \param       speed 设定的风量值
//! \return      无
//***************************************************************************
void Nature_Out(u8 spd_)
{
	if(f_1s)
	{
		f_1s = 0;
		num_1s++;
		if(num_1s == 25)
		{
			num_1s = 0;
			nature_cnt++;
			if(nature_cnt >= 32)	// 25s * 32 = 800s
			{
				nature_cnt = 0;
				slp_cnt ++;
				if(slp_cnt > 1)		// 多长时间睡眠模式风强度降一级
				{
					slp_cnt = 0;
					if(mode == 2 && spd_ > 1)
					{
						spd_ -= 1;
						////////////////////////////////////////time_speed_dsp(1);
					}
				}
			}
								if(spd_ == 3)
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
										H_M_L_OUT(3);
										break;
									}
									case 2 :
									case 8 :
									case 12 :
									case 24 :
									{
										H_M_L_OUT(2);
										break;
									}
									case 4 :
									case 17 :
									case 20 :
									case 30 :
									{
										H_M_L_OUT(1);
										break;
									}
									default : {}
								}
								else if(spd_ == 2)
								switch(nature_cnt)
								{
									case 4 :
									case 10 :
									case 15 :
									case 23 :
									{
										H_M_L_OUT(3);
										break;
									}
									case 0 :
									case 5 :
									case 12 :
									case 19 :
									case 24 :
									case 29 :
									{
										H_M_L_OUT(2);
										break;
									}
									case 2 :
									case 8 :
									case 17 :
									case 22 :
									case 27 :
									case 31 :
									{
										H_M_L_OUT(1);
										break;
									}
									default : {}
								}
								else if(spd_ == 1)			
								switch(nature_cnt)
								{
									case 6 :
									case 22 :
									{
										H_M_L_OUT(3);
										break;
									}
									case 2 :
									case 10 :
									case 14 :
									case 20 :
									case 27 :
									case 31 :
									{
										H_M_L_OUT(2);
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
										H_M_L_OUT(1);
										break;
									}
									default : {}
								}
		}
	}
}
