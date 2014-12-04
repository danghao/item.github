#ifndef		_USER_H_
#define		_USER_H_

#include	<SN8F27E65.h>

#define	 	uint  	unsigned int
#define		uchar  	unsigned char
#define 	ulong	unsigned long

#define		BEGIN_BIT	1

#define		SDO		FP14
#define		SDI		FP15
#define		SCK		FP16
#define		SCS 	FP17

void	InitalSystem(void);

#endif