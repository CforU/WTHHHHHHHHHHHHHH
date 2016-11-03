#include "MarkerTool.h"

//默认标绘图标 为点 
int MarkerTool::MarkerType=0; //默认标绘类型 点类型
QString MarkerTool::MarkerIcon = "Resources/icon/gis/mkSvg/icon_bhtjd_2.svg";//是否会出bug  是否合理 每次创建工具都是默认的工具
QString MarkerTool::defaultMarkerIcon = QString("Resources/icon/gis/mkSvg/icon_bhtjd_2.svg");


MarkerTool::MarkerTool(QgsMapCanvas* mapCanvas)
:QgsMapTool(mapCanvas)
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

//####################内部函数###################################

int MarkerTool::addVertex(const QgsPoint& point){	
	// 1 将鼠标释放位置的点转换成地图上的位置
	QgsVectorLayer *vlayer = qobject_cast<QgsVectorLayer *>(mCanvas->currentLayer());
	QgsPoint layerPoint = toLayerCoordinates(vlayer, point);
	// 2 创建图层
	if (!mRubberBand) // 没有rubber band，就创建一个
	{
		mRubberBand = new QgsRubberBand(mCanvas, QGis::Line);
		mRubberBand->setWidth(2);
		mRubberBand->setColor(QColor(0, 255, 0));

	}
	// 3 在图层上标记点
	mRubberBand->addPoint(point);
	// 4 追加点
	m_captureList.append(layerPoint);

	m_stringPoints.append(point.toString());	
	//test
	
	return 0;
}

void MarkerTool::markerLine(QgsMapMouseEvent* e)
{
	// 获取当前图层
	QgsVectorLayer* layer = qobject_cast<QgsVectorLayer*>(mCanvas->currentLayer());
	// 得到点坐标，转换为地图坐标
	QgsPoint savePoint = toLayerCoordinates(layer, mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()));
	//添加顶点
	addVertex(mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()));

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
	MarkerPointList.append(psvg);//管理车辆标绘点
	return psvg;
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
			scene = sItem->scene();
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
//############ 筛选 操作 ######################
//显示车辆链表中第i个标绘
void MarkerTool::on_showMarker(int i){
	MarkerPointList.at(i)->setVisible(true);
}
//隐藏车辆链表中第i个标绘
void MarkerTool::on_hideMarker(int i){
	MarkerPointList.at(i)->setVisible(false);
}

//############ 内部静态成员外部接口 操作 ######################
//设置标绘图标类型
void MarkerTool::setMarkerType(int type)
{
	MarkerType = type;
}
//设置当前标绘图标
void MarkerTool::setMarkerIconPath(QString path)
{
	MarkerIcon = path;// Path

}
//设置默认的标绘图标
void MarkerTool::setDefaultMarkerIcon(QString path)
{
	defaultMarkerIcon = path;//Path
}

//########################################################

// 通过读取数据库中车辆id获取车辆类型
int MarkerTool::getVehicleTypeId(int aVehicleType)
{
	int id = 0;
	QSqlQuery sqlQuery;

	QString typeStr = "";

	switch (aVehicleType)
	{
	case 6:
		typeStr = QStringLiteral("履带");
		break;
	case 8:
		typeStr = QStringLiteral("轮巡");
		break;
	case 9:
		typeStr = QStringLiteral("轮式");
		break;
	default:
		break;
	}

	sqlQuery.exec(
		QString("select id from t_car where car_type=%1").arg(typeStr)
		);
	if (sqlQuery.next())
	{
		id = sqlQuery.value(0).toInt();
		return id;
	}
	else
	{
		qDebug() << "无此类型";
		return -1;
	}

}
//从数据库根据车辆id判断车辆的类型 
MarKerVehicleType MarkerTool::getVechileType(int id)
{

	//调用数据库接口 获取type
	int typeId = getVehicleTypeId(id);
	// MarkerTool::MarKerVehicleType type = MarkerTool::MarKerVehicleType(typeId);
	switch (typeId){
	case 4:
		return MarKerVehicleType::CommandCar; //指挥车
		break;
	case 5:
		return MarKerVehicleType::UAV; //无人机
		break;
	case 6:
		return MarKerVehicleType::TrackedVehicle;//履带车
		break;
	case 7:
		return MarKerVehicleType::DumpedCar;//抛投车
		break;
	case 8:
		return MarKerVehicleType::WheelPatrolCar;// 轮巡车
		break;
	case 9:
		return MarKerVehicleType::WheeledVehicles;//轮式车
		break;
	default:
		return MarKerVehicleType::CarDefault; //无车 默认 
	}

}


