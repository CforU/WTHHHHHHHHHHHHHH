
#include "GisApp.h"

GisApp::GisApp(QWidget *parent) :
QWidget(parent)
{	
	init();//初始化
	this->installEventFilter(this);//安装事件过滤器
}

void GisApp::init_ui()
{
	//Flags
	//search 显示标志
	searchFlag = false;
	//比例尺默认显示
	ScaleFlagsEnable = true;
	//setScaleBarEnable(true);
	//地图管理器显示
	mMapLayerManagerFlag = false;

	WidgetSize = QSize(1024, 768);//主窗体大小
	MapSize = QSize(500, 500);//地图显示大小
	

	//左边菜单实例化
	leftBar = new  LeftBar();
	iconBar = new IconBar;
	leftStack = new QStackedWidget;
	leftStack->addWidget(leftBar);
	leftStack->addWidget(iconBar);
	leftStack->setCurrentIndex(0);
	mMarkerFlag = false;

	//右边按钮实例化
	rightBar = new RightBar();
	
	//中心窗体
	MapWidget = new QMainWindow;

	//地图系统创建 最先创建
	mGisSystem = new GisSystem();//创建
	MapWidget->setCentralWidget(mGisSystem);

	//搜索框
	searchBox = new  MapSearchBox(mGisSystem->mapCanvas);
	s = mGisSystem->mapCanvas->scene()->addWidget(searchBox);
	//searchBox->move(MapWidget->x() + 10, MapWidget->y() + 50);
	//s->setPos(50, 50);
	//s->hide();
	searchBox->hide();
	//s->show();
	//searchBox->move(50, 50);

	//比例尺
	myWidget = new ScaleWidget(MapWidget);
	myWidget->move(0, 700);//比例尺位置
	myWidget->resize(200, 80);//控件大小

	//筛选
	myFilterWidget = new FilterWidget(MapWidget);
	myFilterWidget->move(585,0);
	

	//状态栏
	sta = MapWidget->statusBar();
	sta->setStyleSheet("background:rgb(36, 44, 49); border:1px solid white; font - size:18px; color:#ffffff; font - family:Microsoft YaHei;");//border: 2px;
	//显示地图经纬度控件初始化
	m_lblCoordinate = new QLabel();
	m_lblCoordinate->setMinimumSize(100, 20);
	m_lblCoordinate->setFrameShape(QFrame::WinPanel);
	m_lblCoordinate->setFrameShadow(QFrame::Sunken);
	sta->addWidget(m_lblCoordinate);

	//显示测量的距离或面积
	m_labLengthAndArea = new QLabel();
	m_labLengthAndArea->setMinimumSize(100, 20);
	m_labLengthAndArea->setFrameShape(QFrame::WinPanel);
	m_labLengthAndArea->setFrameShadow(QFrame::Sunken);
	sta->addWidget(m_labLengthAndArea);

	//地图工具
	mMarkerTool = new MarkerTool(mGisSystem->mapCanvas);
	//设置是否开启比例尺 配置文件
	setShowScaleBar();

	//主窗体布局
	QHBoxLayout *hlay = new QHBoxLayout;
	//hlay->addStretch(3);
	hlay->addWidget(leftStack, 2);
	hlay->addWidget(MapWidget, 13);
	hlay->addWidget(rightBar, 2);
	//hlay->addStretch(3);
	hlay->setMargin(0);
	hlay->setSpacing(0);
	this->setLayout(hlay);

	this->resize(WidgetSize);
}
//地图信号连接处理
void  GisApp::connect_signal()
{
	//信号连接

	connect(leftBar->m_FirstBtn, SIGNAL(clicked()), this, SLOT(on_search()));
	connect(leftBar->m_SecondBtn, SIGNAL(clicked()), this, SLOT(on_navagation()));//路径标绘 以后是路径导航
	connect(leftBar->m_ThirdBtn, SIGNAL(clicked()), mGisSystem, SLOT(MapLoad()));//点击按钮实现添加栅格图片
	connect(leftBar->m_FourthBtn, SIGNAL(clicked()), this, SLOT(mapSwitch()));//地图切换
	connect(leftBar->m_FifthBtn, SIGNAL(clicked()), mGisSystem, SLOT(showMyPos()));//显示当前位置
	connect(leftBar->m_SixBtn, SIGNAL(clicked()), mGisSystem, SLOT(zoomInMode()));//放大
	connect(leftBar->m_SeventhBtn, SIGNAL(clicked()), mGisSystem, SLOT(zoomOutMode()));//缩小
	connect(leftBar->m_EighthBtn, SIGNAL(clicked()), mGisSystem, SLOT(panMode()));
	connect(leftBar->m_ninethBtn, SIGNAL(clicked()), this, SLOT(on_Marker()));//图绘	 //markr
	
	
	//右边前三个信号连接
	connect(rightBar->childWdt->base_btn1, SIGNAL(clicked()), this, SLOT(RightChildWidget_btn1_on_clicked()));//分层
	connect(rightBar->childWdt->base_btn2, SIGNAL(clicked()), this, SLOT(RightChildWidget_btn2_on_clicked()));//筛选
	connect(rightBar->childWdt->base_btn3, SIGNAL(clicked()), this, SLOT(RightChildWidget_btn3_on_clicked()));//测量

	//connect(rightBar->childWdt->measure_btn1, SIGNAL(clicked()), mGisSystem, SLOT(Measure_Line()));//mesure 

	connect(rightBar->childWdt->measure_btn1, SIGNAL(clicked()), mGisSystem, SLOT(Measure_Line()));// 测距
	connect(rightBar->childWdt->measure_btn2, SIGNAL(clicked()), mGisSystem, SLOT(Measure_Area()));//测面积
	connect(rightBar->childWdt->reset_btn3, SIGNAL(clicked()), mGisSystem, SLOT(ResetMeasure()));//mesure  清除地图上测量信息
	//右边信号连接
	//移动地图
	connect(rightBar->m_FourthBtn, SIGNAL(clicked()), mGisSystem, SLOT(RightMove()));//右移地图
	connect(rightBar->m_FifthBtn, SIGNAL(clicked()), mGisSystem, SLOT(LeftMove()));//左移地图
	connect(rightBar->m_SixBtn, SIGNAL(clicked()), mGisSystem, SLOT(UpMove()));//上移地图
	connect(rightBar->m_SeventhBtn, SIGNAL(clicked()), mGisSystem, SLOT(DownMove()));//下移地图
	//connect(rightBar->m_EighthBtn, SIGNAL(clicked()), this, SLOT(on_enter()));//
	connect(rightBar->m_ninethBtn, SIGNAL(clicked()), this, SLOT(on_return()));
	//画布连接信号和槽
	connect(mGisSystem->mapCanvas, SIGNAL(xyCoordinates(QgsPoint)), this, SLOT(showMousePoint(QgsPoint)));//鼠标当前坐标
	//发送比例尺数据
	connect(mGisSystem, SIGNAL(sendData(int, int)), myWidget, SLOT(getData(int, int)));
	//测试保存和加载
	//connect(leftBar->m_SecondBtn, SIGNAL(clicked()), this, SLOT(saveMarkerPath2File()));
	//connect(leftBar->m_FourthBtn, SIGNAL(clicked()), this, SLOT(loadMarkerPath2File()));

	//动态创建筛选 子控件
	connect(mMarkerTool, SIGNAL(createWidget()), myFilterWidget, SLOT(addItem()));
	connect(myFilterWidget, SIGNAL(showMarker(int)), mMarkerTool, SLOT(on_showMarker(int)));//显示标绘点
	connect(myFilterWidget, SIGNAL(hideMarker(int)), mMarkerTool, SLOT(on_hideMarker(int)));//隐藏标绘点
}




