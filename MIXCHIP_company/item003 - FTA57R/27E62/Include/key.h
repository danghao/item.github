//***************************************************************************
//!
//! \file   key.h
//! \brief  定义宏、函数接口、变量接口、类型等
//! \author D.H.
//! \date   2014-12-01
//! \email  danghao0815@163.com
//!
//***************************************************************************

#ifndef _KEY_H_
#define _KEY_H_

#include "typedefine.h"

extern	bit  f_10ms;
extern	bit undis_in;

void 	Key_Read	(void);	// 读键值
void 	Key_Process	(void);	// 按键处理函数

#endif