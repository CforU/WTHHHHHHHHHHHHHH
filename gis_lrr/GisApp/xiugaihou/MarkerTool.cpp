#include "MarkerTool.h"

//默认标绘图标 为点 
int MarkerTool::MarkerType = 0; //默认标绘类型 点类型
QString MarkerTool::MarkerIcon = "Resources/icon/gis/mkSvg/icon_bhtjd_2.svg";//是否会出bug  是否合理 每次创建工具都是默认的工具
QString MarkerTool::defaultMarkerIcon = QString("Resources/icon/gis/mkSvg/icon_bhtjd_2.svg");


MarkerTool::MarkerTool(QgsMapCanvas* mapCanvas)
: QgsMapTool(mapCanvas)
{
	mToolName = tr("Marker");	
	mRubberBand = NULL;//绘制线 画布
	moveFlag = false; //移动点标志

}

MarkerTool::~MarkerTool()
{
//	delete mRubberBand;
}


//############### 事件处理 ########################################

// 1 重写鼠标释放事件 
void MarkerTool::canvasReleaseEvent(QgsMapMouseEvent* e)
{
	
	if (e->button() == Qt::LeftButton  && itemSelectFlag == false) /* 鼠标左键*/
	{
		QgsAnnotationItem* sItem = selectedItem();
		if (sItem == nullptr){
			//markerPoint(e);
			QgsPoint mapPoint = mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos());
			//markerPoint(mapPoint, MarkerType);
			ManuallyMaker(mapPoint);
		}
	}
	if (e->button() == Qt::RightButton) /* 鼠标右键*/ {
		
	}
	moveFlag = false;
	itemSelectFlag = false;
}

//重写鼠标双击事件
void MarkerTool::canvasDoubleClickEvent(QgsMapMouseEvent* e) {
	//删除线
	//if (e->button() == Qt::LeftButton && mCptFlag == CaptureLine) /* 鼠标双击左键*/ {
		if (e->button() == Qt::RightButton) /* 鼠标双击左键*/ {		
			deleteItemAll();
	}
	
	
}

// 重写鼠标按下事件
void MarkerTool::canvasPressEvent(QgsMapMouseEvent* e) {


	if (e->button() == Qt::RightButton ) /* 鼠标右键*/
	{
		moveFlag = true;//移动点标志
	}

	if (!mCanvas)
	{
		return;
	}

	QgsAnnotationItem* sItem = selectedItem();
	if (sItem)
	{
		mCurrentMoveAction = sItem->moveActionForPosition(e->pos());
		if (mCurrentMoveAction != QgsAnnotationItem::NoAction)
		{
			return;
		}
	}

	if (!sItem || mCurrentMoveAction == QgsAnnotationItem::NoAction)
	{
		//select a new item if there is one at this position
		mCanvas->scene()->clearSelection();
		QgsAnnotationItem* existingItem = itemAtPos(e->pos());
		//获取索引号
		if (PathMarkerList.contains(existingItem)){
			pointIndex = PathMarkerList.indexOf(existingItem);
		}
		if (existingItem)
		{
			existingItem->setSelected(true);
		}
		else
		{
			//otherwise create new one
			//createItem(e);
			return;
		}
	}

}

// 重写鼠标移动事件
void MarkerTool::canvasMoveEvent(QgsMapMouseEvent* e)
{
	QgsAnnotationItem* sItem = selectedItem();
	if (sItem && (e->buttons() & Qt::LeftButton))
	{

		//判断是否移动标绘点
		if ((mCurrentMoveAction == QgsAnnotationItem::MoveMapPosition) )
		{
			sItem->setMapPosition(toMapCoordinates(e->pos()));
			mMovePoint = sItem->mapPosition();
			sItem->update();
			QgsProject::instance()->setDirty(true);
			if (mRubberBand && PathMarkerList.contains(sItem) ){
				mRubberBand->movePoint(pointIndex, mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()), 0);
			}
		}
		
	}
	else if (sItem)
	{
		QgsAnnotationItem::MouseMoveAction moveAction = sItem->moveActionForPosition(e->pos());
		if (mCanvas )
		{
			mCanvas->setCursor(QCursor(sItem->cursorShapeForAction(moveAction)));
			itemSelectFlag = true;
		}
	}
	mLastMousePosition = e->pos();

}

