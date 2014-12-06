#include "txdata.h"

bit tx_data_ok;

void Tx_Data(void)
{
	if(f_10ms)
	{
		f_10ms = 0;
		if(tx_data_ok)
		{
			tx_data_ok = 0;
			UTXD = 0xe1;
		}
	}
}
