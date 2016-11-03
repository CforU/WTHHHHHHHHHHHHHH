#include "ALPMarkerTool.h"

ALPMarkerTool::ALPMarkerTool(QgsMapCanvas* mapCanvas)
: QgsMapTool(mapCanvas)
{
}

ALPMarkerTool::~ALPMarkerTool()
{
}

//############### �¼����� ########################################

// 1 ��д����ͷ��¼� 
void ALPMarkerTool::canvasReleaseEvent(QgsMapMouseEvent* e)
{
}

//��д���˫���¼�
void ALPMarkerTool::canvasDoubleClickEvent(QgsMapMouseEvent* e) 
{
}

// ��д��갴���¼�
void ALPMarkerTool::canvasPressEvent(QgsMapMouseEvent* e) 
{
}

// ��д����ƶ��¼�
void ALPMarkerTool::canvasMoveEvent(QgsMapMouseEvent* e)
{
}
//############### ��ʱ�������� ########################################

//��������
QgsRubberBand*  ALPMarkerTool::createRubberBand(QgsMapCanvas* mapCanvas, QGis::GeometryType geometryType )
{
	QgsRubberBand*  mRubberBand = new QgsRubberBand(mCanvas, geometryType);
	if (mRubberBand){
		mRubberBand->setWidth(2);
		mRubberBand->setColor(QColor(0, 255, 0, 125));
		return mRubberBand;
	}
	return (QgsRubberBand*)NULL;
}

int ALPMarkerTool::rubberBandInsertPoint(QgsRubberBand* mRubberBand, int index, const QgsPoint& point, bool hlp )
{
	return 0;
}
int ALPMarkerTool::rubberBandAppendPoint(QgsRubberBand* mRubberBand, const QgsPoint& point, bool hlp )
{
	//�Ƿ���Ҫ��������ת��
	mRubberBand->addPoint(point);
	//�����յ㴦 
	if (hlp){
		HighLightPoint(point);
	}
	return 0;
}

void ALPMarkerTool::rubberBandMarkerLine(QgsRubberBand* mRubberBand, QList<QgsPoint>  &LinePosList)
{
	if (LinePosList.isEmpty()){
		return;
	}
	for (int i = 0; i < LinePosList.size(); ++i){
		rubberBandAppendPoint(mRubberBand, LinePosList.at(i));
	}
}
//����ɾ���� �м�ɾ�� ĩβɾ��
int ALPMarkerTool::rubberBandRemovePoint(QgsRubberBand* mRubberBand, int index/*, const QgsPoint& point*/)
{
	mRubberBand->removePoint(index);
	return 0;
}
int ALPMarkerTool::rubberBandRemoveLastPoint(QgsRubberBand* mRubberBand/*, const QgsPoint& point*/)
{
	mRubberBand->removeLastPoint();
	return 0;
}
//�����ƶ���
int ALPMarkerTool::rubberBandMovePoint(QgsRubberBand* mRubberBand, int index, const QgsPoint& point)
{
	mRubberBand->movePoint(index,point);
	return 0;
}
//ɾ������
void ALPMarkerTool::deleteRubberBand(QgsRubberBand* mRubberBand)
{
	delete mRubberBand;
	mRubberBand = NULL;
	if (hlp){
		delete hlpRubberBand;
		hlpRubberBand = NULL;
	}
}
//��ջ�������
void ALPMarkerTool::clearRubberBand(QgsRubberBand* mRubberBand)
{
	mRubberBand->reset();
}
//��ȡͼ��ĵ�        //�����⣡��
QList<QgsPoint*> ALPMarkerTool::getPoints(QgsRubberBand* mRubberBand){	
	int i = 0;
	QList<QgsPoint*> tmpPointList;
	QgsPoint *tmpPoint = const_cast<QgsPoint*>( mRubberBand->getPoint(0, i) );
	while (tmpPoint){
		tmpPointList.append(tmpPoint);
	}
	return tmpPointList;
}

//�����յ�
void ALPMarkerTool::HighLightPoint(const QgsPoint& point){
	if (!hlpRubberBand){
		hlpRubberBand = new QgsRubberBand(mCanvas, QGis::Point);
		hlpRubberBand->setColor(QColor(255, 0, 0));
		hlpRubberBand->setWidth(2);
		hlpRubberBand->setIcon(QgsRubberBand::ICON_CIRCLE);
		hlpRubberBand->setIconSize(10);
	}
	hlpRubberBand->addPoint(point);
}