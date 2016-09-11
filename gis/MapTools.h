#ifndef __MAPTOOLS_H__
#define __MAPTOOLS_H__

#include <QObject>
#include <QMouseEvent>
#include <QList>
#include <qgsmaptool.h>
#include <qgsmapcanvas.h>
#include "qgsmapmouseevent.h"
#include <qgsvectorlayer.h>
#include "qgsfeature.h"
#include <qgsgeometryvalidator.h>
#include <qgsvertexmarker.h>
#include "qgsrubberband.h"
#include "qgis.h"
#include <QStringList>
#include <qgsvectorlayer.h>
#include <qgslogger.h>
#include <qgsvectordataprovider.h>
#include "qgscsexception.h"
#include "qgsproject.h"
#include "qgsmaplayerregistry.h"
#include "qgsmaptopixel.h"
#include "qgsgeometry.h"
#include "qgsfeature.h"
#include <qgsmaptool.h>
#include <qgsmapcanvas.h>
#include "qgsmapmouseevent.h"
#include <qgsvectorlayer.h>
#include "qgsfeature.h"
#include <qgsgeometryvalidator.h>
#include <qgsvertexmarker.h>
#include "qgsrubberband.h"
#include "qgis.h"

#include <qgssymbollayerv2.h>
#include <qgssymbolv2.h>
#include <qgsmarkersymbollayerv2.h>
#include <qgsvectorlayerrenderer.h>
#include <qgsrendercontext.h>
#include <qgssinglesymbolrendererv2.h>
#include <qgssymbollayerv2.h>
#include "qgssvgannotationitem.h"
#include <QStringList>
#include <qgsvectorlayer.h>
#include <qgslogger.h>
#include <qgsvectordataprovider.h>
#include "qgscsexception.h"
#include "qgsproject.h"
#include "qgsmaplayerregistry.h"
#include "qgsmaptopixel.h"
#include "qgsgeometry.h"
#include "qgsfeature.h"
#include "qgsdistancearea.h"

//第二部分
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


// 

#include "qgsmaptool.h"

class MapTools : public QgsMapTool
{
	Q_OBJECT	
public:
	MapTools(QgsMapCanvas* mapCanvas);//通用构造
	~MapTools();
	//! 重写鼠标指针释放事件
	void canvasReleaseEvent(QgsMapMouseEvent* e) override;
	// 重写鼠标双击事件
	void canvasDoubleClickEvent(QgsMapMouseEvent* e) override;
	// 重写鼠标按下事件
	void canvasPressEvent(QgsMapMouseEvent* e) override;
	// 重写鼠标移动事件
	void canvasMoveEvent(QgsMapMouseEvent* e) override;
	
};

#endif //__MAPTOOLS_H__