#ifndef INS_H
#define INS_H

#include <QtWidgets/QMainWindow>
#include "qserialport.h"

#define COMPORT				"COM3"

#define END				(0xFFFFFFC0)
#define ESC				(0xFFFFFFDB)
#define ESC_END		(0xFFFFFFDC)
#define ESC_ESC		(0xFFFFFFDD)
#define VERIFY			(0xFFFFFFE5)
#define MAX_DATA_LENGTH 1024

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

class INS : public QMainWindow
{
	Q_OBJECT

public:
	INS(QWidget *parent = 0);
	~INS();

	int read(INSInfo* insData);
	int formatINSInfo(INSInfo* insData, char* buf, int buf_size);

	/*------------------------------------------------------------------
	1�Լ죺
	������				����				У����
	1�ֽ�(0XF0)		     ��				 1�ֽ�
	���ܣ�����Զ�λ����װ�÷����Լ����������ʽ��
	���ȣ�2���ֽ�
	------------------------------------------------------------------*/
	void verify();//�Լ�

	/*------------------------------------------------------------------
	2��׼(Ѱ��)��
	������				����				У����
	1�ֽ�(0XF3)	     ��				 1�ֽ�
	���ܣ�����Զ�λ����װ�÷��Ͷ�׼(Ѱ��)���������ʽ��
	���ȣ�2���ֽ�
	------------------------------------------------------------------*/
	void seeking();//��׼(Ѱ��)

	/*------------------------------------------------------------------
	3����װ����
	������				����				γ��				�߳�				У����
	1�ֽ�(0XF6)	   ���ֽ�		  ���ֽ�			  ���ֽ�		  	    1�ֽ�
	���ܣ�����Զ�λ����װ�÷�������װ�����������ʽ��
	���ȣ�14���ֽ�
	����/γ��ֵ(ʮ������,��λ��ǰ)��(��λΪ0.000001��)
	�߳�Hֵ(ʮ������,��λ��ǰ),(�߳�H��λΪm����Χ-9999~9999m)
	------------------------------------------------------------------*/
	void initPos(int lng, int lat, int H);//����װ��

	/*------------------------------------------------------------------
	4�������ã�
	������				�������				����ֵ				У����
	1�ֽ�(0XF4)		  һ�ֽ�				     ���ֽ�				 1�ֽ�
	���ܣ�����Զ�λ����װ�÷�����Ҫ�޸ĵġ�������š���������ֵ��
	��������ʽ��
	���ȣ�7���ֽ�
	���������ֵΪ1-8����Ӧ���壺
	�������				  ��������				������λ
	1						����װ���			 0.01mil
	2						  ���ϵ��			     0.0001
	3						��̼�������			 0.0001
	4						������װ���			 0.01mil
	5-8						  ���ò���
	------------------------------------------------------------------*/
	void setConfigure(unsigned char id, int val);//��������
	
/*-------------------------------������----------------------------------*/
	/*------------------------------------------------------------------
	������ȡ��
	������			  	    �������						У����
	1�ֽ�(0XF3)		      һ�ֽ�			  				 1�ֽ�
	���ܣ�����Զ�λ����װ�÷�����Ҫ��ȡ�Ĳ�����ţ�������ʽ;
	���ȣ�3���ֽ�
	��һ���ֽ�Ϊ0XF3λ�����֣����Ͳ�����ż�����ֵ
	�ڶ��ֽ�Ϊ������ţ���ֵ��ΧΪ1-8
	�����ֽ�ΪУ���֡�
	------------------------------------------------------------------*/
	void getConfigure(unsigned char id);//for debug
	void read();//for debug
private:
	QSerialPort * myCom;
};


#endif // INS_H
