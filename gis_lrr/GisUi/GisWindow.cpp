
#include "GisWindow.h"

GisWindow::GisWindow(QWidget *parent) :
QWidget(parent)
{
	init_ui();//初始化UI
	connect_signal();//连接信号
	//QTimer::singleShot(0, this, SLOT(init()));//延迟执行 放入到事件循环中 下次事件循环进行执行  相当于flash里面的callLater()函数 
	init();//初始化
	this->installEventFilter(this);//安装事件过滤器
}

void GisWindow::init_ui()
{
	//Flags
	//search 显示标志
	searchFlag = false;
	//比例尺默认显示
	ScaleFlagsEnable = true;
	//setScaleBarEnable(true);
	

	WidgetSize = QSize(1024, 768);//主窗体大小
	MapSize = QSize(500, 500);//地图显示大小
	this->resize(WidgetSize);
	//中心窗体
	MapWidget = new QMainWindow;
	
	//地图系统创建 最先创建
	mGisSystem = new GisSystem();//创建
	MapWidget->setCentralWidget(mGisSystem);


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
	//地图UI
	//搜索框
	searchBox = new  MapSearchBox();
	// searchBox->move(MapWidget->x() + 10, MapWidget->y() + 50); mGisSystem
	//searchBox->raise();

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
}
//地图信号连接处理
void  GisWindow::connect_signal()
{
	//信号连接
	//信号连接
	//放大缩小漫游功能信号与槽的连接
	//connect(MapWidget, SIGNAL(clicked()), mGisSystem, SLOT(zoomFull()));
	//connect(toolBar->raster, SIGNAL(clicked()), mGisSystem, SLOT(addVectorLayers()));//点击按钮实现添加矢量图片
	connect(leftBar->m_FirstBtn, SIGNAL(clicked()), this, SLOT(on_search()));
	//connect(leftBar->m_SecondBtn, SIGNAL(clicked()), this, SLOT(on_Action_AddFeatureTool_Line()));//路径标绘 以后是路径导航
	connect(leftBar->m_ThirdBtn, SIGNAL(clicked()), mGisSystem, SLOT(MapLoad()));//点击按钮实现添加栅格图片
	connect(leftBar->m_FifthBtn, SIGNAL(clicked()), mGisSystem, SLOT(showMyPos()));//显示当前位置
	connect(leftBar->m_SixBtn, SIGNAL(clicked()), mGisSystem, SLOT(zoomInMode()));//放大
	connect(leftBar->m_SeventhBtn, SIGNAL(clicked()), mGisSystem, SLOT(zoomOutMode()));//缩小
	connect(leftBar->m_EighthBtn, SIGNAL(clicked()), mGisSystem, SLOT(panMode()));
	connect(leftBar->m_ninethBtn, SIGNAL(clicked()), this, SLOT(on_Marker()));//图绘	 //markr

	//右边信号连接
	connect(rightBar->childWdt->measure_btn1, SIGNAL(clicked()), mGisSystem, SLOT(on_actionMeasure_Line()));//mesure 
	//connect(rightBar->m_SecondBtn, SIGNAL(clicked()), this, SLOT(on_Action_AddFeatureTool_None()));//mesure 
	connect(rightBar->childWdt->measure_btn2, SIGNAL(clicked()), mGisSystem, SLOT(on_actionMeasure_Area()));//
	connect(rightBar->childWdt->reset_btn3, SIGNAL(clicked()), mGisSystem, SLOT(ResetMeasure()));//mesure  清除地图上测量信息

	//移动地图
	connect(rightBar->m_FourthBtn, SIGNAL(clicked()), mGisSystem, SLOT(RightMove()));//右移地图
	connect(rightBar->m_FifthBtn, SIGNAL(clicked()), mGisSystem, SLOT(LeftMove()));//左移地图
	connect(rightBar->m_SixBtn, SIGNAL(clicked()), mGisSystem, SLOT(UpMove()));//上移地图
	connect(rightBar->m_SeventhBtn, SIGNAL(clicked()), mGisSystem, SLOT(DownMove()));//下移地图
	//connect(rightBar->m_EighthBtn, SIGNAL(clicked()), this, SLOT(on_eightBtn_clicked()));//
	connect(rightBar->m_ninethBtn, SIGNAL(clicked()), this, SLOT(on_return()));
	//画布连接信号和槽
	connect(mGisSystem, SIGNAL(xyCoordinates(QgsPoint)), this, SLOT(showMousePoint(QgsPoint)));//鼠标当前坐标
	connect(mGisSystem, SIGNAL(renderComplete(QPainter *)), this, SLOT(showScaleBar(QPainter *))); //显示比例尺
	//地图操作
	//connect(this, SIGNAL(moveSignal(MapControl c)), this, SLOT(MoveAndControlMap(MapControl c)));
	//测试保存和加载
	connect(leftBar->m_SecondBtn, SIGNAL(clicked()), mGisSystem->mapTools.markerTool, SLOT(saveMarkerPath2File()));
	connect(leftBar->m_FourthBtn, SIGNAL(clicked()), mGisSystem->mapTools.markerTool, SLOT(loadMarkerPath2File()));

}


