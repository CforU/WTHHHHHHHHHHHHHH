
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
	//search ��ʾ��־
	searchFlag = false;
	//������Ĭ����ʾ
	ScaleFlagsEnable = true;
	//setScaleBarEnable(true);



	WidgetSize = QSize(1024, 768);//�������С
	MapSize = QSize(500, 500);//��ͼ��ʾ��С
	this->resize(WidgetSize);
	//���Ĵ���
	MapWidget = new QMainWindow;
	

	//��ͼ��ͼ����
	mapCanvas = new QgsMapCanvas();//����
	mapCanvas->enableAntiAliasing(true);//���������Ч��
	mapCanvas->setCanvasColor(QColor(255, 255, 255));
	mapCanvas->setVisible(true);
	MapWidget->setCentralWidget(mapCanvas);
	

	//��߲˵�ʵ����
	leftBar = new  LeftBar();
	iconBar = new ContrlBar;
	leftStack = new QStackedWidget;
	leftStack->addWidget(leftBar);
	leftStack->addWidget(iconBar);
	leftStack->setCurrentIndex(0);
	mMarkerFlag = true;
	//�ұ߰�ťʵ����
	rightBar = new RightBar();
	//��ͼUI
	//������
	searchBox = new  MapSearchBox();
	// searchBox->move(MapWidget->x() + 10, MapWidget->y() + 50); mapCanvas
	//searchBox->raise();

	//״̬��
	sta = MapWidget->statusBar();
	//��ʾ��ͼ��γ�ȿؼ���ʼ��
	m_lblCoordinate = new QLabel();
	m_lblCoordinate->setMinimumSize(100, 20);
	m_lblCoordinate->setFrameShape(QFrame::WinPanel);
	m_lblCoordinate->setFrameShadow(QFrame::Sunken);
	sta->addWidget(m_lblCoordinate);
	//��ʾ�����ľ�������
	m_labLengthAndArea = new QLabel();
	m_labLengthAndArea->setMinimumSize(100, 20);
	m_labLengthAndArea->setFrameShape(QFrame::WinPanel);
	m_labLengthAndArea->setFrameShadow(QFrame::Sunken);
	sta->addWidget(m_labLengthAndArea);

	mMapManager = new MapManager(mapCanvas);//��ͼ������ ��Ҫ�ڵ�ͼ������֮��
	mRouteAnalysis = new RouteAnalysis();//·������
	//Checking if arduino is connected or not
	mINS = new INS(COMPORT);//�ߵ���

	
	

	//�����岼��
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
	//�ź�����
	//�ź�����
	//�Ŵ���С���ι����ź���۵�����
	//connect(MapWidget, SIGNAL(clicked()), mapCanvas, SLOT(zoomFull()));
	//connect(toolBar->raster, SIGNAL(clicked()), mapCanvas, SLOT(addVectorLayers()));//�����ťʵ�����ʸ��ͼƬ
	connect(leftBar->m_FirstBtn, SIGNAL(clicked()), this, SLOT(on_search()));
	connect(leftBar->m_SecondBtn, SIGNAL(clicked()), this, SLOT(on_Action_AddFeatureTool_Line()));//·����� �Ժ���·������
	connect(leftBar->m_ThirdBtn, SIGNAL(clicked()), this, SLOT(addRasterLayers()));//�����ťʵ�����դ��ͼƬ
	connect(leftBar->m_FifthBtn, SIGNAL(clicked()), this, SLOT(showMyPos()));//��ʾ��ǰλ��
	connect(leftBar->m_SixBtn, SIGNAL(clicked()), this, SLOT(zoomInMode()));//�Ŵ�
	connect(leftBar->m_SeventhBtn, SIGNAL(clicked()), this, SLOT(zoomOutMode()));//��С
	connect(leftBar->m_EighthBtn, SIGNAL(clicked()), this, SLOT(panMode()));
	connect(leftBar->m_ninethBtn, SIGNAL(clicked()), this, SLOT(on_Marker()));//ͼ��	 //markr

	//�ұ��ź�����
	connect(rightBar->m_FirstBtn, SIGNAL(clicked()), this, SLOT(on_Action_AddFeatureTool_Point()));//mesure 
	connect(rightBar->m_SecondBtn, SIGNAL(clicked()), this, SLOT(on_Action_AddFeatureTool_None()));//mesure 
	connect(rightBar->m_ThirdBtn, SIGNAL(clicked()), this, SLOT(on_actionMeasure_Area()));//mesure 
	//connect(rightBar->m_EighthBtn, SIGNAL(clicked()), this, SLOT(on_eightBtn_clicked()));//
	connect(rightBar->m_ninethBtn, SIGNAL(clicked()), this, SLOT(on_return()));
	//���������źźͲ�
	connect(mapCanvas, SIGNAL(xyCoordinates(QgsPoint)), this, SLOT(showMousePoint(QgsPoint)));//��굱ǰ����
	connect(mapCanvas, SIGNAL(renderComplete(QPainter *)), this, SLOT(showScaleBar(QPainter *))); //��ʾ������

}

