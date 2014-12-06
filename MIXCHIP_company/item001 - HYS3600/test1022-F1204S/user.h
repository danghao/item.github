#ifndef _USER_H_
#define _USER_H_

#include	"MC97F1204S.h"
#define	uint	unsigned	int
#define	uchar	unsigned	char

#define	DATA	P04		//out
#define	WR		P05		//out
#define	CS		P06		//out
#define	LED		P03		//out
#define	RXD 	P10  	// in
#define	TXD 	P07  	// out

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