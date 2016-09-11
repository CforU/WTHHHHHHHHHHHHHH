#include "MapTools.h"

#define		POINT_INDEX		1	//点索引号

/*
// 获取当前图层
QgsVectorLayer* layer = qobject_cast<QgsVectorLayer*>(mCanvas->currentLayer());
// 得到点坐标，转换为地图坐标
QgsPoint savePoint = toLayerCoordinates(layer, mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()));
//事件处理
if (e->button() == Qt::LeftButton) // 鼠标左键
	{
		switch (currentToolType)
		{
		case ToolTypeNone:
			break;
		case MarkerPoint:
			break;
		case MarkerLine:
			break;
		case MarkerNone:
			break;
		case MeasureLine:
			break;
		case MeasureArea:
			break;
		default:
			break;
		}
	}
if (e->button() == Qt::RightButton) // 鼠标右键
{

	switch (currentToolType)
	{
	case ToolTypeNone:
		break;
	case MarkerPoint:
		break;
	case MarkerLine:
		break;
	case MarkerNone:
		break;
	case MeasureLine:
		break;
	case MeasureArea:
		break;
	default:
		break;
	}
}

*/


MapTools::MapTools(QgsMapCanvas* mapCanvas)
: QgsMapTool(mapCanvas)
{
}

MapTools::~MapTools()
{
}

// 1 重写鼠标释放事件 
void MapTools::canvasReleaseEvent(QgsMapMouseEvent* e)
{
	Q_UNUSED(e);
}

//重写鼠标双击事件
void MapTools::canvasDoubleClickEvent(QgsMapMouseEvent* e)
{
	Q_UNUSED(e);
}

// 重写鼠标按下事件
void MapTools::canvasPressEvent(QgsMapMouseEvent* e) 
{
	Q_UNUSED(e);
}

// 重写鼠标移动事件
void MapTools::canvasMoveEvent(QgsMapMouseEvent* e) {
	Q_UNUSED(e);
}


