#include "MarkerTool.h"
#define		POINT_INDEX		1	//点索引号

//默认标绘图标 为点 
QString MarkerTool::MarkerIcon = "Resources/icon/gis/mkSvg/icon_bhtjd_2.svg";//是否会出bug  是否合理 每次创建工具都是默认的工具
QString MarkerTool::defaultMarkerIcon = QString("Resources/icon/gis/mkSvg/icon_bhtjd_2.svg");


//MarkerTool::MarkerTool(QgsMapCanvas* mapCanvas, CaptureMode flags)
MarkerTool::MarkerTool(QgsMapCanvas* mapCanvas, CaptureMode cptflag)
: MapTools(mapCanvas), mCptFlag(cptflag)
{
	mToolName = tr("Marker");
	pRubber = NULL;//绘制点 画布
	pRubber2 = NULL;//绘制拐点 画布
	mRubberBand = NULL;//绘制线 画布
	moveFlag = false; //移动点标志

	testTimer = new QTimer(this);
	create_point();
	num = 0;
	connect(testTimer, SIGNAL(timeout()), this, SLOT(movePath()));
	//旋转角度
	angle = 0;
}
void MarkerTool::create_point()
{
	//test
	for (int i = 0; i++; i < 60){
		PathPoint[i] = QPoint(i * 10, i * 6);
		pp.append(new QPoint(i * 10, i * 6));
	}

}


MarkerTool::~MarkerTool()
{
	delete pRubber;
	delete pRubber2;
	delete mRubberBand;
}


// 1 重写鼠标释放事件 
void MarkerTool::canvasReleaseEvent(QgsMapMouseEvent* e)
{
	moveFlag = false;

	if (e->button() == Qt::LeftButton) /* 鼠标左键*/
	{
		if (mCptFlag == CapturePoint){
			
		}
		if (mCptFlag == CaptureLine ){
			markerLine(e);
		}

	}
	if (e->button() == Qt::RightButton) /* 鼠标右键*/ {
		markerPoint(e);
	}


}

//重写鼠标双击事件
void MarkerTool::canvasDoubleClickEvent(QgsMapMouseEvent* e) {
	//删除线
	if (e->button() == Qt::LeftButton && mCptFlag == CaptureLine) /* 鼠标双击左键*/ {
		//删除点
		delete pRubber;
		pRubber = NULL;
		//删除点
		delete pRubber2;
		pRubber2 = NULL;
		//删除线
		delete mRubberBand;
		mRubberBand = NULL;
		return;
	}
	//删除选中的标绘图标
	if (e->button() == Qt::LeftButton){
		QgsAnnotationItem* sItem = selectedItem();
		if (sItem)
		{
			QGraphicsScene* scene = sItem->scene();
			if (scene)
			{
				scene->removeItem(sItem);
			}
			delete sItem;
			sItem = nullptr;

		}
	}
	if (e->button() == Qt::RightButton)
	{
		if (tFlag == false){
			//开始运行定时器，定时时间间隔为1000ms
			testTimer->start(1000);
			tFlag = true;
			//num = 0;
		}
		else{
			//停止运行定时器
			if (testTimer->isActive())
				testTimer->stop();
			tFlag = false;
		}
	}
	
}

