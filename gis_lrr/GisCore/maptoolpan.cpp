
#include "maptoolpan.h"

#include "qgsmapcanvas.h"
#include "qgscursors.h"
#include "qgsmaptopixel.h"
#include <QBitmap>
#include <QCursor>
#include <QMouseEvent>


MapToolPan::MapToolPan(QgsMapCanvas* canvas)
    : QgsMapTool( canvas )
    , mDragging( false )
{
  mToolName = tr( "Pan" );
  // set cursor
  mCursor = QCursor( Qt::OpenHandCursor );
}

void MapToolPan::canvasPressEvent(QgsMapMouseEvent* e)
{
  if ( e->button() == Qt::LeftButton )
    mCanvas->setCursor( QCursor( Qt::ClosedHandCursor ) );
}


void MapToolPan::canvasMoveEvent(QgsMapMouseEvent* e)
{
  if (( e->buttons() & Qt::LeftButton ) )
  {
    mDragging = true;
    // move map and other canvas items
    mCanvas->panAction( e );
  }
}

void MapToolPan::canvasReleaseEvent(QgsMapMouseEvent* e)
{
  if ( e->button() == Qt::LeftButton )
  {
    if ( mDragging )
    {
      mCanvas->panActionEnd( e->pos() );
      mDragging = false;
    }
    else // add pan to mouse cursor
    {
      // transform the mouse pos to map coordinates
      QgsPoint center = mCanvas->getCoordinateTransform()->toMapPoint( e->x(), e->y() );
     // mCanvas->setCenter( center );
      mCanvas->refresh();
    }
  }
  mCanvas->setCursor( mCursor );
}
