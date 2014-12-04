//***************************************************************************
//!
//! \file    rxdata.h
//! \brief   ÐÍºÅ:HCA22090R(WiFi) MCU:27E62
//! \version V1.0
//! \author  D.H.
//! \date    2014-11-01
//! \email   danghao0815@163.com
//!
//***************************************************************************

#ifndef _RXDATA_H_
#define _RXDATA_H_

#include "typedefine.h"


extern bit RX_pack_ok; 
extern u8 RX_data[20];
extern u8 send_data[13];
extern u8 receive_data[13];

extern u8 RX_ptr_buf;
extern u8 send_data_buf;
extern u8 chksum_send;
extern u8 data_ptr;
extern bit In_send;

void	RxData 			(void);


#endif