// 重写鼠标按下事件
void MarkerTool::canvasPressEvent(QgsMapMouseEvent* e) {


	if (e->button() == Qt::RightButton /*&& mCptFlag == CaptureLine*/) /* 鼠标右键*/
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
void MarkerTool::canvasMoveEvent(QgsMapMouseEvent* e) {

	if (mRubberBand && pRubber2 && moveFlag) {
		//移动点
		mRubberBand->movePoint(POINT_INDEX, mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()), 0);
		pRubber2->movePoint(POINT_INDEX, mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()), 0);
		return;
	}


	QgsAnnotationItem* sItem = selectedItem();
	if (sItem && (e->buttons() & Qt::LeftButton))
	{
		//判断是否移动标绘点
		if (mCurrentMoveAction == QgsAnnotationItem::MoveMapPosition)
		{
			sItem->setMapPosition(toMapCoordinates(e->pos()));
			mMovePoint = sItem->mapPosition();
			sItem->update();
			QgsProject::instance()->setDirty(true);
		}
	}
	else if (sItem)
	{
		QgsAnnotationItem::MouseMoveAction moveAction = sItem->moveActionForPosition(e->pos());
		if (mCanvas)
		{
			mCanvas->setCursor(QCursor(sItem->cursorShapeForAction(moveAction)));
		}
	}
	mLastMousePosition = e->pos();

}
int MarkerTool::addVertex(const QgsPoint& point){
	QgsPoint layerPoint;
	// 1 将鼠标释放位置的点转换成地图上的位置
	nextPoint(point, layerPoint);//
	// 2 创建图层
	if (!mRubberBand) // 没有rubber band，就创建一个
	{
		mRubberBand = createRubberBand(  QGis::Line);
	}
	// 3 在图层上标记点
	mRubberBand->addPoint(point);
	// 4 追加点
	m_captureList.append(layerPoint);
	// 5 创建临时图层
	//if (!mTempRubberBand)
	//{
	//	mTempRubberBand = createRubberBand(QGis::Line, true);
	//}
	//// 6 在临时图层上标记点
	//mTempRubberBand->addPoint(point);
	return 0;
}


void MarkerTool::markerPoint(QgsMapMouseEvent* e)
{
	
	//标绘点
	//if (!pRubber) {
	//	pRubber = createRubberBand(QGis::Point);
	//}
	//pRubber->setColor(QColor(0, 0, 255));
	//pRubber->setWidth(2);
	//pRubber->setIcon(QgsRubberBand::ICON_CROSS);
	//pRubber->setIconSize(10);
	//pRubber->addPoint(savePoint, true);
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

	addVertex(mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()));

	//测试地图坐标体系
	// 获取当前图层
	//QgsVectorLayer* layer = qobject_cast<QgsVectorLayer*>(mCanvas->currentLayer());
	//// 得到点坐标，转换为地图坐标
	//QgsPoint savePoint = toLayerCoordinates(layer, mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()));
	//QgsPoint layerPoint;
	//// 1 将鼠标释放位置的点转换成地图上的位置
	//QgsPoint point = mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos());
	//nextPoint(point, layerPoint);//
	//qDebug() << " e->pos(): " << e->pos() << "---" << "Position:" << point.toQPointF();
	//qDebug() << " savePoint: " << savePoint.toString();

}

void MarkerTool::markerLine(QgsMapMouseEvent* e)
{
	// 获取当前图层
	QgsVectorLayer* layer = qobject_cast<QgsVectorLayer*>(mCanvas->currentLayer());
	// 得到点坐标，转换为地图坐标
	QgsPoint savePoint = toLayerCoordinates(layer, mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()));
	//高亮拐点处
	if (!pRubber2){
		pRubber2 = createRubberBand(QGis::Point);
	}
	pRubber2->setColor(QColor(255, 0, 0));
	pRubber2->setWidth(2);
	pRubber2->setIcon(QgsRubberBand::ICON_CIRCLE);
	pRubber2->setIconSize(5);
	pRubber2->addPoint(savePoint, true);
	//添加顶点
	addVertex(mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()));

}


