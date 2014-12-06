#ifndef _USER_H_
#define _USER_H_

#include"STM8S103F3P.h"
#define uint unsigned int 
#define uchar unsigned char 
#define LED_ON 		PA_ODR |= 0x08 	// =1
#define LED_OFF 	PA_ODR &= ~0x08 
#define	DATA_ON		PC_ODR |= 0x80 	// =1
#define	DATA_OFF	PC_ODR &= ~0x80 
#define	WR_ON			PD_ODR |= 0x04 	// =1
#define	WR_OFF		PD_ODR &= ~0x04 
#define	CS_ON			PD_ODR |= 0x08 	// =1
#define	CS_OFF		PD_ODR &= ~0x08 

extern void TIM2_Init(void);
extern void UART1_Init(void);
extern void init(void);
extern void tx_pack(void);
extern void	rx_pack(void);
extern void key(void);
extern void lcd(void);
extern void timer(void);
extern void write_add(uint add);
extern void write_dat(uchar dat);
extern void lcd_13bit(uint add_dat);
extern void lcd_12bit(uint com);
extern void Lcd_Init(uchar dsp_dat);

#endif