//清空行进路径
void GisApp::clearAdvancePath()
{
	if (travelPath){
		delete travelPath;
		travelPath = NULL;
	}

}


bool GisApp::eventFilter(QObject *target, QEvent *event)
{
#if 0
    if (event->type() == GisEvent::GisEventType)
    {
  
        GisEvent *e = static_cast<GisEvent*>(event);
        //GisEvent::GisEventType->gisData //数据处理
        QgsPoint pos(e->gisData.dwdx_INFO_MSG.global_x / 1000000.0, e->gisData.dwdx_INFO_MSG.global_y / 1000000.0);
        updatePosition(e->gisData.dwdx_INFO_MSG.id, pos);//跟新车辆位置 内部实现如果没有这个id 会进行标记
		//行进路线标绘
		//MarkerVehicleAdvanceRoute();
#if 0
		//如果是新的车辆 就清除旧的路径
		//qDebug() << "id=" << e->gisData.dwdx_INFO_MSG.id;
		if (e->gisData.dwdx_INFO_MSG.id != id){
			vid = e->gisData.dwdx_INFO_MSG.id;
			clearAdvancePath();
		}
#endif

		if (!travelPath) // 没有rubber band，就创建一个
		{
			travelPath = new QgsRubberBand(mapCanvas, QGis::Line);
			travelPath->setWidth(2);
			travelPath->setColor(QColor(0, 255, 0));
		}
		travelPath->addPoint(pos);

        if (centerFlag == true){
            mapCanvas->setCenter(pos);//居中显示
            mapCanvas->refresh();
        }
        return true;
    }
#endif
    //其它部件产生的事件则交给基类处理
    return QWidget::eventFilter(target, event);

}

