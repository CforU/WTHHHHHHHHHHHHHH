#include "MapTools.h"

#define		POINT_INDEX		1	//��������

/*
// ��ȡ��ǰͼ��
QgsVectorLayer* layer = qobject_cast<QgsVectorLayer*>(mCanvas->currentLayer());
// �õ������꣬ת��Ϊ��ͼ����
QgsPoint savePoint = toLayerCoordinates(layer, mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()));
//�¼�����
if (e->button() == Qt::LeftButton) // ������
	{
		switch (currentToolType)
		{
		case ToolTypeNone:
			break;
		case MarkerPoint:
			break;
		case MarkerLine:
			break;
		case MarkerNone:
			break;
		case MeasureLine:
			break;
		case MeasureArea:
			break;
		default:
			break;
		}
	}
if (e->button() == Qt::RightButton) // ����Ҽ�
{

	switch (currentToolType)
	{
	case ToolTypeNone:
		break;
	case MarkerPoint:
		break;
	case MarkerLine:
		break;
	case MarkerNone:
		break;
	case MeasureLine:
		break;
	case MeasureArea:
		break;
	default:
		break;
	}
}

*/


MapTools::MapTools(QgsMapCanvas* mapCanvas)
: QgsMapTool(mapCanvas)
{
}

MapTools::~MapTools()
{
}

// 1 ��д����ͷ��¼� 
void MapTools::canvasReleaseEvent(QgsMapMouseEvent* e)
{
	Q_UNUSED(e);
}

//��д���˫���¼�
void MapTools::canvasDoubleClickEvent(QgsMapMouseEvent* e)
{
	Q_UNUSED(e);
}

// ��д��갴���¼�
void MapTools::canvasPressEvent(QgsMapMouseEvent* e) 
{
	Q_UNUSED(e);
}

// ��д����ƶ��¼�
void MapTools::canvasMoveEvent(QgsMapMouseEvent* e) {
	Q_UNUSED(e);
}


