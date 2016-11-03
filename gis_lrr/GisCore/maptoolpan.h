#ifndef MAPTOOLPAN_H
#define MAPTOOLPAN_H


#include "qgsmaptool.h"
class QgsMapCanvas;



class  MapToolPan : public QgsMapTool
{
    Q_OBJECT

  public:
    //! constructor
    MapToolPan( QgsMapCanvas* canvas );

    virtual Flags flags() const override { return QgsMapTool::Transient | QgsMapTool::AllowZoomRect; }

    //! Mouse press event
    virtual void canvasPressEvent( QgsMapMouseEvent* e ) override;

    //! Overridden mouse move event
    virtual void canvasMoveEvent( QgsMapMouseEvent* e ) override;

    //! Overridden mouse release event
    virtual void canvasReleaseEvent( QgsMapMouseEvent* e ) override;

  private:

    //! Flag to indicate a map canvas drag operation is taking place
    bool mDragging;

};

#endif  //MAPTOOLPAN_H
