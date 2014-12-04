#ifndef _USER_H_
#define _USER_H_

#include	"SH79F083A.h"
#define	uint	unsigned	int
#define	uchar	unsigned	char

#define	DATA	P1_7		//out
#define	WR		P1_6		//out
#define	CS		P4_1		//out
#define	LED		P4_2		//out
//	#define	RXD 	P3_0  	// in
//	#define	TXD 	P3_1  	// out

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