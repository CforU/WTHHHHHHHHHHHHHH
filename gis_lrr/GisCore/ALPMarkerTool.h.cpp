#include "ALPMarkerTool.h"

ALPMarkerTool::ALPMarkerTool(QgsMapCanvas* mapCanvas)
: QgsMapTool(mapCanvas)
{

}

ALPMarkerTool::~ALPMarkerTool()
{
	//	delete mRubberBand;
}


//############### �¼����� ########################################

// 1 ��д����ͷ��¼� 
void ALPMarkerTool::canvasReleaseEvent(QgsMapMouseEvent* e)
{


}

//��д���˫���¼�
void ALPMarkerTool::canvasDoubleClickEvent(QgsMapMouseEvent* e) {
	

}

// ��д��갴���¼�
void ALPMarkerTool::canvasPressEvent(QgsMapMouseEvent* e) {


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

int ALPMarkerTool::rubberBandInsertPoint(QgsRubberBand* mRubberBand, int index, const QgsPoint& point)
{
	return 0;
}
int ALPMarkerTool::rubberBandAppendPoint(QgsRubberBand* mRubberBand, const QgsPoint& point)
{
	//�Ƿ���Ҫ��������ת��
	mRubberBand->addPoint(point);
	//�Ƿ���Ҫ����
	return 0;
}

void ALPMarkerTool::rubberBandMarkerLine(QgsRubberBand* mRubberBand, QList<QgsPoint>  LinePosList)
{ 
	if (LinePosList.isEmpty()){
		return;
	}
	//�����յ㴦 //��Ҫ���й���
	QgsRubberBand *tmpRubberBand = new QgsRubberBand(mCanvas, QGis::Point);
	tmpRubberBand->setColor(QColor(255, 0, 0));
	tmpRubberBand->setWidth(2);
	tmpRubberBand->setIcon(QgsRubberBand::ICON_CIRCLE);
	tmpRubberBand->setIconSize(10);

	for (int i = 0; i < LinePosList.size(); ++i){
		//�����յ㴦
		tmpRubberBand->addPoint(LinePosList.at(i),true);
		rubberBandAppendPoint(mRubberBand, LinePosList.at(i));
	}

}
//����ɾ���� �м�ɾ�� ĩβɾ��
int ALPMarkerTool::rubberBandRemovePoint(QgsRubberBand* mRubberBand, int index, const QgsPoint& point)
{
	return 0;
}
int ALPMarkerTool::rubberBandDeletePoint(QgsRubberBand* mRubberBand, const QgsPoint& point)
{
	return 0;
}
//�����ƶ���
int ALPMarkerTool::rubberBandMovePoint(QgsRubberBand* mRubberBand, int index, const QgsPoint& point)
{
	return 0;
}
//ɾ������
void ALPMarkerTool::deleteRubberBand(QgsRubberBand* mRubberBand)
{
	
}
//��ջ�������
void ALPMarkerTool::clearRubberBand(QgsRubberBand* mRubberBand)
{

}