// 重写鼠标按压事件 移动点的时候
void MarkerTool::canvasPressEvent_MovePoint(QgsMapMouseEvent* e)
{
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

// 重写鼠标移动事件 移动点的时候
void MarkerTool::canvasMoveEvent_MovePoint(QgsMapMouseEvent* e)
{


	QgsAnnotationItem* sItem = selectedItem();
	if (sItem && (e->buttons() & Qt::LeftButton))
	{
		//判断是否移动标绘点
		if (mCurrentMoveAction == QgsAnnotationItem::MoveMapPosition)
		{
			sItem->setMapPosition(toMapCoordinates(e->pos()));
			mMovePoint = sItem->mapPosition();
			sItem->update();
			QgsProject::instance()->setDirty(true);
		}


		/**************************************************************************************************************/
		////判断是否移动边框
		//else if (mCurrentMoveAction == QgsAnnotationItem::MoveFramePosition)
		//{
		//	if (sItem->mapPositionFixed())
		//	{
		//		sItem->setOffsetFromReferencePoint(sItem->offsetFromReferencePoint() + (e->pos() - mLastMousePosition));
		//	}
		//	else
		//	{
		//		QPointF newCanvasPos = sItem->pos() + (e->pos() - mLastMousePosition);
		//		sItem->setMapPosition(toMapCoordinates(newCanvasPos.toPoint()));
		//	}
		//	sItem->update();
		//	QgsProject::instance()->setDirty(true);
		//}
		/************************************************************************************************************/
		/*
		else if (mCurrentMoveAction != QgsAnnotationItem::NoAction)
		{
			//handle the frame resize actions
			QSizeF size = sItem->frameSize();
			double xmin = sItem->offsetFromReferencePoint().x();
			double ymin = sItem->offsetFromReferencePoint().y();
			double xmax = xmin + size.width();
			double ymax = ymin + size.height();

			if (mCurrentMoveAction == QgsAnnotationItem::ResizeFrameRight ||
				mCurrentMoveAction == QgsAnnotationItem::ResizeFrameRightDown ||
				mCurrentMoveAction == QgsAnnotationItem::ResizeFrameRightUp)
			{
				xmax += e->pos().x() - mLastMousePosition.x();
			}
			if (mCurrentMoveAction == QgsAnnotationItem::ResizeFrameLeft ||
				mCurrentMoveAction == QgsAnnotationItem::ResizeFrameLeftDown ||
				mCurrentMoveAction == QgsAnnotationItem::ResizeFrameLeftUp)
			{
				xmin += e->pos().x() - mLastMousePosition.x();
			}
			if (mCurrentMoveAction == QgsAnnotationItem::ResizeFrameUp ||
				mCurrentMoveAction == QgsAnnotationItem::ResizeFrameLeftUp ||
				mCurrentMoveAction == QgsAnnotationItem::ResizeFrameRightUp)
			{
				ymin += e->pos().y() - mLastMousePosition.y();
			}
			if (mCurrentMoveAction == QgsAnnotationItem::ResizeFrameDown ||
				mCurrentMoveAction == QgsAnnotationItem::ResizeFrameLeftDown ||
				mCurrentMoveAction == QgsAnnotationItem::ResizeFrameRightDown)
			{
				ymax += e->pos().y() - mLastMousePosition.y();
			}

			//switch min / max if necessary
			double tmp;
			if (xmax < xmin)
			{
				tmp = xmax;
				xmax = xmin;
				xmin = tmp;
			}
			if (ymax < ymin)
			{
				tmp = ymax;
				ymax = ymin;
				ymin = tmp;
			}

			sItem->setOffsetFromReferencePoint(QPointF(xmin, ymin));
			sItem->setFrameSize(QSizeF(xmax - xmin, ymax - ymin));
			sItem->update();
			QgsProject::instance()->setDirty(true);
			return;
		}*/
		
	}
	/********************************************************************************/
	else if (sItem)
	{
		QgsAnnotationItem::MouseMoveAction moveAction = sItem->moveActionForPosition(e->pos());
		if (mCanvas)
		{
			mCanvas->setCursor(QCursor(sItem->cursorShapeForAction(moveAction)));
		}
	}
	mLastMousePosition = e->pos();
	/**************************************************************************************/
}


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

//下一个点
int MarkerTool::nextPoint(const QgsPoint& mapPoint, QgsPoint& layerPoint)
{
	QgsVectorLayer *vlayer = qobject_cast<QgsVectorLayer *>(mCanvas->currentLayer());

	layerPoint = toLayerCoordinates(vlayer, mapPoint); //transform snapped point back to layer crs

	return 0;
}
//创建RubberBand图层
QgsRubberBand* MarkerTool::createRubberBand(QGis::GeometryType geometryType /*= QGis::Point*/, bool alternativeBand /*= false*/)
{
	
	QgsRubberBand* rb = new QgsRubberBand(mCanvas);
	rb->setWidth(2);
	rb->setColor(QColor(0,255,0));
//	rb->show();
	return rb;
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

void MarkerTool::movePath()
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
			QgsPoint point = mCanvas->mapSettings().mapToPixel().toMapCoordinates(QPoint(num*10,num*10));
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

//标绘点
void  MarkerTool::markerPoint(QgsPoint point)
{

}
//标绘路径
void  MarkerTool::markerPath(QList<QgsPoint> path)
{


}

