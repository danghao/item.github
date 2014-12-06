#include	"user.h"

u8 read1;
bit key_on;
bit key_on_3s;
bit key_in;
bit key_3s_in;
u8 KeyChat;
u8 keynum;
u8 KeyChkbuf;
u8 KeyInbuf;
u8 KeyFIFO;
bit Fkeyin;
bit key_0s_in;
u8 seconds;
bit sys_on;

/****************  key  ****************/
void key(void)
{
	if(f_100ms)
	{
		f_100ms = 0;
		read(0x20);
		switch(read1)
		{
			case 0x04 :
			{
				keynum = 1;
				break;
			}
			case 0x02 :
			{
				keynum = 2;
				break;
			}
			case 0x80 :
			{
				keynum = 3;
				break;
			}
			case 0x01 :	// TIMER
			{
				keynum = 4;
				break;
			}
			default :	{keynum = 0;}
		}
//////////////////////////////////////////////////////////////
		if(KeyChkbuf != keynum)
		{	
			if(keynum == 0)
			{
				Fkeyin = 0;
				if(KeyChkbuf == 1)
				{
					if(!key_3s_in && (seconds > 0 || KeyChat >= 5))
					{
						key_on = 1;				/* key ok */
						KeyFIFO = KeyChkbuf; 
					}
					else if(key_3s_in)
					key_3s_in = 0;
				}
				else if(KeyChkbuf == 3)
				{
					if(key_3s_in)
					key_3s_in = 0;
				}
			}
			else
			{
				Fkeyin = 1;
				KeyChat = 0;
				seconds = 0;
			}
			KeyChkbuf = keynum;
		}
		if(Fkeyin)							 
		{
			if(KeyChat == 5)
			{
				if(KeyChkbuf == 3 && sys_on == 0 && timer_on == 0)
				{
				}
				else if(KeyChkbuf != 1)
				{
					Fkeyin = 0;
					key_on = 1;	
					KeyFIFO = KeyChkbuf; 
				}
			}
			else if(KeyChat == 100)
			{
				seconds ++;
				if(seconds == 3)
				{
					key_3s_in = 1;
					Fkeyin = 0;
					key_on_3s = 1;
					KeyFIFO = KeyChkbuf; 
				}
				else
				KeyChat = 0;
			}
			KeyChat++;
		}
	}
/****************  key ok  ****************/
	if(key_on || key_on_3s)
	{
		switch(KeyFIFO)
		{
			case 1 :	// on/off
			{
				break;
			}
			case 2 :	// speed
			{
				break;
			}
			case 3 :	// AI 智能模式
			{
				break;
			}
			case 4 :	// TIMER
			{
				break;
			}
		}
		key_on = 0;
		key_on_3s = 0;
	}
}

/****************  key drive  ****************/
void start(void)
{
	delay(5);
	SDA = 1;	//
	delay(5);
	SCL = 1;	//
	delay(5);
	SDA = 0;	//
	delay(16);
	SCL = 0;	//
	delay(5);	
}
void sr(void)
{
	delay(5);
	SDA = 1;	//
	delay(5);
	SCL = 1;	//
	delay(10);
	SDA = 0;	//
	delay(5);
	SCL = 0;	//
	delay(5);	
}
void stop(void)
{
	SCL = 0;	//
	delay(5);	
	SDA = 0;	//
	delay(5);	
	SCL = 1;	//
	delay(16);	
	SDA = 1;	//
	delay(10);
}
bit chkack(void)
{
	uint i = 16;
	bit f_error = 0;
	SCL = 0;
	SDA = 1;
	P4M  	&=	0x7f;	//[P47]in
	delay(32);	
	SCL = 1;	delay(10);
loop:
	if(SDA)
	{
		i--;
		if(i)
		goto loop;
		else 
		f_error = 1;
	}
	else if(i != 0)
	{
		f_error = 0;
	}
	SCL = 0;	delay(5);
	SDA = 0;	
	P4M  	|=	0x80;	//[P47]out
	SDA = 0;		
	if(!f_error)	delay(32);
	return f_error;
}

void sendack(void)
{
	SCL = 0;
	delay(5);
	SDA = 0;		
	delay(5);
	SCL = 1;
	delay(5);
	SCL = 0;
	SDA = 0;		
	delay(1);
	SDA = 0;		
}

void sendnack(void)
{
	SCL = 0;
	delay(5);
	SDA = 1;		
	delay(5);
	SCL = 1;
	delay(10);
	SCL = 0;
	delay(5);
	SDA = 0;		
}

void wr_8(uint dat)
{
	uint i;
	for(i=0;i<8;i++)
	{
		SCL = 0;	delay(8);
		if((dat&0x80))SDA = 1;
		else 		SDA = 0;
		dat <<= 1;
		delay(5);
		SCL = 1;
		delay(5);
		SCL = 0;
	}
}

uint rd_8(void)
{
	uint i,dat;
	P4M  	&=	0x7f;
	delay(5);
	for(i=0;i<8;i++)
	{
		dat <<= 1;
		SCL = 0;
		delay(5);
		SCL = 1;
		delay(5);
		if(SDA) dat |= 0x01;
	}
	SCL = 0;
	delay(5);
	SDA = 0;
	P4M  	|=	0x80;
	SDA = 0;
	delay(5);
	return dat;
}

/****************  write CTP005  ****************/
void write(uint com,uint dat)
{
	start();
	wr_8(0x68);		// address 从机地址
	if(chkack())	return;
	wr_8(com);		// command 写指令
	if(chkack())	return;
	wr_8(dat);		// data 写数据
	if(chkack())	return;
	stop();
}

/****************  read CTP005  ****************/
void read(uint com)
{
	start();
	wr_8(0x68);		// 向从机写
	if(chkack())	return;
	wr_8(com);		// 地址0x20 0x21
	if(chkack())	return;
	sr();
	wr_8(0x69);		// 从地址读
	if(chkack())	return;
	read1 = rd_8();	// data 读数据
	sendnack();
	stop();
}
