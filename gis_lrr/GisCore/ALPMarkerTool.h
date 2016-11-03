#ifndef __ALPMARKERTOOL_H__
#define __ALPMARKERTOOL_H__

//点线面标绘工具  Area Line Point
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

//SVG 标绘工具
class  ALPMarkerTool:public QgsMapTool
{
	Q_OBJECT
public:
	ALPMarkerTool(QgsMapCanvas* mapCanvas);
	~ALPMarkerTool();

	//! 重写鼠标指针释放事件
	void canvasReleaseEvent(QgsMapMouseEvent* e) override;
	// 重写鼠标双击事件
	void canvasDoubleClickEvent(QgsMapMouseEvent* e) override;
	// 重写鼠标按下事件
	void canvasPressEvent(QgsMapMouseEvent* e) override;
	// 重写鼠标移动事件
	void canvasMoveEvent(QgsMapMouseEvent* e) override;

public:
	//创建画布
	QgsRubberBand*  createRubberBand(QgsMapCanvas* mapCanvas, QGis::GeometryType geometryType = QGis::Line);
	//画布添加点  插入 追加 
	int rubberBandInsertPoint(QgsRubberBand* mRubberBand, int index, const QgsPoint& point,bool hlp = true);
	int rubberBandAppendPoint(QgsRubberBand* mRubberBand, const QgsPoint& point, bool hlp = true);
	void rubberBandMarkerLine(QgsRubberBand* mRubberBand, QList<QgsPoint>  &LinePosList);
	//画布删除点 中间删除 末尾删除
	int rubberBandRemovePoint(QgsRubberBand* mRubberBand, int index/*, const QgsPoint& point*/);
	int rubberBandRemoveLastPoint(QgsRubberBand* mRubberBand/*, const QgsPoint& point*/);
	//画布移动点
	int rubberBandMovePoint(QgsRubberBand* mRubberBand, int index, const QgsPoint& point);
	//删除画布
	void deleteRubberBand(QgsRubberBand* mRubberBand);
	//清空画布操作
	void clearRubberBand(QgsRubberBand* mRubberBand);
	//获取图层上的点
	QList<QgsPoint*> getPoints(QgsRubberBand* mRubberBand);
	//高亮拐点
	void HighLightPoint(const QgsPoint& point);
private:
	QgsRubberBand *hlpRubberBand;
	bool hlp; // 高亮拐点(hightLightPoint )
	
};

#endif //__ALPMARKERTOOL_H__