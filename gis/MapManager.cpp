#include "MapManager.h"

MapManager::MapManager(QgsMapCanvas* mapCanvas):mapCanvas(mapCanvas)
{
	
	//setPosition = *INS::get_position();
	//qDebug() << "setPosition:" << setPosition.toString() ;
}
MapManager::~MapManager()
{

}
void MapManager::layerTree()
{

}

//��ͼ���� //Ӱ�������
void MapManager::MapLoad(void)
{

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
	mapCanvas->refresh();//ˢ��ͼ��

}


//���դ��ͼ��
void MapManager::addRasterLayers()
{
	/*
	*
	*
	*/

	/*
	*��һ��ִ�о���ֱ�Ӽ���ָ���õĵ�ͼ��
	*�ٴξͿ���ͨ�������ťʵ��ѡ����ص�ͼ�Ĺ���
	*/
	QgsRasterLayer* rasterLayer;//����һ��դ��ͼ��
	if (state == true){//ѡ����صĵ�ͼ��ַ
		QString filename = QFileDialog::getOpenFileName(nullptr, QObject::tr("open vector"), "", "*.tif");
		QStringList temp = filename.split(QDir::separator());
		QString basename = temp.at(temp.size() - 1);
		rasterLayer = new QgsRasterLayer(filename, basename, "gdal", false);//��դ���ͼ���ݼ��ص�դ��ͼ����

	}
	else{//�򿪳���ֱ�Ӽ������úõĵ�ͼ
		//rasterLayer = new QgsRasterLayer("fortest/mapdata/test.tif", "gdal", false);//��դ���ͼ���ݼ��ص�դ��ͼ����
		rasterLayer = new QgsRasterLayer("E:/Maps/world.tif", "gdal", false);//��դ���ͼ���ݼ��ص�դ��ͼ����
		//rasterLayer = new QgsRasterLayer("C://Map//J50G001036_Level_19.tif", "gdal", false);//����դ��ͼ��
		state = 1;//��������1�´���ִ�о�ִ��ѡ����ص�ͼ��ַ����
	}

	if (!rasterLayer->isValid())
	{
		//QMessageBox::critical(this, "error", "layer is invalid");
		return;
	}
	
	QgsMapLayerRegistry::instance()->addMapLayer(rasterLayer);//
	mapCanvasLayerSet.append(rasterLayer);
	mapCanvas->setExtent(rasterLayer->extent());
	mapCanvas->setLayerSet(mapCanvasLayerSet);
	mapCanvas->setVisible(true);
	mapCanvas->freeze(false);
	mapCanvas->refresh();
}

