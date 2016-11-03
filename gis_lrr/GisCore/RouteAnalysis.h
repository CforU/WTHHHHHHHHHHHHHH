#ifndef __ROUTEANALUSIS_H__
#define __ROUTEANALUSIS_H__

//this class for Analysis to the map


class RouteAnalysis
{
public:
	RouteAnalysis();
	~RouteAnalysis();
	//路径标绘
	void RoutePloting();
	//路径规划
	void RoutPlanning();//应该是两个参数 一个起点 一个重点
};

#endif //__ROUTEANALUSIS_H__