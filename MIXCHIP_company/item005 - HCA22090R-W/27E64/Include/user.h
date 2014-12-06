#ifndef _user_h_
#define _user_h_

#include <SN8F27E64.h>
#include <stdlib.h>

#define uchar unsigned char
#define uint unsigned int

#define DIO 	FP15
#define CLK		FP14
#define STB		FP13

#define SDA		FP47
#define SCL		FP50

typedef	unsigned char u8;
typedef	unsigned long u16;

void	initial	(void);
void 	timer(void);
void 	buzzer (void );
void 	led (void);
void 	key (void);

void 	led_wr (uint);
void 	led_wrDATA (uint);

void 	delay(uint);
void 	write(uint,uint);
void	read (uint);

extern	bit f_1s;
extern	bit f10ms;
extern	bit BUZZER_ON;
extern	bit BUZZER1_ON;	//bi
extern	bit BUZZER2_ON;	//bibi
extern	bit BUZZER3_ON;	//bi~

//数据准备 led_data[8]; led_data_ok = 1;
extern uint led_data[8];
extern bit  led_data_ok;
extern bit f_100ms;
extern u8 read1;
extern bit timer_on;
extern bit sys_on;


#endif