//是否显示比例尺
void GisApp::setShowScaleBar()
{
	//通过QSettings 获取是否显示比例尺的设置
	mGisSystem->setScaleBarEnable(RCSettings::getValue(RCSettings::GIS, "ScaleBarEnableFlag", "1").toBool());
}
//***********************//
//开启导航
void GisApp::on_navagation()
{

}
//地图切换
void GisApp::mapSwitch()
{

}
//开启标绘功能
void GisApp::on_Marker()
{
	qDebug() << "marker #############";
	//开启标绘功能
	mGisSystem->setMapTool(mMarkerTool);
	//切换菜单
	qDebug() << mMarkerFlag;
	if (mMarkerFlag == false)
	{
		leftStack->setCurrentIndex(1);
		mMarkerFlag = true;
	}

}
//返回
void GisApp::on_return()
{
	//获取当前所在功能 根据当前功能进行返回

	//切换菜单
	if (mMarkerFlag == true)
	{
		leftStack->setCurrentIndex(0);
		mMarkerFlag = false;
		//关闭标绘功能 或者切换为别的功能
		goto on_return;
	}
	if (mMapLayerManagerFlag == true){
		mGisSystem->hide_LayerManager();
		mMapLayerManagerFlag = false;
		rightBar->childWdt->setCurrentIndex(0);
		//全选没做
		goto on_return;
	}
	//其他flags  依次返回 每次只需要返回一个 
	if (1){//根据条件来进行返回 这里默认直接处理
		rightBar->childWdt->setCurrentIndex(0);
		goto on_return; //这里展示不能直接返回
	}
	// ....

on_return:
	this->mGisSystem->panMode();//启动激活漫游功能
}

void GisApp::on_search(void)
{
	
	//gde
	if (searchFlag == false)
	{
		leftBar->m_FirstBtn->setCheckable(true);
		s->show();
	//	mGisSystem->mapCanvas->unsetMapTool(mGisSystem->mapTools.mPan);
		searchFlag = true;
	}
	else
	{
		leftBar->m_FirstBtn->setCheckable(false);
		s->hide();
	//	mGisSystem->mapCanvas->unsetMapTool(mGisSystem->mapTools.mPan);
		searchFlag = false;
	}
}

void GisApp::getSearchText()
{

}
//确认按钮
void GisApp::on_enter()
{

}
//图层管理器
void GisApp::on_LayerManager()
{
	mGisSystem->show_LayerManager();
	mMapLayerManagerFlag = true;
	//还缺乏一个全选功能
}

//获取我的位置
QgsPoint GisApp::getMyPos()
{
	//从惯导获取我的位置
	INSInfo* insData = new INSInfo;
	QgsPoint *setPosition = new QgsPoint;
	//	mINS->read(insData);
	setPosition->setX(insData->Longitude / 1000000);
	setPosition->setY(insData->Latitude / 1000000);

	return *setPosition;
}
//显示我的位置
void GisApp::showMyPos(void)
{
	//通过配置文件获取我的位置的svg图标 标绘我的位置 
	//mGisSystem->showMyPos(getMyPos(), RCSettings::getValue(RCSettings::GIS, "MySelfSvg", "Resources/icon/gis/mkSvg/icon_bhtjd_2.svg").toString());
	//没有使用底层的实现

	if (centerFlag == true){
		centerFlag = false;
	}
	else{
		centerFlag = true;
	}
	mGisSystem->mapTools.svgMarkerTool->createItem(getMyPos(), RCSettings::getValue(RCSettings::GIS, "MySelfSvg", "Resources/icon/gis/mkSvg/icon_bhtjd_2.svg").toString());
	mGisSystem->mapCanvas->setCenter(getMyPos());//居中显示
	//mGisSystem->mapCanvas->setCenter(*setPosition);//居中显示
	//mGisSystem->mapCanvas->zoomScale(100000000000);//放大比例
	mGisSystem->mapCanvas->refresh();

}
void GisApp::showMyPos(QgsPoint pos)
{
	//使用默认标绘图标
	//获取默认svg图标 从配置文件
	// mGisSystem->showMyPos(pos, svgPath);
	//	QgsSvgAnnotationItem* mySelfItem;
}




