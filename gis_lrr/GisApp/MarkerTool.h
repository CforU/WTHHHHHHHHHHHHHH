#ifndef MARKERTOOL_H
#define MARKERTOOL_H

//qt
#include <QObject>
#include <QtWidgets>
#include <QMouseEvent>
#include <QList>
#include <qfile.h>
#include <qtextstream.h>
//QSeq
#include <QSqlQuery>
//QGis
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



#include "GisHeader.h"
#include "../../modules/rcsettings/rcsetting.h"

//#include "../GisCore/MapTools.h"
//#include "../GisCore/MapManager.h" //������
//AddFeatureTool

class MarkerTool : public QgsMapTool
{
	Q_OBJECT
public:
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


public:
	void saveMarkerPath2File();//����·�����ļ�
	void loadMarkerPath2File();//����·�����ļ�
	void savePath2xml();
	void loadPath2xml();

private:
	int addVertex(const QgsPoint& point);
	void markerLine(QgsMapMouseEvent* e);

	QgsRubberBand* mRubberBand;//������ ����

	QList<QgsPoint> m_captureList;
	QgsAnnotationItem::MouseMoveAction mCurrentMoveAction;
	QPointF mLastMousePosition;
	QgsPoint mMovePoint;
	bool moveFlag;//�ƶ����־
	bool itemSelectFlag=false;
	int pointIndex;//��Ҫ�ƶ��ĵ������

	//�����ݿ���ݳ���id�жϳ���������
	int getVehicleTypeId(int aVehicleType);//�������ݿ��ȡ����id
	MarKerVehicleType getVechileType(int id);

public:
	//���еı����� ��������������ͼ��
	QList<QgsAnnotationItem*>  MarkerPointList;
	//����·�����������
	//QList<QgsPoint>  PathList;//��ʱδ��

	//########## ���б��ͼ��Ĺ���################
	//���е��������͵ı�������� ��ȥ·���ͳ���
	QList<QgsAnnotationItem*>  OhterMarkerList;
	//���е�·�����͵ı��������
	QList<QgsAnnotationItem*>  PathMarkerList;
	//���еĳ������͵ı��������
	QMap<int /*id*/, QgsAnnotationItem* /*���*/>  CarMarkerMap;

	QList<QgsPoint>  PathMarkerPointList; //���ص�ʱ���õ�����
	QStringList m_stringPoints; //�����ʱ���õ��б�

	//���г�������Ĺ�������
	//���еĳ������͵ı��������

	//����·�� �Ĺ���
	//ÿ��·����·�������

	//����
	void markerPoint(QgsMapMouseEvent* e);
	void markerPoint(QgsPoint pos, int type);
	//�ֶ����
	void ManuallyMaker(QgsPoint pos);

	//item ���
	QgsSvgAnnotationItem* createItem(QgsPoint pos, QString svgPath);//����item
	QgsAnnotationItem* selectedItem(); //��ȡѡ�е�item
	int deleteItem(QgsAnnotationItem* sItem);//ɾ��item
	void deleteItemAll();
	QgsAnnotationItem* itemAtPos(QPointF pos);

	
public:	//�ⲿ����
	//������� 
	QgsAnnotationItem* VehicleMarker(QgsPoint pos, MarKerVehicleType type);
	void VehicleMarker(QgsPoint pos, int id);
	//����λ�ø��� �Ƕ�ҲҪ����
	void updateVehiclePosition(QgsPoint pos, int id);
	//ɾ������
	void delteVechile(int id);//ɾ����������
	
	//·������
	void markerRoutePoint(QgsPoint pos, MarkerRoutePointType type);
	//·����� /*��� �м�� �յ� */
	void RouteMarker(QList<QgsAnnotationItem*>  PathMarkerList);
	void RouteMarker(QList<QgsPoint>  PathList);

	//�����ͼ ɾ�����г�����·��
	void clearUpMarker();

public: //�ֶ����ʹ��
	
	static  int MarkerType;//���ͼ������
	static  QString MarkerIcon;// ���SVGͼ��·��
	static  QString defaultMarkerIcon;//Ĭ�ϱ��SVGͼ��·��
	static void setMarkerType(int type); //���ñ��ͼ������
	static void setMarkerIconPath(QString path); //���ñ��SVGͼ��·��
	static void setDefaultMarkerIcon(QString path);//����Ĭ�ϱ��SVGͼ��·��

signals:
	void createWidget();
public slots:
	void on_showMarker(int i);
	void on_hideMarker(int i);
};


#endif // MARKERTOOL_H