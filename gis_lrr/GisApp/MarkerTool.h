#ifndef MARKERTOOL_H
#define MARKERTOOL_H

//qt
#include <QObject>
#include <QtWidgets>
#include <QMouseEvent>
#include <QList>
#include <qfile.h>
#include <qtextstream.h>
//QSeq
#include <QSqlQuery>
//QGis
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



#include "GisHeader.h"
#include "../../modules/rcsettings/rcsetting.h"

//#include "../GisCore/MapTools.h"
//#include "../GisCore/MapManager.h" //不合理
//AddFeatureTool

class MarkerTool : public QgsMapTool
{
	Q_OBJECT
public:
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


public:
	void saveMarkerPath2File();//保存路径到文件
	void loadMarkerPath2File();//加载路径到文件
	void savePath2xml();
	void loadPath2xml();

private:
	int addVertex(const QgsPoint& point);
	void markerLine(QgsMapMouseEvent* e);

	QgsRubberBand* mRubberBand;//绘制线 画布

	QList<QgsPoint> m_captureList;
	QgsAnnotationItem::MouseMoveAction mCurrentMoveAction;
	QPointF mLastMousePosition;
	QgsPoint mMovePoint;
	bool moveFlag;//移动点标志
	bool itemSelectFlag=false;
	int pointIndex;//需要移动的点的索引

	//从数据库根据车辆id判断车辆的类型
	int getVehicleTypeId(int aVehicleType);//操作数据库获取类型id
	MarKerVehicleType getVechileType(int id);

public:
	//所有的标绘点句柄 包括车辆和其他图标
	QList<QgsAnnotationItem*>  MarkerPointList;
	//所有路径点管理链表
	//QList<QgsPoint>  PathList;//暂时未用

	//########## 所有标绘图标的管理################
	//所有的其他类型的标绘句柄链表 除去路径和车辆
	QList<QgsAnnotationItem*>  OhterMarkerList;
	//所有的路径类型的标绘句柄链表
	QList<QgsAnnotationItem*>  PathMarkerList;
	//所有的车辆类型的标绘句柄链表
	QMap<int /*id*/, QgsAnnotationItem* /*句柄*/>  CarMarkerMap;

	QList<QgsPoint>  PathMarkerPointList; //加载的时候用的链表
	QStringList m_stringPoints; //保存的时候用的列表

	//所有车辆标绘点的管理链表
	//所有的车辆类型的标绘句柄链表

	//所有路径 的管理
	//每条路径的路径点管理

	//点标绘
	void markerPoint(QgsMapMouseEvent* e);
	void markerPoint(QgsPoint pos, int type);
	//手动标绘
	void ManuallyMaker(QgsPoint pos);

	//item 相关
	QgsSvgAnnotationItem* createItem(QgsPoint pos, QString svgPath);//创建item
	QgsAnnotationItem* selectedItem(); //获取选中的item
	int deleteItem(QgsAnnotationItem* sItem);//删除item
	void deleteItemAll();
	QgsAnnotationItem* itemAtPos(QPointF pos);

	
public:	//外部调用
	//车辆标绘 
	QgsAnnotationItem* VehicleMarker(QgsPoint pos, MarKerVehicleType type);
	void VehicleMarker(QgsPoint pos, int id);
	//车辆位置更新 角度也要处理
	void updateVehiclePosition(QgsPoint pos, int id);
	//删除车辆
	void delteVechile(int id);//删除车辆标绘点
	
	//路径点标绘
	void markerRoutePoint(QgsPoint pos, MarkerRoutePointType type);
	//路径标绘 /*起点 中间点 终点 */
	void RouteMarker(QList<QgsAnnotationItem*>  PathMarkerList);
	void RouteMarker(QList<QgsPoint>  PathList);

	//清除地图 删除所有车辆和路线
	void clearUpMarker();

public: //手动标绘使用
	
	static  int MarkerType;//标绘图标类型
	static  QString MarkerIcon;// 标绘SVG图标路径
	static  QString defaultMarkerIcon;//默认标绘SVG图标路径
	static void setMarkerType(int type); //设置标绘图标类型
	static void setMarkerIconPath(QString path); //设置标绘SVG图标路径
	static void setDefaultMarkerIcon(QString path);//设置默认标绘SVG图标路径

signals:
	void createWidget();
public slots:
	void on_showMarker(int i);
	void on_hideMarker(int i);
};


#endif // MARKERTOOL_H