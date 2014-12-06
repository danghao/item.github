#ifndef		_USER_H_
#define 	_USER_H_

#include <SN8P2604A.h>

#define		uint	unsigned int
#define		uchar	unsigned char

#define		time_dec	60	// 可调参数 计时时间缩短为 1/time_dec

#define 	DIO 	FP12
#define 	CLK		FP11
#define 	STB		FP10
#define 	SDI		FP16
#define 	SDO		FP17

extern void initial(void);
extern void timer(void);
extern void key(void);
extern void led(void);
extern void buzzer(void);

extern void led_wr (uint com);
extern void led_wrDATA (uint com);
extern void delay(uint x);

extern void time_dsp(void);

extern	bit buzzer_on;
extern 	bit buzzer1_on;
extern 	bit buzzer2_on;
extern 	bit buz_en;
extern 	uint BUZ_CNT;

extern	bit F_125us;
extern	bit f_10ms;
extern	bit f2_10ms;
extern	bit f3_10ms;

extern 	bit sys_on;
extern 	bit shan;
extern  bit led_on_off;
extern	bit led_data_ok;
extern	uint led_data[];
extern	bit ffp13;
extern	bit ffp14;
extern	uint LED_CODE[];
extern	bit un_display;
extern	bit	undis_ok;
extern	bit f_display;
extern	bit timer_on;
extern	uint time_to;
extern	uint time_cnt1;
extern	uint time_cnt2;
extern	uint time_cnt3;
extern	uint num_10ms;
extern	uint num2_10ms;
extern	uint num_1s;
extern	uint speed;
extern	bit timer_keyin;


#endif	

