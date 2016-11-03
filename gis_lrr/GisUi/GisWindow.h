#ifndef __GISWINDOW_H__
#define __GISWINDOW_H__

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

//QGIS tool QgsMapToolTouch
#include <qgsmaptoolpan.h>
#include <qgsmaptoolzoom.h>



//ui
//#include "GisUi\ContrlBar.h"

#include "LeftBar.h"
#include "RightBar.h"
#include "MarkerBar.h"
#include "IconBar.h"
#include "MapSearchBox.h"
//gis core 
#include "../GisCore/GisSystem.h"
#include "../GisCore/MeasureTool.h"
//#include "../GisCore/MapManager.h"
#include "../GisCore/RouteAnalysis.h"
#include "modules\INS\INS.h"
#include "../GisApp/MarkerTool.h"
//地图画布

// RCS 数据 事件和结构
//#include "PushEvent.h"
//#include "GisData.h"

class GisWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GisWindow(QWidget *parent = 0);
	void  init_ui();
	void  connect_signal();
	bool  eventFilter(QObject *target, QEvent *event);//事件过滤
	
private slots:
	//search box show and hide
	void on_search(void);
	//search
	void getSearchText();
	//标绘
	void on_Marker();
	//返回
	void on_return();
	//确定

	//显示当前经纬度坐标
	void showMousePoint(const QgsPoint& p);
	//显示当前测量长度
	void showMesureLength(double length);
	//显示当前测量面积
	void showMesureArea(double Area);
	//test
	void on_eightBtn_clicked();

private:	

	//菜单栏
	LeftBar    * leftBar;
	IconBar    * iconBar;
	RightBar   * rightBar;
	QStackedWidget *leftStack;
	bool      mMarkerFlag;//标绘标志
	bool      ScaleFlagsEnable;//比例尺使能标志

	//UI控件
	//search box
	MapSearchBox *searchBox;
	bool          searchFlag;


	//中心窗体
	QMainWindow    *MapWidget;
	// 地图画布  放上面去了
	GisSystem     *mGisSystem;// 地图地图系统  需要最先构建	 
	//地图状态栏
	QStatusBar *sta;
	//地图坐标
	QLabel * m_lblCoordinate;
	//长度距离
	QLabel * m_labLengthAndArea;


	QSize WidgetSize;//主窗体大小
	QSize MapSize;//地图画布大小
	
	
	// 解析RCS数据 返回经纬坐标和ID
	//void Resolver(GisData *Data);
	//地图中心切换标志
	bool      centerFlag = true;
	

public: //API接口
	// 提供给其他人以模块的
	//初始化 加载地图  加载当前位置  (从惯导获取当前位置  标绘当前位置)
	void  init();   
	//放大 缩小 移动 (漫游)  已经作为公有槽函数 可以直接调用
	//路径保存
	void PathSave2Sql();//路径保存
	void PathSave2Xml();//路径保存
	//需要 数据库提供的本模块接口有 LoadHisttoryPath(加载历史路径) 和 SavePath();(保存路径到数据库)
	// 1 加载历史路径 需要封装一个path类
	int  LoadHistoryRoad(/* path 路径编号 */);  

	// ########### 路径操作 规划/分析/ #################
	void PathPloting(QgsPoint from, QgsPoint to);//路径规划
	int  AutoRoutePloting();    //  2 自动规划路径 可以调用 PathPloting
	//路径更新
	int  MarkerVehiclePosition();  //标记位置(position/类型)  负责标绘和更新车辆位置
	int  MarkerVehicleAdvanceRoute();  //标绘路径(行进路径)
	//路径自动进标绘
	void PathMarker(/*起点 中间点 终点 */);//路径标绘(一般用作标绘历史路径或者标绘自动规划的路径)
	
	//########## 以下优先完成###############

	//登录成功之后发送的事件处理 
	//连接的时候标绘
	//断开连接的时候清除标绘
	//RCS 实时更新数据处理 安装事件过滤器 
	
	 //车辆位置点标绘
	 //void markerVehichle();
	 void VehicleMarker(QgsPoint pos, int id);//车辆标绘 
	 //位置点 更新处理接口
	 void updatePosition(int id, QgsPoint pos);
	 //清除地图标绘接口
	 void delteVechile(int id);//删除车辆标绘点
	 void clearUpMap();//清空地图


};

#endif // __GISWINDOW_H__
