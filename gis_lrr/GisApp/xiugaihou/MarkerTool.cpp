#include "MarkerTool.h"

//Ĭ�ϱ��ͼ�� Ϊ�� 
int MarkerTool::MarkerType = 0; //Ĭ�ϱ������ ������
QString MarkerTool::MarkerIcon = "Resources/icon/gis/mkSvg/icon_bhtjd_2.svg";//�Ƿ���bug  �Ƿ���� ÿ�δ������߶���Ĭ�ϵĹ���
QString MarkerTool::defaultMarkerIcon = QString("Resources/icon/gis/mkSvg/icon_bhtjd_2.svg");


MarkerTool::MarkerTool(QgsMapCanvas* mapCanvas)
: QgsMapTool(mapCanvas)
{
	mToolName = tr("Marker");	
	mRubberBand = NULL;//������ ����
	moveFlag = false; //�ƶ����־

}

MarkerTool::~MarkerTool()
{
//	delete mRubberBand;
}


//############### �¼����� ########################################

// 1 ��д����ͷ��¼� 
void MarkerTool::canvasReleaseEvent(QgsMapMouseEvent* e)
{
	
	if (e->button() == Qt::LeftButton  && itemSelectFlag == false) /* ������*/
	{
		QgsAnnotationItem* sItem = selectedItem();
		if (sItem == nullptr){
			//markerPoint(e);
			QgsPoint mapPoint = mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos());
			//markerPoint(mapPoint, MarkerType);
			ManuallyMaker(mapPoint);
		}
	}
	if (e->button() == Qt::RightButton) /* ����Ҽ�*/ {
		
	}
	moveFlag = false;
	itemSelectFlag = false;
}

//��д���˫���¼�
void MarkerTool::canvasDoubleClickEvent(QgsMapMouseEvent* e) {
	//ɾ����
	//if (e->button() == Qt::LeftButton && mCptFlag == CaptureLine) /* ���˫�����*/ {
		if (e->button() == Qt::RightButton) /* ���˫�����*/ {		
			deleteItemAll();
	}
	
	
}

// ��д��갴���¼�
void MarkerTool::canvasPressEvent(QgsMapMouseEvent* e) {


	if (e->button() == Qt::RightButton ) /* ����Ҽ�*/
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

// ��д����ƶ��¼�
void MarkerTool::canvasMoveEvent(QgsMapMouseEvent* e)
{
	QgsAnnotationItem* sItem = selectedItem();
	if (sItem && (e->buttons() & Qt::LeftButton))
	{

		//�ж��Ƿ��ƶ�����
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

//####################�ڲ����� ָ��·������###################################
//����·�����
QgsRubberBand* MarkerTool::createRoute()
{
	
	QgsRubberBand* mRubberBandRoute = new QgsRubberBand(mCanvas, QGis::Line);
	mRubberBandRoute->setWidth(2);
	mRubberBandRoute->setColor(QColor(0, 255, 0));

	return mRubberBandRoute;
	
}
QgsRubberBand* MarkerTool::createRoutePoint(const QgsPoint& point)
{
	// 1 ������ͷ�λ�õĵ�ת���ɵ�ͼ�ϵ�λ��
	QgsVectorLayer *vlayer = qobject_cast<QgsVectorLayer *>(mCanvas->currentLayer());
	QgsPoint layerPoint = toLayerCoordinates(vlayer, point);
	//����һ��·�����
	QgsRubberBand* mRubberBandRoute = createRoute();
	// 3 ��ͼ���ϱ�ǵ�
	mRubberBandRoute->addPoint(point);
	return mRubberBandRoute;
}
//���·����
int MarkerTool::addRoutePoint(QgsRubberBand* mRubberBand ,const QgsPoint& point){
	// 1 ������ͷ�λ�õĵ�ת���ɵ�ͼ�ϵ�λ��
	QgsVectorLayer *vlayer = qobject_cast<QgsVectorLayer *>(mCanvas->currentLayer());
	QgsPoint layerPoint = toLayerCoordinates(vlayer, point);
	// 2 ����ͼ��
	if (!mRubberBand) // û��rubber band���ʹ���һ��
	{
		return -1;
		//mRubberBand = createRoute();
	}
		
	// 3 ��ͼ���ϱ�ǵ�
	mRubberBand->addPoint(point);
	m_captureList.append(layerPoint);
	return 0;
}
//���·����
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
			deleteItem(PathList.at(i)); //ɾ������
		}
		PathList.clear();
	}
}



