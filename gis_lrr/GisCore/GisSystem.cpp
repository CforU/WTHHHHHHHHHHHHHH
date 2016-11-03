
#include "GisSystem.h"

//#include "PushEvent.h"
//#include "GisData.h"

#include <QGraphicsProxyWidget>
#include <QGraphicsAnchorLayout>

GisSystem::GisSystem(QWidget *parent) :
QMainWindow(parent)
{
	QgsApplication::setPrefixPath("3rdparty/qgis/apps/qgis", true); // ע�⣺�������·���ĳ��������Qgis��·��������
	QgsApplication::initQgis();
	SysInit();
	//init();//��ʼ��
	
}

void GisSystem::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.drawPixmap(0, 0, QPixmap("Resources/icon/gis/mobil/bg_map_2.png"));
}

void GisSystem::SysInit()
{
	//��ͼ��ͼ���� ���ȴ���
	mapCanvas = new QgsMapCanvas();//����
	mapCanvas->enableAntiAliasing(true);//���������Ч��
	mapCanvas->setCanvasColor(QColor(255, 255, 255));
	mapCanvas->setVisible(true);
	this->setCentralWidget(mapCanvas);
	
	//��ͼ������ ��Ҫ�ڵ�ͼ������֮��
	//mMapManager = new MapManager(mapCanvas);
	//·������
	mRouteAnalysis = new RouteAnalysis();

	//������ͼ����
	create_mapTool();

	//! ��ʼ��ͼ�������
	//QWidget w;
	
#if 1
	mlayerTreeView = new QgsLayerTreeView(mapCanvas);
	initLayerTreeView();
	view = mapCanvas->scene()->addWidget(mlayerTreeView);
	view->setSelected(true);
	mlayerTreeView->move(mapCanvas->width(), 0);
	mlayerTreeView->hide();
	
#endif	
	//���в�����ʾ������

	//���μ��ص�ͼ
	firstLoad();

	//�ź����� ��ʾ������
	connect(mapCanvas, SIGNAL(renderComp lete(QPainter *)), this, SLOT(showScaleBar(QPainter *))); //��ʾ������


}

//������ͼ����
void GisSystem::create_mapTool(){
	mapTools.mZoomIn = new QgsMapToolZoom(mapCanvas, false /* zoomIn */);
	mapTools.mZoomOut = new QgsMapToolZoom(mapCanvas, true /* zoomOut */);
	mapTools.mPan = new MapToolPan(mapCanvas);
#ifdef HAVE_TOUCH
	//mapTools.mTouch = new QgsMapToolTouch(mapCanvas); //����
#endif
	//����
	mapTools.addMeasureToolLine = new MeasureTool(mapCanvas, false);
	mapTools.addMeasureToolArea = new MeasureTool(mapCanvas, true);
	//���
	mapTools.svgMarkerTool = new SvgMarkerTool(mapCanvas);
	mapTools.ALPMarkerTool = new ALPMarkerTool(mapCanvas);


}

//ͼ���������ʼ������
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
	
	//mlayerTreeView->setStyleSheet(styleTwo); //������ʽ

	// ���ӵ�ͼ������ͼ�������
	mlayerTreeCanvasBridge = new QgsLayerTreeMapCanvasBridge(QgsProject::instance()->layerTreeRoot(), mapCanvas, this);
	connect(QgsProject::instance(), SIGNAL(writeProject(QDomDocument&)), mlayerTreeCanvasBridge, SLOT(writeProject(QDomDocument&)));
	connect(QgsProject::instance(), SIGNAL(readProject(QDomDocument)), mlayerTreeCanvasBridge, SLOT(readProject(QDomDocument)));

}

