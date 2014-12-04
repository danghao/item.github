#include	"led.h"

#include	"delay.h"

u8 led_data[4] = {0xda,0x81};
bit led_data_ok = 1;
u8 temp2;
u8 led_cnt;
u8 LED_CODE[12] = { 0xeb,0x81,0xda,0xd9,0xb1,0x79,0x7b,0xc1,0xfb,0xf9 };  // 0~9 
bit	undis_ok;

//***************************************************************************
//! \brief       led显示函数
//! \param       无
//! \return      无
//***************************************************************************
void led(void)
{
	if(led_data_ok && !un_display)	// 如果led显示缓存更新完成，且不在熄屏状态
	{
		led_cnt ++;
		switch(led_cnt)
		{
			case 1 :
			{
				led_wr(0xc0);		// 更新 led0
				led_wrDATA(led_data[0]);
				break;
			}
			case 2 :
			{
				led_wr(0xc2);		// 更新 led1
				led_wrDATA(led_data[1]);
				break;
			}
			case 3 :
			{
				led_wr(0xc8);		// 更新 led2 SW RHY SLP
				led_wrDATA(led_data[2]);
				break;
			}
			case 4 :
			{
				led_wr(0xca);		// 更新 led3 ECO TIMER
				led_wrDATA(led_data[3]);
				break;
			}
			default :	// led显示更新完成，cnt归零
			{
				led_cnt = 0;
				led_data_ok = 0;	// 关 入口标志位
			}
		}
	}
	else if(un_display && !undis_ok)	// 否则，如果熄屏状态，且还没有执行熄屏
	{
//		__asm("nop")
		led_wr(0xc0);	led_wrDATA(0);
		led_wr(0xc2);	led_wrDATA(0);
		led_wr(0xc8);	led_wrDATA(0);
		led_wr(0xca);	led_wrDATA(0);
//		__asm("nop")
		undis_ok = 1;	// 熄屏成功标志位
	}
}

//***************************************************************************
//! \brief       时间显示子函数
//! \param       无
//! \return      无
//***************************************************************************
void time_dsp(void)
{
	if(time_to < 6)						// 当时间小于3 hour，按照*.*格式显示
	{
		led_data[1] = LED_CODE[time_to/2] | 0x04;	// 十位
		led_data[0] = LED_CODE[5*(time_to%2)];		// 个位
	}
	else if((time_to-3)<10)				// 当时间小于10 hour，按照*.*格式显示
	{
		led_data[1] = LED_CODE[time_to-3] | 0x04;
		led_data[0] = 0xeb;
	}
	else								// 当时间>=10 hour，按照**.格式显示
	{
		led_data[1] = LED_CODE[(time_to-3)/10];
		led_data[0] = LED_CODE[(time_to-3)%10] | 0x04;
	}
}

//***************************************************************************
//! \brief       LED显示 写地址子函数
//! \param       无
//! \return      无
//***************************************************************************
void led_wr(u8 com)
{
	u8 i;
	STB=1;
		delay(4);
	STB=0;
		delay(4);
	for(i=0;i<8;i++)
	{
		CLK=0;
		if(com & 0x01)
		DIO=1;
		else
		DIO=0;
		delay(4);
		com>>=1;
		CLK=1;
		delay(4);
	}
}

//***************************************************************************
//! \brief       LED显示 写数据子函数
//! \param       无
//! \return      无
//***************************************************************************
void led_wrDATA(u8 dat)
{
	u8 i;
	delay(4);
	for(i=0;i<8;i++)
	{
		CLK=0;
		if(dat & 0x01)
		DIO=1;
		else
		DIO=0;
		delay(4);
		dat>>=1;
		CLK=1;
		delay(4);
	}
}
