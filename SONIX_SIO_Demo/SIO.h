#ifndef		_SIO_H_
#define		_SIO_H_

#include	"User.h"


void	Serial_Trs_Rec(void);
void	EW_EN_Or_DS(bit ,uint);
void	SIO_WRITE(bit,uint,uint);
uint	SIO_READ(bit,uint);
void	WRAL(bit,uint,uint);
void	ERAL(bit,uint);

#endif