#ifndef		_FUN_H_
#define 	_FUN_H_

#include "typedefine.h"

extern	bit f2_10ms;
extern	bit  f_1s;

extern  u8  time_to;
extern  u8  mode;
extern  u8  speed;
extern  bit timer_on;
extern  bit ion;
extern  bit sys_on;
extern  bit quiet;
extern  u8 	num_1s;

void fun(void);
void H_M_L_OUT(u8);
void Nature_Out(u8);

#endif
