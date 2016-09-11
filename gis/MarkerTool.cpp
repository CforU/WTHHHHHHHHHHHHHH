#include "MarkerTool.h"
#define		POINT_INDEX		1	//��������

//Ĭ�ϱ��ͼ�� Ϊ�� 
QString MarkerTool::MarkerIcon = "Resources/icon/gis/mkSvg/icon_bhtjd_2.svg";//�Ƿ���bug  �Ƿ���� ÿ�δ������߶���Ĭ�ϵĹ���
QString MarkerTool::defaultMarkerIcon = QString("Resources/icon/gis/mkSvg/icon_bhtjd_2.svg");


//MarkerTool::MarkerTool(QgsMapCanvas* mapCanvas, CaptureMode flags)
MarkerTool::MarkerTool(QgsMapCanvas* mapCanvas, CaptureMode cptflag)
: MapTools(mapCanvas), mCptFlag(cptflag)
{
	mToolName = tr("Marker");
	pRubber = NULL;//���Ƶ� ����
	pRubber2 = NULL;//���ƹյ� ����
	mRubberBand = NULL;//������ ����
	moveFlag = false; //�ƶ����־

	testTimer = new QTimer(this);
	create_point();
	num = 0;
	connect(testTimer, SIGNAL(timeout()), this, SLOT(movePath()));
	//��ת�Ƕ�
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


// 1 ��д����ͷ��¼� 
void MarkerTool::canvasReleaseEvent(QgsMapMouseEvent* e)
{
	moveFlag = false;

	if (e->button() == Qt::LeftButton) /* ������*/
	{
		if (mCptFlag == CapturePoint){
			
		}
		if (mCptFlag == CaptureLine ){
			markerLine(e);
		}

	}
	if (e->button() == Qt::RightButton) /* ����Ҽ�*/ {
		markerPoint(e);
	}


}

//��д���˫���¼�
void MarkerTool::canvasDoubleClickEvent(QgsMapMouseEvent* e) {
	//ɾ����
	if (e->button() == Qt::LeftButton && mCptFlag == CaptureLine) /* ���˫�����*/ {
		//ɾ����
		delete pRubber;
		pRubber = NULL;
		//ɾ����
		delete pRubber2;
		pRubber2 = NULL;
		//ɾ����
		delete mRubberBand;
		mRubberBand = NULL;
		return;
	}
	//ɾ��ѡ�еı��ͼ��
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
			//��ʼ���ж�ʱ������ʱʱ����Ϊ1000ms
			testTimer->start(1000);
			tFlag = true;
			//num = 0;
		}
		else{
			//ֹͣ���ж�ʱ��
			if (testTimer->isActive())
				testTimer->stop();
			tFlag = false;
		}
	}
	
}

// ��д��갴���¼�
void MarkerTool::canvasPressEvent(QgsMapMouseEvent* e) {


	if (e->button() == Qt::RightButton /*&& mCptFlag == CaptureLine*/) /* ����Ҽ�*/
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
void MarkerTool::canvasMoveEvent(QgsMapMouseEvent* e) {

	if (mRubberBand && pRubber2 && moveFlag) {
		//�ƶ���
		mRubberBand->movePoint(POINT_INDEX, mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()), 0);
		pRubber2->movePoint(POINT_INDEX, mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()), 0);
		return;
	}


	QgsAnnotationItem* sItem = selectedItem();
	if (sItem && (e->buttons() & Qt::LeftButton))
	{
		//�ж��Ƿ��ƶ�����
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
	// 1 ������ͷ�λ�õĵ�ת���ɵ�ͼ�ϵ�λ��
	nextPoint(point, layerPoint);//
	// 2 ����ͼ��
	if (!mRubberBand) // û��rubber band���ʹ���һ��
	{
		mRubberBand = createRubberBand(  QGis::Line);
	}
	// 3 ��ͼ���ϱ�ǵ�
	mRubberBand->addPoint(point);
	// 4 ׷�ӵ�
	m_captureList.append(layerPoint);
	// 5 ������ʱͼ��
	//if (!mTempRubberBand)
	//{
	//	mTempRubberBand = createRubberBand(QGis::Line, true);
	//}
	//// 6 ����ʱͼ���ϱ�ǵ�
	//mTempRubberBand->addPoint(point);
	return 0;
}


