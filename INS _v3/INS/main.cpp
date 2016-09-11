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

	//printf("坐标X:%d\n", insData->X);
	//printf("坐标Y:%d\n", insData->Y);
	//printf("高程:%d\n", insData->Altitude);
	//printf("区号:%d\n", insData->Zone);
	//printf("经度:%d\n", insData->Longitude);
	//printf("纬度:%d\n", insData->Latitude);
	//printf("航向角:%d\n", insData->HeadAngle);
	//printf("俯仰角:%d\n", insData->PitchAngle);
	//printf("倾斜角:%d\n", insData->SlantAangle);
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
	//printf("本次里程:%d\n", insData->Mileage);
	//printf("GPS授时(hhmmss.sss):%.2d", insData->HH);
	//printf(":%.2d", insData->mm);
	//printf(":%.2d\n", insData->sss);
	//printf("GPS授时(yyyymmdd):%d", insData->yyyy);
	//printf("-%d", insData->MM);
	//printf("-%d\n", insData->dd);
	//printf("工作状态:%d\n", insData->Workingstatus);
	delete insData;
	return 0;
}
