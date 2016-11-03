#ifndef __VEHICLEMARKERTOOL_H__
#define __VEHICLEMARKERTOOL_H__


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

// 自己写的
#include "../GisCore/SvgMarkerTool.h"

//SVG 标绘工具
class VehicleMarkerTool : public SvgMarkerTool
{
	Q_OBJECT
public:
	VehicleMarkerTool(QgsMapCanvas* mapCanvas);
	~VehicleMarkerTool();
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
	//获取标绘点坐标链表
	const QList<QgsPoint> &points() { return mPointList; }
	//获取Svg标绘点句柄
	const QList<QgsAnnotationItem*> &Svgpoints() { return mSvgList; }

#endif
};
	

#endif //__VEHICLEMARKERTOOL_H__