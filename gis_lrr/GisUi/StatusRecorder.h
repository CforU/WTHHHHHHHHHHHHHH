#ifndef __STATUSRECODER_H__
#define __STATUSRECODER_H__

#include <qmap.h>
#include <qlist.h>

// StatusRecorder ״̬��¼�� ���ڼ�¼�����Ĳ����� ���ڸ�����ʾ�ͷ���

//��¼��Ҫ�İ���  1 ״̬���л� 2 �����л� 
//��������Ϊture ����Ϊfalse	

class StatusRecorder
{
public:
	StatusRecorder();
	~StatusRecorder();
	enum btnCode{

	};
	//QList<QMap<enum btnCode, bool status> >  rcording;//��¼����
	//Map��¼������ֵ�� ����״̬ ��������Ϊture ����Ϊfalse	

	QList<QMap<enum btnCode, bool> >  rcording;//��¼���� 
	bool  rFlags;//���ر�־  ����Ҫ����  false ���践��
	static void recode();//  ��¼һ����¼ //static  //��¼��Ҫ�İ���  1 ״̬���л� 2 �����л� 
	static void returns();// ������    //static  //ͨ����־λ�Ӻ���ǰ����ÿһ�����أ�  ��ǰ����÷��صĲ���

};
#endif __STATUSRECODER_H__