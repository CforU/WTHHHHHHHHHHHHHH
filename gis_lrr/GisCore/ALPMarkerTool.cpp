#include "ALPMarkerTool.h"

ALPMarkerTool::ALPMarkerTool(QgsMapCanvas* mapCanvas)
: QgsMapTool(mapCanvas)
{
}

ALPMarkerTool::~ALPMarkerTool()
{
}

//############### 事件处理 ########################################

// 1 重写鼠标释放事件 
void ALPMarkerTool::canvasReleaseEvent(QgsMapMouseEvent* e)
{
}

//重写鼠标双击事件
void ALPMarkerTool::canvasDoubleClickEvent(QgsMapMouseEvent* e) 
{
}

// 重写鼠标按下事件
void ALPMarkerTool::canvasPressEvent(QgsMapMouseEvent* e) 
{
}

// 重写鼠标移动事件
void ALPMarkerTool::canvasMoveEvent(QgsMapMouseEvent* e)
{
}
//############### 临时画布操作 ########################################

//创建画布
QgsRubberBand*  ALPMarkerTool::createRubberBand(QgsMapCanvas* mapCanvas, QGis::GeometryType geometryType )
{
	QgsRubberBand*  mRubberBand = new QgsRubberBand(mCanvas, geometryType);
	if (mRubberBand){
		mRubberBand->setWidth(2);
		mRubberBand->setColor(QColor(0, 255, 0, 125));
		return mRubberBand;
	}
	return (QgsRubberBand*)NULL;
}

int ALPMarkerTool::rubberBandInsertPoint(QgsRubberBand* mRubberBand, int index, const QgsPoint& point, bool hlp )
{
	return 0;
}
int ALPMarkerTool::rubberBandAppendPoint(QgsRubberBand* mRubberBand, const QgsPoint& point, bool hlp )
{
	//是否需要进行坐标转换
	mRubberBand->addPoint(point);
	//高亮拐点处 
	if (hlp){
		HighLightPoint(point);
	}
	return 0;
}

void ALPMarkerTool::rubberBandMarkerLine(QgsRubberBand* mRubberBand, QList<QgsPoint>  &LinePosList)
{
	if (LinePosList.isEmpty()){
		return;
	}
	for (int i = 0; i < LinePosList.size(); ++i){
		rubberBandAppendPoint(mRubberBand, LinePosList.at(i));
	}
}
//画布删除点 中间删除 末尾删除
int ALPMarkerTool::rubberBandRemovePoint(QgsRubberBand* mRubberBand, int index/*, const QgsPoint& point*/)
{
	mRubberBand->removePoint(index);
	return 0;
}
int ALPMarkerTool::rubberBandRemoveLastPoint(QgsRubberBand* mRubberBand/*, const QgsPoint& point*/)
{
	mRubberBand->removeLastPoint();
	return 0;
}
//画布移动点
int ALPMarkerTool::rubberBandMovePoint(QgsRubberBand* mRubberBand, int index, const QgsPoint& point)
{
	mRubberBand->movePoint(index,point);
	return 0;
}
//删除画布
void ALPMarkerTool::deleteRubberBand(QgsRubberBand* mRubberBand)
{
	delete mRubberBand;
	mRubberBand = NULL;
	if (hlp){
		delete hlpRubberBand;
		hlpRubberBand = NULL;
	}
}
//清空画布操作
void ALPMarkerTool::clearRubberBand(QgsRubberBand* mRubberBand)
{
	mRubberBand->reset();
}
//获取图层的点        //有问题！？
QList<QgsPoint*> ALPMarkerTool::getPoints(QgsRubberBand* mRubberBand){	
	int i = 0;
	QList<QgsPoint*> tmpPointList;
	QgsPoint *tmpPoint = const_cast<QgsPoint*>( mRubberBand->getPoint(0, i) );
	while (tmpPoint){
		tmpPointList.append(tmpPoint);
	}
	return tmpPointList;
}

//高亮拐点
void ALPMarkerTool::HighLightPoint(const QgsPoint& point){
	if (!hlpRubberBand){
		hlpRubberBand = new QgsRubberBand(mCanvas, QGis::Point);
		hlpRubberBand->setColor(QColor(255, 0, 0));
		hlpRubberBand->setWidth(2);
		hlpRubberBand->setIcon(QgsRubberBand::ICON_CIRCLE);
		hlpRubberBand->setIconSize(10);
	}
	hlpRubberBand->addPoint(point);
}