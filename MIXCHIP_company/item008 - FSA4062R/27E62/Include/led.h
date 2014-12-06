#ifndef		_LED_H_
#define 	_LED_H_

#include "typedefine.h"

extern	u8  time_to;
extern	bit un_display;


void led(void);
void led_wr(u8);
void led_wrDATA(u8);

#endif	