//显示当前鼠标位置的坐标
void GisApp::showMousePoint(const QgsPoint& p)
{
	m_lblCoordinate->setText(QString("x=%1,y=%2").arg(p.x()).arg(p.y()));
}
//显示当前测量长度
void GisApp::showMesureLength(double length)
{
	m_labLengthAndArea->setText(QString(tr("length: %1 (m)").arg(length)));
}
//显示当前测量面积
void GisApp::showMesureArea(double Area)
{
	m_labLengthAndArea->setText(QString(tr("Area: %1 (m^2)").arg(Area)));
}


//三个特殊的槽函数
void GisApp::RightChildWidget_btn1_on_clicked()
{
	rightBar->childWdt->setCurrentIndex(1);
	on_LayerManager();
}
void GisApp::RightChildWidget_btn2_on_clicked()
{
	rightBar->childWdt->setCurrentIndex(2);
}
void GisApp::RightChildWidget_btn3_on_clicked()
{
	rightBar->childWdt->setCurrentIndex(3);
}

//#################################################################

// 通过读取数据库中车辆id获取车辆类型
int GisApp::getVehicleTypeId(int aVehicleType)
{
	int id = 0;
	QSqlQuery sqlQuery;

	QString typeStr = "";

	switch (aVehicleType)
	{
	case 6:
		typeStr = QStringLiteral("履带");
		break;
	case 8:
		typeStr = QStringLiteral("轮巡");
		break;
	case 9:
		typeStr = QStringLiteral("轮式");
		break;
	default:
		break;
	}

	sqlQuery.exec(
		QString("select id from t_car where car_type=%1").arg(typeStr)
		);
	if (sqlQuery.next())
	{
		id = sqlQuery.value(0).toInt();
		return id;
	}
	else
	{
		qDebug() << "无此类型";
		return -1;
	}

}
//从数据库根据车辆id判断车辆的类型 
MarKerVehicleType GisApp::getVechileType(int id)
{

	//调用数据库接口 获取type
	int typeId = getVehicleTypeId(id);
	// MarkerTool::MarKerVehicleType type = MarkerTool::MarKerVehicleType(typeId);
	switch (typeId){
	case 4:
		return MarKerVehicleType::CommandCar; //指挥车
		break;
	case 5:
		return MarKerVehicleType::UAV; //无人机
		break;
	case 6:
		return MarKerVehicleType::TrackedVehicle;//履带车
		break;
	case 7:
		return MarKerVehicleType::DumpedCar;//抛投车
		break;
	case 8:
		return MarKerVehicleType::WheelPatrolCar;// 轮巡车
		break;
	case 9:
		return MarKerVehicleType::WheeledVehicles;//轮式车
		break;
	default:
		return MarKerVehicleType::CarDefault; //无车 默认 
	}

}
// 解析RCS数据 返回经纬坐标和ID
//void GisApp::Resolver(GisData *Data){}

