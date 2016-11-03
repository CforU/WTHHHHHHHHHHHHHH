#ifndef MARKERTOOL_H
#define MARKERTOOL_H

//qt
#include <QObject>
#include <QMouseEvent>
#include <QList>
#include <qfile.h>
#include <qtextstream.h>
//QSeq
#include <QSqlQuery>
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
#include "qgsmapmouseevent.h"
#include <qgsvectorlayer.h>
#include "qgsfeature.h"
#include <qgsgeometryvalidator.h>
#include <qgsvertexmarker.h>
#include "qgsrubberband.h"
#include "qgis.h"




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




#include "MapTools.h"
#include "MapManager.h"

//AddFeatureTool

class MarkerTool : public QgsMapTool
{
	Q_OBJECT
public:
	/*
	enum CaptureMode // ʸ��������
	{
		CaptureNone,       // ��
		CapturePoint,      // ��
		CaptureLine,       // ��
		CapturePolygon     // ��
	};*/
	

	MarkerTool(QgsMapCanvas* mapCanvas);
	~MarkerTool();

	//! ��д���ָ���ͷ��¼�
	void canvasReleaseEvent(QgsMapMouseEvent* e) override;
	// ��д���˫���¼�
	void canvasDoubleClickEvent(QgsMapMouseEvent* e) override;
	// ��д��갴���¼�
	void canvasPressEvent(QgsMapMouseEvent* e) override;
	// ��д����ƶ��¼�
	void canvasMoveEvent(QgsMapMouseEvent* e) override;
	//��ȡ����·��
	const QList<QgsPoint> &points() { return m_captureList; }

//private:
public:
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

	//·����ز��� 
	//��������
	QgsRubberBand*  createRubberBand();
	//������ӵ�  ���� ׷�� 
	int rubberBandInsertPoint(QgsRubberBand* mRubberBand, int index, const QgsPoint& point);
	int rubberBandAppendPoint(QgsRubberBand* mRubberBand, const QgsPoint& point);
	//����ɾ���� �м�ɾ�� ĩβɾ��
	int rubberBandRemovePoint(QgsRubberBand* mRubberBand, int index, const QgsPoint& point);
	int rubberBandDeletePoint(QgsRubberBand* mRubberBand, const QgsPoint& point);
	//�����ƶ���
	int rubberBandMovePoint(QgsRubberBand* mRubberBand, int index, const QgsPoint& point);
	//ɾ������
	void deleteRoute(QgsRubberBand* mRubberBand);
	
	
	//####################################################//

	//���е�·�����͵ı��������
	QList<QgsAnnotationItem*>  PathMarkerList;
	//���еĳ������͵ı��������
	QMap<int /*id*/, QgsAnnotationItem* /*���*/>  CarMarkerMap;

	QgsAnnotationItem::MouseMoveAction mCurrentMoveAction;
	QPointF mLastMousePosition;
	QgsPoint mMovePoint;
	bool moveFlag;//�ƶ����־
	bool itemSelectFlag=false;
	int pointIndex;//��Ҫ�ƶ��ĵ������
	

	//����·�����
	QgsRubberBand* createRoute();
	QgsRubberBand* createRoutePoint(const QgsPoint& point);
	//���·���� ��������
	int addRoutePoint(QgsRubberBand* mRubberBand,const QgsPoint& point);
	//���·���� ���ߺ�ͼ��
	QgsSvgAnnotationItem* MarkerRoutePoint(QgsRubberBand* mRubberBand, const QgsPoint& point, QString svgPath);
	//ɾ��·��
	void deleteRoute(QgsRubberBand* mRubberBand, QList<QgsAnnotationItem*>  PathMarkerList);
	
	

	//************  �ֶ���� ** //

	//���·�� 
	//���б���
	//QList<QgsPoint> m_captureList;
	//�����
	//QgsRubberBand* mRubberBand;//������ ����
	void markerLine(QgsMapMouseEvent* e);
	int  addRoutePoint(const QgsPoint& point);
	void deleteRoute();
	//�ֶ����
	void ManuallyMaker(QgsPoint pos)
	//����
	void markerPoint(QgsMapMouseEvent* e);
	void markerPoint(QgsPoint pos, int type);
	
public:			
	//�����ͼ ɾ�����г�����·��
	void clearUpMarker();

public: //�ֶ����ʹ��
	static  int MarkerType;//���ͼ������
	static  QString MarkerIcon;// ���SVGͼ��·��
	static  QString defaultMarkerIcon;//Ĭ�ϱ��SVGͼ��·��
	static void setMarkerType(int type); //���ñ��ͼ������
	static void setMarkerIconPath(QString path); //���ñ��SVGͼ��·��
	static void setDefaultMarkerIcon(QString path);//����Ĭ�ϱ��SVGͼ��·��
};


#endif // MARKERTOOL_H