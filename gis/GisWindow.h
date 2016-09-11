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

//QGIS tool
#include <qgsmaptoolpan.h>
#include <qgsmaptoolzoom.h>

//ui
#include "GisUi\ContrlBar.h"
#include "GisUi\LeftBar.h"
#include "GisUi\RightBar.h"
#include "GisUi\ContrlBar.h"
#include "GisUi\MarkerBar.h"
#include "GisUi\MapSearchBox.h"
//tool
#include "MarkerTool.h"
#include "MeasureTool.h"
#include "MapManager.h"
#include "RouteAnalysis.h"
#include "INS.h"
//地图画布

class GisWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GisWindow(QWidget *parent = 0);
	void  init_ui();
	void  connect_signal();

	//设置是否开启比例尺
	void setScaleBarEnable(bool);

signals:
	void emitText(QString Text);

public slots :
	// 添加矢量图层
	void addVectorLayers();
	// 添加栅格图层
	void addRasterLayers();
	//使用放大功能
	void zoomInMode();
	//缩小
	void zoomOutMode();
	//漫游
	void panMode();
	//全屏
	void zoomFull();
	//激活标绘点工具
	void on_Action_AddFeatureTool_Point();
	void on_Action_AddFeatureTool_Line();
	void on_Action_AddFeatureTool_None();
	//激活测距离工具
	void on_actionMeasure_Line();
	//激活测面积工具
	void on_actionMeasure_Area();
	//search box show and hide
	void on_search(void);
	//search
	void getSearchText();
	//标绘
	void on_Marker();
	//返回
	void on_return();
	//标记
//	void updateMarker();//坐标移动算法
	//显示当前经纬度坐标
	void showMousePoint(const QgsPoint& p);
	//显示当前测量长度
	void showMesureLength( double length);
	//显示当前测量面积
	void showMesureArea(double Area);
	//显示比例尺
	void showScaleBar(QPainter *theQPainter);
	//test
	void on_eightBtn_clicked();
	// 我的位置
	void showMyPos(void);
public:	
	
	MapManager    *mMapManager;//地图管理器 
	RouteAnalysis *mRouteAnalysis;//路径分析
	INS           *mINS;//惯导
	//菜单栏
	LeftBar    * leftBar;
	ContrlBar  * iconBar;
	RightBar   * rightBar;
	QStackedWidget *leftStack;
	bool      mMarkerFlag;
	bool      ScaleFlagsEnable;
	//UI控件
	//search box
	MapSearchBox *searchBox;
	bool   searchFlag;

	//中心窗体
	QMainWindow    *MapWidget;
	// 地图画布
	QgsMapCanvas* mapCanvas;
	 

	//地图状态栏
	QStatusBar *sta;
	//地图坐标
	QLabel * m_lblCoordinate;
	//长度距离
	QLabel * m_labLengthAndArea;

	QSize WidgetSize;//主窗体大小
	QSize MapSize;//地图画布大小
	

	//接口 

	

};

#endif // __GISWINDOW_H__
