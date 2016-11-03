#include "MapTools.h"

MapTools::MapTools(): mZoomIn(nullptr)
, mZoomOut(nullptr)
, mPan(nullptr)
#ifdef HAVE_TOUCH
//	, mTouch(0)
#endif
, addMeasureToolLine(nullptr)
, addMeasureToolArea(nullptr)
, svgMarkerTool(nullptr)
, ALPMarkerTool(nullptr)
{
}

MapTools::~MapTools()
{
}
//������ͼ���� �������ڲ�����
void MapTools::create_mapTool()
{
#if 0
	mZoomIn = new QgsMapToolZoom(mapCanvas, false /* zoomIn */);
	mZoomOut = new QgsMapToolZoom(mapCanvas, true /* zoomOut */);
	mPan = new QgsMapToolPan(mapCanvas);
#ifdef HAVE_TOUCH
	//mapTools.mTouch = new QgsMapToolTouch(mapCanvas); //����
#endif
	//����
	addMeasureToolLine = new MeasureTool(mapCanvas, false);
	addMeasureToolArea = new MeasureTool(mapCanvas, true);
	//���
	//���
	mapTools.svgMarkerTool = new SvgMarkerTool(mapCanvas);
	mapTools.ALPMarkerTool = new ALPMarkerTool(mapCanvas);
#endif
}