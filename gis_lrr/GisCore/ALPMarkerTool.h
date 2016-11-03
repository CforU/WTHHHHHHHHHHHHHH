#ifndef __ALPMARKERTOOL_H__
#define __ALPMARKERTOOL_H__

//�������湤��  Area Line Point
//Qt
#include <QGraphicsScene>

//QGis
#include <qgsmaptool.h>
#include <qgsmapcanvas.h>
#include "qgsmaptopixel.h"
#include <qgssymbollayerv2.h>
#include <qgssymbolv2.h>
#include <qgsmarkersymbollayerv2.h>
#include <qgsvectorlayerrenderer.h>
#include "qgssvgannotationitem.h"
#include "QgsRubberBand.h"
#include "qgsmapmouseevent.h"

#include "QgsProject.h"

//SVG ��湤��
class  ALPMarkerTool:public QgsMapTool
{
	Q_OBJECT
public:
	ALPMarkerTool(QgsMapCanvas* mapCanvas);
	~ALPMarkerTool();

	//! ��д���ָ���ͷ��¼�
	void canvasReleaseEvent(QgsMapMouseEvent* e) override;
	// ��д���˫���¼�
	void canvasDoubleClickEvent(QgsMapMouseEvent* e) override;
	// ��д��갴���¼�
	void canvasPressEvent(QgsMapMouseEvent* e) override;
	// ��д����ƶ��¼�
	void canvasMoveEvent(QgsMapMouseEvent* e) override;

public:
	//��������
	QgsRubberBand*  createRubberBand(QgsMapCanvas* mapCanvas, QGis::GeometryType geometryType = QGis::Line);
	//������ӵ�  ���� ׷�� 
	int rubberBandInsertPoint(QgsRubberBand* mRubberBand, int index, const QgsPoint& point,bool hlp = true);
	int rubberBandAppendPoint(QgsRubberBand* mRubberBand, const QgsPoint& point, bool hlp = true);
	void rubberBandMarkerLine(QgsRubberBand* mRubberBand, QList<QgsPoint>  &LinePosList);
	//����ɾ���� �м�ɾ�� ĩβɾ��
	int rubberBandRemovePoint(QgsRubberBand* mRubberBand, int index/*, const QgsPoint& point*/);
	int rubberBandRemoveLastPoint(QgsRubberBand* mRubberBand/*, const QgsPoint& point*/);
	//�����ƶ���
	int rubberBandMovePoint(QgsRubberBand* mRubberBand, int index, const QgsPoint& point);
	//ɾ������
	void deleteRubberBand(QgsRubberBand* mRubberBand);
	//��ջ�������
	void clearRubberBand(QgsRubberBand* mRubberBand);
	//��ȡͼ���ϵĵ�
	QList<QgsPoint*> getPoints(QgsRubberBand* mRubberBand);
	//�����յ�
	void HighLightPoint(const QgsPoint& point);
private:
	QgsRubberBand *hlpRubberBand;
	bool hlp; // �����յ�(hightLightPoint )
	
};

#endif //__ALPMARKERTOOL_H__