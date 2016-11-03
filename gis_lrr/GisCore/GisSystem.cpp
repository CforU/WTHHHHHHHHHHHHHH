
#include "GisSystem.h"

//#include "PushEvent.h"
//#include "GisData.h"

#include <QGraphicsProxyWidget>
#include <QGraphicsAnchorLayout>

GisSystem::GisSystem(QWidget *parent) :
QMainWindow(parent)
{
	QgsApplication::setPrefixPath("3rdparty/qgis/apps/qgis", true); // 注意：把这里的路径改成你电脑上Qgis的路径！！！
	QgsApplication::initQgis();
	SysInit();
	//init();//初始化
	
}

void GisSystem::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.drawPixmap(0, 0, QPixmap("Resources/icon/gis/mobil/bg_map_2.png"));
}

void GisSystem::SysInit()
{
	//地图画图创建 最先创建
	mapCanvas = new QgsMapCanvas();//创建
	mapCanvas->enableAntiAliasing(true);//开启反锯齿效果
	mapCanvas->setCanvasColor(QColor(255, 255, 255));
	mapCanvas->setVisible(true);
	this->setCentralWidget(mapCanvas);
	
	//地图管理类 需要在地图画布类之后
	//mMapManager = new MapManager(mapCanvas);
	//路径分析
	mRouteAnalysis = new RouteAnalysis();

	//创建地图工具
	create_mapTool();

	//! 初始化图层管理器
	//QWidget w;
	
#if 1
	mlayerTreeView = new QgsLayerTreeView(mapCanvas);
	initLayerTreeView();
	view = mapCanvas->scene()->addWidget(mlayerTreeView);
	view->setSelected(true);
	mlayerTreeView->move(mapCanvas->width(), 0);
	mlayerTreeView->hide();
	
#endif	
	//进行布局显示布局器

	//初次加载地图
	firstLoad();

	//信号连接 显示比例尺
	connect(mapCanvas, SIGNAL(renderComp lete(QPainter *)), this, SLOT(showScaleBar(QPainter *))); //显示比例尺


}

//创建地图工具
void GisSystem::create_mapTool(){
	mapTools.mZoomIn = new QgsMapToolZoom(mapCanvas, false /* zoomIn */);
	mapTools.mZoomOut = new QgsMapToolZoom(mapCanvas, true /* zoomOut */);
	mapTools.mPan = new MapToolPan(mapCanvas);
#ifdef HAVE_TOUCH
	//mapTools.mTouch = new QgsMapToolTouch(mapCanvas); //触摸
#endif
	//测量
	mapTools.addMeasureToolLine = new MeasureTool(mapCanvas, false);
	mapTools.addMeasureToolArea = new MeasureTool(mapCanvas, true);
	//标绘
	mapTools.svgMarkerTool = new SvgMarkerTool(mapCanvas);
	mapTools.ALPMarkerTool = new ALPMarkerTool(mapCanvas);


}

//图层管理器初始化函数
void GisSystem::initLayerTreeView()
{
	QgsLayerTreeModel* model = new QgsLayerTreeModel(QgsProject::instance()->layerTreeRoot(), this);
	model->setFlag(QgsLayerTreeModel::AllowNodeRename);
	model->setFlag(QgsLayerTreeModel::AllowNodeReorder);
	model->setFlag(QgsLayerTreeModel::AllowNodeChangeVisibility);
	model->setFlag(QgsLayerTreeModel::ShowLegendAsTree);
	model->setFlag(QgsLayerTreeModel::AllowLegendChangeState, false);
	model->setAutoCollapseLegendNodes(10);
	mlayerTreeView->setModel(model);
	
	//mlayerTreeView->setStyleSheet(styleTwo); //设置样式

	// 连接地图画布和图层管理器
	mlayerTreeCanvasBridge = new QgsLayerTreeMapCanvasBridge(QgsProject::instance()->layerTreeRoot(), mapCanvas, this);
	connect(QgsProject::instance(), SIGNAL(writeProject(QDomDocument&)), mlayerTreeCanvasBridge, SLOT(writeProject(QDomDocument&)));
	connect(QgsProject::instance(), SIGNAL(readProject(QDomDocument)), mlayerTreeCanvasBridge, SLOT(readProject(QDomDocument)));

}

