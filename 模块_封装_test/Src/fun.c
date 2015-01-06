#include	"fun.h"

// *************************************************************
// \brief       输出控制函数
// \param       无
// *************************************************************

bit sys_on;
bit sys_buf;
u8  speed;
u8  speed_buf;
u8  mode;
u8  mode_buf;

void Fun (void)
{
	if(sys_buf != sys_on)
	{
		sys_buf = sys_on;
		if(sys_on)
		{
		}
		else
		{
		}
	}
	else if(sys_on)
	{
		if(speed_buf != speed)
		{
			speed_buf = speed;
			// ...
		}
		if(mode_buf != mode)
		{
			mode_buf = mode;
			switch(mode)
			{
				case 1 :
				{
					break;
				}
				case 2 :
				{
					break;
				}
				default : {}
			}
		}
		switch(mode)
		{
			case 1 :
			{
				break;
			}
			case 2 :
			{
				break;
			}
			default : {}
		}
	}
}