void MarkerTool::markerPoint(QgsMapMouseEvent* e)
{
	
	//����
	//if (!pRubber) {
	//	pRubber = createRubberBand(QGis::Point);
	//}
	//pRubber->setColor(QColor(0, 0, 255));
	//pRubber->setWidth(2);
	//pRubber->setIcon(QgsRubberBand::ICON_CROSS);
	//pRubber->setIconSize(10);
	//pRubber->addPoint(savePoint, true);
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

	addVertex(mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()));

	//���Ե�ͼ������ϵ
	// ��ȡ��ǰͼ��
	//QgsVectorLayer* layer = qobject_cast<QgsVectorLayer*>(mCanvas->currentLayer());
	//// �õ������꣬ת��Ϊ��ͼ����
	//QgsPoint savePoint = toLayerCoordinates(layer, mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()));
	//QgsPoint layerPoint;
	//// 1 ������ͷ�λ�õĵ�ת���ɵ�ͼ�ϵ�λ��
	//QgsPoint point = mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos());
	//nextPoint(point, layerPoint);//
	//qDebug() << " e->pos(): " << e->pos() << "---" << "Position:" << point.toQPointF();
	//qDebug() << " savePoint: " << savePoint.toString();

}

void MarkerTool::markerLine(QgsMapMouseEvent* e)
{
	// ��ȡ��ǰͼ��
	QgsVectorLayer* layer = qobject_cast<QgsVectorLayer*>(mCanvas->currentLayer());
	// �õ������꣬ת��Ϊ��ͼ����
	QgsPoint savePoint = toLayerCoordinates(layer, mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()));
	//�����յ㴦
	if (!pRubber2){
		pRubber2 = createRubberBand(QGis::Point);
	}
	pRubber2->setColor(QColor(255, 0, 0));
	pRubber2->setWidth(2);
	pRubber2->setIcon(QgsRubberBand::ICON_CIRCLE);
	pRubber2->setIconSize(5);
	pRubber2->addPoint(savePoint, true);
	//��Ӷ���
	addVertex(mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()));

}


// ��д��갴ѹ�¼� �ƶ����ʱ��
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

// ��д����ƶ��¼� �ƶ����ʱ��
void MarkerTool::canvasMoveEvent_MovePoint(QgsMapMouseEvent* e)
{


	QgsAnnotationItem* sItem = selectedItem();
	if (sItem && (e->buttons() & Qt::LeftButton))
	{
		//�ж��Ƿ��ƶ�����
		if (mCurrentMoveAction == QgsAnnotationItem::MoveMapPosition)
		{
			sItem->setMapPosition(toMapCoordinates(e->pos()));
			mMovePoint = sItem->mapPosition();
			sItem->update();
			QgsProject::instance()->setDirty(true);
		}


		/**************************************************************************************************************/
		////�ж��Ƿ��ƶ��߿�
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

//��һ����
int MarkerTool::nextPoint(const QgsPoint& mapPoint, QgsPoint& layerPoint)
{
	QgsVectorLayer *vlayer = qobject_cast<QgsVectorLayer *>(mCanvas->currentLayer());

	layerPoint = toLayerCoordinates(vlayer, mapPoint); //transform snapped point back to layer crs

	return 0;
}
//����RubberBandͼ��
QgsRubberBand* MarkerTool::createRubberBand(QGis::GeometryType geometryType /*= QGis::Point*/, bool alternativeBand /*= false*/)
{
	
	QgsRubberBand* rb = new QgsRubberBand(mCanvas);
	rb->setWidth(2);
	rb->setColor(QColor(0,255,0));
//	rb->show();
	return rb;
}

//���õ�ǰ���ͼ��
void MarkerTool::setMarkerIconPath(QString path)
{
	MarkerIcon = path;// Path

}
//����Ĭ�ϵı��ͼ��
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
			// sItem->markerSymbol()->setAngle((angle += 6) % 360));// ������ת ����Ŀǰ�޷���ת
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

//����
void  MarkerTool::markerPoint(QgsPoint point)
{

}
//���·��
void  MarkerTool::markerPath(QList<QgsPoint> path)
{


}

