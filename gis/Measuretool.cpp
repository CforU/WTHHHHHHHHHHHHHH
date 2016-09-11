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
: MapTools(canvas), mMeasureArea(measureArea)
{
	mRubberBandPoints = 0;
	mRubberBandLines = 0;
	mRubberBandPoly = 0;
	/*QgsGeometry* */g = new QgsGeometry();
	// ���
	/*QgsDistanceArea* */ DA = new QgsDistanceArea();
}

MeasureTool::~MeasureTool()
{
	delete mRubberBandLines;
	delete mRubberBandPoints;
	delete mRubberBandPoly;
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
			mRubberBandPoints = createRubberBand(QGis::Point);
		}
		mRubberBandPoints->setColor(QColor(255, 0, 0));
		mRubberBandPoints->setWidth(2);
		mRubberBandPoints->setIcon(QgsRubberBand::ICON_CIRCLE);
		mRubberBandPoints->setIconSize(10);
		mRubberBandPoints->addPoint(savePoint, true);

		if (!mMeasureArea){//�����
			//�����
			addLine(mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()));
			double total = DA->measureLine(m_captureList);
			//qDebug() << "Measure Lines : " << total << " (m) ";
			emit length_sigle(total);
			
		}
		else{//�����
			//��Ӽ���ͼ��
			addPoly(mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()));
			g = QgsGeometry::fromPolygon(QgsPolygon() << m_captureList.toVector());
			double area = DA->measureArea(g);
			//qDebug() << "Measure Areas : " << area << " (m^2) ";
			emit Area_signal(area);
		}
	}
}

int MeasureTool::addLine(const QgsPoint& point){
	QgsPoint layerPoint;
	// 1 ������ͷ�λ�õĵ�ת���ɵ�ͼλ���ϵĵ�
	nextPoint(point, layerPoint);//
	// 2 ����ͼ��
	if (!mRubberBandLines) // û��rubber band���ʹ���һ��
	{
		mRubberBandLines = createRubberBand(QGis::Line);
	}
	// 3 ��ͼ���ϱ�ǵ�
	mRubberBandLines->addPoint(point);
	// 4 ׷�ӵ�
	m_captureList.append(layerPoint);

	return 0;
}

int MeasureTool::addPoly(const QgsPoint& point){
	QgsPoint layerPoint;
	// 1 ������ͷ�λ�õĵ�ת���ɵ�ͼλ���ϵĵ�
	nextPoint(point, layerPoint);//
	// 2 ����ͼ��
	if (!mRubberBandPoly) // û��rubber band���ʹ���һ��
	{
		mRubberBandPoly = createRubberBand(QGis::Polygon);
	}
	// 3 ��ͼ���ϱ�ǵ�
	mRubberBandPoly->addPoint(point);
	// 4 ׷�ӵ�
	m_captureList.append(layerPoint);

	return 0;
}

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
