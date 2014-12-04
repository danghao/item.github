#ifndef _user_
#define _user_

#include <SN8F27E62.h>

#define uchar unsigned char
#define uint unsigned int
#define H_1H 			FP04
#define M_2H 			FP03
#define L_4H_RST 		FP02
#define E_8H_LOCK 		FP00
#define I_O 			FP53
#define HW_dat 			FP47
#define H_outp 			FP52
#define M_outp 			FP51
#define L_outp 			FP50
#define BUZZER 			FP10
#define HMLE_CTR	 	FP05
#define H1248_CTR	 	FP06
#define RST_LOCK_OI_CTR	FP43

void	initial	(void);
void	adc	(void);
void	key	(void);
void	led	(void);
void	hwjc(void);
void	rst(void);
void	keyprocess(void);

#endif