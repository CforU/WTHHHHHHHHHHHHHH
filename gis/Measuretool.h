
#ifndef MEASURETOOL_H
#define MEASURETOOL_H
#include "GisWindow.h"
#include "qgsmaptool.h"

#include "MapTools.h"

class QgsDistanceArea;
class QgsMapCanvas;
class QgsRubberBand;



class  MeasureTool : public MapTools
{
    Q_OBJECT
  public:
	  MeasureTool(QgsMapCanvas* canvas, bool measureArea);
	  ~MeasureTool();
    // Inherited from QgsMapTool
    //! Mouse release event for overriding
    virtual void canvasReleaseEvent( QgsMapMouseEvent* e ) override;
signals:
	void length_sigle(double);
	void Area_signal(double);
  protected:
	
	QList<QgsPoint> m_captureList;

	QgsRubberBand *mRubberBandPoints;

	QgsRubberBand *mRubberBandLines;

	QgsRubberBand *mRubberBandPoly;

	QgsGeometry* g;

	QgsDistanceArea* DA;

    //! indicates whether we're measuring distances or areas
    bool mMeasureArea;

	int addLine(const QgsPoint& point);

	int addPoly(const QgsPoint& point);

	int nextPoint(const QgsPoint& mapPoint, QgsPoint& layerPoint);

	QgsRubberBand* createRubberBand(QGis::GeometryType geometryType = QGis::Line, bool alternativeBand = false);

};

#endif
