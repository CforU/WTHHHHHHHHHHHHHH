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

//SVG ��湤��
class RouteMarkerTool : public QgsMapTool
{
	Q_OBJECT
public:
	RouteMarkerTool(QgsMapCanvas* mapCanvas);
	~RouteMarkerTool();
#if 0
	//! ��д���ָ���ͷ��¼�
	void canvasReleaseEvent(QgsMapMouseEvent* e) override;
	// ��д���˫���¼�
	void canvasDoubleClickEvent(QgsMapMouseEvent* e) override;
	// ��д��갴���¼�
	void canvasPressEvent(QgsMapMouseEvent* e) override;
	// ��д����ƶ��¼�
	void canvasMoveEvent(QgsMapMouseEvent* e) override;

public:

	
#endif
};

#endif //__ROUTEMARKERTOOL_H__