bool GisWindow::eventFilter(QObject *target, QEvent *event)
{
#if 0
    if (event->type() == GisEvent::GisEventType)
    {
        qDebug() << "GisWindow eventFilter";
        GisEvent *e = static_cast<GisEvent*>(event);
        //GisEvent::GisEventType->gisData //数据处理
        QgsPoint pos(e->gisData.dwdx_INFO_MSG.global_x / 1000000.0, e->gisData.dwdx_INFO_MSG.global_y / 1000000.0);
        qDebug() << "pos:" << pos.toString();
        updatePosition(e->gisData.dwdx_INFO_MSG.id, pos);//跟新车辆位置 内部实现如果没有这个id 会进行标记
        //
        if (centerFlag == true){
            mapCanvas->setCenter(pos);//居中显示
            mapCanvas->refresh();
        }
        return true;
    }
    //其它部件产生的事件则交给基类处理
    //return this->pai ::eventFilter(target, event);
#endif
    return QWidget::eventFilter(target, event);

}

//***********************//

void GisWindow::on_Marker()
{
	qDebug() << "marker #############";
	//开启标绘功能
	mGisSystem->on_Action_AddFeatureTool_Point();
	//切换菜单
	qDebug() << mMarkerFlag;
	if (mMarkerFlag == false)
	{
		leftStack->setCurrentIndex(1);
		mMarkerFlag = true;
	}

}


void GisWindow::on_return()
{
	//获取当前所在功能 根据当前功能进行返回

	//切换菜单
	if (mMarkerFlag == true)
	{
		leftStack->setCurrentIndex(0);
		mMarkerFlag = false;
		//关闭标绘功能 或者切换为别的功能
		this->mGisSystem->panMode();//启动激活漫游功能
		return;
	}
	//其他flags  依次返回 每次只需要返回一个 
	if (1){//根据条件来进行返回 这里默认直接处理
		rightBar->childWdt->setCurrentIndex(0);
		// return; //这里展示不能直接返回
	}
	qDebug() << "return  #############";
}

//显示当前鼠标位置的坐标
void GisWindow::showMousePoint(const QgsPoint& p)
{
	m_lblCoordinate->setText(QString("x=%1,y=%2").arg(p.x()).arg(p.y()));
}
//显示当前测量长度
void GisWindow::showMesureLength(double length)
{
	qDebug() << "Measure Lines : " << length << " (m) ";
	m_labLengthAndArea->setText(QString(tr("length: %1 (m)").arg(length)));
}
//显示当前测量面积
void GisWindow::showMesureArea(double Area)
{

	m_labLengthAndArea->setText(QString(tr("Area: %1 (m^2)").arg(Area)));
	qDebug() << "Measure Areas : " << Area << " (m^2) ";

}
void GisWindow::on_search(void)
{
	if (searchFlag == false)
	{
		leftBar->m_FirstBtn->setCheckable(true);
		searchBox->move(this->x() + 150, this->y() + 40);
		searchBox->show();
		searchFlag = true;
		qDebug() << "search show";
	}
	else
	{
		leftBar->m_FirstBtn->setCheckable(false);
		searchBox->hide();
		searchFlag = false;
		qDebug() << "search hide";
	}
}

void GisWindow::getSearchText()
{

}
void GisWindow::on_eightBtn_clicked()
{

}

//##############  API ###################################################################
//初始化地图
void  GisWindow::init()   //初始化 加载地图  加载当前位置  (从惯导获取当前位置  标绘当前位置)
{
	mGisSystem->init();
}
//放大 缩小 移动 (漫游)  已经作为公有槽函数 可以直接调用

//路径保存
void GisWindow::PathSave2Sql()//路径保存
{
	mGisSystem->PathSave2Sql();
}
void GisWindow::PathSave2Xml()//路径保存
{
	mGisSystem->PathSave2Xml();
}
//提供给 VMwindow
int GisWindow::LoadHistoryRoad(/* path */) // 1 加载历史路径 需要封装一个path类 
{
	mGisSystem->LoadHistoryRoad();
	return 0;
}

void GisWindow::PathMarker(/*起点 中间点 终点 */)//路径标绘(一般用作标绘历史路径或者标绘自动规划的路径)
{
	mGisSystem->PathMarker();
}
//路径规划
void GisWindow::PathPloting(QgsPoint from, QgsPoint to)//路径规划
{
	mGisSystem->PathPloting(from, to);
}

int GisWindow::AutoRoutePloting()  //  2 自动规划路径 可以调用 PathPloting
{
	mGisSystem->AutoRoutePloting();
	return 0;
}

//提供给 RCS
int  GisWindow::MarkerVehiclePosition()  //标记位置(position/类型) 
{
	mGisSystem->MarkerVehiclePosition();
	return 0;
}
int  GisWindow::MarkerVehicleAdvanceRoute() //标绘路径(行进路径)
{
	mGisSystem->MarkerVehicleAdvanceRoute();
	return 0;
}

//车辆标绘 
void GisWindow::VehicleMarker(QgsPoint pos, int id)
{
	mGisSystem->VehicleMarker(pos, id);
}
//位置点 更新处理接口
void GisWindow::updatePosition(int id, QgsPoint pos)
{
	mGisSystem->updatePosition(id,pos);

}

//清除地图标绘接口
void GisWindow::clearUpMap()//清空地图
{
	mGisSystem->clearUpMap();
}
void GisWindow::delteVechile(int id)//删除车辆标绘点
{
	mGisSystem->delteVechile(id);
}
