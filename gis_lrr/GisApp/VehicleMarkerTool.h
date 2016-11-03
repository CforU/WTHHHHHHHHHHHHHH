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

// �Լ�д��
#include "../GisCore/SvgMarkerTool.h"

//SVG ��湤��
class VehicleMarkerTool : public SvgMarkerTool
{
	Q_OBJECT
public:
	VehicleMarkerTool(QgsMapCanvas* mapCanvas);
	~VehicleMarkerTool();
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
	//��ȡ������������
	const QList<QgsPoint> &points() { return mPointList; }
	//��ȡSvg������
	const QList<QgsAnnotationItem*> &Svgpoints() { return mSvgList; }

#endif
};
	

#endif //__VEHICLEMARKERTOOL_H__