//#############  地图操作 ##########################################
//添加矢量图层
void GisSystem::addVectorLayers()
{
	QString filename = QFileDialog::getOpenFileName(nullptr, QObject::tr("open vector"), "", "*.shp");
	QStringList temp = filename.split(QDir::separator());
	QString basename = temp.at(temp.size() - 1);
	QgsVectorLayer* vecLayer = new QgsVectorLayer(filename, basename, "ogr", false);
	if (!vecLayer->isValid())
	{
		//QMessageBox::critical(this, "error", "layer is invalid");
		return;
	}
	QgsMapLayerRegistry::instance()->addMapLayer(vecLayer);
	mapCanvasLayerSet.append(vecLayer);
	mapCanvas->setExtent(vecLayer->extent());
	mapCanvas->setLayerSet(mapCanvasLayerSet);//将图层加载到图层集内
	mapCanvas->setVisible(true);
	mapCanvas->freeze(false);
	QgsCoordinateReferenceSystem wgs84(4326, QgsCoordinateReferenceSystem::EpsgCrsId);
	QgsCoordinateReferenceSystem web(3857, QgsCoordinateReferenceSystem::EpsgCrsId);
	mapCanvas->setDestinationCrs(wgs84);  //坐标正确
	//mapCanvas->setDestinationCrs(web); //距离正确
	mapCanvas->setCrsTransformEnabled(true);
	mapCanvas->setExtent(mapCanvas->fullExtent());
	mapCanvas->zoomScale(10000);
	mapCanvas->refresh();//刷新图层
}

//添加栅格图层
void GisSystem::addRasterLayers()
{
	/*
	*第一次执行就是直接加载指定好的地图，
	*再次就可以通过点击按钮实现选择加载地图的功能
	*/
	QgsRasterLayer* rasterLayer;//创建一个栅格图层
	QString filename = QFileDialog::getOpenFileName(nullptr, QObject::tr("open vector"), "", "*.tif");
	QStringList temp = filename.split(QDir::separator());
	QString basename = temp.at(temp.size() - 1);
	rasterLayer = new QgsRasterLayer(filename, basename, "gdal", false);//将栅格地图数据加载到栅格图层中
	if (!rasterLayer->isValid())
	{
		return;
	}
	QgsMapLayerRegistry::instance()->addMapLayer(rasterLayer);//
	mapCanvasLayerSet.append(rasterLayer);
	mapCanvas->setExtent(rasterLayer->extent());
	mapCanvas->setLayerSet(mapCanvasLayerSet);
	mapCanvas->setVisible(true);
	mapCanvas->freeze(false);
	QgsCoordinateReferenceSystem wgs84(4326, QgsCoordinateReferenceSystem::EpsgCrsId);
	QgsCoordinateReferenceSystem web(3857, QgsCoordinateReferenceSystem::EpsgCrsId);
	mapCanvas->setDestinationCrs(wgs84);  //坐标正确
	//mapCanvas->setDestinationCrs(web); //距离正确
	mapCanvas->setCrsTransformEnabled(true);
	mapCanvas->setExtent(mapCanvas->fullExtent());
	mapCanvas->zoomScale(10000);
	mapCanvas->refresh();
}
//加载多种地图
//地图加载 //影像金字塔
void GisSystem::MapLoad(void)
{
	/*
	*第一次执行就是直接加载指定好的地图，
	*再次就可以通过点击按钮实现选择加载地图的功能
	*/
	QgsMapLayer* Layer;//创建一个图层

	QString filename = QFileDialog::getOpenFileName(nullptr, QObject::tr("open Map"), "", "*.tif *.shp");
	QStringList temp = filename.split(QDir::separator());
	QString basename = temp.at(temp.size() - 1);
	if (filename.isNull())
		return;

	QFileInfo  f(filename);
	if (f.suffix() == "tif"){
		Layer = new QgsRasterLayer(filename, basename, "gdal", false);//将栅格地图数据加载到栅格图层中
		//Layer = new QgsRasterLayer("Resources/mapdata/zgc.tif", "gdal", false);//将栅格地图数据加载到栅格图层中
		//rasterLayer = new QgsRasterLayer("C://Map//J50G001036_Level_19.tif", "gdal", false);//创建栅格图层
	}
	else if (f.suffix() == "shp"){
		Layer = new QgsVectorLayer(filename, basename, "ogr", false);
	}
	if (!Layer->isValid())
	{
		//QMessageBox::critical(this, "error", "layer is invalid");
		return;
	}
	QgsMapLayerRegistry::instance()->addMapLayer(Layer);//
	mapCanvasLayerSet.append(Layer);
	mapCanvas->setExtent(Layer->extent());
	mapCanvas->setLayerSet(mapCanvasLayerSet);
	mapCanvas->setVisible(true);
	mapCanvas->freeze(false);
	QgsCoordinateReferenceSystem wgs84(4326, QgsCoordinateReferenceSystem::EpsgCrsId);
	QgsCoordinateReferenceSystem web(3857, QgsCoordinateReferenceSystem::EpsgCrsId);
	mapCanvas->setDestinationCrs(wgs84);  //坐标正确
	//mapCanvas->setDestinationCrs(web); //距离正确
	mapCanvas->setCrsTransformEnabled(true);
	mapCanvas->setExtent(mapCanvas->fullExtent());
	mapCanvas->zoomScale(10000);
	mapCanvas->refresh();
}

