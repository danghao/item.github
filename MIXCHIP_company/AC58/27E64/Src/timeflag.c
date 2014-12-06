#include "timeflag.h"

bit  f_125us;

bit  f_250us;

bit f_10ms;		// tx data
bit f2_10ms;

bit f_50ms;
bit f2_50ms;

bit f_500ms;
		
bit  bit_125us;
u8	num_250us;
u8	num_10ms;
u8	num_50ms;


void TimeFlag (void)
{
	if(f_t0)
	{
		f_t0 = 0;
		f_125us		=	1;
		bit_125us	^=	1;
		if(bit_125us)
		{
			f_250us		=	1;
			num_250us 	+=	1;
			if(num_250us == 40)
			{
				num_250us	=	0;
				f_10ms		=	1;
				f2_10ms 	=	1;
				num_10ms 	+=	1;
				if(num_10ms == 5)
				{
					num_10ms	=	0;
					f2_50ms =	1;
					f_50ms =	1;
					num_50ms	+=	1;
					if(num_50ms == 10)
					{
						num_50ms	=	0;
						f_500ms =	1;
					}
				}
			}
		}
	}
}
