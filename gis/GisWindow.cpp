
#include "GisWindow.h"


GisWindow::GisWindow(QWidget *parent) :
QWidget(parent)
{
	//this->setWindowFlags(Qt::FramelessWindowHint);
	init_ui();
	connect_signal();

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
	

	//地图画图创建
	mapCanvas = new QgsMapCanvas();//创建
	mapCanvas->enableAntiAliasing(true);//开启反锯齿效果
	mapCanvas->setCanvasColor(QColor(255, 255, 255));
	mapCanvas->setVisible(true);
	MapWidget->setCentralWidget(mapCanvas);
	

	//左边菜单实例化
	leftBar = new  LeftBar();
	iconBar = new ContrlBar;
	leftStack = new QStackedWidget;
	leftStack->addWidget(leftBar);
	leftStack->addWidget(iconBar);
	leftStack->setCurrentIndex(0);
	mMarkerFlag = true;
	//右边按钮实例化
	rightBar = new RightBar();
	//地图UI
	//搜索框
	searchBox = new  MapSearchBox();
	// searchBox->move(MapWidget->x() + 10, MapWidget->y() + 50); mapCanvas
	//searchBox->raise();

	//状态栏
	sta = MapWidget->statusBar();
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

	mMapManager = new MapManager(mapCanvas);//地图管理类 需要在地图画布类之后
	mRouteAnalysis = new RouteAnalysis();//路径分析
	//Checking if arduino is connected or not
	mINS = new INS(COMPORT);//惯导类

	
	

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

void  GisWindow::connect_signal()
{
	//信号连接
	//信号连接
	//放大缩小漫游功能信号与槽的连接
	//connect(MapWidget, SIGNAL(clicked()), mapCanvas, SLOT(zoomFull()));
	//connect(toolBar->raster, SIGNAL(clicked()), mapCanvas, SLOT(addVectorLayers()));//点击按钮实现添加矢量图片
	connect(leftBar->m_FirstBtn, SIGNAL(clicked()), this, SLOT(on_search()));
	connect(leftBar->m_SecondBtn, SIGNAL(clicked()), this, SLOT(on_Action_AddFeatureTool_Line()));//路径标绘 以后是路径导航
	connect(leftBar->m_ThirdBtn, SIGNAL(clicked()), this, SLOT(addRasterLayers()));//点击按钮实现添加栅格图片
	connect(leftBar->m_FifthBtn, SIGNAL(clicked()), this, SLOT(showMyPos()));//显示当前位置
	connect(leftBar->m_SixBtn, SIGNAL(clicked()), this, SLOT(zoomInMode()));//放大
	connect(leftBar->m_SeventhBtn, SIGNAL(clicked()), this, SLOT(zoomOutMode()));//缩小
	connect(leftBar->m_EighthBtn, SIGNAL(clicked()), this, SLOT(panMode()));
	connect(leftBar->m_ninethBtn, SIGNAL(clicked()), this, SLOT(on_Marker()));//图绘	 //markr

	//右边信号连接
	connect(rightBar->m_FirstBtn, SIGNAL(clicked()), this, SLOT(on_Action_AddFeatureTool_Point()));//mesure 
	connect(rightBar->m_SecondBtn, SIGNAL(clicked()), this, SLOT(on_Action_AddFeatureTool_None()));//mesure 
	connect(rightBar->m_ThirdBtn, SIGNAL(clicked()), this, SLOT(on_actionMeasure_Area()));//mesure 
	//connect(rightBar->m_EighthBtn, SIGNAL(clicked()), this, SLOT(on_eightBtn_clicked()));//
	connect(rightBar->m_ninethBtn, SIGNAL(clicked()), this, SLOT(on_return()));
	//画布连接信号和槽
	connect(mapCanvas, SIGNAL(xyCoordinates(QgsPoint)), this, SLOT(showMousePoint(QgsPoint)));//鼠标当前坐标
	connect(mapCanvas, SIGNAL(renderComplete(QPainter *)), this, SLOT(showScaleBar(QPainter *))); //显示比例尺

}

//添加矢量图层
void GisWindow::addVectorLayers()
{
	mMapManager->addVectorLayers();
}

//添加栅格图层
void GisWindow::addRasterLayers()
{
	mMapManager->addRasterLayers();
}

//放大操作
void GisWindow::zoomInMode()
{
	printf("mode_zoomIn ok!!/n");
	//mpPanTool= new QgsMapToolPan(mainMapCanvas);    
	//mpPanTool->setAction(ui.mpActionPan);    
	QgsMapToolZoom *mpZoomInTool = new QgsMapToolZoom(mapCanvas, false);
	//mpZoomInTool->setAction(ui.actionZoom_in);    
	//   
	//mpZoomOutTool->setAction(ui.mpActionZoomOut);
	mapCanvas->setMapTool(mpZoomInTool); //需要添加qgs里面的maptool，不能使用qt里面的action //切换成对应的工具

}
//缩小操作
void GisWindow::zoomOutMode()
{
	QgsMapToolZoom *mpZoomOutTool = new QgsMapToolZoom(mapCanvas, true);
	mapCanvas->setMapTool(mpZoomOutTool);
}
//漫游
void GisWindow::panMode()
{
	QgsMapToolPan *mpPanTool = new QgsMapToolPan(mapCanvas);
	mapCanvas->setMapTool(mpPanTool);
}

//显示全屏
void GisWindow::zoomFull()
{

}

//激活标绘点工具
void GisWindow::on_Action_AddFeatureTool_Point(){

	QgsMapTool* markerTool = new MarkerTool(mapCanvas, MarkerTool::CapturePoint);
	mapCanvas->setMapTool(markerTool);
}
void GisWindow::on_Action_AddFeatureTool_Line(){

	QgsMapTool* markerTool = new MarkerTool(mapCanvas, MarkerTool::CaptureLine);
	mapCanvas->setMapTool(markerTool);
}
void GisWindow::on_Action_AddFeatureTool_None(){

	QgsMapTool* markerTool = new MarkerTool(mapCanvas, MarkerTool::CaptureNone);
	mapCanvas->setMapTool(markerTool);
}
void GisWindow::getSearchText()
{

}

void GisWindow::on_Marker()
{
	//开启标绘功能
	on_Action_AddFeatureTool_Point();
	//切换菜单
	if (mMarkerFlag == true)
	{
		leftStack->setCurrentIndex(1);
		mMarkerFlag = false;
	}
	
}
void GisWindow::on_return()
{
	//获取当前所在功能 根据当前功能进行返回

	//切换菜单
	if (mMarkerFlag == false)
	{
		leftStack->setCurrentIndex(0);
		mMarkerFlag = true;
		//关闭标绘功能 或者切换为别的功能
		this->panMode();//启动激活漫游功能
		return;
	}
	//其他flags  依次返回 每次只需要返回一个 

}



void GisWindow::on_actionMeasure_Line(){
	QgsMapTool* addMeasureTool = new MeasureTool(mapCanvas, false);
	mapCanvas->setMapTool(addMeasureTool);
	connect(addMeasureTool, SIGNAL(length_sigle(double)), this, SLOT(showMesureLength(double)));
}

void GisWindow::on_actionMeasure_Area(){
	QgsMapTool* addMeasureTool = new MeasureTool(mapCanvas, true);
	mapCanvas->setMapTool(addMeasureTool);
	connect(addMeasureTool, SIGNAL(Area_signal(double)), this, SLOT(showMesureArea(double)));

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

//设置是否开启比例尺
// 如果使用暂时会报错
void GisWindow::setScaleBarEnable(bool en)
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

void GisWindow::showScaleBar(QPainter *theQPainter){

	double mScale = mapCanvas->scale();
	double conversionFactor = 39.3700787;
	qDebug() << "Scale:  1 : " << mScale / conversionFactor;

	/////////////////////////////////////



	/*		显示比例尺			*/
	int myBufferSize = 1; //softcode this later



	//Get canvas dimensions
	int myCanvasHeight = theQPainter->device()->height();
	int myCanvasWidth = theQPainter->device()->width();

	qDebug() << "myCanvasHeight = " << myCanvasHeight;
	qDebug() << "myCanvasWidth = " << myCanvasWidth;


	double myMapUnitsPerPixelDouble = qAbs(mapCanvas->mapUnitsPerPixel());



	// Hard coded sizes
	int myMajorTickSize = 8;
	int myTextOffsetX = 3;


	int mPreferredSize = 30; //The size preferred size of the scale bar
	double myActualSize = mPreferredSize;

	QSettings settings;

	QGis::UnitType myPreferredUnits = QGis::Meters;
	QGis::UnitType myMapUnits = mapCanvas->mapUnits();

	// Adjust units meter/feet/... or vice versa
	myMapUnitsPerPixelDouble *= QgsUnitTypes::fromUnitToUnitFactor(myMapUnits, myPreferredUnits);
	myMapUnits = myPreferredUnits;

	//Calculate size of scale bar for preferred number of map units
	double myScaleBarWidth = mPreferredSize / myMapUnitsPerPixelDouble;

	//If scale bar is very small reset to 1/4 of the canvas wide
	if (myScaleBarWidth < 30)
	{
		myScaleBarWidth = myCanvasWidth / 4.0; // pixels
		myActualSize = myScaleBarWidth * myMapUnitsPerPixelDouble; // map units
	}

	//if scale bar is more than half the canvas wide keep halving until not
	while (myScaleBarWidth > myCanvasWidth / 3.0)
	{
		myScaleBarWidth = myScaleBarWidth / 3;
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

	///////////////////////////////////////////////

	//Get type of map units and set scale bar unit label text
	QString myScaleBarUnitLabel;
	switch (myMapUnits)
	{
	case QGis::Meters:
		if (myActualSize > 1000.0)
		{
			myScaleBarUnitLabel = tr(" km");
			myActualSize = myActualSize / 1000;
		}
		else if (myActualSize < 0.01)
		{
			myScaleBarUnitLabel = tr(" mm");
			myActualSize = myActualSize * 1000;
		}
		else if (myActualSize < 0.1)
		{
			myScaleBarUnitLabel = tr(" cm");
			myActualSize = myActualSize * 100;
		}
		else
			myScaleBarUnitLabel = tr(" m");
		break;

	}

	//Set font and calculate width of unit label
	int myFontSize = 10; //we use this later for buffering
	QFont myFont("helvetica", myFontSize);
	theQPainter->setFont(myFont);
	QFontMetrics myFontMetrics(myFont);
	double myFontWidth = myFontMetrics.width(myScaleBarUnitLabel);
	double myFontHeight = myFontMetrics.height();

	//Set the maximum label
	QString myScaleBarMaxLabel = QLocale::system().toString(myActualSize);

	//Calculate total width of scale bar and label
	double myTotalScaleBarWidth = myScaleBarWidth + myFontWidth;

	int mMarginHorizontal = 529;//画布的宽
	int mMarginVertical = 460;//和高

	int myMarginW = 10;
	int myMarginH = 20;
	int myOriginX = 0;
	int myOriginY = 0;
	//BottomRight:
	myOriginX += myCanvasWidth - myOriginX - myMarginW - (static_cast< int >(myTotalScaleBarWidth));
	myOriginY += myCanvasHeight - myOriginY - myMarginH;

	//TopLeft
	//myOriginX += myMarginW;
	//myOriginY += myMarginH;

	/////////////////////////////////////////

	//Cast myScaleBarWidth to int for drawing
	int myScaleBarWidthInt = static_cast< int >(myScaleBarWidth);
	//		绘制Tick UP
	//Set pen to draw with
	QPen myForegroundPen(Qt::green, 2);
	QPen myBackgroundPen(Qt::white, 4);

	QPolygon myTickUpArray(4);
	//draw a buffer first so bar shows up on dark images
	theQPainter->setPen(myBackgroundPen);
	myTickUpArray.putPoints(0, 4,
		myOriginX, myOriginY,
		myOriginX, myOriginY + myMajorTickSize,
		myScaleBarWidthInt + myOriginX, myOriginY + myMajorTickSize,
		myScaleBarWidthInt + myOriginX, myOriginY
		);
	theQPainter->drawPolyline(myTickUpArray);
	//now draw the bar itself in user selected color
	theQPainter->setPen(myForegroundPen);
	myTickUpArray.putPoints(0, 4,
		myOriginX, myOriginY,
		myOriginX, myOriginY + myMajorTickSize,
		myScaleBarWidthInt + myOriginX, myOriginY + myMajorTickSize,
		myScaleBarWidthInt + myOriginX, myOriginY
		);
	theQPainter->drawPolyline(myTickUpArray);

	//////////////////////////////////////////

	//  	绘制比例尺
	//Do drawing of scale bar text
	//

	QColor myBackColor = Qt::white;
	QColor myForeColor = Qt::black;

	//Draw the minimum label buffer
	theQPainter->setPen(myBackColor);
	myFontWidth = myFontMetrics.width("0");
	myFontHeight = myFontMetrics.height();

	for (int i = 0 - myBufferSize; i <= myBufferSize; i++)
	{
		for (int j = 0 - myBufferSize; j <= myBufferSize; j++)
		{
			theQPainter->drawText(int(i + (myOriginX - (myFontWidth / 2))),
				int(j + (myOriginY - (myFontHeight / 4))),
				"0");
		}
	}

	//Draw minimum label
	theQPainter->setPen(myForeColor);

	theQPainter->drawText(
		int(myOriginX - (myFontWidth / 2)),
		int(myOriginY - (myFontHeight / 4)),
		"0"
		);

	//
	//Draw maximum label
	//
	theQPainter->setPen(myBackColor);
	myFontWidth = myFontMetrics.width(myScaleBarMaxLabel);
	myFontHeight = myFontMetrics.height();
	//first the buffer
	for (int i = 0 - myBufferSize; i <= myBufferSize; i++)
	{
		for (int j = 0 - myBufferSize; j <= myBufferSize; j++)
		{
			theQPainter->drawText(int(i + (myOriginX + myScaleBarWidthInt - (myFontWidth / 2))),
				int(j + (myOriginY - (myFontHeight / 4))),
				myScaleBarMaxLabel);
		}
	}
	//then the text itself
	theQPainter->setPen(myForeColor);
	theQPainter->drawText(
		int(myOriginX + myScaleBarWidthInt - (myFontWidth / 2)),
		int(myOriginY - (myFontHeight / 4)),
		myScaleBarMaxLabel
		);

	//绘制单位标签
	//Draw unit label 
	//
	theQPainter->setPen(myBackColor);
	//first the buffer
	for (int i = 0 - myBufferSize; i <= myBufferSize; i++)
	{
		for (int j = 0 - myBufferSize; j <= myBufferSize; j++)
		{
			theQPainter->drawText(i + (myOriginX + myScaleBarWidthInt + myTextOffsetX),
				j + (myOriginY + myMajorTickSize),
				myScaleBarUnitLabel);
		}
	}
	//then the text itself
	theQPainter->setPen(myForeColor);
	theQPainter->drawText(
		(myOriginX + myScaleBarWidthInt + myTextOffsetX),
		(myOriginY + myMajorTickSize),
		myScaleBarUnitLabel
		);
}

void GisWindow::on_eightBtn_clicked()
{
	
}

void GisWindow::showMyPos(void)
{
	INSInfo* insData = new INSInfo;
	QgsPoint *setPosition = new QgsPoint;
	mINS->read(insData);

	setPosition->setX(insData->Longitude /1000000);
	setPosition->setY(insData->Latitude / 1000000);
	mapCanvas->setCenter(*setPosition);//居中显示
	mapCanvas->zoomScale(10000000);//放大比例
	mapCanvas->refresh();
}
