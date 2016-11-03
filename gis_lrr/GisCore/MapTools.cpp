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
//创建地图工具 不建议内部创建
void MapTools::create_mapTool()
{
#if 0
	mZoomIn = new QgsMapToolZoom(mapCanvas, false /* zoomIn */);
	mZoomOut = new QgsMapToolZoom(mapCanvas, true /* zoomOut */);
	mPan = new QgsMapToolPan(mapCanvas);
#ifdef HAVE_TOUCH
	//mapTools.mTouch = new QgsMapToolTouch(mapCanvas); //触摸
#endif
	//测量
	addMeasureToolLine = new MeasureTool(mapCanvas, false);
	addMeasureToolArea = new MeasureTool(mapCanvas, true);
	//标绘
	//标绘
	mapTools.svgMarkerTool = new SvgMarkerTool(mapCanvas);
	mapTools.ALPMarkerTool = new ALPMarkerTool(mapCanvas);
#endif
}