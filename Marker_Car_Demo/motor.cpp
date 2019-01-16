#include "motor.h"

Motor::Motor(QObject *parent) : QObject(parent)
{

}

void Motor::startConnect()
{
	emit start();
}

void Motor::setPWM(int motorA, int motorB, int motorC)
{
	int orderLength = 16;
	char * orderBuf = new char[orderLength];
	memset(orderBuf, 0, orderLength);

	char temp;
	int payload[3] = { motorA, motorB, motorC };

	int bufBase = 0;
	orderBuf[bufBase++] = 0x55;		//packet��ʼ��־
	orderBuf[bufBase++] = 13;		//������Ч���ݵĳ���
	orderBuf[bufBase++] = 0x00;		//�����ַ�

	//��motorA,motorB,motorC��ֵ���ΰ��ո�8λ����8λ��˳��װ��orderBuf��
	for (int i = 0; i < 3; i++)
	{
		for (int j = 24; j >= 0; j = j - 8)
		{
			temp = (payload[i] >> j) & unsigned(0xFF);
			orderBuf[orderLength - 1] ^= temp;	//CRCУ�������
			orderBuf[bufBase++] = temp;			//װ��ȡ�����ֽ�
		}
	}
	emit writeData(QByteArray(orderBuf, orderLength));
	//�ͷ��ڴ�
	delete orderBuf;
}