//放大操作
void GisSystem::zoomInMode()
{
	if (mapCanvas->scale() > 1000){
		MoveAndControlMap(MapControl::ZoomIn);
	}
}
//缩小操作
void GisSystem::zoomOutMode()
{
	if (mapCanvas->scale() < 80000000){
		MoveAndControlMap(MapControl::ZoomOut);
	}
}
//漫游
void GisSystem::panMode()
{
	mapCanvas->setMapTool(mapTools.mPan);
}

//显示全屏
void GisSystem::zoomFull()
{

}

// 上下左右移动地图的槽函数
//左移
void GisSystem::LeftMove()
{
	MoveAndControlMap(MapControl::Left);	
}
//右移
void GisSystem::RightMove()
{
	MoveAndControlMap(MapControl::Right);
}
//上移
void GisSystem::UpMove()
{
	MoveAndControlMap(MapControl::Up);
	
}
//下移
void GisSystem::DownMove()
{
	MoveAndControlMap(MapControl::Down);
}
//最终操作的槽函数
void GisSystem::MoveAndControlMap(MapControl c)
{
	//地图中间点
	if (centerFlag == true){
		centerFlag = false;
	}
	
	QKeyEvent *e;
	switch (c)
	{
	case MapControl::Right:
		e = new QKeyEvent(QEvent::KeyPress, Qt::Key_Left, Qt::NoModifier, "aa", false, 1);
		QApplication::sendEvent(mapCanvas,e);
		break;

	case MapControl::Left:
		e = new QKeyEvent(QEvent::KeyPress, Qt::Key_Right, Qt::NoModifier, "aa", false, 1);
		QApplication::sendEvent(mapCanvas, e);
		break;

	case MapControl::Up:
		e = new QKeyEvent(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier, "aa", false, 1);
		QApplication::sendEvent(mapCanvas, e);
		break;

	case MapControl::Down:
		e = new QKeyEvent(QEvent::KeyPress, Qt::Key_Down, Qt::NoModifier, "aa", false, 1);
		QApplication::sendEvent(mapCanvas, e);
		break;

	case MapControl::ZoomIn:
		e = new QKeyEvent(QEvent::KeyPress, Qt::Key_PageUp, Qt::NoModifier, "aa", false, 1);
		QApplication::sendEvent(mapCanvas, e);
		break;

	case MapControl::ZoomOut:
		e = new QKeyEvent(QEvent::KeyPress, Qt::Key_PageDown, Qt::NoModifier, "aa", false, 1);
		QApplication::sendEvent(mapCanvas, e);
		break;

	default:
		break;
	}

}

//激活SVG标绘点工具
void GisSystem::MarkerSvg()
{
	mapCanvas->setMapTool(mapTools.svgMarkerTool);
}
// ALP Area Line Point
void GisSystem::ALPMarler()
{
	mapCanvas->setMapTool(mapTools.ALPMarkerTool);
}

//显示和隐藏图层管理器
void GisSystem::show_LayerManager()
{
	mlayerTreeView->show();
}
void GisSystem::hide_LayerManager()
{
	mlayerTreeView->hide();
}

//测距离
void GisSystem::Measure_Line(){
	
	mapCanvas->setMapTool(mapTools.addMeasureToolLine);
	
}
//测面积
void GisSystem::Measure_Area(){	
	mapCanvas->setMapTool(mapTools.addMeasureToolArea);	
}

//重置测量标记信息 进入下次测量
void GisSystem::ResetMeasure()
{
	mapTools.addMeasureToolArea->clearUpMeasure();
	mapTools.addMeasureToolLine->clearUpMeasure();
}
//切换地图工具
void GisSystem::setMapTool(QgsMapTool *tool)
{
	if (tool)
	{
		mapCanvas->setMapTool(tool);
	}
}
//设置是否开启比例尺
// 如果使用暂时会报错
void GisSystem::setScaleBarEnable(bool en)
{
	ScaleFlagsEnable = en;
	//如果未连接 disconnect 会不会报错 
	if (ScaleFlagsEnable)
	{
		connect(mapCanvas, SIGNAL(renderComplete(QPainter *)), this, SLOT(showScaleBar(QPainter *)));//显示比例尺
	}
	else
	{
		disconnect(mapCanvas, SIGNAL(renderComplete(QPainter *)), this, SLOT(showScaleBar(QPainter *)));//显示比例尺
	}
}

