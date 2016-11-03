#ifndef __GISHEADER_H__
#define  __GISHEADER_H__

#if 1
enum MarkerRoutePointType{
	RouteDefault,
	StartPoint, //起点
	PassPoint,  //经过的点 中点
	EndPoint,   //终点 
};
enum MarKerVehicleType
{
	CarDefault,
	CommandCar = 4,     //指挥车
	UAV,            //无人机
	TrackedVehicle, //履带车
	DumpedCar,      //抛投车
	WheelPatrolCar, // 轮巡车
	WheeledVehicles //轮式车
};


#endif

#endif // __GISHEADER_H__