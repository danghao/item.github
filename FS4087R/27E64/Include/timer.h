#ifndef		_TIMER_H_
#define 	_TIMER_H_

#include "typedefine.h"

extern  bit f1s;

extern	u8 speed;
extern  u8 mode;
extern  u8 led_buf[3];
extern  u8 LED_CODE[12];
extern  bit sys_on;
extern  bit buzzer0_on;
extern  bit buzzer1_on;
extern  bit buzzer2_on;
extern	u8 time_to;
extern  bit	delay_15s_in;

extern  u8 buz_cnt;
extern  bit BUZ_EN;


extern void timer	(void);

#endif	
