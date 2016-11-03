#ifndef MARKERTOOL_H
#define MARKERTOOL_H

//qt
#include <QObject>
#include <QMouseEvent>
#include <QList>
#include <qfile.h>
#include <qtextstream.h>
//QSeq
#include <QSqlQuery>
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
#include "qgsmapmouseevent.h"
#include <qgsvectorlayer.h>
#include "qgsfeature.h"
#include <qgsgeometryvalidator.h>
#include <qgsvertexmarker.h>
#include "qgsrubberband.h"
#include "qgis.h"




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
#include "MapManager.h"

//AddFeatureTool

class MarkerTool : public QgsMapTool
{
	Q_OBJECT
public:
	/*
	enum CaptureMode // 矢量化类型
	{
		CaptureNone,       // 无
		CapturePoint,      // 点
		CaptureLine,       // 线
		CapturePolygon     // 面
	};*/
	

	MarkerTool(QgsMapCanvas* mapCanvas);
	~MarkerTool();

	//! 重写鼠标指针释放事件
	void canvasReleaseEvent(QgsMapMouseEvent* e) override;
	// 重写鼠标双击事件
	void canvasDoubleClickEvent(QgsMapMouseEvent* e) override;
	// 重写鼠标按下事件
	void canvasPressEvent(QgsMapMouseEvent* e) override;
	// 重写鼠标移动事件
	void canvasMoveEvent(QgsMapMouseEvent* e) override;
	//获取标绘点路径
	const QList<QgsPoint> &points() { return m_captureList; }

//private:
public:
	//Svg item 相关  (自动标绘)
	//创建item
	QgsSvgAnnotationItem* createItem(QgsPoint pos, QString svgPath);
	//更新item位置
	void updateItemPositon(QgsAnnotationItem* sItem, QgsPoint pos);
	//删除item
	int deleteItem(QgsAnnotationItem* sItem);
	//删除所有item
	void deleteItemAll();
	//pos所在的item
	QgsAnnotationItem* itemAtPos(QPointF pos);
	//获取选中的item
	QgsAnnotationItem* selectedItem(); 

	//路径相关操作 
	//创建画布
	QgsRubberBand*  createRubberBand();
	//画布添加点  插入 追加 
	int rubberBandInsertPoint(QgsRubberBand* mRubberBand, int index, const QgsPoint& point);
	int rubberBandAppendPoint(QgsRubberBand* mRubberBand, const QgsPoint& point);
	//画布删除点 中间删除 末尾删除
	int rubberBandRemovePoint(QgsRubberBand* mRubberBand, int index, const QgsPoint& point);
	int rubberBandDeletePoint(QgsRubberBand* mRubberBand, const QgsPoint& point);
	//画布移动点
	int rubberBandMovePoint(QgsRubberBand* mRubberBand, int index, const QgsPoint& point);
	//删除画布
	void deleteRoute(QgsRubberBand* mRubberBand);
	
	
	//####################################################//

	//所有的路径类型的标绘句柄链表
	QList<QgsAnnotationItem*>  PathMarkerList;
	//所有的车辆类型的标绘句柄链表
	QMap<int /*id*/, QgsAnnotationItem* /*句柄*/>  CarMarkerMap;

	QgsAnnotationItem::MouseMoveAction mCurrentMoveAction;
	QPointF mLastMousePosition;
	QgsPoint mMovePoint;
	bool moveFlag;//移动点标志
	bool itemSelectFlag=false;
	int pointIndex;//需要移动的点的索引
	

	//创建路径标绘
	QgsRubberBand* createRoute();
	QgsRubberBand* createRoutePoint(const QgsPoint& point);
	//添加路径点 仅仅标线
	int addRoutePoint(QgsRubberBand* mRubberBand,const QgsPoint& point);
	//标绘路径点 标线和图标
	QgsSvgAnnotationItem* MarkerRoutePoint(QgsRubberBand* mRubberBand, const QgsPoint& point, QString svgPath);
	//删除路径
	void deleteRoute(QgsRubberBand* mRubberBand, QList<QgsAnnotationItem*>  PathMarkerList);
	
	

	//************  手动标绘 ** //

	//标绘路径 
	//所有标绘点
	//QList<QgsPoint> m_captureList;
	//添加线
	//QgsRubberBand* mRubberBand;//绘制线 画布
	void markerLine(QgsMapMouseEvent* e);
	int  addRoutePoint(const QgsPoint& point);
	void deleteRoute();
	//手动标绘
	void ManuallyMaker(QgsPoint pos)
	//点标绘
	void markerPoint(QgsMapMouseEvent* e);
	void markerPoint(QgsPoint pos, int type);
	
public:			
	//清除地图 删除所有车辆和路线
	void clearUpMarker();

public: //手动标绘使用
	static  int MarkerType;//标绘图标类型
	static  QString MarkerIcon;// 标绘SVG图标路径
	static  QString defaultMarkerIcon;//默认标绘SVG图标路径
	static void setMarkerType(int type); //设置标绘图标类型
	static void setMarkerIconPath(QString path); //设置标绘SVG图标路径
	static void setDefaultMarkerIcon(QString path);//设置默认标绘SVG图标路径
};


#endif // MARKERTOOL_H