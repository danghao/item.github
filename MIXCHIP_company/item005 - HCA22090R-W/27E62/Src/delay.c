//***************************************************************************
//!
//! \file    delay.c
//! \brief   �ͺ�:HCA22090R(WiFi) MCU:27E62
//! \version V1.0
//! \author  D.H.
//! \date    2014-11-01
//! \email   danghao0815@163.com
//!
//***************************************************************************

#include	"delay.h"

//***************************************************************************
//! \brief       ��ʱ����
//! \param       nms ��ʱ��ms��
//! \return      ��
//***************************************************************************
void Delay_ms(u8 nms)		
{
	volatile u8 i;
	volatile u8 j;
	for(i=0;i<nms;i++)
	{
		WDTR = 0x5A;
		for(j=0;j<135;j++)
		{
			;
		}
	}
}