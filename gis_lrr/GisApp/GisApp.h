#ifndef __GISAPP_H__
#define __GISAPP_H__

#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QFrame>
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QSize>
#include <QWidget>
#include <QPixmap>
#include <QPalette>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QtWidgets/QMainWindow>
#include <QList>
#include <QString>
#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QStatusBar>
#include <qtimer.h>

// QGis include
#include <qgsmapcanvas.h>
#include <qgsmaplayer.h>
#include <qgsmaptool.h>
#include <qgsvectorlayer.h>
#include <qgsmaplayerregistry.h>
#include <qgsrasterlayer.h>
#include "qgssvgannotationitem.h"

//QGIS tool QgsMapToolTouch
#include <qgsmaptoolpan.h>
#include <qgsmaptoolzoom.h>



//ui
//#include "GisUi\ContrlBar.h"

#include "../GisUi/LeftBar.h"
#include "../GisUi/RightBar.h"
#include "../GisUi/MarkerBar.h"
#include "../GisUi/IconBar.h"
#include "../GisUi/MapSearchBox.h"
//gis core 
#include "../GisCore/GisSystem.h"
#include "../GisCore/MeasureTool.h"
//#include "../GisCore/MapManager.h"
#include "../GisCore/RouteAnalysis.h"
#include "modules\INS\INS.h"

//
#include "../../modules/rcsettings/rcsetting.h"
//地图画布

#include "GisHeader.h"
#include "MarkerTool.h"
// RCS 数据 事件和结构
//#include "PushEvent.h"
//#include "GisData.h"
#include "ScaleWidget.h"
#include "FilterWidget.h"

class GisApp : public QWidget
{
    Q_OBJECT
public:
	explicit GisApp(QWidget *parent = 0);
	void  init_ui();
	void  connect_signal();
	bool  eventFilter(QObject *target, QEvent *event);//事件过滤
	
private slots:
	//search box show and hide
	void on_search(void);
	//开启导航
	void on_navagation();
	//地图切换
	void mapSwitch();
	//search
	void getSearchText();
	//标绘
	void on_Marker();
	//返回
	void on_return();
	//显示当前经纬度坐标
	void showMousePoint(const QgsPoint& p);
	//显示当前测量长度
	void showMesureLength(double length);
	//显示当前测量面积
	void showMesureArea(double Area);
	//是否显示比例尺
	void setShowScaleBar();
	//enter 按钮
	void on_enter();
	//图层管理器
	void on_LayerManager();

	//获取我的位置
	QgsPoint getMyPos();
	void showMyPos();
	void showMyPos(QgsPoint pos);//指定定点使用 以后可以不用
	//清空行进路径
	void clearAdvancePath();


private slots:
	void RightChildWidget_btn1_on_clicked();
	void RightChildWidget_btn2_on_clicked();
	void RightChildWidget_btn3_on_clicked();

private:	
	//菜单栏
	LeftBar    * leftBar;
	IconBar    * iconBar;
	RightBar   * rightBar;
	QStackedWidget *leftStack;
	bool      mMarkerFlag;//标绘标志
	bool      ScaleFlagsEnable;//比例尺使能标志
	bool      mMapLayerManagerFlag;//地图管理器显示
	//UI控件
	//search box
	MapSearchBox *searchBox;
	bool          searchFlag;
	QGraphicsProxyWidget* s;//searchBox 的代理

	//中心窗体
	QMainWindow    *MapWidget;
	// 地图画布  放上面去了
	GisSystem     *mGisSystem;// 地图地图系统  需要最先构建	 
	//车辆标绘工具
	MarkerTool   *mMarkerTool;

	//地图状态栏
	QStatusBar *sta;
	//地图坐标
	QLabel * m_lblCoordinate;
	//长度距离
	QLabel * m_labLengthAndArea;

	QSize WidgetSize;//主窗体大小
	QSize MapSize;//地图画布大小
	
