
#ifndef MEASURETOOL_H
#define MEASURETOOL_H
//#include "../GisCore/GisWindow.h"
#include "qgsmaptool.h"
#include "qtooltip.h"

class QgsDistanceArea;
class QgsMapCanvas;
class QgsRubberBand;


class  MeasureTool : public QgsMapTool
{
    Q_OBJECT
  public:
	  MeasureTool(QgsMapCanvas* canvas, bool measureArea);
	  ~MeasureTool();
    virtual void canvasReleaseEvent( QgsMapMouseEvent* e ) override;
signals:
	//不用了 以后使用在地图上显示
	//void length_sigle(double);
	//void Area_signal(double);
protected:
	QList<QgsPoint> m_captureList;
	QgsRubberBand *mRubberBandPoints;
	QgsRubberBand *mRubberBandPoly;
	QgsGeometry* g;
	QgsDistanceArea* DA;

    //! indicates whether we're measuring distances or areas
    bool mMeasureArea;
	int addPoly(const QgsPoint& point, QGis::GeometryType geometryType);

public:
	//清除地图上测量标识信息
	void clearUpMeasure();
};

#endif
