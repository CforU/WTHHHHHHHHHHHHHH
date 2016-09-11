#ifndef __MAPMANAGER_H__
#define __MAPMANAGER_H__

// QGis include
#include <qgsmapcanvas.h>
#include <qgsmaplayer.h>
#include <qgsmaptool.h>
#include <qgsvectorlayer.h>
#include <qgsmaplayerregistry.h>
#include <qgsrasterlayer.h>
//Qt
#include <qobject.h>
#include <qfiledialog.h>
#include <qstring.h>

#include "INS.h"
//��ͼ����������   �����ͼͼ��  �����ͼͼ��  �����ͼ���ͼ�� ��ͼ����� ���ص�ͼ
// 
class INS;
class MapManager :public QObject
{
	Q_OBJECT
public:
	MapManager(QgsMapCanvas* mapCanvas);
	~MapManager();

	//****ͼ�����***//
		void layerTree();
	//****��ͼ����***//
		// ���ʸ��ͼ��
		void addVectorLayers();
		// ���դ��ͼ��
		void addRasterLayers();
		//��ͼ����
		void MapLoad(void);//Ӱ�������

	//****���ͼ�����***//
		//ѡ��ͼ��
		//����ͼ��
	//****��ͼ�������***//
	//****��ͼ����***//
	//****��ͼ���߹���***//

	//
	QList<QgsMapCanvasLayer> mapCanvasLayerSet; // ��ͼ�������õ�ͼ�㼯��
	QgsMapCanvas* mapCanvas; //��ͼ����
	bool state = 0;//�Ƿ��ǵ�һ�μ��ص�ͼ 
	/*Test �������������ʾ*/
	QgsPoint setPosition;

};


#endif //__MAPMANAGER_H__