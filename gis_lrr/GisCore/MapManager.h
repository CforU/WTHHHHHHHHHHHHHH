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
#include <qpair.h>
#include <qmap.h>

//RCSettings �����ļ�
#include "../../modules/rcsettings/rcsetting.h"

//#inclide "E:\Qt\RemoteControl-new\RemoteControl\modules\rcsettings\rcsetings.h"


//��ͼ����������   �����ͼͼ��  �����ͼͼ��  �����ͼ���ͼ�� ��ͼ����� ���ص�ͼ
// 

class MapManager 
{
public:
	MapManager(QgsMapCanvas* mapCanvas);
	MapManager();
	~MapManager();
	static MapManager* instance();
public: //API
	static MapManager* theMapManger;
	//****ͼ�����***//
		void layerTree();
	//****��ͼ����***//
		// ���ʸ��ͼ��
		void addVectorLayers();
		// ���դ��ͼ��
		void addRasterLayers();
		//��ͼ����
		void MapLoad(void);//Ӱ�������
		void firstLoad();//���μ���
	//****���ͼ�����***//
		//��ǰͼ��
		QMap<int /*type*/,QString /*path*/>   MarkerIcon;
		QMap<int /*type*/, QString /*path*/>   MarkerIconSvg;
		//QMap<int /*type*/, QPair<const char*, QString> >   MarkerIcon;
		//��ʼ����ǰͼ��
		void init_MarkerIcon();
		//ѡ��ͼ��
		//����ͼ��
	//****��ͼ�������***//
		  //���������ļ� 
		  //ʹ��QSettings 

	
	//****��ͼ���߹���***//

	//
	QList<QgsMapCanvasLayer> mapCanvasLayerSet; // ��ͼ�������õ�ͼ�㼯��
	QgsMapCanvas* mapCanvas; //��ͼ����
private:
	//bool state = 0;//�Ƿ��ǵ�һ�μ��ص�ͼ 


};


#endif //__MAPMANAGER_H__