	//地图中心切换标志 是否放到底层
	bool      centerFlag = true;
	//行进路径
	QgsRubberBand* travelPath;
	int vid;//车辆id 
	ScaleWidget* myWidget;//比例尺控件
	FilterWidget* myFilterWidget;//筛选

private:
#if 0
	//路径画布
	QgsRubberBand* mRubberBand;
	//所有的路径类型的标绘句柄链表
	QList<QgsAnnotationItem*>  PathMarkerList;
	//路径点的链表
	QList<QgsPoint>  PathMarkerPointList;
	//标绘路径点
	void markerRoutePoint(QgsPoint pos, QgsRubberBand* mRubberBand, MarkerRoutePointType type);

	//所有的车辆类型的标绘句柄链表
	QMap<int /*id*/, QgsAnnotationItem* /*句柄*/>  CarMarkerMap;
#endif
	//从数据库根据车辆id判断车辆的类型
	int getVehicleTypeId(int aVehicleType);//操作数据库获取类型id
	MarKerVehicleType getVechileType(int id);
	// 解析RCS数据 返回经纬坐标和ID
	//void Resolver(GisData *Data);
	void firstLoad();//初次加载
public: //API接口

	//初始化 加载地图  加载当前位置  (从惯导获取当前位置  标绘当前位置)
	void  init();   
		
	//路径保存加载
	void PathSave2Sql();//路径保存
	void PathSave2Xml();//路径保加载存
	void loadPath2xml();//路径
	void saveMarkerPath2File();//保存路径到文件
	void loadMarkerPath2File();//加载路径到文件
	// 1 加载历史路径 最好封装一个path类
	int  LoadHistoryRoad(/* path 路径编号 */);
	

	// ########### 路径操作 规划/分析/ #################
	//路径规划
	void PathPloting(QgsPoint from, QgsPoint to);
	//路径更新
	int  MarkerVehicleAdvanceRoute(QgsRubberBand* mRubberBand,QList<QgsPoint>  PathList);  //标绘路径(行进路径)
	//路径自动进标绘
	void RouteMarker(QList<QgsPoint>  PathList);

	//########## 车辆  ###############
	//车辆标绘 
	void VehicleMarker(QgsPoint pos, int id);
	//位置点 更新处理接口
	void updatePosition(int id, QgsPoint pos);
	//清除地图标绘接口
	void delteVechile(int id);//删除车辆标绘点

	//###################################
	//清空地图
	void clearUpMap();


	
#if 0
	void PathPloting(QgsPoint from, QgsPoint to);//路径规划
	int  AutoRoutePloting();    //  2 自动规划路径 可以调用 PathPloting
	//路径更新
	int  MarkerVehiclePosition();  //标记位置(position/类型)  负责标绘和更新车辆位置
	int  MarkerVehicleAdvanceRoute();  //标绘路径(行进路径)

	//路径自动进标绘
	void PathMarker(/*起点 中间点 终点 */);//路径标绘(一般用作标绘历史路径或者标绘自动规划的路径)
	//路径点标绘
	//所有的路径类型的标绘句柄链表
	QList<QgsAnnotationItem*>  PathMarkerList;
	QList<QgsPoint>  PathList; //路径点的链表
	QStringList m_stringPoints; //保存的时候用的列表

	//路径画布
	QgsRubberBand* mRubberBand;
	void markerRoutePoint(QgsPoint pos, QgsRubberBand* mRubberBand, MarkerRoutePointType type);
	void markerRoutePoint(QgsPoint pos, QgsRubberBand* mRubberBand);
	//路径标绘 /*起点 中间点 终点 */
	//void RouteMarker(QList<QgsAnnotationItem*>  PathMarkerList);
	void RouteMarker(QList<QgsPoint>  PathList);

	//########## 以下优先完成###############

	//登录成功之后发送的事件处理 
	//连接的时候标绘
	//断开连接的时候清除标绘
	//RCS 实时更新数据处理 安装事件过滤器 
	
	 //车辆位置点标绘
	 //void markerVehichle();
	
	 //所有的车辆类型的标绘句柄链表
	 QMap<int /*id*/, QgsAnnotationItem* /*句柄*/>  CarMarkerMap;
	 //车辆标绘
	 void VehicleMarker(QgsPoint pos, int id);
	 //位置点 更新处理接口
	 void updatePosition(int id, QgsPoint pos);
	 //清除地图标绘接口
	 void delteVechile(int id);//删除车辆标绘点

	 //清空地图
	 void clearUpMap();
#endif

};

#endif // __GISAPP_H__
