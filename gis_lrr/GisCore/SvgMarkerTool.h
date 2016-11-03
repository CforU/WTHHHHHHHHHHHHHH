#ifndef __SVGMARKERTOOL_H__
#define __SVGMARKERTOOL_H__

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

#include "qgsmapmouseevent.h"

#include "QgsProject.h"

//SVG 标绘工具
class SvgMarkerTool : public QgsMapTool
{
	Q_OBJECT
public:
	SvgMarkerTool(QgsMapCanvas* mapCanvas);
	~SvgMarkerTool();

	//! 重写鼠标指针释放事件
	void canvasReleaseEvent(QgsMapMouseEvent* e) override;
	// 重写鼠标双击事件
	void canvasDoubleClickEvent(QgsMapMouseEvent* e) override;
	// 重写鼠标按下事件
	void canvasPressEvent(QgsMapMouseEvent* e) override;
	// 重写鼠标移动事件
	void canvasMoveEvent(QgsMapMouseEvent* e) override;


	//Svg item 相关  (自动标绘)
	//创建item
	QgsSvgAnnotationItem* createItem(QgsPoint pos, QString svgPath);
	//更新item位置
	void updateItemPositon(QgsAnnotationItem* sItem, QgsPoint pos);
	//删除item
	int deleteItem(QgsAnnotationItem* sItem);
	//删除所有item
	void deleteItemAll();
	//pos所在的item
	QgsAnnotationItem* itemAtPos(QPointF pos);
	//获取选中的item
	QgsAnnotationItem* selectedItem();


	public slots:

protected:
	//所有点链表
	QList<QgsPoint> mPointList;
	//所有的标绘句柄链表
	QList<QgsAnnotationItem*>  mSvgList;


	//以下变量是否需要
	bool moveFlag;//移动点标志
	bool itemSelectFlag;//item选中标志

	QgsAnnotationItem::MouseMoveAction mCurrentMoveAction;
	int pointIndex;//需要移动的点的索引
	QgsPoint mMovePoint;//移动点的位置
	QPointF mLastMousePosition;//上一个鼠标移动点

public:
	//以下是否需要
	QString MarkerSvgPath;// 标绘SVG图标路径
	QString defaultMarkerSvgPath;//默认标绘SVG图标路径
	void setMarkerIconPath(QString path); //设置标绘SVG图标路径
	void setDefaultMarkerIcon(QString path);//设置默认标绘SVG图标路径
};
#endif //__SVGMARKERTOOL_H__