//#############  ��ͼ���� ##########################################
//���ʸ��ͼ��
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
	mapCanvas->setLayerSet(mapCanvasLayerSet);//��ͼ����ص�ͼ�㼯��
	mapCanvas->setVisible(true);
	mapCanvas->freeze(false);
	QgsCoordinateReferenceSystem wgs84(4326, QgsCoordinateReferenceSystem::EpsgCrsId);
	QgsCoordinateReferenceSystem web(3857, QgsCoordinateReferenceSystem::EpsgCrsId);
	mapCanvas->setDestinationCrs(wgs84);  //������ȷ
	//mapCanvas->setDestinationCrs(web); //������ȷ
	mapCanvas->setCrsTransformEnabled(true);
	mapCanvas->setExtent(mapCanvas->fullExtent());
	mapCanvas->zoomScale(10000);
	mapCanvas->refresh();//ˢ��ͼ��
}

//���դ��ͼ��
void GisSystem::addRasterLayers()
{
	/*
	*��һ��ִ�о���ֱ�Ӽ���ָ���õĵ�ͼ��
	*�ٴξͿ���ͨ�������ťʵ��ѡ����ص�ͼ�Ĺ���
	*/
	QgsRasterLayer* rasterLayer;//����һ��դ��ͼ��
	QString filename = QFileDialog::getOpenFileName(nullptr, QObject::tr("open vector"), "", "*.tif");
	QStringList temp = filename.split(QDir::separator());
	QString basename = temp.at(temp.size() - 1);
	rasterLayer = new QgsRasterLayer(filename, basename, "gdal", false);//��դ���ͼ���ݼ��ص�դ��ͼ����
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
	mapCanvas->setDestinationCrs(wgs84);  //������ȷ
	//mapCanvas->setDestinationCrs(web); //������ȷ
	mapCanvas->setCrsTransformEnabled(true);
	mapCanvas->setExtent(mapCanvas->fullExtent());
	mapCanvas->zoomScale(10000);
	mapCanvas->refresh();
}
//���ض��ֵ�ͼ
//��ͼ���� //Ӱ�������
void GisSystem::MapLoad(void)
{
	/*
	*��һ��ִ�о���ֱ�Ӽ���ָ���õĵ�ͼ��
	*�ٴξͿ���ͨ�������ťʵ��ѡ����ص�ͼ�Ĺ���
	*/
	QgsMapLayer* Layer;//����һ��ͼ��

	QString filename = QFileDialog::getOpenFileName(nullptr, QObject::tr("open Map"), "", "*.tif *.shp");
	QStringList temp = filename.split(QDir::separator());
	QString basename = temp.at(temp.size() - 1);
	if (filename.isNull())
		return;

	QFileInfo  f(filename);
	if (f.suffix() == "tif"){
		Layer = new QgsRasterLayer(filename, basename, "gdal", false);//��դ���ͼ���ݼ��ص�դ��ͼ����
		//Layer = new QgsRasterLayer("Resources/mapdata/zgc.tif", "gdal", false);//��դ���ͼ���ݼ��ص�դ��ͼ����
		//rasterLayer = new QgsRasterLayer("C://Map//J50G001036_Level_19.tif", "gdal", false);//����դ��ͼ��
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
	mapCanvas->setDestinationCrs(wgs84);  //������ȷ
	//mapCanvas->setDestinationCrs(web); //������ȷ
	mapCanvas->setCrsTransformEnabled(true);
	mapCanvas->setExtent(mapCanvas->fullExtent());
	mapCanvas->zoomScale(10000);
	mapCanvas->refresh();
}

//�Ŵ����
void GisSystem::zoomInMode()
{
	if (mapCanvas->scale() > 1000){
		MoveAndControlMap(MapControl::ZoomIn);
	}
}
//��С����
void GisSystem::zoomOutMode()
{
	if (mapCanvas->scale() < 80000000){
		MoveAndControlMap(MapControl::ZoomOut);
	}
}
//����
void GisSystem::panMode()
{
	mapCanvas->setMapTool(mapTools.mPan);
}

//��ʾȫ��
void GisSystem::zoomFull()
{

}

// ���������ƶ���ͼ�Ĳۺ���
//����
void GisSystem::LeftMove()
{
	MoveAndControlMap(MapControl::Left);	
}
//����
void GisSystem::RightMove()
{
	MoveAndControlMap(MapControl::Right);
}
//����
void GisSystem::UpMove()
{
	MoveAndControlMap(MapControl::Up);
	
}
//����
void GisSystem::DownMove()
{
	MoveAndControlMap(MapControl::Down);
}
//���ղ����Ĳۺ���
void GisSystem::MoveAndControlMap(MapControl c)
{
	//��ͼ�м��
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

//����SVG���㹤��
void GisSystem::MarkerSvg()
{
	mapCanvas->setMapTool(mapTools.svgMarkerTool);
}
// ALP Area Line Point
void GisSystem::ALPMarler()
{
	mapCanvas->setMapTool(mapTools.ALPMarkerTool);
}

//��ʾ������ͼ�������
void GisSystem::show_LayerManager()
{
	mlayerTreeView->show();
}
void GisSystem::hide_LayerManager()
{
	mlayerTreeView->hide();
}

//�����
void GisSystem::Measure_Line(){
	
	mapCanvas->setMapTool(mapTools.addMeasureToolLine);
	
}
//�����
void GisSystem::Measure_Area(){	
	mapCanvas->setMapTool(mapTools.addMeasureToolArea);	
}

//���ò��������Ϣ �����´β���
void GisSystem::ResetMeasure()
{
	mapTools.addMeasureToolArea->clearUpMeasure();
	mapTools.addMeasureToolLine->clearUpMeasure();
}
//�л���ͼ����
void GisSystem::setMapTool(QgsMapTool *tool)
{
	if (tool)
	{
		mapCanvas->setMapTool(tool);
	}
}
//�����Ƿ���������
// ���ʹ����ʱ�ᱨ��
void GisSystem::setScaleBarEnable(bool en)
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
	//ȡ��
	double scaler = pow(10.0, myPowerOf10);
	myActualSize = qRound(myActualSize / scaler) * scaler;
	myScaleBarWidth = myActualSize / myMapUnitsPerPixelDouble;
	emit sendData(myActualSize, myScaleBarWidth);//��������
}

// �ҵ�λ��
QgsSvgAnnotationItem*  GisSystem::showMyPos(QgsPoint pos, QString svgPath)
{
	if (!mySelfItem){
		mySelfItem = mapTools.svgMarkerTool->createItem(pos, svgPath);
	}
	else{
		mapTools.svgMarkerTool->updateItemPositon(mySelfItem, pos);
	}
	mapCanvas->setCenter(pos);//������ʾ
	//mapCanvas->setCenter(pos);//������ʾ
	//mapCanvas->zoomScale(100000000000);//�Ŵ����
	mapCanvas->refresh();

	return mySelfItem;
}

//���μ��ص�ͼ
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
	mapCanvas->setLayerSet(mapCanvasLayerSet);//��ͼ����ص�ͼ�㼯��
	mapCanvas->setVisible(true);
	mapCanvas->freeze(false);
	QgsCoordinateReferenceSystem wgs84(4326, QgsCoordinateReferenceSystem::EpsgCrsId);
	QgsCoordinateReferenceSystem web(3857, QgsCoordinateReferenceSystem::EpsgCrsId);
	mapCanvas->setDestinationCrs(wgs84);  //������ȷ
	//mapCanvas->setDestinationCrs(web); //������ȷ
	mapCanvas->setCrsTransformEnabled(true);
	mapCanvas->setExtent(mapCanvas->fullExtent());
	mapCanvas->zoomScale(11339.6);
	mapCanvas->refresh();//ˢ��ͼ��

}



//##############  API ###################################################################

//�����ͼ���ӿ�
void GisSystem::clearUpMap()//��յ�ͼ
{
	mapTools.addMeasureToolArea->clearUpMeasure();
	mapTools.addMeasureToolLine->clearUpMeasure();
	//������������ Ҳ��Ҫ������Դ

}
