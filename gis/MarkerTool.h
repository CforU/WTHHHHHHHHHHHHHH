#ifndef MARKERTOOL_H
#define MARKERTOOL_H

#include <QObject>
#include <QMouseEvent>
#include <QList>
#include <qgsmaptool.h>
#include <qgsmapcanvas.h>
#include "qgsmapmouseevent.h"
#include <qgsvectorlayer.h>
#include "qgsfeature.h"
#include <qgsgeometryvalidator.h>
#include <qgsvertexmarker.h>
#include "qgsrubberband.h"
#include "qgis.h"
#include <QStringList>
#include <qgsvectorlayer.h>
#include <qgslogger.h>
#include <qgsvectordataprovider.h>
#include "qgscsexception.h"
#include "qgsproject.h"
#include "qgsmaplayerregistry.h"
#include "qgsmaptopixel.h"
#include "qgsgeometry.h"
#include "qgsfeature.h"
/*
#include <QgsSvgMarkerSymbolLayerV2>
#include <QgsSymbolLayerV2List>
#include <QgsMarkerSymbolV2>
#include <QgsMarkerSymbolV2>
#include <QgsSvgAnnotationItem>
*/
#include <qgsmaptool.h>
#include <qgsmapcanvas.h>
#include "qgsmapmouseevent.h"
#include <qgsvectorlayer.h>
#include "qgsfeature.h"
#include <qgsgeometryvalidator.h>
#include <qgsvertexmarker.h>
#include "qgsrubberband.h"
#include "qgis.h"


#include <qgssymbollayerv2.h>
#include <qgssymbolv2.h>
#include <qgsmarkersymbollayerv2.h>
#include <qgsvectorlayerrenderer.h>
#include <qgsrendercontext.h>
#include <qgssinglesymbolrendererv2.h>
#include <qgssymbollayerv2.h>
#include "qgssvgannotationitem.h"
#include <QStringList>
#include <qgsvectorlayer.h>
#include <qgslogger.h>
#include <qgsvectordataprovider.h>
#include "qgscsexception.h"
#include "qgsproject.h"
#include "qgsmaplayerregistry.h"
#include "qgsmaptopixel.h"
#include "qgsgeometry.h"
#include "qgsfeature.h"
#include "qgsdistancearea.h"


#include "MapTools.h"

//AddFeatureTool

class MarkerTool : public MapTools
{
	Q_OBJECT

public:
	enum CaptureMode // ʸ��������
	{
		CaptureNone,       // ��
		CapturePoint,      // ��
		CaptureLine,       // ��
		CapturePolygon     // ��
	};

	MarkerTool(QgsMapCanvas* mapCanvas , CaptureMode cptflag);
	~MarkerTool();

	//! ��д���ָ���ͷ��¼�
	void canvasReleaseEvent(QgsMapMouseEvent* e) override;
	// ��д���˫���¼�
	void canvasDoubleClickEvent(QgsMapMouseEvent* e) override;
	// ��д��갴���¼�
	void canvasPressEvent(QgsMapMouseEvent* e) override;
	// ��д����ƶ��¼�
	void canvasMoveEvent(QgsMapMouseEvent* e) override;

	//void paint(QgsMapCanvas* mapCanvas, QgsPoint savePoint);
	
	const QList<QgsPoint> &points() { return m_captureList; }

	//// �����ƶ�ʹ��
	bool tFlag;//��ʱ��������־
	int num ;//��ǰ�ƶ�����
	void create_point();
	double angle;//��ת�Ƕ�
	QPoint PathPoint[60];
	QList<QPoint*> pp;
	QTimer *testTimer;
public slots:
	void  movePath(void);
	//����
	void  markerPoint(QgsPoint point);
	//���·��
	void  markerPath(QList<QgsPoint> path);


private:
	int addVertex(const QgsPoint& point);
	void markerPoint(QgsMapMouseEvent* e);
	void markerLine(QgsMapMouseEvent* e);
	int nextPoint(const QgsPoint& mapPoint, QgsPoint& layerPoint);
	QgsRubberBand* createRubberBand(QGis::GeometryType geometryType = QGis::Line, bool alternativeBand = false);

	QgsRubberBand *pRubber;//���Ƶ� ����
	QgsRubberBand *pRubber2;//���ƹյ� ����
	QgsRubberBand* mRubberBand;//������ ����

	bool moveFlag;//�ƶ����־
	bool svgFlag;//
	CaptureMode mCptFlag;
	QList<QgsPoint> m_captureList;
	QgsAnnotationItem* itemAtPos(QPointF pos);
	QgsAnnotationItem::MouseMoveAction mCurrentMoveAction;
	QPointF mLastMousePosition;
	QgsPoint mMovePoint;

	void canvasPressEvent_MovePoint(QgsMapMouseEvent* e);
	void canvasMoveEvent_MovePoint(QgsMapMouseEvent* e);
	QgsAnnotationItem* selectedItem();
	//QgsAnnotationItem* itemAtPos(QPointF pos);

public:
	//���ͼ��
	static  QString MarkerIcon;// Path
	static  QString defaultMarkerIcon;//Path
	static void setMarkerIconPath(QString path);
	static void setDefaultMarkerIcon(QString path);


};


#endif // MARKERTOOL_H