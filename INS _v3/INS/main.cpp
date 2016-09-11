#include "INS.h"


int main()
{
	INS* ins = new INS(COMPORT);
	INSInfo* insData = new INSInfo;
	int result = ins->read(insData);
	if (result){
		printf("Error to read!\n");
	}
	else{
		printf("Connection established at port %s\n" ,COMPORT);
	}

	/***********TEST*****************/
	char p[1024] = {};
	result = ins->formatINSInfo(insData, p, 1024);
	if (!result){
		printf("success to formatINSInfo!\n");
	}
	printf("%s\n", p);

	//printf("����X:%d\n", insData->X);
	//printf("����Y:%d\n", insData->Y);
	//printf("�߳�:%d\n", insData->Altitude);
	//printf("����:%d\n", insData->Zone);
	//printf("����:%d\n", insData->Longitude);
	//printf("γ��:%d\n", insData->Latitude);
	//printf("�����:%d\n", insData->HeadAngle);
	//printf("������:%d\n", insData->PitchAngle);
	//printf("��б��:%d\n", insData->SlantAangle);
	//printf("Vx:%d\n", insData->Vx);
	//printf("Vy:%d\n", insData->Vy);
	//printf("Vz:%d\n", insData->Vz);
	//printf("Wx:%d\n", insData->Wx);
	//printf("Wy:%d\n", insData->Wy);
	//printf("Wz:%d\n", insData->Wz);
	//printf("Ax:%d\n", insData->Ax);
	//printf("Ay:%d\n", insData->Ay);
	//printf("Az:%d\n", insData->Az);
	//printf("Bx:%d\n", insData->Bx);
	//printf("By:%d\n", insData->By);
	//printf("Bz:%d\n", insData->Bz);
	//printf("�������:%d\n", insData->Mileage);
	//printf("GPS��ʱ(hhmmss.sss):%.2d", insData->HH);
	//printf(":%.2d", insData->mm);
	//printf(":%.2d\n", insData->sss);
	//printf("GPS��ʱ(yyyymmdd):%d", insData->yyyy);
	//printf("-%d", insData->MM);
	//printf("-%d\n", insData->dd);
	//printf("����״̬:%d\n", insData->Workingstatus);
	delete insData;
	return 0;
}
