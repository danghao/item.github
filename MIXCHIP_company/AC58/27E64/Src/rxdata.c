#include "rxdata.h"

bit RX_com_in;
bit RX_dat_in;

u8 RX_data[65];
u8 RX_ptr;
u8 RX_byte;
bit RX_pack_ok;
u16 RX_data_add;

u8 TX_data[65];

void Rx_Data(void)
{
	if(RX_ok)
	{
		RX_ok = 0;
		if(RX_com_in)
		{
			RX_ptr ++;
			RX_data[RX_ptr] = RX_buf;
			RX_data_add += RX_buf;	//chk sum
			if(RX_ptr > 10)
			{
				if(RX_data[6] == 0xE9 && RX_ptr == 11)		// �������ø�λʱ ��Ӧ
				{
					// If_Ack = 1;
					RX_com_in = 0;
				}
				else if(RX_ptr == 15 && RX_data[6] == 0xEC)	// WiFiģ�� ״̬�ı䣬���͵�������������
				{
					switch(RX_data[12])
					{
						case 0 :		// �豸��������״̬
						{
							break;
						}
						case 1 :		// �豸��������AP״̬
						{
							break;
						}
						case 2 :		// �Ѿ����ӵ�AP,���Ա��ؿ���
						{
							break;
						}
						case 3 :		// �Ѿ����������Ʒ���,��Զ�̿���
						{
							break;
						}
						default :
						{
							;
						}
					}
					RX_com_in = 0;
				}
				else if(RX_ptr == 19 && RX_data[6] == 0xEE)	// WiFiģ�� ���صĵ�ǰ����ʱ��ֵ
				{
	/*
					RX_data[12] // ����ֽ�
					RX_data[13] // ����ֽ�
					RX_data[14] // ��
					RX_data[15] // ����
					RX_data[16] // Сʱ
					RX_data[17] // ����
					RX_data[18] // ��
					RX_data[19] // ��
	*/
					RX_com_in = 0;
	 			}
				else if(RX_ptr > 19)
				{
					RX_com_in = 0;
				}
			}
		}
		else if(RX_dat_in)
		{
			RX_ptr ++;
			RX_data[RX_ptr] = RX_buf;
			if(RX_ptr < 61)
			{
				RX_data_add += RX_buf;
			}
			else if(RX_ptr==62 && RX_data[61] == (1+~RX_data_add) && RX_data[62]==0x44)
			{
				// һ֡���ݽ���
				RX_dat_in = 0;
			}
			else if(RX_ptr > 62)
			{
				RX_dat_in = 0;
			}
		}
		else
		{
			if(RX_buf == 0xbb)
			{
				RX_data[0] = 0xbb;
				RX_ptr = 0;
				RX_dat_in = 1;
				RX_data_add = 0x0000;	//chk sum
			}
			else
			{
				RX_data[0] = RX_data[1];
				RX_data[1] = RX_data[2];
				RX_data[2] = RX_data[3];
				RX_data[3] = RX_buf;
				if(RX_data[3] == 0x5a && RX_data[2] == 0x5a && RX_data[1] == 0xa5 && RX_data[0] == 0xa5)
				{
					RX_ptr = 3;
					RX_com_in = 1;
					RX_data_add = 0xc0ad;	//chk sum
				}
			}
		}
	}
}
