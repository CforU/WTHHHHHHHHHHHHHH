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
//�е����⣬�������ȹ��� 
MapManager *MapManager::instance()//������MapManger �вι���֮��
{
	//�е㲻����� ����Ҫ���о�
	
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
	mapCanvas->setLayerSet(mapCanvasLayerSet);//��ͼ����ص�ͼ�㼯��
	mapCanvas->setVisible(true);
	mapCanvas->freeze(false);
	QgsCoordinateReferenceSystem wgs84(4326, QgsCoordinateReferenceSystem::EpsgCrsId);
	QgsCoordinateReferenceSystem web(3857, QgsCoordinateReferenceSystem::EpsgCrsId);
	mapCanvas->setDestinationCrs(wgs84);  //������ȷ
	//mapCanvas->setDestinationCrs(web); //������ȷ
	mapCanvas->setCrsTransformEnabled(true);
	mapCanvas->setExtent(mapCanvas->fullExtent());
	mapCanvas->refresh();//ˢ��ͼ��

}

//��ͼ���� //Ӱ�������
void MapManager::MapLoad(void)
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
	mapCanvas->refresh();
}

//���ʸ��ͼ��
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
	mapCanvas->setLayerSet(mapCanvasLayerSet);//��ͼ����ص�ͼ�㼯��
	mapCanvas->setVisible(true);
	mapCanvas->freeze(false);
	QgsCoordinateReferenceSystem wgs84(4326, QgsCoordinateReferenceSystem::EpsgCrsId);
	QgsCoordinateReferenceSystem web(3857, QgsCoordinateReferenceSystem::EpsgCrsId);
	mapCanvas->setDestinationCrs(wgs84);  //������ȷ
	//mapCanvas->setDestinationCrs(web); //������ȷ
	mapCanvas->setCrsTransformEnabled(true);
	mapCanvas->setExtent(mapCanvas->fullExtent());
	mapCanvas->refresh();//ˢ��ͼ��

}


//���դ��ͼ��
void MapManager::addRasterLayers()
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
	mapCanvas->refresh();
}

//########################
//��ʼ�����ͼ��
void MapManager::init_MarkerIcon()
{

#if 1
	//ͨ��QSettings�����ļ���ȡ���ͼ�겢���г�ʼ��  ����ʹ��forѭ��

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
	//�ֶ�д��
	const char* Name[] = { "����", "���","�е�", "�յ�", "ָ�ӳ� ", "���˻� ",
		"��Ѳ", "�Ĵ�", "��ʽ", "test", "test", "test", "test", "test", "test", "test""test", "test", "test" };
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
	MarkerIcon.insert(1, qMakePair("����", "Resources/icon/gis/mkPng/icon_bhtjd_2.png"));
	MarkerIcon.insert(2, qMakePair("���", "Resources/icon/gis/mkPng/icon_bhqd_2.png"));
	MarkerIcon.insert(3, qMakePair("�е�", "Resources/icon/gis/mkPng/icon_bhty_2.png"));
	MarkerIcon.insert(4, qMakePair("�յ�", "Resources/icon/gis/mkPng/icon_bhzd_2.png"));
	MarkerIcon.insert(5, qMakePair("ָ�ӳ� ", "Resources/icon/gis/mkPng/icon_bhzhc_2.png"));
	MarkerIcon.insert(6, qMakePair("���˻� ", "Resources/icon/gis/mkPng/icon_bhwrj_3.png"));
	MarkerIcon.insert(7, qMakePair("��Ѳ", "Resources/icon/gis/mkPng/icon_bhlx_3.png"));
	MarkerIcon.insert(8, qMakePair("�Ĵ�", "Resources/icon/gis/mkPng/icon_bhxld_13.png"));
	MarkerIcon.insert(9, qMakePair("��ʽ", "Resources/icon/gis/mkPng/icon_bhls_3.png"));
	MarkerIcon.insert(10, qMakePair("test", "Resources/icon/gis/mkPng/icon_bhld_3.png"));
	MarkerIcon.insert(11, qMakePair("test", "Resources/icon/gis/mkPng/icon_bhgdq_3.png"));
	MarkerIcon.insert(12, qMakePair("test", "Resources/icon/gis/mkPng/icon_bhls_3.png"));
	MarkerIcon.insert(13, qMakePair("test", "Resources/icon/gis/mkPng/icon_bhls_3.png"));
	MarkerIcon.insert(14, qMakePair("test", "Resources/icon/gis/mkPng/icon_bhld_3.png"));
	MarkerIcon.insert(15, qMakePair("test", "Resources/icon/gis/mkPng/icon_bhgdq_3.png"));
	MarkerIcon.insert(16, qMakePair("test", "Resources/icon/gis/mkPng/icon_bhls_3.png"));

#endif
}