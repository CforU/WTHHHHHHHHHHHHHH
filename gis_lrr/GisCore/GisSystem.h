#ifndef __GISSYSTEM_H__
#define __GISSYSTEM_H__

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

#include <qgraphicswidget.h>
//#inlcude <QGraphicsGridLayout>
#include "qgraphicsgridlayout.h"

// QGis include
#include <qgsmapcanvas.h>
#include <qgsmaplayer.h>
#include <qgsmaptool.h>
#include <qgsvectorlayer.h>
#include <qgsmaplayerregistry.h>
#include <qgsrasterlayer.h>


#include "QgsLayerTreeView.h"
#include "QgsLayerTreeMapCanvasBridge.h"
#include <QgsProject.h>
#include <QgsLayerTreeModel.h>


//QGIS tool QgsMapToolTouch
#include <qgsmaptoolpan.h>
#include <qgsmaptoolzoom.h>



//ui
//#include "GisUi\ContrlBar.h"

//tool
#include "maptoolpan.h"
#include "SvgMarkerTool.h"
#include "ALPMarkerTool.h"
#include "MeasureTool.h"
//#include "MapManager.h"
#include "RouteAnalysis.h"
//#include "modules\INS\INS.h"

#include "MapTools.h"
#include <qpainter.h>
#include <QPaintEvent>
//地图画布

// RCS 数据 事件和结构
//#include "PushEvent.h"
//#include "GisData.h"

class GisSystem : public QMainWindow
{
    Q_OBJECT
public:
	enum MapControl{
		Left,Right,Up,Down,
		ZoomIn,ZoomOut
	};
	explicit GisSystem(QWidget *parent = 0);
	void paintEvent(QPaintEvent *);

private:
	void SysInit();
signals:
	//void emitText(QString Text);
	//移动信号
	//void moveSignal(MapControl c);
	void sendData(int, int);
public slots :
	// 添加矢量图层
	void addVectorLayers();
	// 添加栅格图层
	void addRasterLayers();
	//加载多种地图
	void MapLoad();
	//使用放大功能
	void zoomInMode();
	//缩小
	void zoomOutMode();
	//漫游
	void panMode();
	//全屏
	void zoomFull();
	//激活标绘点工具
	void MarkerSvg(); //svg
	void ALPMarler();// ALP Area Line Point

	//激活测距离工具
	void Measure_Line();
	//激活测面积工具
	void Measure_Area();
	//重置测量标记信息 进入下次测量
	void ResetMeasure();	
	//设置是否开启比例尺
	void setScaleBarEnable(bool);
	//显示比例尺
	void showScaleBar(QPainter *theQPainter);	
	// 我的位置	
	QgsSvgAnnotationItem* showMyPos(QgsPoint pos, QString svgPath);
	// 上下左右移动地图的槽函数
	void LeftMove();
	void RightMove();
	void UpMove();
	void DownMove();
	//最终操作的槽函数
	void MoveAndControlMap(MapControl c);
	//标记
	//void updateMarker();//坐标移动
	//显示和隐藏图层管理器
	void show_LayerManager();
	void hide_LayerManager();
	//初次加载
	void firstLoad();

private:
	QgsSvgAnnotationItem* mySelfItem = nullptr;
	bool      ScaleFlagsEnable;//比例尺使能标志		
	//地图中心切换标志
	bool centerFlag = true;
	void create_mapTool();//在MapTools中已经做了

	//! 图层管理
	QgsLayerTreeView* mlayerTreeView;
	QGraphicsProxyWidget* view;//mlayerTreeView 的代理
	QgsLayerTreeMapCanvasBridge *mlayerTreeCanvasBridge;
	void initLayerTreeView();

public:		
	QList<QgsMapCanvasLayer> mapCanvasLayerSet; // 地图画布所用的图层集合
	QgsMapCanvas  *mapCanvas;// 地图画布  需要最先构建	
	//MapManager    *mMapManager;//地图管理器 
	RouteAnalysis *mRouteAnalysis;//路径分析
	//地图工具
	MapTools  mapTools; //是否提供获取函数

	//切换地图工具
	void setMapTool(QgsMapTool *tool);
	//清空地图
	 void clearUpMap();

	 /*--- add on 2016/10/31 ---*/
	 double myActualSize;
	 double myScaleBarWidth;
	 /*----------------------------*/
};

#endif // __GISSYSTEM_H__
