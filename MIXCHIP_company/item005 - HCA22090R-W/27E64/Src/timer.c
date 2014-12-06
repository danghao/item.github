#include	"user.h"

uint second;
bit timer_on;

void timer(void )
{
	if(f_1s)
	{
		f_1s = 0;
		second ++;
		if(second == 5)
		{
	//		BUZZER1_ON = 1;
		}
		else if(second == 10)
		{
	//		BUZZER2_ON = 1;
		}
		else if(second == 15)
		{
			second = 0;
	//		BUZZER3_ON = 1;
		}
	}
}