//***************************************************************************
//!
//! \file    txdata.h
//! \brief   ÐÍºÅ:HCA22090R(WiFi) MCU:27E62
//! \version V1.0
//! \author  D.H.
//! \date    2014-11-01
//! \email   danghao0815@163.com
//!
//***************************************************************************

#ifndef _TXDATA_H_
#define _TXDATA_H_

#include "typedefine.h"

extern bit f10ms;
extern bit wx_ok;
extern u8 receive_data[13];
extern bit f10ms_2;		
extern bit rx_again;
extern u8 send_data[13];
extern bit TX_product_OK;
extern u8 num_2;


void	TxData 			(void);

#endif