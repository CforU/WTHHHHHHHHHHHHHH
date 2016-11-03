#include "MapManager.h"
#include <qfileinfo.h>
MapManager* MapManager::theMapManger = nullptr;

MapManager::MapManager(QgsMapCanvas* mapCanvas):mapCanvas(mapCanvas)
{
	//
	theMapManger = this;
	init_MarkerIcon();
	
}
MapManager::MapManager()
{
	theMapManger = this;
	init_MarkerIcon();
}
//有点问题，必须最先构造 
MapManager *MapManager::instance()//必须在MapManger 有参构造之后
{
	//有点不合理的 还需要再研究
	
	if (!theMapManger)
	{
		qDebug() << "error! MapManger get instance failed";
		return (MapManager *)NULL;
		//theMapManger = new MapManager;
	}
	return theMapManger;
}

MapManager::~MapManager()
{

}
void MapManager::layerTree()
{

}

void MapManager::firstLoad()
{
	QString MapPath = RCSettings::getValue(RCSettings::GIS, "mapDataPat", "Resources/mapdata/zgc.tif").toString();
	QgsMapLayer* Layer = new QgsRasterLayer(MapPath, "gdal", false);
	if (!Layer->isValid())
	{
		//QMessageBox::critical(this, "error", "layer is invalid");
		return;
	}
	QgsMapLayerRegistry::instance()->addMapLayer(Layer);
	mapCanvasLayerSet.append(Layer);
	mapCanvas->setExtent(Layer->extent());
	mapCanvas->setLayerSet(mapCanvasLayerSet);//将图层加载到图层集内
	mapCanvas->setVisible(true);
	mapCanvas->freeze(false);
	QgsCoordinateReferenceSystem wgs84(4326, QgsCoordinateReferenceSystem::EpsgCrsId);
	QgsCoordinateReferenceSystem web(3857, QgsCoordinateReferenceSystem::EpsgCrsId);
	mapCanvas->setDestinationCrs(wgs84);  //坐标正确
	//mapCanvas->setDestinationCrs(web); //距离正确
	mapCanvas->setCrsTransformEnabled(true);
	mapCanvas->setExtent(mapCanvas->fullExtent());
	mapCanvas->refresh();//刷新图层

}

//地图加载 //影像金字塔
void MapManager::MapLoad(void)
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
	mapCanvas->refresh();
}

//添加矢量图层
void MapManager::addVectorLayers()
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
	mapCanvas->refresh();//刷新图层

}


//添加栅格图层
void MapManager::addRasterLayers()
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
	mapCanvas->refresh();
}

