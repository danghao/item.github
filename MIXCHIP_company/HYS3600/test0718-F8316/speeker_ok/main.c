#include		"MC96F8316.h"
#define uint	unsigned int
#define uchar	unsigned char
#define BUSY 	P25	  //in
#define DATA 	P34	  //out
#define CLK 	P35	  //out
uint	xdata	Ctrl_buf[]	={	0xFE01,	//欢迎使用颈椎、腰椎治疗仪！请选择治疗时间
									0xFD02,	//欢迎使用好一生颈椎、腰椎治疗仪！请选择治疗时间
									0xFC03,	//5分钟，腰椎治疗已选择，请选择治疗方案
									0xFB04,	//20分钟，腰椎治疗已选择，请选择治疗方案
									0xFA05,	//25分钟，腰椎治疗已选择，请选择治疗方案
									0xF906,	//30分钟，腰椎治疗已选择，请选择治疗方案
									0xF807,	//15分钟，阿是治疗已选择，请选择治疗方案
									0xF708,	//20分钟，阿是治疗已选择，请选择治疗方案
									0xF609,	//25分钟，阿是治疗已选择，请选择治疗方案
									0xF50A,	//30分钟，阿是治疗已选择，请选择治疗方案
									0xF40B,	//自动开启，请调节治疗强度。
									0xF30C,	//针灸，请调节治疗强度。
									0xF20D,	//刮痧，请调节治疗强度。
									0xF10E,	//火罐，请调节治疗强度。
									0xF00F,	//推拿，请调节治疗强度。
									0xEF10,	//按摩，请调节治疗强度。
									0xEE11,	//捶击，请调节治疗强度。
									0xED12,	//红外热灸低温
									0xEC13,	//红外热灸低温、超长波开启
									0xEB14,	//红外热灸中温
									0xEA15,	//红外热灸高温，请谨慎调节温度以免烫伤皮肤。
									0xE916,	//红外热灸关闭
									0xE817,	//红外热灸、超长波关闭
									0xE718,	//语音开启
									0xE619,	//语音关闭
									0xE51A,	//请确认电极是否正确放置
									0xE41B,	//请确认仰卧方式是否正确
									0xE31C,	//线路异常，智能检修中
									0xE21D,	//智能检修结束，可以正常使用
									0xE11E,	//线路异常，已关闭
									0xE01F,	//线路异常，请关闭电源
									0xDF20,	//温度高，请确认
									0xDE21,	//高温异常，请关闭电源
									0xDD22,	//治疗中请勿接入电极
									0xDC23,	//请确认手控器是否正确连接
									0xDB24,	//治疗已结束，谢谢使用
									0xDA25,	//欢迎使用颈椎、腰椎治疗仪！自检中，请等待
									0xD926,	//欢迎使用好一生颈椎、腰椎治疗仪！自检中，请等待
									0xD827,	//自检已完成，请选择治疗时间
									0xD728,	//强度1
									0xD629,	//强度2
									0xD52A,	//强度3
									0xD42B,	//强度4
									0xD32C,	//强度5
									0xD22D,	//强度6
									0xD12E,	//强度7
									0xD02F,	//强度8
									0xCF30,	//强度9
									0xCE31,	//强度10
									0xCD32,	//强度11
									0xCC33,	//强度12
									0xCB34,	//强度13
									0xCA35,	//强度14
									0xC936,	//强度15
									0xC837,	//嘟（短音）
									0xC738,	//嘟（长音）
									0xC639	//嘟嘟
									};
uchar	j_static	=	0;
uint	ctr_buf		=	0xFFF1;
uchar	i_static;
uchar	clk_num;
uchar	num_1s;
uint	num_500us;

bit		f_1s		=	0;
bit		start_on	=	0;
bit 	stop_on		=	0;
bit 	start		=	0;
bit		wr_in		=	0;
bit 	f_500us		=	0;
void write_speak(void)	/*调用时 wr_in=1;ctr_buf=Ctrl_buf[*]*/
{
	if(wr_in)			
	{
		if(stop_on)
		{
			i_static++;
			if(i_static == 4)
			{
				i_static=0;
				CLK=1;
				wr_in=0;
				stop_on=0;
				start=0;
			}
		}
		else if(!start_on && start)
		{
			clk_num++;
			if(clk_num<31)
			{
				if(clk_num%2 == 1)
				{
					CLK=0;
		 			if(ctr_buf & 0x8000)	 
					DATA=1;
					else
					DATA=0;
					ctr_buf<<=1;
				}
				else
				{
					CLK=1;
				}
			}
			else if(clk_num == 31)
			{
				CLK=0;
				stop_on=1;
			}
		}
		else if(start_on)
		{
			i_static++;
			if(i_static == 20)
			{
				i_static=0;
				start_on=0;
				start=1;
				CLK=1;
			}
		}
		else if(!start)
		{
 			if(ctr_buf & 0x8000)	 
				DATA=1;
			else
				DATA=0;
			ctr_buf<<=1;
			CLK=0;
			start_on=1;
		}
	}
}

void main()
{
	P2IO    &=	~0x20;		// in
	P3IO    |=	0x30;		// out
	CLK=1;
	DATA=1;
	T0CR	=	0x80;
	T0CR	|=	0x03;		//Fx/4->4us
	T0DR	=	0x83;		//4us*125=500us  125/0.95372=131
    IE2     = 	0x02;		//T0	en
    EA      = 	1;
	while(1)
	{
		if(f_500us)
		{
			f_500us=0;
			write_speak();
		}
		if(f_1s)	// 3s
		{
			f_1s=0;
			num_1s++;
			if(num_1s == 5)
			{
				num_1s=0;
				j_static += 1;
				if(j_static == 57)
				j_static = 0;
				ctr_buf=Ctrl_buf[j_static];
				wr_in=1;
			}
		}
	}
}
void T0_Int_Handler(void) interrupt 13 using 1
{
	f_500us		=	1;
	num_500us++;
	if(num_500us == 2000)  // 1s
	{
		num_500us	=	0;
		f_1s=1;
	}
}
