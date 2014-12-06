//***************************************************************************
//!
//! \file    linkcheck.h
//! \brief   ÐÍºÅ:HCA22090R(WiFi) MCU:27E62
//! \version V1.0
//! \author  D.H.
//! \date    2014-11-01
//! \email   danghao0815@163.com
//!
//***************************************************************************

#ifndef _LINKCHECK_H_
#define _LINKCHECK_H_

#include "typedefine.h"

extern	bit f_500ms;
extern bit f1_50ms;
extern bit f2_50ms;	// keylink
extern bit In_send;
extern bit key_link;
extern bit kuaishan;
extern u8 send_data_buf;
extern u8 chksum_send;
extern u8 data_ptr;
extern u8 send_data[13];

void    LinkCheck		(void);

#endif