//***************************************************************************
//!
//! \file   led.h
//! \brief  定义宏、函数接口、变量接口、类型等
//! \author D.H.
//! \date   2014-12-02
//! \email  danghao0815@163.com
//!
//***************************************************************************

#ifndef _LED_H_
#define _LED_H_

#include "typedefine.h"

#define LED_CS1 FP52
#define LED_CS2 FP50
#define LED_CS3 FP47

extern	bit 	   f_1ms;
extern	bit	  un_display;

void led(void);


#endif