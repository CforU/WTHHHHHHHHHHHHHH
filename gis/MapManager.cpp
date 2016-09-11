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

//地图加载 //影像金字塔
void MapManager::MapLoad(void)
{

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
	mapCanvas->refresh();//刷新图层

}


//添加栅格图层
void MapManager::addRasterLayers()
{
	/*
	*
	*
	*/

	/*
	*第一次执行就是直接加载指定好的地图，
	*再次就可以通过点击按钮实现选择加载地图的功能
	*/
	QgsRasterLayer* rasterLayer;//创建一个栅格图层
	if (state == true){//选择加载的地图地址
		QString filename = QFileDialog::getOpenFileName(nullptr, QObject::tr("open vector"), "", "*.tif");
		QStringList temp = filename.split(QDir::separator());
		QString basename = temp.at(temp.size() - 1);
		rasterLayer = new QgsRasterLayer(filename, basename, "gdal", false);//将栅格地图数据加载到栅格图层中

	}
	else{//打开程序直接加载设置好的地图
		//rasterLayer = new QgsRasterLayer("fortest/mapdata/test.tif", "gdal", false);//将栅格地图数据加载到栅格图层中
		rasterLayer = new QgsRasterLayer("E:/Maps/world.tif", "gdal", false);//将栅格地图数据加载到栅格图层中
		//rasterLayer = new QgsRasterLayer("C://Map//J50G001036_Level_19.tif", "gdal", false);//创建栅格图层
		state = 1;//将条件置1下次再执行就执行选择加载地图地址方法
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

