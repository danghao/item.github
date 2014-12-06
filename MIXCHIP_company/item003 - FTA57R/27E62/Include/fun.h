//***************************************************************************
//!
//! \file   key.h
//! \brief  定义宏、函数接口、变量接口、类型等
//! \author D.H.
//! \date   2014-12-01
//! \email  danghao0815@163.com
//!
//***************************************************************************

#ifndef _FUN_H_
#define _FUN_H_

#include "typedefine.h"

#define	H_OUT	FP03
#define M_OUT	FP05
#define L_OUT	FP06
#define SW_OUT	FP43

extern  bit   f_dt;
extern	bit  f2_dt;

extern	bit 	 sys_on;
extern	bit 	  sw_on;
extern	u8 		time_to;		// 定时时间
extern	u8 	   	   mode;		// 上电初始 普通模式 
extern	u8 	      speed;		// 上电初始 中档运行 3s

void	H_M_L_OUT	(u8  );
void	Nature_Out	(u8  );
void	Time_Flag	(void);
void	Delay_ms	(u8  );
void	Fun			(void);


#endif