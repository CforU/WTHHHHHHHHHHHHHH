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
	//MapTools(QgsMapCanvas* mapCanvas);//ͨ�ù���
	MapTools();//ͨ�ù���
	~MapTools();
	void create_mapTool();

public:
	QgsMapToolZoom *mZoomIn;
	QgsMapToolZoom *mZoomOut;
	MapToolPan *mPan;
#ifdef HAVE_TOUCH
	//	QgsMapTool *mTouch; //��ͼ��������
#endif
	//����
	MeasureTool* addMeasureToolLine;
	MeasureTool* addMeasureToolArea;
	//���
	SvgMarkerTool* svgMarkerTool;
	ALPMarkerTool* ALPMarkerTool;
private:
	//QgsMapCanvas* mapCanvas;
};


#endif //__MAPTOOLS_H__