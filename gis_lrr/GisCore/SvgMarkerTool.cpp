#include "SvgMarkerTool.h"

SvgMarkerTool::SvgMarkerTool(QgsMapCanvas* mapCanvas)
: QgsMapTool(mapCanvas)
{
	mToolName = tr("SvgMarkerTool");
	moveFlag = false;//�ƶ����־
	itemSelectFlag = false;
	pointIndex = 0;//��Ҫ�ƶ��ĵ������

}

SvgMarkerTool::~SvgMarkerTool()
{
	//���е�����
	mPointList.clear();
	//���еı��������
	mSvgList.clear();
}


//############### �¼����� ########################################

// 1 ��д����ͷ��¼� 
void SvgMarkerTool::canvasReleaseEvent(QgsMapMouseEvent* e)
{

	if (e->button() == Qt::LeftButton  && itemSelectFlag == false) /* ������*/
	{
		QgsAnnotationItem* sItem = selectedItem();
		if (sItem == nullptr){		
			//QgsPoint mapPoint = mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos());			
			//createItem(mapPoint, MarkerSvgPath);
		}
	}
	if (e->button() == Qt::RightButton) /* ����Ҽ�*/ {

	}
	moveFlag = false;
	itemSelectFlag = false;
}

//��д���˫���¼�
void SvgMarkerTool::canvasDoubleClickEvent(QgsMapMouseEvent* e) {
	//ɾ����
	//if (e->button() == Qt::LeftButton && mCptFlag == CaptureLine) /* ���˫�����*/ {
	if (e->button() == Qt::RightButton) /* ���˫�����*/ {
		deleteItemAll();
	}


}

// ��д��갴���¼�
void SvgMarkerTool::canvasPressEvent(QgsMapMouseEvent* e) {

	if (e->button() == Qt::RightButton) /* ����Ҽ�*/
	{
		moveFlag = true;//�ƶ����־
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
		//��ȡ������
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

// ��д����ƶ��¼�
void SvgMarkerTool::canvasMoveEvent(QgsMapMouseEvent* e)
{
	QgsAnnotationItem* sItem = selectedItem();
	if (sItem && (e->buttons() & Qt::LeftButton))
	{

		//�ж��Ƿ��ƶ�����
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

//############ item ���� ######################
//����item
QgsSvgAnnotationItem* SvgMarkerTool::createItem(QgsPoint pos, QString svgPath)
{

	QgsSvgMarkerSymbolLayerV2 *svgMarker = new QgsSvgMarkerSymbolLayerV2(svgPath);
	svgMarker->setVerticalAnchorPoint(QgsMarkerSymbolLayerV2::Bottom);//��ͼ��������óɵ׶�
	svgMarker->setSize(8);//����ͼ���С

	QgsSymbolLayerV2List symList;//������������
	symList.append(svgMarker);//��ͼ����뵽����������
	QgsMarkerSymbolV2* markSym = new QgsMarkerSymbolV2(symList);

	QgsSvgAnnotationItem *psvg = new QgsSvgAnnotationItem(mCanvas);
	psvg->setMarkerSymbol(markSym);//������ʾ��ʽ
	psvg->setMapPosition(pos);
	psvg->setFrameSize(QSizeF(0, 0));//������ʾ���С 00ȥ��ʾ��
	//psvg->setFrameBorderWidth(10); ��֪����ɶ
	//psvg->setOffsetFromReferencePoint(QPointF(0, 0)); //�����ƶ���Ⱦ��ʾ���ƫ��λ��
	//QgsRectangle r(0,0,20,20);
	//psvg->setRect(r, true);
	//���й���
	mSvgList.append(psvg);


	return psvg;
}
void SvgMarkerTool::updateItemPositon(QgsAnnotationItem* sItem, QgsPoint pos)//����itemλ��
{
	if (sItem)
	{
		sItem->setMapPosition(pos);
		// sItem->markerSymbol()->setAngle((angle += 6) % 360));// ������ת ����Ŀǰ�޷���ת
		sItem->update();
	}
}
//ɾ��item
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
//ɾ��item
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
			mRubberBand->removePoint(pointIndex);       ///////ɾ��·�����ϵĵ�
			mSvgList.removeAt(pointIndex);
		}
		else {
			scene->removeItem(sItem);
		}
		delete sItem;
		sItem = nullptr;
	}
	else{
		//ɾ��svgͼ��
		for (int i = 0; i < mSvgList.size(); ++i){
			scene = mSvgList.at(i)->scene();
			scene->removeItem(mSvgList.at(i));
		}
		mSvgList.clear();
		//ɾ����
		delete mRubberBand;
		mRubberBand = NULL;
	}
#endif

}
//ѡ��
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