void GisSystem::showScaleBar(QPainter *theQPainter){
	//Get canvas dimensions
	int myCanvasHeight = theQPainter->device()->height();
	int myCanvasWidth = theQPainter->device()->width();

	double myMapUnitsPerPixelDouble = qAbs(mapCanvas->mapUnitsPerPixel());

	myActualSize = 30;

	QSettings settings;

	QGis::UnitType myPreferredUnits = QGis::Meters;
	QGis::UnitType myMapUnits = mapCanvas->mapUnits();

	// Adjust units meter/feet/... or vice versa
	myMapUnitsPerPixelDouble *= QgsUnitTypes::fromUnitToUnitFactor(myMapUnits, myPreferredUnits);
	myMapUnits = myPreferredUnits;

	//Calculate size of scale bar for preferred number of map units
	myScaleBarWidth = 30 / myMapUnitsPerPixelDouble;

	//If scale bar is very small reset to 1/4 of the canvas wide
	if (myScaleBarWidth < 30)
	{
		myScaleBarWidth = myCanvasWidth / 8.0; // pixels
		myActualSize = myScaleBarWidth * myMapUnitsPerPixelDouble; // map units
	}

	//if scale bar is more than half the canvas wide keep halving until not
	while (myScaleBarWidth > myCanvasWidth / 5.0)
	{
		myScaleBarWidth = myScaleBarWidth / 5;
	}
	myActualSize = myScaleBarWidth * myMapUnitsPerPixelDouble;

	// Work out the exponent for the number - e.g, 1234 will give 3,
	// and .001234 will give -3
	double myPowerOf10 = floor(log10(myActualSize));

	// snap to integer < 10 times power of 10
	//取整
	double scaler = pow(10.0, myPowerOf10);
	myActualSize = qRound(myActualSize / scaler) * scaler;
	myScaleBarWidth = myActualSize / myMapUnitsPerPixelDouble;
	emit sendData(myActualSize, myScaleBarWidth);//发送数据
}

// 我的位置
QgsSvgAnnotationItem*  GisSystem::showMyPos(QgsPoint pos, QString svgPath)
{
	if (!mySelfItem){
		mySelfItem = mapTools.svgMarkerTool->createItem(pos, svgPath);
	}
	else{
		mapTools.svgMarkerTool->updateItemPositon(mySelfItem, pos);
	}
	mapCanvas->setCenter(pos);//居中显示
	//mapCanvas->setCenter(pos);//居中显示
	//mapCanvas->zoomScale(100000000000);//放大比例
	mapCanvas->refresh();

	return mySelfItem;
}

//初次加载地图
void GisSystem::firstLoad()
{
	//QString MapPath = RCSettings::getValue(RCSettings::GIS, "mapDataPat", "Resources/mapdata/zgc.tif").toString();
	QgsMapLayer* Layer = new QgsRasterLayer("Resources/mapdata/zgc.tif", "gdal", false);
	if (!Layer->isValid())
	{
		//QMessageBox::critical(this, "error", "layer is invalid");
		return;
	}
	QgsMapLayerRegistry::instance()->addMapLayer(Layer);
	mapCanvasLayerSet.append(Layer);
	//mapCanvas->setExtent(Layer->extent());
	mapCanvas->setLayerSet(mapCanvasLayerSet);//将图层加载到图层集内
	mapCanvas->setVisible(true);
	mapCanvas->freeze(false);
	QgsCoordinateReferenceSystem wgs84(4326, QgsCoordinateReferenceSystem::EpsgCrsId);
	QgsCoordinateReferenceSystem web(3857, QgsCoordinateReferenceSystem::EpsgCrsId);
	mapCanvas->setDestinationCrs(wgs84);  //坐标正确
	//mapCanvas->setDestinationCrs(web); //距离正确
	mapCanvas->setCrsTransformEnabled(true);
	mapCanvas->setExtent(mapCanvas->fullExtent());
	mapCanvas->zoomScale(11339.6);
	mapCanvas->refresh();//刷新图层

}



//##############  API ###################################################################

//清除地图标绘接口
void GisSystem::clearUpMap()//清空地图
{
	mapTools.addMeasureToolArea->clearUpMeasure();
	mapTools.addMeasureToolLine->clearUpMeasure();
	//其他几个工具 也需要处理资源

}
