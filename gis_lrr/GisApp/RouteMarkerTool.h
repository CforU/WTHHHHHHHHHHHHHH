#ifndef __ROUTEMARKERTOOL_H__
#define __ROUTEMARKERTOOL_H__

//Qt
#include <QGraphicsScene>

//QGis
#include <qgsmaptool.h>
#include <qgsmapcanvas.h>
#include "qgsmaptopixel.h"
#include <qgssymbollayerv2.h>
#include <qgssymbolv2.h>
#include <qgsmarkersymbollayerv2.h>
#include <qgsvectorlayerrenderer.h>
#include "qgssvgannotationitem.h"

#include "qgsmapmouseevent.h"

#include "QgsProject.h"

//SVG 标绘工具
class RouteMarkerTool : public QgsMapTool
{
	Q_OBJECT
public:
	RouteMarkerTool(QgsMapCanvas* mapCanvas);
	~RouteMarkerTool();
#if 0
	//! 重写鼠标指针释放事件
	void canvasReleaseEvent(QgsMapMouseEvent* e) override;
	// 重写鼠标双击事件
	void canvasDoubleClickEvent(QgsMapMouseEvent* e) override;
	// 重写鼠标按下事件
	void canvasPressEvent(QgsMapMouseEvent* e) override;
	// 重写鼠标移动事件
	void canvasMoveEvent(QgsMapMouseEvent* e) override;

public:

	
#endif
};

#endif //__ROUTEMARKERTOOL_H__