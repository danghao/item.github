#include	"user.h"

uint	DelayTime;
uint	Add_Time;
uint	ADC_Result;
ulong	ADC_Buf; 

void	ADC_Scan(void);
void	ADC_DataAverage(void);
void	InitalADC(void);

void	main(void)
{
	InitalADC();
	while(1)
	{
		WDTR = 0x5A;
		ADC_Scan();
		ADC_DataAverage();
	}
}

__interrupt	isr(void)
{

}

void 	ADC_Scan(void)
{

	for(Add_Time=0;Add_Time<8;Add_Time++)
	{
		FADS = 1;						//Start ADC
		while(!FEOC);
		ADC_Buf += ADB;
	}
}

void	ADC_DataAverage(void)		
{
	ADC_Result = ADC_Buf >>3;		
	ADC_Buf = 0;					
}

void	InitalADC(void)
{
	P4CON = 0x20;				 	//Selected AIN5(P4.5) as ADC IO Port
	P4M = 0x00;						//Set P4.5 as input state
	P4UR = 0xDF;					//Prohibited P4.5 pull-up resistor
	FADLEN = 0;						//Set Fcpu/1;8-Bit ADC
	
	ADM = 0X15;

	FADENB = 1;						//Enable ADC
	NOP(100);
}
									