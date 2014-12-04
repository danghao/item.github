#ifndef		_TYPEDEFINE_H_
#define 	_TYPEDEFINE_H_

#include <SN8F27E62.h>

#define		time_dec	60		// 可调参数 计时时间缩短为 1/time_dec

#define 	DIO 	FP53
#define 	CLK		FP00
#define 	STB		FP02

#define 	SDI		FP47
#define 	SDO		FP50

#define 	REC		FP04

#define 	SW_OUT	FP06
#define 	CMD_OUT	FP51
#define 	FO_OUT	FP52

typedef	unsigned char	u8;
typedef	unsigned long	u16;

#endif	
