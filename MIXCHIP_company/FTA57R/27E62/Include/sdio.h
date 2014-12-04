//***************************************************************************
//!
//! \file   sdio.h
//! \brief  定义宏、函数接口、变量接口、类型等
//! \author D.H.
//! \date   2014-12-02
//! \email  danghao0815@163.com
//!
//***************************************************************************

#ifndef _SDIO_H_
#define _SDIO_H_

#include "typedefine.h"

#define DI		FP46
#define DO		FP45

void send (void);
void receive (void);

#endif