#include "user.h"


void init(void)
{
	PA_DDR |= 0x08;		// PA3 OUT 
	PA_CR1 |= 0x08;
	PA_CR2 &= ~0x08;
	PB_DDR |= 0x30;		// PB4 PB5 OUT
	PB_CR1 |= 0x30;
	PB_CR2 &= ~0x30;
	PC_DDR |= 0x88;		// PC3 7 OUT 
	PC_CR1 |= 0x88;	
	PC_CR2 &= ~0x88;
	PC_DDR &= ~0x70;	// PC4 5 6 IN
	PC_CR1 |= 0x70;		
	PC_CR2 &= ~0x70;
	PD_DDR |= 0x2C;		// PD2 3 5(tx) OUT
	PD_CR1 |= 0x2C;
	PD_CR2 &= ~0x2C;
	PC_DDR &= ~0x40;	// PD6(rx) IN
	PC_CR1 |= 0x40;		
	PC_CR2 &= ~0x40;

	LED_OFF;		// LCD背景灯光关
	CS_ON;
	WR_ON;
	DATA_ON;
	Lcd_Init(0xFF);
	LED_ON;		// LCD背景灯光开

	TIM2_Init();
	UART1_Init();

}