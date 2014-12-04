#include "main.h"

#include "buzzer.h"
#include "fun.h"
#include "initial.h"
#include "key.h"
#include "led.h"
#include "rec.h"
#include "sdio.h"
#include "timer.h"

	bit shan;
    u8 num_5ms;

void main(void)
{
	WDTR = 0x5A;
	SYS_Init();
	while(1)
	{
		WDTR = 0x5A;
		key();
		led();
		buzzer();
		timer();
		rec();
		receive();
		send();
	}
}

void __interrupt [0x08] isr_t0 (void)	//125us
{
	FT0IRQ = 0;
	T0C = 0xc8;
	if(BUZ_EN)
	{
		BUZ = ~BUZ;
	}
	f_01ms = 1;
	f_dt = 1;
}