//####################内部函数 指针路径操作###################################
//创建路径标绘
QgsRubberBand* MarkerTool::createRoute()
{
	
	QgsRubberBand* mRubberBandRoute = new QgsRubberBand(mCanvas, QGis::Line);
	mRubberBandRoute->setWidth(2);
	mRubberBandRoute->setColor(QColor(0, 255, 0));

	return mRubberBandRoute;
	
}
QgsRubberBand* MarkerTool::createRoutePoint(const QgsPoint& point)
{
	// 1 将鼠标释放位置的点转换成地图上的位置
	QgsVectorLayer *vlayer = qobject_cast<QgsVectorLayer *>(mCanvas->currentLayer());
	QgsPoint layerPoint = toLayerCoordinates(vlayer, point);
	//创建一个路径标绘
	QgsRubberBand* mRubberBandRoute = createRoute();
	// 3 在图层上标记点
	mRubberBandRoute->addPoint(point);
	return mRubberBandRoute;
}
//添加路径点
int MarkerTool::addRoutePoint(QgsRubberBand* mRubberBand ,const QgsPoint& point){
	// 1 将鼠标释放位置的点转换成地图上的位置
	QgsVectorLayer *vlayer = qobject_cast<QgsVectorLayer *>(mCanvas->currentLayer());
	QgsPoint layerPoint = toLayerCoordinates(vlayer, point);
	// 2 创建图层
	if (!mRubberBand) // 没有rubber band，就创建一个
	{
		return -1;
		//mRubberBand = createRoute();
	}
		
	// 3 在图层上标记点
	mRubberBand->addPoint(point);
	m_captureList.append(layerPoint);
	return 0;
}
//标绘路径点
QgsSvgAnnotationItem* MarkerTool::MarkerRoutePoint(QgsRubberBand* mRubberBand, const QgsPoint& point, QString svgPath)
{
	if (!addRoutePoint(mRubberBand, point)){
		QgsSvgAnnotationItem* svg = createItem(point, svgPath);
		return svg;
	}
	return (QgsSvgAnnotationItem*)(NULL);
	
}
void MarkerTool::deleteRoute(QgsRubberBand* mRubberBand, QList<QgsAnnotationItem*>  PathList)
{
	if (mRubberBand){
		delete mRubberBand;
		mRubberBand = NULL;
	}
	if (!PathList.isEmpty){
		for (int i = 0; i< PathList.size(); ++i) {
			deleteItem(PathList.at(i)); //删除标绘点
		}
		PathList.clear();
	}
}



//############ item 操作 ######################
//创建item
QgsSvgAnnotationItem* MarkerTool::createItem(QgsPoint pos, QString svgPath)
{

	QgsSvgMarkerSymbolLayerV2 *svgMarker = new QgsSvgMarkerSymbolLayerV2(svgPath);
	svgMarker->setVerticalAnchorPoint(QgsMarkerSymbolLayerV2::Bottom);//将图标瞄点设置成底端
	svgMarker->setSize(8);//设置图标大小

	QgsSymbolLayerV2List symList;//创建符号链表
	symList.append(svgMarker);//将图标加入到符号链表里
	QgsMarkerSymbolV2* markSym = new QgsMarkerSymbolV2(symList);	
	

	QgsSvgAnnotationItem *psvg = new QgsSvgAnnotationItem(mCanvas);
	psvg->setMarkerSymbol(markSym);//设置显示样式
	psvg->setMapPosition(pos);
	psvg->setFrameSize(QSizeF(0, 0));//设置提示框大小 00去提示框
	//psvg->setFrameBorderWidth(10); 不知道干啥
	//psvg->setOffsetFromReferencePoint(QPointF(0, 0)); //可以移动渲染提示框的偏移位置
	//QgsRectangle r(0,0,20,20);
	//psvg->setRect(r, true);
					

	return psvg;
}
void MarkerTool::updateItemPositon(QgsAnnotationItem* sItem, QgsPoint pos)//更新item位置
{
	if (sItem)
	{
		sItem->setMapPosition(pos);
		// sItem->markerSymbol()->setAngle((angle += 6) % 360));// 设置旋转 但是目前无法旋转
		sItem->update();
	}
}
//删除item
int MarkerTool::deleteItem(QgsAnnotationItem* sItem)
{
	if (sItem)
	{
		QGraphicsScene* scene = sItem->scene();
		if (scene)
		{
			scene->removeItem(sItem);
		}
		delete sItem;
		sItem = nullptr;
		return 0;

	}
	else{
		return -1;
	}

}
//删除item
void MarkerTool::deleteItemAll()
{
	QgsAnnotationItem* sItem = selectedItem();
	QGraphicsScene* scene;
	if (sItem){
		if (PathMarkerList.contains(sItem))
		{
			scene = sItem->scene();
			scene->removeItem(sItem);
			pointIndex = PathMarkerList.indexOf(sItem);
			mRubberBand->removePoint(pointIndex);       ///////删除路径线上的点
			PathMarkerList.removeAt(pointIndex);
		}
		else {
			scene->removeItem(sItem);
		}
		delete sItem;
		sItem = nullptr;
	}
	else{
		//删除svg图标
		for (int i = 0; i < PathMarkerList.size(); ++i){
			scene = PathMarkerList.at(i)->scene();
			scene->removeItem(PathMarkerList.at(i));
		}
		PathMarkerList.clear();
		//删除线
		delete mRubberBand;
		mRubberBand = NULL;
	}
}
//选中
QgsAnnotationItem* MarkerTool::selectedItem()
{
	if (!mCanvas || !mCanvas->scene())
	{
		return nullptr;
	}
	QList<QGraphicsItem *> gItemList = mCanvas->scene()->selectedItems();
	QList<QGraphicsItem *>::iterator it = gItemList.begin();
	for (; it != gItemList.end(); ++it)
	{
		QgsAnnotationItem* aItem = dynamic_cast<QgsAnnotationItem*>(*it);
		if (aItem)
		{
			return aItem;
		}
	}
	return nullptr;
}