//############  API  ###################
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

	addVertex(mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()));

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
		emit createWidget();//发送信号 动态创建筛选控件
	}
}

//车辆标绘 
QgsAnnotationItem* MarkerTool::VehicleMarker(QgsPoint pos, MarKerVehicleType type)
{
	
	QString path = RCSettings::getValue(RCSettings::GIS, QString("svg/%1").arg((int)type), "Resources/icon/gis/mkSvg/icon_bhtjd_2.svg").toString();
	//QString path = MapManager::instance()->MarkerIconSvg[ctype];
	QgsAnnotationItem* item = createItem(pos, path);
	return item;
}
//车辆标绘 
void MarkerTool::VehicleMarker(QgsPoint pos, int id)
{
	//标绘车辆
	//QgsAnnotationItem* item = VehicleMarker(pos, getVechileType(id));
	QgsAnnotationItem* item = VehicleMarker(pos,MarKerVehicleType::WheelPatrolCar);
	//放入链表管理	
	if (item)
	{
		CarMarkerMap.insert(id, item);
	}
}
//车辆位置更新 角度也要处理
void MarkerTool::updateVehiclePosition(QgsPoint pos, int id)
{
	//如果id 不存在是不是标绘出来一辆新的 
	QgsAnnotationItem* sItem=NULL;
	if (CarMarkerMap.contains(id)){
		sItem = CarMarkerMap.value(id);
	}
	else
	{
	    //如果无此id 是否创建一个标绘		
		VehicleMarker(pos, id);
		return;
	}
	if (sItem)
	{
		sItem->setMapPosition(pos);
		// sItem->markerSymbol()->setAngle((angle += 6) % 360));// 设置旋转 但是目前无法旋转
		mMovePoint = sItem->mapPosition();
		sItem->update();
	}
}
//删除车辆
void MarkerTool::delteVechile(int id)//删除车辆标绘点
{
	//如果id 不存在是不是标绘出来一辆新的 
	QgsAnnotationItem* sItem = NULL;
	if (CarMarkerMap.contains(id)){
		sItem = CarMarkerMap.value(id);
	}
	if (sItem)
	{
		deleteItem(sItem); //删除标绘点
		CarMarkerMap.remove(id);//清除管理链表
		sItem = NULL;
	}
}

//路径点标绘
void MarkerTool::markerRoutePoint(QgsPoint pos, MarkerRoutePointType type)
{
	QString path = RCSettings::getValue(RCSettings::GIS, QString("svg/%1").arg((int)type), "Resources/icon/gis/mkSvg/icon_bhtjd_2.svg").toString();
	QgsSvgAnnotationItem* svg = createItem(pos, path);			
	PathMarkerList.append(svg);							
	addVertex(pos);//是否需要在这个地方处理

}
//路径标绘
void MarkerTool::RouteMarker(QList<QgsAnnotationItem*>  PathMarkerList)/*起点 中间点 终点 */
{
	//标绘起点和终点  循环标绘中间点 
	int i = 1;
	markerRoutePoint(PathMarkerList.at(0)->pos(), MarkerRoutePointType::StartPoint);
	for (i=1;i<= PathMarkerList.size()-2;i++){
		markerRoutePoint(PathMarkerList.at(i)->pos(), MarkerRoutePointType::PassPoint);
	}
	markerRoutePoint(PathMarkerList.last()->pos(), MarkerRoutePointType::EndPoint);

}
//路径标绘
void MarkerTool::RouteMarker(QList<QgsPoint>  PathList)
{

	if (PathList.isEmpty()){
		return;
	}

	//标绘起点和终点  循环标绘中间点 
	int i = 1;
	markerRoutePoint(PathList.at(0), MarkerRoutePointType::StartPoint);
	for (i=1; i<= PathList.size() - 2; i++){
		markerRoutePoint(PathList.at(i), MarkerRoutePointType::PassPoint);
	}
	markerRoutePoint(PathList.last(), MarkerRoutePointType::EndPoint);
}


