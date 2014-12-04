//***************************************************
//	Interrupt routine Multi
//***************************************************
void __interrupt [0x08] ISR_WAKE(void)
{
	if(FWAKEIRQ)
	{
		FWAKEIRQ = 0;
	}
}
//-------------------------------------------------
void __interrupt [0x09] ISR_INT0(void)
{
	if(FP00IRQ)
	{
		FP00IRQ = 0;
	}
}
//-------------------------------------------------
void __interrupt [0x0A] ISR_INT1(void)
{
	if(FP01IRQ)
	{
		FP01IRQ = 0;
	}
}
//-------------------------------------------------
void __interrupt [0x0B] ISR_T0(void)
{
	if(FT0IRQ)
	{
		FT0IRQ = 0;
	}
}
//-------------------------------------------------
void __interrupt [0x0C] ISR_TC0(void)
{
	if(FTC0IRQ)
	{
		FTC0IRQ =0;
	}
}
//-------------------------------------------------
void __interrupt [0x0D] ISR_TC1(void)
{
	if(FTC1IRQ)
	{
		FTC1IRQ =0;
	}
}
//-------------------------------------------------
void __interrupt [0x0E] ISR_TC2(void)
{
	if(FTC2IRQ)
	{
		FTC2IRQ =0;
	}
}
//-------------------------------------------------
void __interrupt [0x0F] ISR_T1(void)
{
	if(FT1IRQ)
	{
		FT1IRQ =0;
	}
}
//-------------------------------------------------
void __interrupt [0x010] ISR_ADC(void)
{
	if(FADCIRQ)
	{
		FADCIRQ =0;
	}
}
//-------------------------------------------------
void __interrupt [0x011] ISR_SIO(void)
{
	if(FSIOIRQ)
	{
		FSIOIRQ =0;
	}
}	
//-------------------------------------------------
void __interrupt [0x012] ISR_MSP(void)
{
	if(FMSPIRQ)
	{
		FMSPIRQ =0;
	}
}
//-------------------------------------------------
void __interrupt [0x13] ISR_UART_RX(void)
{
	if(FURXIRQ)
	{
		FURXIRQ=0;
	}
}
//-------------------------------------------------
void __interrupt [0x14] ISR_UART_TX(void)
{
	if(FUTXIRQ)
	{
		FUTXIRQ=0;
	}
}
