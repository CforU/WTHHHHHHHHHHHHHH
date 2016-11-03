#include "MeasureTool.h"

#include "qgsdistancearea.h"
#include "qgsmapcanvas.h"
#include "qgsmaprenderer.h"
#include "qgsmaptopixel.h"
#include "qgsrubberband.h"
#include "qgsvectorlayer.h"
#include "qgssnappingutils.h"
#include "qgstolerance.h"

#include "qgscursors.h"
#include <QMouseEvent>
#include <QSettings>

MeasureTool::MeasureTool(QgsMapCanvas* canvas, bool measureArea)
: QgsMapTool(canvas), mMeasureArea(measureArea)
{
	mRubberBandPoints = 0;
	mRubberBandPoly = 0;
	//���  /*QgsGeometry* */
	g = new QgsGeometry();
	//�����  /*QgsDistanceArea* */ 
	DA = new QgsDistanceArea();
}

MeasureTool::~MeasureTool()
{
//	delete mRubberBandPoints;
//	delete mRubberBandPoly;
}



void MeasureTool::canvasReleaseEvent(QgsMapMouseEvent* e)
{
	// ��ȡ��ǰͼ��
	QgsVectorLayer* layer = qobject_cast<QgsVectorLayer*>(mCanvas->currentLayer());

	// �õ������꣬ת��Ϊ��ͼ����
	QgsPoint savePoint = toLayerCoordinates(layer, mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()));

	if (e->button() == Qt::LeftButton) /* ������*/{
		//�����յ㴦
		if (!mRubberBandPoints){
			mRubberBandPoints = new QgsRubberBand(mCanvas, QGis::Point);
			mRubberBandPoints->setWidth(2);
			mRubberBandPoints->setColor(QColor(0, 255, 0));
		}
		mRubberBandPoints->setColor(QColor(255, 0, 0));
		mRubberBandPoints->setWidth(2);
		mRubberBandPoints->setIcon(QgsRubberBand::ICON_CIRCLE);
		mRubberBandPoints->setIconSize(10);
		mRubberBandPoints->addPoint(savePoint, true);
		QPoint p;
		p.setX(e->pos().x() + 50 + 1440);
		p.setY(e->pos().y());
		QRect r = QRect();
		if (!mMeasureArea){//�����
			//�����
			addPoly(mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()), QGis::Line);
			double total = DA->measureLine(m_captureList);
			if (total){
				QToolTip::showText(p, QString::number(total) + "(m)"); //tips
			}
		}
		else{//�����
			//��Ӽ���ͼ��
			addPoly(mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()), QGis::Polygon);
			g = QgsGeometry::fromPolygon(QgsPolygon() << m_captureList.toVector());
			double area = DA->measureArea(g);
			if (area){
				QToolTip::showText(p, QString::number(area / 1000000, 'g', 2) + "(km^2)", 0, r, 99999); //tips
			}
		}
	}
}

int MeasureTool::addPoly(const QgsPoint& point, QGis::GeometryType geometryType)
{
	// 1 ������ͷ�λ�õĵ�ת���ɵ�ͼλ���ϵĵ�
	QgsVectorLayer *vlayer = qobject_cast<QgsVectorLayer *>(mCanvas->currentLayer());
	QgsPoint layerPoint = toLayerCoordinates(vlayer, point);

	QgsCoordinateReferenceSystem wgs84(4326, QgsCoordinateReferenceSystem::EpsgCrsId);
	QgsCoordinateReferenceSystem web(3857, QgsCoordinateReferenceSystem::EpsgCrsId);
	QgsCoordinateTransform trans(wgs84, web);
	QgsPoint ptWeb = trans.transform(layerPoint, QgsCoordinateTransform::ForwardTransform);

	// 2 ����ͼ��
	if (!mRubberBandPoly) // û��rubber band���ʹ���һ��
	{
		mRubberBandPoly = new QgsRubberBand(mCanvas, geometryType);
		mRubberBandPoly->setWidth(2);
		mRubberBandPoly->setColor(QColor(0, 255, 0, 125));
	}

	// 3 ��ͼ���ϱ�ǵ�
	mRubberBandPoly->addPoint(point);
	// 4 ׷�ӵ�
	m_captureList.append(ptWeb);


	return 0;
}

void MeasureTool::clearUpMeasure()
{	
	if (mRubberBandPoints){
		delete mRubberBandPoints;		
		mRubberBandPoints = NULL;
	}
	if (mRubberBandPoly){
		delete mRubberBandPoly;
		mRubberBandPoly = NULL;
	}
	m_captureList.clear();
	
}













#if 0
//ת����Ϊ��ͼλ���ϵĵ�
int MeasureTool::nextPoint(const QgsPoint& mapPoint, QgsPoint& layerPoint)
{
	QgsVectorLayer *vlayer = qobject_cast<QgsVectorLayer *>(mCanvas->currentLayer());

	layerPoint = toLayerCoordinates(vlayer, mapPoint); //transform snapped point back to layer crs

	return 0;
}
//����RubberBandͼ��
QgsRubberBand* MeasureTool::createRubberBand(QGis::GeometryType geometryType /*= QGis::Point*/, bool alternativeBand /*= false*/)
{
	QgsRubberBand* rb = new QgsRubberBand(mCanvas, geometryType);
	rb->setWidth(2);
	rb->setColor(QColor(0, 255, 0 , 125));
	rb->show();
	return rb;
}
#endif