//############ item ���� ######################
//����item
QgsSvgAnnotationItem* MarkerTool::createItem(QgsPoint pos, QString svgPath)
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
					

	return psvg;
}
void MarkerTool::updateItemPositon(QgsAnnotationItem* sItem, QgsPoint pos)//����itemλ��
{
	if (sItem)
	{
		sItem->setMapPosition(pos);
		// sItem->markerSymbol()->setAngle((angle += 6) % 360));// ������ת ����Ŀǰ�޷���ת
		sItem->update();
	}
}
//ɾ��item
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
//ɾ��item
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
			mRubberBand->removePoint(pointIndex);       ///////ɾ��·�����ϵĵ�
			PathMarkerList.removeAt(pointIndex);
		}
		else {
			scene->removeItem(sItem);
		}
		delete sItem;
		sItem = nullptr;
	}
	else{
		//ɾ��svgͼ��
		for (int i = 0; i < PathMarkerList.size(); ++i){
			scene = PathMarkerList.at(i)->scene();
			scene->removeItem(PathMarkerList.at(i));
		}
		PathMarkerList.clear();
		//ɾ����
		delete mRubberBand;
		mRubberBand = NULL;
	}
}
//ѡ��
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
//############�ֶ����###############//
int MarkerTool::addRoutePoint(const QgsPoint& point)
{
	// 1 ������ͷ�λ�õĵ�ת���ɵ�ͼ�ϵ�λ��
	QgsVectorLayer *vlayer = qobject_cast<QgsVectorLayer *>(mCanvas->currentLayer());
	QgsPoint layerPoint = toLayerCoordinates(vlayer, point);
	// 2 ����ͼ��
	if (!mRubberBand) // û��rubber band���ʹ���һ��
	{
		mRubberBand = createRoute();
	}

	// 3 ��ͼ���ϱ�ǵ�
	mRubberBand->addPoint(point);

	return 0;
}
void MarkerTool::markerLine(QgsMapMouseEvent* e)
{
	// ��ȡ��ǰͼ��
	QgsVectorLayer* layer = qobject_cast<QgsVectorLayer*>(mCanvas->currentLayer());
	// �õ������꣬ת��Ϊ��ͼ����
	QgsPoint savePoint = toLayerCoordinates(layer, mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()));
	//��Ӷ���
	addRoutePoint(mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()));
}
void MarkerTool::deleteRoute()
{
	delete mRubberBand;
	mRubberBand = NULL;
	for (int i = 0; i< PathMarkerList.size(); ++i) {
		deleteItem(PathMarkerList.at(i)); //ɾ������
	}
	PathMarkerList.clear();


}
//����
void MarkerTool::markerPoint(QgsPoint pos, int type)
{
	//contains(key) ������ �鿴�Ƿ���� 
	//QString path = MapManager::instance()->MarkerIconSvg[type];
	createItem(pos, MarkerIcon);
}
//����
void MarkerTool::markerPoint(QgsMapMouseEvent* e)
{

	QgsSvgMarkerSymbolLayerV2 *svgMarker = new QgsSvgMarkerSymbolLayerV2(MarkerIcon.isNull() ? MarkerIcon : MarkerIcon);
	svgMarker->setVerticalAnchorPoint(QgsMarkerSymbolLayerV2::Bottom);//��ͼ��������óɵ׶�
	qDebug() << MarkerIcon << "  : " << MarkerIcon;
	qDebug() << "Marker symbol";
	QgsSymbolLayerV2List symList;//������������
	symList.append(svgMarker);//��ͼ����뵽����������
	QgsMarkerSymbolV2* markSym = new QgsMarkerSymbolV2(symList);
	svgMarker->setSize(8);//����ͼ���С
	QgsSvgAnnotationItem *psvg = new QgsSvgAnnotationItem(mCanvas);
	psvg->setMarkerSymbol(markSym);//������ʾ��ʽ
	psvg->setMapPosition(mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()));
	PathMarkerList.append(psvg);

	addRoutePoint(mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()));

}
//�ֶ����
void MarkerTool::ManuallyMaker(QgsPoint pos)
{
	//·�� ��������֮�以�� �յ����յ㻥�� ֻ�ܴ���һ��

	if (MarkerType == 1 || MarkerType == 2 || MarkerType == 3){ //·�����
		MarkerRoutePointType ctype = (MarkerRoutePointType)MarkerType;
		markerRoutePoint(pos, ctype);
	}
	else  //�������
	{
		MarKerVehicleType ctype = (MarKerVehicleType)MarkerType;
		VehicleMarker(pos, ctype);
	}
}

//�����ͼ�ϵı������
void MarkerTool::clearUpMarker()
{
	//���� �������� CarMarkerMap ���� ѭ��ɾ��item ��������������� �ͷ�ָ��	
	QMap<int, QgsAnnotationItem*>::const_iterator i;
	for (i = CarMarkerMap.constBegin(); i != CarMarkerMap.constEnd(); ++i) {
		//qDebug() << i.key() << ":" << i.value();
		deleteItem(i.value()); //ɾ������
	}
	CarMarkerMap.clear();
	//����·������
}



