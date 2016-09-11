#ifndef __MAPMANAGER_H__
#define __MAPMANAGER_H__

// QGis include
#include <qgsmapcanvas.h>
#include <qgsmaplayer.h>
#include <qgsmaptool.h>
#include <qgsvectorlayer.h>
#include <qgsmaplayerregistry.h>
#include <qgsrasterlayer.h>
//Qt
#include <qobject.h>
#include <qfiledialog.h>
#include <qstring.h>

#include "INS.h"
//地图管理器负责   管理地图图层  管理地图图标  管理地图标绘图层 地图标绘信 加载地图
// 
class INS;
class MapManager :public QObject
{
	Q_OBJECT
public:
	MapManager(QgsMapCanvas* mapCanvas);
	~MapManager();

	//****图层管理***//
		void layerTree();
	//****地图管理***//
		// 添加矢量图层
		void addVectorLayers();
		// 添加栅格图层
		void addRasterLayers();
		//地图加载
		void MapLoad(void);//影像金字塔

	//****标绘图标管理***//
		//选择图标
		//更换图标
	//****地图标绘点管理***//
	//****地图管理***//
	//****地图工具管理***//

	//
	QList<QgsMapCanvasLayer> mapCanvasLayerSet; // 地图画布所用的图层集合
	QgsMapCanvas* mapCanvas; //地图画布
	bool state = 0;//是否是第一次加载地图 
	/*Test 给定坐标居中显示*/
	QgsPoint setPosition;

};


#endif //__MAPMANAGER_H__