#ifndef __GISHEADER_H__
#define  __GISHEADER_H__

#if 1
enum MarkerRoutePointType{
	RouteDefault,
	StartPoint, //���
	PassPoint,  //�����ĵ� �е�
	EndPoint,   //�յ� 
};
enum MarKerVehicleType
{
	CarDefault,
	CommandCar = 4,     //ָ�ӳ�
	UAV,            //���˻�
	TrackedVehicle, //�Ĵ���
	DumpedCar,      //��Ͷ��
	WheelPatrolCar, // ��Ѳ��
	WheeledVehicles //��ʽ��
};


#endif

#endif // __GISHEADER_H__