QgsAnnotationItem* MarkerTool::itemAtPos(QPointF pos)
{
	if (!mCanvas)
	{
		return nullptr;
	}

	QList<QGraphicsItem *> graphicItems = mCanvas->items(pos.toPoint());
	QList<QGraphicsItem *>::iterator gIt = graphicItems.begin();
	for (; gIt != graphicItems.end(); ++gIt)
	{
		QgsAnnotationItem* annotationItem = dynamic_cast<QgsAnnotationItem*>(*gIt);
		if (annotationItem)
		{
			return annotationItem;
		}
	}
	return nullptr;
}



//########################################################


//############  API  ###################
//############手动标绘###############//
int MarkerTool::addRoutePoint(const QgsPoint& point)
{
	// 1 将鼠标释放位置的点转换成地图上的位置
	QgsVectorLayer *vlayer = qobject_cast<QgsVectorLayer *>(mCanvas->currentLayer());
	QgsPoint layerPoint = toLayerCoordinates(vlayer, point);
	// 2 创建图层
	if (!mRubberBand) // 没有rubber band，就创建一个
	{
		mRubberBand = createRoute();
	}

	// 3 在图层上标记点
	mRubberBand->addPoint(point);

	return 0;
}
void MarkerTool::markerLine(QgsMapMouseEvent* e)
{
	// 获取当前图层
	QgsVectorLayer* layer = qobject_cast<QgsVectorLayer*>(mCanvas->currentLayer());
	// 得到点坐标，转换为地图坐标
	QgsPoint savePoint = toLayerCoordinates(layer, mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()));
	//添加顶点
	addRoutePoint(mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()));
}
void MarkerTool::deleteRoute()
{
	delete mRubberBand;
	mRubberBand = NULL;
	for (int i = 0; i< PathMarkerList.size(); ++i) {
		deleteItem(PathMarkerList.at(i)); //删除标绘点
	}
	PathMarkerList.clear();


}
//标绘点
void MarkerTool::markerPoint(QgsPoint pos, int type)
{
	//contains(key) 错误处理 查看是否存在 
	//QString path = MapManager::instance()->MarkerIconSvg[type];
	createItem(pos, MarkerIcon);
}
//标绘点
void MarkerTool::markerPoint(QgsMapMouseEvent* e)
{

	QgsSvgMarkerSymbolLayerV2 *svgMarker = new QgsSvgMarkerSymbolLayerV2(MarkerIcon.isNull() ? MarkerIcon : MarkerIcon);
	svgMarker->setVerticalAnchorPoint(QgsMarkerSymbolLayerV2::Bottom);//将图标瞄点设置成底端
	qDebug() << MarkerIcon << "  : " << MarkerIcon;
	qDebug() << "Marker symbol";
	QgsSymbolLayerV2List symList;//创建符号链表
	symList.append(svgMarker);//将图标加入到符号链表里
	QgsMarkerSymbolV2* markSym = new QgsMarkerSymbolV2(symList);
	svgMarker->setSize(8);//设置图标大小
	QgsSvgAnnotationItem *psvg = new QgsSvgAnnotationItem(mCanvas);
	psvg->setMarkerSymbol(markSym);//设置显示样式
	psvg->setMapPosition(mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()));
	PathMarkerList.append(psvg);

	addRoutePoint(mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()));

}
//手动标绘
void MarkerTool::ManuallyMaker(QgsPoint pos)
{
	//路径 起点与起点之间互斥 终点与终点互斥 只能存在一个

	if (MarkerType == 1 || MarkerType == 2 || MarkerType == 3){ //路径标绘
		MarkerRoutePointType ctype = (MarkerRoutePointType)MarkerType;
		markerRoutePoint(pos, ctype);
	}
	else  //车辆标绘
	{
		MarKerVehicleType ctype = (MarKerVehicleType)MarkerType;
		VehicleMarker(pos, ctype);
	}
}

//清楚地图上的标绘内容
void MarkerTool::clearUpMarker()
{
	//遍历 车辆容器 CarMarkerMap 容器 循环删除item 并且清楚容器内容 释放指针	
	QMap<int, QgsAnnotationItem*>::const_iterator i;
	for (i = CarMarkerMap.constBegin(); i != CarMarkerMap.constEnd(); ++i) {
		//qDebug() << i.key() << ":" << i.value();
		deleteItem(i.value()); //删除标绘点
	}
	CarMarkerMap.clear();
	//遍历路径容器
}



