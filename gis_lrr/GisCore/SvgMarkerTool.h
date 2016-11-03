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

//SVG ��湤��
class SvgMarkerTool : public QgsMapTool
{
	Q_OBJECT
public:
	SvgMarkerTool(QgsMapCanvas* mapCanvas);
	~SvgMarkerTool();

	//! ��д���ָ���ͷ��¼�
	void canvasReleaseEvent(QgsMapMouseEvent* e) override;
	// ��д���˫���¼�
	void canvasDoubleClickEvent(QgsMapMouseEvent* e) override;
	// ��д��갴���¼�
	void canvasPressEvent(QgsMapMouseEvent* e) override;
	// ��д����ƶ��¼�
	void canvasMoveEvent(QgsMapMouseEvent* e) override;


	//Svg item ���  (�Զ����)
	//����item
	QgsSvgAnnotationItem* createItem(QgsPoint pos, QString svgPath);
	//����itemλ��
	void updateItemPositon(QgsAnnotationItem* sItem, QgsPoint pos);
	//ɾ��item
	int deleteItem(QgsAnnotationItem* sItem);
	//ɾ������item
	void deleteItemAll();
	//pos���ڵ�item
	QgsAnnotationItem* itemAtPos(QPointF pos);
	//��ȡѡ�е�item
	QgsAnnotationItem* selectedItem();


	public slots:

protected:
	//���е�����
	QList<QgsPoint> mPointList;
	//���еı��������
	QList<QgsAnnotationItem*>  mSvgList;


	//���±����Ƿ���Ҫ
	bool moveFlag;//�ƶ����־
	bool itemSelectFlag;//itemѡ�б�־

	QgsAnnotationItem::MouseMoveAction mCurrentMoveAction;
	int pointIndex;//��Ҫ�ƶ��ĵ������
	QgsPoint mMovePoint;//�ƶ����λ��
	QPointF mLastMousePosition;//��һ������ƶ���

public:
	//�����Ƿ���Ҫ
	QString MarkerSvgPath;// ���SVGͼ��·��
	QString defaultMarkerSvgPath;//Ĭ�ϱ��SVGͼ��·��
	void setMarkerIconPath(QString path); //���ñ��SVGͼ��·��
	void setDefaultMarkerIcon(QString path);//����Ĭ�ϱ��SVGͼ��·��
};
#endif //__SVGMARKERTOOL_H__

