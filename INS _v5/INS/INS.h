#ifndef INS_H
#define INS_H

#define COMPORT				"COM3"

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define END    (0xFFFFFFC0)
#define VERIFY    (0xFFFFFFE5)
#define MAX_DATA_LENGTH 1024
#define ARDUINO_WAIT_TIME	2000


typedef struct{
	int X;
	int Y;
	short Altitude;
	char Zone;
	int Longitude;
	int Latitude;
	short HeadAngle;
	short PitchAngle;
	short SlantAangle;
	short Vx;
	short Vy;
	short Vz;
	short Wx;
	short Wy;
	short Wz;
	short Ax;
	short Ay;
	short Az;
	short Bx;
	short By;
	short Bz;
	short Mileage;
	short HH;
	short mm;
	char sss;
	short yyyy;
	char MM;
	char dd;
	char Workingstatus;
} INSInfo;

class INS 
{
public:
	INS(const char* commport);
    ~INS();

	int read(INSInfo* insData);
	int formatINSInfo(INSInfo* insData, char* buf, int buf_size);


	/*------------------------------------------------------------------
	�Լ죺
			������				����				У����
		1�ֽ�(0XF0)		     ��				 1�ֽ�
	���ܣ�����Զ�λ����װ�÷����Լ����������ʽ��
	------------------------------------------------------------------*/
	void verify();//�Լ�
	/*------------------------------------------------------------------
	����װ����
	������				����				γ��				�߳�				У����
	1�ֽ�(0XF6)	   ���ֽ�		  ���ֽ�			  ���ֽ�		  	    1�ֽ�
	���ܣ�����Զ�λ����װ�÷�������װ�����������ʽ��
	����/γ��ֵ(ʮ������,��λ��ǰ)��(��λΪ0.000001��)
	�߳�Hֵ(ʮ������,��λ��ǰ),(�߳�H��λΪm����Χ-9999~9999m)
	------------------------------------------------------------------*/
	void initPos(int lng, int lat, int H);//����װ��
	/*------------------------------------------------------------------
	�������ã�
	������				�������				����ֵ				У����
	1�ֽ�(0XF4)		  һ�ֽ�				     ���ֽ�				 1�ֽ�
	���ܣ�����Զ�λ����װ�÷�����Ҫ�޸ĵġ�������š���������ֵ��
	��������ʽ��
		���������ֵΪ1-8����Ӧ���壺
		�������				  ��������				������λ
			1						����װ���			 0.01mil
			2						  ���ϵ��			     0.0001
			3						��̼�������			 0.0001
			4						������װ���			 0.01mil
		  5-8						  ���ò���
	------------------------------------------------------------------*/
	void seeking();//��׼(Ѱ��)
	/*------------------------------------------------------------------
	��׼(Ѱ��)��
	������				����				У����
	1�ֽ�(0XF3)	     ��				 1�ֽ�
	���ܣ�����Զ�λ����װ�÷��Ͷ�׼(Ѱ��)���������ʽ��
	------------------------------------------------------------------*/
	void setConfigure(unsigned char id, int val);//��������

	void read();//for debug

private:
	HANDLE handler;
};

#endif // INS_H