//���ʸ��ͼ��
void GisWindow::addVectorLayers()
{
	mMapManager->addVectorLayers();
}

//���դ��ͼ��
void GisWindow::addRasterLayers()
{
	mMapManager->addRasterLayers();
}

//�Ŵ����
void GisWindow::zoomInMode()
{
	printf("mode_zoomIn ok!!/n");
	//mpPanTool= new QgsMapToolPan(mainMapCanvas);    
	//mpPanTool->setAction(ui.mpActionPan);    
	QgsMapToolZoom *mpZoomInTool = new QgsMapToolZoom(mapCanvas, false);
	//mpZoomInTool->setAction(ui.actionZoom_in);    
	//   
	//mpZoomOutTool->setAction(ui.mpActionZoomOut);
	mapCanvas->setMapTool(mpZoomInTool); //��Ҫ���qgs�����maptool������ʹ��qt�����action //�л��ɶ�Ӧ�Ĺ���

}
//��С����
void GisWindow::zoomOutMode()
{
	QgsMapToolZoom *mpZoomOutTool = new QgsMapToolZoom(mapCanvas, true);
	mapCanvas->setMapTool(mpZoomOutTool);
}
//����
void GisWindow::panMode()
{
	QgsMapToolPan *mpPanTool = new QgsMapToolPan(mapCanvas);
	mapCanvas->setMapTool(mpPanTool);
}

//��ʾȫ��
void GisWindow::zoomFull()
{

}

//������㹤��
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
	//������湦��
	on_Action_AddFeatureTool_Point();
	//�л��˵�
	if (mMarkerFlag == true)
	{
		leftStack->setCurrentIndex(1);
		mMarkerFlag = false;
	}
	
}
void GisWindow::on_return()
{
	//��ȡ��ǰ���ڹ��� ���ݵ�ǰ���ܽ��з���

	//�л��˵�
	if (mMarkerFlag == false)
	{
		leftStack->setCurrentIndex(0);
		mMarkerFlag = true;
		//�رձ�湦�� �����л�Ϊ��Ĺ���
		this->panMode();//�����������ι���
		return;
	}
	//����flags  ���η��� ÿ��ֻ��Ҫ����һ�� 

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
//��ʾ��ǰ���λ�õ�����
void GisWindow::showMousePoint(const QgsPoint& p)
{
	m_lblCoordinate->setText(QString("x=%1,y=%2").arg(p.x()).arg(p.y()));
}
//��ʾ��ǰ��������
void GisWindow::showMesureLength(double length)
{
	qDebug() << "Measure Lines : " << length << " (m) ";
	m_labLengthAndArea->setText(QString(tr("length: %1 (m)").arg(length)));
}
//��ʾ��ǰ�������
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

//�����Ƿ���������
// ���ʹ����ʱ�ᱨ��
void GisWindow::setScaleBarEnable(bool en)
{
	ScaleFlagsEnable = en;
	//���δ���� disconnect �᲻�ᱨ�� 
	if (ScaleFlagsEnable)
	{
		connect(mapCanvas, SIGNAL(renderComplete(QPainter *)), this, SLOT(showScaleBar(QPainter *)));//��ʾ������
	}
	else
	{
		disconnect(mapCanvas, SIGNAL(renderComplete(QPainter *)), this, SLOT(showScaleBar(QPainter *)));//��ʾ������
	}
}

void GisWindow::showScaleBar(QPainter *theQPainter){

	double mScale = mapCanvas->scale();
	double conversionFactor = 39.3700787;
	qDebug() << "Scale:  1 : " << mScale / conversionFactor;

	/////////////////////////////////////



	/*		��ʾ������			*/
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
	//ȡ��
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

	int mMarginHorizontal = 529;//�����Ŀ�
	int mMarginVertical = 460;//�͸�

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
	//		����Tick UP
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

	//  	���Ʊ�����
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

	//���Ƶ�λ��ǩ
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
	mapCanvas->setCenter(*setPosition);//������ʾ
	mapCanvas->zoomScale(10000000);//�Ŵ����
	mapCanvas->refresh();
}
