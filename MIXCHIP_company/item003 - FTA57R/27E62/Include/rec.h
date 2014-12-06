//***************************************************************************
//!
//! \file   rec.h
//! \brief  定义宏、函数接口、变量接口、类型等
//! \author D.H.
//! \date   2014-12-02
//! \email  danghao0815@163.com
//!
//***************************************************************************

#ifndef _REC_H_
#define _REC_H_

#include "typedefine.h"
#include <stdlib.h>

#define REC		FP04

extern	bit      key_on;
extern	bit   key_on_3s;
extern	u8 	    KeyFIFO;

void rec(void);

#endif