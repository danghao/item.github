#ifndef		_TIMER_H_
#define 	_TIMER_H_

#include "typedefine.h"

extern  bit f_01ms;	//rec
extern	bit f_10ms;	//key

extern  bit f_t0;
extern	bit f2_10ms;
extern	bit f3_10ms;

extern 	bit sys_on;
extern	bit timer_on;
extern	bit timer_keyin;
extern	u8 led_data[];
extern	u8 LED_CODE[];
extern	u8 speed;
extern	bit led_data_ok;
extern	u8 time_to;

void time_flag(void);
void timer(void);
void time_dsp(void);

#endif
