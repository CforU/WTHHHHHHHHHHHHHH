#include "ALPMarkerTool.h"

ALPMarkerTool::ALPMarkerTool(QgsMapCanvas* mapCanvas)
: QgsMapTool(mapCanvas)
{

}

ALPMarkerTool::~ALPMarkerTool()
{
	//	delete mRubberBand;
}


//############### 事件处理 ########################################

// 1 重写鼠标释放事件 
void ALPMarkerTool::canvasReleaseEvent(QgsMapMouseEvent* e)
{


}

//重写鼠标双击事件
void ALPMarkerTool::canvasDoubleClickEvent(QgsMapMouseEvent* e) {
	

}

// 重写鼠标按下事件
void ALPMarkerTool::canvasPressEvent(QgsMapMouseEvent* e) {


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

int ALPMarkerTool::rubberBandInsertPoint(QgsRubberBand* mRubberBand, int index, const QgsPoint& point)
{
	return 0;
}
int ALPMarkerTool::rubberBandAppendPoint(QgsRubberBand* mRubberBand, const QgsPoint& point)
{
	//是否需要进行坐标转换
	mRubberBand->addPoint(point);
	//是否需要管理
	return 0;
}

void ALPMarkerTool::rubberBandMarkerLine(QgsRubberBand* mRubberBand, QList<QgsPoint>  LinePosList)
{ 
	if (LinePosList.isEmpty()){
		return;
	}
	//高亮拐点处 //需要进行管理
	QgsRubberBand *tmpRubberBand = new QgsRubberBand(mCanvas, QGis::Point);
	tmpRubberBand->setColor(QColor(255, 0, 0));
	tmpRubberBand->setWidth(2);
	tmpRubberBand->setIcon(QgsRubberBand::ICON_CIRCLE);
	tmpRubberBand->setIconSize(10);

	for (int i = 0; i < LinePosList.size(); ++i){
		//高亮拐点处
		tmpRubberBand->addPoint(LinePosList.at(i),true);
		rubberBandAppendPoint(mRubberBand, LinePosList.at(i));
	}

}
//画布删除点 中间删除 末尾删除
int ALPMarkerTool::rubberBandRemovePoint(QgsRubberBand* mRubberBand, int index, const QgsPoint& point)
{
	return 0;
}
int ALPMarkerTool::rubberBandDeletePoint(QgsRubberBand* mRubberBand, const QgsPoint& point)
{
	return 0;
}
//画布移动点
int ALPMarkerTool::rubberBandMovePoint(QgsRubberBand* mRubberBand, int index, const QgsPoint& point)
{
	return 0;
}
//删除画布
void ALPMarkerTool::deleteRubberBand(QgsRubberBand* mRubberBand)
{
	
}
//清空画布操作
void ALPMarkerTool::clearRubberBand(QgsRubberBand* mRubberBand)
{

}
