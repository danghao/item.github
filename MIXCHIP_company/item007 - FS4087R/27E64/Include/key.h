#ifndef		_KEY_H_
#define 	_KEY_H_

#include "typedefine.h"

extern	u8 num2_1s;

extern	bit  timer_on;
extern	u8 t_cnt1;
extern	u8 t_cnt2;

extern	bit un_display;
extern  u8 led_buf[3];
extern  u8 LED_CODE[12];
extern  bit buzzer0_on;
extern  bit buzzer1_on;
extern  bit buzzer2_on;
extern	bit BUZ_EN;
extern	bit sys_3s_ok;
extern	u8 buz_cnt;

extern void key		(void);

#endif	
