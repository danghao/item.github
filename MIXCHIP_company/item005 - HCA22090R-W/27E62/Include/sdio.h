//***************************************************************************
//!
//! \file    sdio.h
//! \brief   ÐÍºÅ:HCA22090R(WiFi) MCU:27E62
//! \version V1.0
//! \author  D.H.
//! \date    2014-11-01
//! \email   danghao0815@163.com
//!
//***************************************************************************

#ifndef _SDIO_H_
#define _SDIO_H_

#include "typedefine.h"

extern bit f125us;
extern bit f_send;

void 	Sd_Send 		(void);
void 	Sd_Receive 		(void);


#endif