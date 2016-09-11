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
	enum CaptureMode // 矢量化类型
	{
		CaptureNone,       // 无
		CapturePoint,      // 点
		CaptureLine,       // 线
		CapturePolygon     // 面
	};

	MarkerTool(QgsMapCanvas* mapCanvas , CaptureMode cptflag);
	~MarkerTool();

	//! 重写鼠标指针释放事件
	void canvasReleaseEvent(QgsMapMouseEvent* e) override;
	// 重写鼠标双击事件
	void canvasDoubleClickEvent(QgsMapMouseEvent* e) override;
	// 重写鼠标按下事件
	void canvasPressEvent(QgsMapMouseEvent* e) override;
	// 重写鼠标移动事件
	void canvasMoveEvent(QgsMapMouseEvent* e) override;

	//void paint(QgsMapCanvas* mapCanvas, QgsPoint savePoint);
	
	const QList<QgsPoint> &points() { return m_captureList; }

	//// 测试移动使用
	bool tFlag;//定时器启动标志
	int num ;//当前移动索引
	void create_point();
	double angle;//旋转角度
	QPoint PathPoint[60];
	QList<QPoint*> pp;
	QTimer *testTimer;
public slots:
	void  movePath(void);
	//标绘点
	void  markerPoint(QgsPoint point);
	//标绘路径
	void  markerPath(QList<QgsPoint> path);


private:
	int addVertex(const QgsPoint& point);
	void markerPoint(QgsMapMouseEvent* e);
	void markerLine(QgsMapMouseEvent* e);
	int nextPoint(const QgsPoint& mapPoint, QgsPoint& layerPoint);
	QgsRubberBand* createRubberBand(QGis::GeometryType geometryType = QGis::Line, bool alternativeBand = false);

	QgsRubberBand *pRubber;//绘制点 画布
	QgsRubberBand *pRubber2;//绘制拐点 画布
	QgsRubberBand* mRubberBand;//绘制线 画布

	bool moveFlag;//移动点标志
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
	//标绘图标
	static  QString MarkerIcon;// Path
	static  QString defaultMarkerIcon;//Path
	static void setMarkerIconPath(QString path);
	static void setDefaultMarkerIcon(QString path);


};


#endif // MARKERTOOL_H