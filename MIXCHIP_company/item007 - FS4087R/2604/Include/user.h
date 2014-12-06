#ifndef		_USER_H_
#define 	_USER_H_
//////////////////////////////////      include
#include <SN8P2604A.h>
//////////////////////////////////      macro
#define		uint	unsigned int
#define		uchar	unsigned char
#define BUZ		FP15
#define LED_5	FP16
#define LED_10	FP17
#define LED_11	FP20
#define REC		FP02	// ���� IN
#define DI	 	FP12	// in 
#define DO 		FP13	// out
#define LL 		FP00	// out
#define L 		FP50
#define M 		FP51
#define H 		FP52
#define SW	 	FP53
#define ION		FP11
#define FAN		FP01

//////////////////////////////////      ����
extern void initial(void);
extern void key(void);
extern void led(void);
extern void buzzer(void);
extern void timer(void);
extern void rec(void);
extern void send (void);
extern void receive (void);

//////////////////////////////////      ���� ʱ���־
extern	bit f_01ms;					
extern	bit f_2ms;
extern	bit f_10ms;
extern  bit f2_10ms;
extern  bit f1s;
extern  bit f_dt;
extern  bit f_2dt;

//////////////////////////////////      ���� ��ʱ
extern	bit  timer_on;
extern	uint time_to;
extern  bit	delay_15s_in;
extern	uint t_cnt1;
extern	uint t_cnt2;
//////////////////////////////////      ���� ����
extern  uint KeyFIFO;
extern  bit	key_on;
extern  bit	key_on_3s;
//////////////////////////////////      ���� ���ܲ���
extern  bit sys_on;
extern	bit un_display;
extern	bit SLP;
extern	uint speed;
extern  uint mode;
//////////////////////////////////      ���� led buf
extern  uint LED_CODE[12];
extern  uint led_buf[3];
//////////////////////////////////      ���� buzzer
extern	bit BUZ_EN;
extern	uint buz_cnt;
extern  bit buzzer0_on;
extern  bit buzzer1_on;
extern  bit buzzer2_on;
//////////////////////////////////		��������
extern  bit In_send;
extern  uint data_ptr;
extern  uint send_data_buf;
extern  uint chksum_send;
extern  uint send_data[13];	
extern  uint receive_data[13];	

#endif	

