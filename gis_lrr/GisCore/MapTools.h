#ifndef __MAPTOOLS_H__
#define __MAPTOOLS_H__


// Gis maptool
#include "qgsmaptool.h"
#include <qgsmaptoolpan.h>
#include <qgsmaptoolzoom.h>
// tool
#include "maptoolpan.h"
#include "MeasureTool.h"
#include "SvgMarkerTool.h"
#include "ALPMarkerTool.h"


class MapTools 
{	
public:
	//MapTools(QgsMapCanvas* mapCanvas);//通用构造
	MapTools();//通用构造
	~MapTools();
	void create_mapTool();

public:
	QgsMapToolZoom *mZoomIn;
	QgsMapToolZoom *mZoomOut;
	MapToolPan *mPan;
#ifdef HAVE_TOUCH
	//	QgsMapTool *mTouch; //地图触摸工具
#endif
	//测量
	MeasureTool* addMeasureToolLine;
	MeasureTool* addMeasureToolArea;
	//标绘
	SvgMarkerTool* svgMarkerTool;
	ALPMarkerTool* ALPMarkerTool;
private:
	//QgsMapCanvas* mapCanvas;
};


#endif //__MAPTOOLS_H__