//########################
//初始化标绘图标
void MapManager::init_MarkerIcon()
{

#if 1
	//通过QSettings配置文件获取标绘图标并进行初始化  可以使用for循环

	//MarkerIcon

	MarkerIcon.insert(0, RCSettings::getValue(RCSettings::GIS, "png/0", "Resources/icon/gis/mkPng/icon_bhtjd_2.png").toString());
	MarkerIcon.insert(1, RCSettings::getValue(RCSettings::GIS, "png/1", "Resources/icon/gis/mkPng/icon_bhqd_2.png").toString());
	MarkerIcon.insert(2, RCSettings::getValue(RCSettings::GIS, "png/2", "Resources/icon/gis/mkPng/icon_bhty_2.png").toString());
	MarkerIcon.insert(3, RCSettings::getValue(RCSettings::GIS, "png/3", "Resources/icon/gis/mkPng/icon_bhzd_2.png").toString());
	MarkerIcon.insert(4, RCSettings::getValue(RCSettings::GIS, "png/4", "Resources/icon/gis/mkPng/icon_bhzhc_2.png").toString());
	MarkerIcon.insert(5, RCSettings::getValue(RCSettings::GIS, "png/5", "Resources/icon/gis/mkPng/icon_bhwrj_3.png").toString());
	MarkerIcon.insert(6, RCSettings::getValue(RCSettings::GIS, "png/6", "Resources/icon/gis/mkPng/icon_bhlx_3.png").toString());
	MarkerIcon.insert(7, RCSettings::getValue(RCSettings::GIS, "png/7", "Resources/icon/gis/mkPng/icon_bhxld_13.png").toString());
	MarkerIcon.insert(8, RCSettings::getValue(RCSettings::GIS, "png/8", "Resources/icon/gis/mkPng/icon_bhls_3.png").toString());
	MarkerIcon.insert(9, RCSettings::getValue(RCSettings::GIS, "png/9", "Resources/icon/gis/mkPng/icon_bhld_3.png").toString());
	MarkerIcon.insert(10, RCSettings::getValue(RCSettings::GIS, "png/10", "Resources/icon/gis/mkPng/icon_bhgdq_3.png").toString());
	MarkerIcon.insert(11, RCSettings::getValue(RCSettings::GIS, "png/11", "Resources/icon/gis/mkPng/icon_bhls_3.png").toString());
	MarkerIcon.insert(12, RCSettings::getValue(RCSettings::GIS, "png/12", "Resources/icon/gis/mkPng/icon_bhls_3.png").toString());
	MarkerIcon.insert(13, RCSettings::getValue(RCSettings::GIS, "png/13", "Resources/icon/gis/mkPng/icon_bhld_3.png").toString());
	MarkerIcon.insert(14, RCSettings::getValue(RCSettings::GIS, "png/14", "Resources/icon/gis/mkPng/icon_bhgdq_3.png").toString());
	MarkerIcon.insert(15, RCSettings::getValue(RCSettings::GIS, "png/15", "Resources/icon/gis/mkPng/icon_bhls_3.png").toString());


	//MarkerIconSvg;

	MarkerIconSvg.insert(0, RCSettings::getValue(RCSettings::GIS, "svg/0", "Resources/icon/gis/mkSvg/icon_bhtjd_2.svg").toString());
	MarkerIconSvg.insert(1, RCSettings::getValue(RCSettings::GIS, "svg/1", "Resources/icon/gis/mkSvg/icon_bhqd_2.svg").toString());
	MarkerIconSvg.insert(2, RCSettings::getValue(RCSettings::GIS, "svg/2", "Resources/icon/gis/mkSvg/icon_bhty_2.svg").toString());
	MarkerIconSvg.insert(3, RCSettings::getValue(RCSettings::GIS, "svg/3", "Resources/icon/gis/mkSvg/icon_bhzd_2.svg").toString());
	MarkerIconSvg.insert(4, RCSettings::getValue(RCSettings::GIS, "svg/4", "Resources/icon/gis/mkSvg/icon_bhzhc_2.svg").toString());
	MarkerIconSvg.insert(5, RCSettings::getValue(RCSettings::GIS, "svg/5", "Resources/icon/gis/mkSvg/icon_bhwrj_3.svg").toString());
	MarkerIconSvg.insert(6, RCSettings::getValue(RCSettings::GIS, "svg/6", "Resources/icon/gis/mkSvg/icon_bhlx_3.svg").toString());
	MarkerIconSvg.insert(7, RCSettings::getValue(RCSettings::GIS, "svg/7", "Resources/icon/gis/mkSvg/icon_bhxld_13.svg").toString());
	MarkerIconSvg.insert(8, RCSettings::getValue(RCSettings::GIS, "svg/8", "Resources/icon/gis/mkSvg/icon_bhls_3.svg").toString());
	MarkerIconSvg.insert(9, RCSettings::getValue(RCSettings::GIS, "svg/9", "Resources/icon/gis/mkSvg/icon_bhld_3.svg").toString());
	MarkerIconSvg.insert(10, RCSettings::getValue(RCSettings::GIS, "svg/10", "Resources/icon/gis/mkSvg/icon_bhgdq_3.svg").toString());
	MarkerIconSvg.insert(11, RCSettings::getValue(RCSettings::GIS, "svg/11", "Resources/icon/gis/mkSvg/icon_bhls_3.svg").toString());
	MarkerIconSvg.insert(12, RCSettings::getValue(RCSettings::GIS, "svg/12", "Resources/icon/gis/mkSvg/icon_bhls_3.svg").toString());
	MarkerIconSvg.insert(13, RCSettings::getValue(RCSettings::GIS, "svg/13", "Resources/icon/gis/mkSvg/icon_bhld_3.svg").toString());
	MarkerIconSvg.insert(14, RCSettings::getValue(RCSettings::GIS, "svg/14", "Resources/icon/gis/mkSvg/icon_bhgdq_3.svg").toString());
	MarkerIconSvg.insert(15, RCSettings::getValue(RCSettings::GIS, "svg/15", "Resources/icon/gis/mkSvg/icon_bhls_3.svg").toString());

#else
	//手动写入
	const char* Name[] = { "画点", "起点","中点", "终点", "指挥车 ", "无人机 ",
		"轮巡", "履带", "轮式", "test", "test", "test", "test", "test", "test", "test""test", "test", "test" };
	//MarkerIcon
	MarkerIcon.insert(0,  "Resources/icon/gis/mkPng/icon_bhtjd_2.png");
	MarkerIcon.insert(1,  "Resources/icon/gis/mkPng/icon_bhqd_2.png");
	MarkerIcon.insert(2, "Resources/icon/gis/mkPng/icon_bhty_2.png");
	MarkerIcon.insert(3, "Resources/icon/gis/mkPng/icon_bhzd_2.png");
	MarkerIcon.insert(4,  "Resources/icon/gis/mkPng/icon_bhzhc_2.png");
	MarkerIcon.insert(5,  "Resources/icon/gis/mkPng/icon_bhwrj_3.png");
	MarkerIcon.insert(6,  "Resources/icon/gis/mkPng/icon_bhlx_3.png");
	MarkerIcon.insert(7,  "Resources/icon/gis/mkPng/icon_bhxld_13.png");
	MarkerIcon.insert(8, "Resources/icon/gis/mkPng/icon_bhls_3.png");
	MarkerIcon.insert(9,  "Resources/icon/gis/mkPng/icon_bhld_3.png");
	MarkerIcon.insert(10,  "Resources/icon/gis/mkPng/icon_bhgdq_3.png");
	MarkerIcon.insert(11,  "Resources/icon/gis/mkPng/icon_bhls_3.png");
	MarkerIcon.insert(12, "Resources/icon/gis/mkPng/icon_bhls_3.png");
	MarkerIcon.insert(13,  "Resources/icon/gis/mkPng/icon_bhld_3.png");
	MarkerIcon.insert(14,  "Resources/icon/gis/mkPng/icon_bhgdq_3.png");
	MarkerIcon.insert(15, "Resources/icon/gis/mkPng/icon_bhls_3.png");

	//MarkerIconSvg;
	
	MarkerIconSvg.insert(0,  "Resources/icon/gis/mkSvg/icon_bhtjd_2.svg");
	MarkerIconSvg.insert(1,  "Resources/icon/gis/mkSvg/icon_bhqd_2.svg");
	MarkerIconSvg.insert(2, "Resources/icon/gis/mkSvg/icon_bhty_2.svg");
	MarkerIconSvg.insert(3, "Resources/icon/gis/mkSvg/icon_bhzd_2.svg");
	MarkerIconSvg.insert(4,  "Resources/icon/gis/mkSvg/icon_bhzhc_2.svg");
	MarkerIconSvg.insert(5,  "Resources/icon/gis/mkSvg/icon_bhwrj_3.svg");
	MarkerIconSvg.insert(6,  "Resources/icon/gis/mkSvg/icon_bhlx_3.svg");
	MarkerIconSvg.insert(7,  "Resources/icon/gis/mkSvg/icon_bhxld_13.svg");
	MarkerIconSvg.insert(8, "Resources/icon/gis/mkSvg/icon_bhls_3.svg");
	MarkerIconSvg.insert(9,  "Resources/icon/gis/mkSvg/icon_bhld_3.svg");
	MarkerIconSvg.insert(10,  "Resources/icon/gis/mkSvg/icon_bhgdq_3.svg");
	MarkerIconSvg.insert(11,  "Resources/icon/gis/mkSvg/icon_bhls_3.svg");
	MarkerIconSvg.insert(12, "Resources/icon/gis/mkSvg/icon_bhls_3.svg");
	MarkerIconSvg.insert(13,  "Resources/icon/gis/mkSvg/icon_bhld_3.svg");
	MarkerIconSvg.insert(14,  "Resources/icon/gis/mkSvg/icon_bhgdq_3.svg");
	MarkerIconSvg.insert(15, "Resources/icon/gis/mkSvg/icon_bhls_3.svg");

#endif


#if 0
	MarkerIcon.insert(1, qMakePair("画点", "Resources/icon/gis/mkPng/icon_bhtjd_2.png"));
	MarkerIcon.insert(2, qMakePair("起点", "Resources/icon/gis/mkPng/icon_bhqd_2.png"));
	MarkerIcon.insert(3, qMakePair("中点", "Resources/icon/gis/mkPng/icon_bhty_2.png"));
	MarkerIcon.insert(4, qMakePair("终点", "Resources/icon/gis/mkPng/icon_bhzd_2.png"));
	MarkerIcon.insert(5, qMakePair("指挥车 ", "Resources/icon/gis/mkPng/icon_bhzhc_2.png"));
	MarkerIcon.insert(6, qMakePair("无人机 ", "Resources/icon/gis/mkPng/icon_bhwrj_3.png"));
	MarkerIcon.insert(7, qMakePair("轮巡", "Resources/icon/gis/mkPng/icon_bhlx_3.png"));
	MarkerIcon.insert(8, qMakePair("履带", "Resources/icon/gis/mkPng/icon_bhxld_13.png"));
	MarkerIcon.insert(9, qMakePair("轮式", "Resources/icon/gis/mkPng/icon_bhls_3.png"));
	MarkerIcon.insert(10, qMakePair("test", "Resources/icon/gis/mkPng/icon_bhld_3.png"));
	MarkerIcon.insert(11, qMakePair("test", "Resources/icon/gis/mkPng/icon_bhgdq_3.png"));
	MarkerIcon.insert(12, qMakePair("test", "Resources/icon/gis/mkPng/icon_bhls_3.png"));
	MarkerIcon.insert(13, qMakePair("test", "Resources/icon/gis/mkPng/icon_bhls_3.png"));
	MarkerIcon.insert(14, qMakePair("test", "Resources/icon/gis/mkPng/icon_bhld_3.png"));
	MarkerIcon.insert(15, qMakePair("test", "Resources/icon/gis/mkPng/icon_bhgdq_3.png"));
	MarkerIcon.insert(16, qMakePair("test", "Resources/icon/gis/mkPng/icon_bhls_3.png"));

#endif
}