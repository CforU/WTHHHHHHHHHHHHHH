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
	// 测距
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
	// 获取当前图层
	QgsVectorLayer* layer = qobject_cast<QgsVectorLayer*>(mCanvas->currentLayer());

	// 得到点坐标，转换为地图坐标
	QgsPoint savePoint = toLayerCoordinates(layer, mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()));

	if (e->button() == Qt::LeftButton) /* 鼠标左键*/{
		//高亮拐点处
		if (!mRubberBandPoints){
			mRubberBandPoints = createRubberBand(QGis::Point);
		}
		mRubberBandPoints->setColor(QColor(255, 0, 0));
		mRubberBandPoints->setWidth(2);
		mRubberBandPoints->setIcon(QgsRubberBand::ICON_CIRCLE);
		mRubberBandPoints->setIconSize(10);
		mRubberBandPoints->addPoint(savePoint, true);

		if (!mMeasureArea){//测距离
			//添加线
			addLine(mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()));
			double total = DA->measureLine(m_captureList);
			//qDebug() << "Measure Lines : " << total << " (m) ";
			emit length_sigle(total);
			
		}
		else{//测面积
			//添加几何图形
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
	// 1 将鼠标释放位置的点转换成地图位置上的点
	nextPoint(point, layerPoint);//
	// 2 创建图层
	if (!mRubberBandLines) // 没有rubber band，就创建一个
	{
		mRubberBandLines = createRubberBand(QGis::Line);
	}
	// 3 在图层上标记点
	mRubberBandLines->addPoint(point);
	// 4 追加点
	m_captureList.append(layerPoint);

	return 0;
}

int MeasureTool::addPoly(const QgsPoint& point){
	QgsPoint layerPoint;
	// 1 将鼠标释放位置的点转换成地图位置上的点
	nextPoint(point, layerPoint);//
	// 2 创建图层
	if (!mRubberBandPoly) // 没有rubber band，就创建一个
	{
		mRubberBandPoly = createRubberBand(QGis::Polygon);
	}
	// 3 在图层上标记点
	mRubberBandPoly->addPoint(point);
	// 4 追加点
	m_captureList.append(layerPoint);

	return 0;
}

//转换点为地图位置上的点
int MeasureTool::nextPoint(const QgsPoint& mapPoint, QgsPoint& layerPoint)
{
	QgsVectorLayer *vlayer = qobject_cast<QgsVectorLayer *>(mCanvas->currentLayer());

	layerPoint = toLayerCoordinates(vlayer, mapPoint); //transform snapped point back to layer crs

	return 0;
}
//创建RubberBand图层
QgsRubberBand* MeasureTool::createRubberBand(QGis::GeometryType geometryType /*= QGis::Point*/, bool alternativeBand /*= false*/)
{
	QgsRubberBand* rb = new QgsRubberBand(mCanvas, geometryType);
	rb->setWidth(2);
	rb->setColor(QColor(0, 255, 0 , 125));
	rb->show();
	return rb;
}