//初次加载地图
void GisApp::firstLoad()
{
	QString MapPath = RCSettings::getValue(RCSettings::GIS, "mapDataPat", "Resources/mapdata/zgc.tif").toString();
	QgsMapLayer* Layer = new QgsRasterLayer(MapPath, "gdal", false);
	if (!Layer->isValid())
	{
		//QMessageBox::critical(this, "error", "layer is invalid");
		return;
	}
#if 1
	QgsMapLayerRegistry::instance()->addMapLayer(Layer);
	mGisSystem->mapCanvasLayerSet.append(Layer);
	//mGisSystem->mapCanvas->setExtent(Layer->extent());
	mGisSystem->mapCanvas->setLayerSet(mGisSystem->mapCanvasLayerSet);//将图层加载到图层集内
	mGisSystem->mapCanvas->setVisible(true);
	mGisSystem->mapCanvas->freeze(false);
	QgsCoordinateReferenceSystem wgs84(4326, QgsCoordinateReferenceSystem::EpsgCrsId);
	QgsCoordinateReferenceSystem web(3857, QgsCoordinateReferenceSystem::EpsgCrsId);
	mGisSystem->mapCanvas->setDestinationCrs(wgs84);  //坐标正确
	//mapCanvas->setDestinationCrs(web); //距离正确
	mGisSystem->mapCanvas->setCrsTransformEnabled(true);
	mGisSystem->mapCanvas->setExtent(mGisSystem->mapCanvas->fullExtent());
	mGisSystem->mapCanvas->zoomScale(11339.6);
	
	mGisSystem->mapCanvas->refresh();//刷新图层
#else
	QgsMapLayerRegistry::instance()->addMapLayer(rasterLayer);//
	mapCanvasLayerSet.append(rasterLayer);
	mapCanvas->setExtent(rasterLayer->extent());
	mapCanvas->setViewportUpdateMode(QGraphicsView::ViewportUpdateMode::SmartViewportUpdate);	
	mapCanvas->setLayerSet(mapCanvasLayerSet);
	mapCanvas->setVisible(true);
	mapCanvas->freeze(false);
	/*---------------------Transform---------------------*/
	QgsCoordinateReferenceSystem wgs84(4326, QgsCoordinateReferenceSystem::EpsgCrsId);
	QgsCoordinateReferenceSystem web(3857, QgsCoordinateReferenceSystem::EpsgCrsId);
	mapCanvas->setDestinationCrs(wgs84);  //坐标正确
	//mapCanvas->setDestinationCrs(web); //距离正确
	mapCanvas->setCrsTransformEnabled(true);
	mapCanvas->setExtent(mapCanvas->fullExtent());
	/*--------------------------------------------------*/

	mapCanvas->zoomScale(11339.6);//放大显示
	mapCanvas->refresh();


#endif
}

//##############  API ###################################################################
//初始化地图
void  GisApp::init()   //初始化 加载地图  加载当前位置  (从惯导获取当前位置  标绘当前位置)
{
	init_ui();//初始化UI
	connect_signal();//连接信号
	//firstLoad();//启动自动加载地图数据
	//mGisSystem->panMode();//开启漫游工具
	
	this->showMyPos();//显示我的位置
	//从标绘行进方向
	//标绘其他车辆位置

}
//路径保存
void GisApp::PathSave2Sql()//路径保存
{
	
}
//保存路径到文件
void GisApp::saveMarkerPath2File()
{
	
}
void GisApp::loadMarkerPath2File()
{

}
//保存路径到XML文件
void GisApp::PathSave2Xml()
{
	
}
//加载XML文件中的路径
void GisApp::loadPath2xml()
{
	
}
//
int GisApp::LoadHistoryRoad(/* path */) // 1 加载历史路径 需要封装一个path类 
{
	
	return 0;
}

//#########自动路径#######################################//

//路径自动进标绘
void GisApp::RouteMarker(QList<QgsPoint>  PathList)
{
	mMarkerTool->RouteMarker(PathList);
}

//路径规划 gis系统暂不提供接口
void GisApp::PathPloting(QgsPoint from, QgsPoint to)//路径规划
{

}

//标绘路径(行进路径) 
int  GisApp::MarkerVehicleAdvanceRoute(QgsRubberBand* mRubberBand, QList<QgsPoint>  PathList)
{
	//mRubberBand 需要创建一个 已经声明;
	// mMarkerTool->
	return 0;
}

//###################### 自动标绘车辆 ##################################

//车辆标绘 
void GisApp::VehicleMarker(QgsPoint pos, int id)
{
	//通过id 传入svg 进行标绘 
	//需要查询数据库   mMarkerTool内部实现了  是否有必要外部查询
	mMarkerTool->VehicleMarker(pos, id);//内部有创建函数 内部也有自己的管理车辆和id的容器

}
//位置点 更新处理接口
void GisApp::updatePosition(int id, QgsPoint pos)
{
	mMarkerTool->updateVehiclePosition(pos, id);//内部有进行管理
}
void GisApp::delteVechile(int id)//删除车辆标绘点
{
	mMarkerTool->delteVechile(id);
}

//###################################
//清除地图标绘接口
void GisApp::clearUpMap()//清空地图
{
	mGisSystem->clearUpMap();
	mMarkerTool->clearUpMarker();
}

