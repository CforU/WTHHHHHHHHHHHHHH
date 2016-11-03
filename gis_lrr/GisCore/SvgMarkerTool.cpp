#include "SvgMarkerTool.h"

SvgMarkerTool::SvgMarkerTool(QgsMapCanvas* mapCanvas)
: QgsMapTool(mapCanvas)
{
	mToolName = tr("SvgMarkerTool");
	moveFlag = false;//移动点标志
	itemSelectFlag = false;
	pointIndex = 0;//需要移动的点的索引

}

SvgMarkerTool::~SvgMarkerTool()
{
	//所有点链表
	mPointList.clear();
	//所有的标绘句柄链表
	mSvgList.clear();
}


//############### 事件处理 ########################################

// 1 重写鼠标释放事件 
void SvgMarkerTool::canvasReleaseEvent(QgsMapMouseEvent* e)
{

	if (e->button() == Qt::LeftButton  && itemSelectFlag == false) /* 鼠标左键*/
	{
		QgsAnnotationItem* sItem = selectedItem();
		if (sItem == nullptr){		
			//QgsPoint mapPoint = mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos());			
			//createItem(mapPoint, MarkerSvgPath);
		}
	}
	if (e->button() == Qt::RightButton) /* 鼠标右键*/ {

	}
	moveFlag = false;
	itemSelectFlag = false;
}

//重写鼠标双击事件
void SvgMarkerTool::canvasDoubleClickEvent(QgsMapMouseEvent* e) {
	//删除线
	//if (e->button() == Qt::LeftButton && mCptFlag == CaptureLine) /* 鼠标双击左键*/ {
	if (e->button() == Qt::RightButton) /* 鼠标双击左键*/ {
		deleteItemAll();
	}


}

// 重写鼠标按下事件
void SvgMarkerTool::canvasPressEvent(QgsMapMouseEvent* e) {

	if (e->button() == Qt::RightButton) /* 鼠标右键*/
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
		if (mSvgList.contains(existingItem)){
			pointIndex = mSvgList.indexOf(existingItem);
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
void SvgMarkerTool::canvasMoveEvent(QgsMapMouseEvent* e)
{
	QgsAnnotationItem* sItem = selectedItem();
	if (sItem && (e->buttons() & Qt::LeftButton))
	{

		//判断是否移动标绘点
		if ((mCurrentMoveAction == QgsAnnotationItem::MoveMapPosition))
		{
			sItem->setMapPosition(toMapCoordinates(e->pos()));
			mMovePoint = sItem->mapPosition();
			sItem->update();			
		}

	}
	else if (sItem)
	{
		QgsAnnotationItem::MouseMoveAction moveAction = sItem->moveActionForPosition(e->pos());
		if (mCanvas)
		{
			mCanvas->setCursor(QCursor(sItem->cursorShapeForAction(moveAction)));
			itemSelectFlag = true;
		}
	}
	mLastMousePosition = e->pos();

}

//############ item 操作 ######################
//创建item
QgsSvgAnnotationItem* SvgMarkerTool::createItem(QgsPoint pos, QString svgPath)
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
	//进行管理
	mSvgList.append(psvg);


	return psvg;
}
void SvgMarkerTool::updateItemPositon(QgsAnnotationItem* sItem, QgsPoint pos)//更新item位置
{
	if (sItem)
	{
		sItem->setMapPosition(pos);
		// sItem->markerSymbol()->setAngle((angle += 6) % 360));// 设置旋转 但是目前无法旋转
		sItem->update();
	}
}
//删除item
int SvgMarkerTool::deleteItem(QgsAnnotationItem* sItem)
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
void SvgMarkerTool::deleteItemAll()
{
#if 0
	QgsAnnotationItem* sItem = selectedItem();
	QGraphicsScene* scene;
	if (sItem){
		if (mSvgList.contains(sItem))
		{
			scene = sItem->scene();
			scene->removeItem(sItem);
			pointIndex = mSvgList.indexOf(sItem);
			mRubberBand->removePoint(pointIndex);       ///////删除路径线上的点
			mSvgList.removeAt(pointIndex);
		}
		else {
			scene->removeItem(sItem);
		}
		delete sItem;
		sItem = nullptr;
	}
	else{
		//删除svg图标
		for (int i = 0; i < mSvgList.size(); ++i){
			scene = mSvgList.at(i)->scene();
			scene->removeItem(mSvgList.at(i));
		}
		mSvgList.clear();
		//删除线
		delete mRubberBand;
		mRubberBand = NULL;
	}
#endif

}
//选中
QgsAnnotationItem* SvgMarkerTool::selectedItem()
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

QgsAnnotationItem* SvgMarkerTool::itemAtPos(QPointF pos)
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