//保存路径到文件
void MarkerTool::saveMarkerPath2File()
{
	QString fileName = ("fortest/path/path.txt");
	QFile file(fileName);
	//QStringList m_stringPoints;
	/*-------------保存坐标点到文件-------------*/
	if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
	{
		qDebug() << "cann't open the file!!!";

	}else{
		qDebug() << "save path!!!";
	}
	QTextStream in(&file);
	QStringList::Iterator it;
	for (it = m_stringPoints.begin(); it != m_stringPoints.end(); ++it){
		in << *it << "\n";//如果写多行，同上循环即可  
	}

	m_captureList.clear();
	m_stringPoints.clear();
	QPoint p = QPoint(500 + 1440, 250);
	QToolTip::showText(p, "save path success!");
	file.close();
	/*-------------------------------------------*/
}
//加载文件路径到地图
void MarkerTool::loadMarkerPath2File()
{
	QString fileName = ("fortest/path/path.txt");
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug() << "cann't open the file!!!";

	}
	else{
		qDebug() << "load path!!!";
	}
	QTextStream in(&file);
	//读取最多10行  
	QStringList str[10];
	for (int i = 0; i < 10; i++){
		str[i] = in.readLine().split(',');//读一行
		if (str[i].at(0) != "" && str[i].at(1) != ""){
			PathMarkerPointList.append( QgsPoint(str[i].at(0).toDouble(), str[i].at(1).toDouble()));
		}
	}
	//自动标绘svg路径图标
	RouteMarker(PathMarkerPointList);
	PathMarkerPointList.clear();//加载完成之后不需要了
	file.close();
}

//保存路径到XML文件
void MarkerTool::savePath2xml()
{
	QPoint p = QPoint(500 + 1440, 250); //双屏
	if (m_stringPoints.isEmpty()){
		QToolTip::showText(p, "NO PATH TO SAVE!");
		return;
	}
	QFile file("fortest/path/myPathData.xml");
	if (!file.open(QFile::WriteOnly | QFile::Text))
	{
		qDebug() << "cann't open the file!!!";

	}
	QXmlStreamWriter writer(&file);
	writer.setAutoFormatting(true);
	writer.writeStartDocument();
	writer.writeStartElement("PathsData");

	//追加写入多条路径信息？？？
	writer.writeTextElement("PathName", "testPath2333");
	writer.writeTextElement("PathLength", QString::number(233, 10));
	writer.writeStartElement("PointsData");
	QStringList::Iterator it;
	for (it = m_stringPoints.begin(); it != m_stringPoints.end(); ++it){
		writer.writeTextElement("PathPoint", *it);
	}

	writer.writeEndElement();
	writer.writeEndElement();
	writer.writeEndDocument();	
	QToolTip::showText( p, "save path success!"); 
	file.close();
}
//加载XML文件中的路径
void MarkerTool::loadPath2xml()
{
	QFile file("fortest/path/myPathData.xml");
	if (!file.open(QFile::ReadOnly | QFile::Text))
	{
		qDebug() << "cann't open the file!!!";

	}
	QStringList strList;
	QXmlStreamReader *reader = new QXmlStreamReader(&file);
	while (!reader->atEnd() && !reader->hasError()) {
		QXmlStreamReader::TokenType token = reader->readNext();
		if (token == QXmlStreamReader::StartDocument) {
			continue;
		}
		//TODO 
		if (reader->isStartElement() && reader->name() == "PointsData"){
			while (!reader->atEnd()){
				reader->readNext();
				if (reader->isStartElement() && reader->name() == "PathPoint"){
					//qDebug() << "point" << reader->readElementText(); //点
					QString pt = reader->readElementText();
					strList.append(pt);
				}
			}
		}
	}
	qDebug() << "strList is :" << strList;
	for (int i = 0; i < strList.count(); ++i){
		QString strPoint = strList.at(i);
		QStringList listPoint = strPoint.split(",");
		//addVertex(QgsPoint(listPoint.at(0).toDouble(), listPoint.at(1).toDouble()));
		PathMarkerPointList.append(QgsPoint(listPoint.at(0).toDouble(), listPoint.at(1).toDouble()));
	}
	RouteMarker(PathMarkerPointList);
	PathMarkerPointList.clear();//加载完成之后不需要了
	m_stringPoints.clear();
	reader->clear();
	file.close();
}


//清除地图上的标绘内容
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


//移动路径 静静做参考
//更新路径
#if 0
void movePath()
{
	if (!mCanvas)
	{
		return;
	}
	if (num < 60){

		QgsAnnotationItem* sItem = selectedItem();
		if (sItem)
		{
			//QgsPoint point = mCanvas->mapSettings().mapToPixel().toMapCoordinates(PathPoint[num]);
			QgsPoint point = mCanvas->mapSettings().mapToPixel().toMapCoordinates(QPoint(num * 10, num * 10));
			sItem->setMapPosition(point);
			// sItem->markerSymbol()->setAngle((angle += 6) % 360));// 设置旋转 但是目前无法旋转
			mMovePoint = sItem->mapPosition();
			sItem->update();
			//QgsProject::instance()->setDirty(true);
			qDebug() << "point::::" << PathPoint[num];
			qDebug() << num;

		}
		num++;
	}
	else{
		num = 0;
	}
}
#endif
