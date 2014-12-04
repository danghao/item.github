#ifndef		_KEY_H_
#define 	_KEY_H_

#include "typedefine.h"

extern	bit f_10ms;
extern	bit F_125us;
extern	u8 num_10ms;
extern	u8 num_1s;
extern	u8 time_cnt1;
extern	u8 time_cnt2;
extern	u8 time_cnt3;

extern	bit buzzer_on;		// BI
extern 	bit buzzer1_on;		// BI—
extern 	bit buzzer2_on;		// BI BI
extern 	u8  BUZ_CNT;
extern 	bit buz_en;			// buzzer使能位

extern	u8  led_data[];		// LED 显示段码缓存区
extern	bit f_display;		// 控制 数码管显示“速度”或“时间”
extern	u8  LED_CODE[];		// LED 显示段码
extern	bit led_data_ok;	// LED 显示码缓存更新完成标志
extern	bit	undis_ok;		// LED 熄屏成功标志

void key(void);

#endif	
