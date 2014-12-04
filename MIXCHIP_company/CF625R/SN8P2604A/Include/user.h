#ifndef		_USER_H_
#define 	_USER_H_

#include <SN8P2604A.h>
#include <typedef_.h>

/**************************************************************
*           IO端口 宏定义
**************************************************************/
#define 	DIO 	FP27
#define 	CLK		FP26
#define 	STB		FP25
#define		REC		FP51
#define 	WATER_F	FP02	// READ
#define 	BT_OUT	FP00	// 1有效
#define 	L_OUT	FP11	// 0有效
#define 	M_OUT	FP14	// 0有效
#define 	H_OUT	FP13	// 0有效
#define 	HUM_OUT	FP52	// 0有效
#define 	ION_OUT	FP53	// 0有效
#define 	SW_OUT	FP12	// 0有效

/**************************************************************
*           函数声明
**************************************************************/
extern void initial(void);
extern void timer(void);
extern void key(void);
extern void led(void);
extern void buzzer(void);
extern void led_wr (u8 com);
extern void led_wrDATA (u8 com);
extern void delay(u8 x);
extern void delayms(u8 y);
extern void L_key_process(void);
extern void fun(void);
extern void time_dsp(void);
extern void time_speed_dsp(u8);	// 0 time 1 speed 2 auto
extern void H_L_M_out(u8 x);


/**************************************************************
*           变量 声明
**************************************************************/
extern	bit buzzer_on;
extern 	bit buzzer1_on;
extern 	bit buzzer2_on;
extern 	bit buz_en;
extern 	u8 BUZ_CNT;

extern	bit F_125us;
extern	bit f_10ms;
extern	bit f2_10ms;
extern	bit f3_10ms;
extern	bit f4_10ms;
extern	bit f_1s;
extern	bit f2_1s;


extern 	bit sys_on;
extern 	bit shan;
extern  bit led_on_off;
extern	bit led_data_ok;
extern	u8 led_data[];
extern	bit ffp13;
extern	bit ffp14;
extern	u8 LED_CODE[];
extern	bit un_display;
extern	bit	undis_ok;
extern	bit f_display;
extern	bit timer_on;
extern	u8 time_to;
extern	u8 time_cnt1;
extern	u8 time_cnt2;
extern	u8 time_cnt3;
extern	u8 num_10ms;
extern	u8 num2_10ms;
extern	u8 num_1s;
extern	u8 speed;
extern	u8 mode;
extern	u8 num2_1s;
extern	bool timer_keyin;
extern	bit sw;
extern	bit ion;
extern	bit SIL;
extern	bit HUM;
extern	bit HUMbuf;
extern	bit notest;
extern	u8 testmode_slp;
extern	u8 testmode_timer;
extern	bit key_on;
extern	bit key_on_3s;
extern	u8 KeyFIFO;

#endif	
