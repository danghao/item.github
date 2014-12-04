#ifndef		_MSP_TX_RX_H_
#define		_MSP_TX_RX_H_

void	MSP_APP(void);

void	MSP_Byte_TX(uint,uint,uint);
void	MSP_Byte_RX(uint,uint,uint);

void	MSP_Page_TX(uint,uint);
void	MSP_Page_RX(uint,uint,uint);

#endif