//***************************************************************************
//!
//! \file   main.c
//! \brief  型号FTAW57R 增加WiFi
//! \author D.H.
//! \date   2014-12-01
//! \email  danghao0815@163.com
//!
//***************************************************************************

#include	"main.h"

#include	"sdio.h"
#include	"rec.h"
#include	"led.h"
#include	"key.h"
#include	"init.h"
#include	"fun.h"
#include	"buzzer.h"

bit BUZ_EN;
bit f_dt;

//***************************************************************************
//! \brief       main 函数
//! \param       无
//! \return      无
//***************************************************************************
void main(void)
{
	SYS_Init();
	while(1)
	{
		Time_Flag ();
		send ();
		receive ();
		rec ();
		Key_Read ();	
		Key_Process ();
		led ();
		buzzer ();
		Fun ();
	}
}

//***************************************************************************
//! \brief       T0 中断函数 125us
//! \param       无
//! \return      无
//***************************************************************************
void __interrupt [0x08] isr_t0 (void)	//125us
{
	FT0IRQ = 0;
	T0C = 0xc8;
	if(BUZ_EN)
	{
		BUZ = ~BUZ;
	}
	f_dt = 1;
}

