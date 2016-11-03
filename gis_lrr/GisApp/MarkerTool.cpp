#include "MarkerTool.h"

//Ĭ�ϱ��ͼ�� Ϊ�� 
int MarkerTool::MarkerType=0; //Ĭ�ϱ������ ������
QString MarkerTool::MarkerIcon = "Resources/icon/gis/mkSvg/icon_bhtjd_2.svg";//�Ƿ���bug  �Ƿ���� ÿ�δ������߶���Ĭ�ϵĹ���
QString MarkerTool::defaultMarkerIcon = QString("Resources/icon/gis/mkSvg/icon_bhtjd_2.svg");


MarkerTool::MarkerTool(QgsMapCanvas* mapCanvas)
:QgsMapTool(mapCanvas)
{
	mToolName = tr("Marker");	
	mRubberBand = NULL;//������ ����
	moveFlag = false; //�ƶ����־

}

MarkerTool::~MarkerTool()
{
//	delete mRubberBand;
}


//############### �¼����� ########################################

// 1 ��д����ͷ��¼� 
void MarkerTool::canvasReleaseEvent(QgsMapMouseEvent* e)
{
	
	
	if (e->button() == Qt::LeftButton  && itemSelectFlag == false) /* ������*/
	{
		QgsAnnotationItem* sItem = selectedItem();
		if (sItem == nullptr){
			//markerPoint(e);
			QgsPoint mapPoint = mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos());
			//markerPoint(mapPoint, MarkerType);
			ManuallyMaker(mapPoint);
		}
	}
	if (e->button() == Qt::RightButton) /* ����Ҽ�*/ {
		
	}
	moveFlag = false;
	itemSelectFlag = false;
}

//��д���˫���¼�
void MarkerTool::canvasDoubleClickEvent(QgsMapMouseEvent* e) {
	//ɾ����
	//if (e->button() == Qt::LeftButton && mCptFlag == CaptureLine) /* ���˫�����*/ {
		if (e->button() == Qt::RightButton) /* ���˫�����*/ {		
			deleteItemAll();
	}
}

// ��д��갴���¼�
void MarkerTool::canvasPressEvent(QgsMapMouseEvent* e) {


	if (e->button() == Qt::RightButton ) /* ����Ҽ�*/
	{
		moveFlag = true;//�ƶ����־
	}

	if (!mCanvas)
	{
		return;
	}

	QgsAnnotationItem* sItem = selectedItem();
	if (sItem)
	{
		mCurrentMoveAction = sItem->moveActionForPosition(e->pos());
		if (mCurrentMoveAction != QgsAnnotationItem::NoAction)
		{
			return;
		}
	}

	if (!sItem || mCurrentMoveAction == QgsAnnotationItem::NoAction)
	{
		//select a new item if there is one at this position
		mCanvas->scene()->clearSelection();
		QgsAnnotationItem* existingItem = itemAtPos(e->pos());
		//��ȡ������
		if (PathMarkerList.contains(existingItem)){
			pointIndex = PathMarkerList.indexOf(existingItem);
		}
		if (existingItem)
		{
			existingItem->setSelected(true);
		}
		else
		{
			//otherwise create new one
			//createItem(e);
			return;
		}
	}

}

// ��д����ƶ��¼�
void MarkerTool::canvasMoveEvent(QgsMapMouseEvent* e)
{
	QgsAnnotationItem* sItem = selectedItem();
	if (sItem && (e->buttons() & Qt::LeftButton))
	{

		//�ж��Ƿ��ƶ�����
		if ((mCurrentMoveAction == QgsAnnotationItem::MoveMapPosition) )
		{
			sItem->setMapPosition(toMapCoordinates(e->pos()));
			mMovePoint = sItem->mapPosition();
			sItem->update();
			QgsProject::instance()->setDirty(true);
			if (mRubberBand && PathMarkerList.contains(sItem) ){
				mRubberBand->movePoint(pointIndex, mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()), 0);
			}
		}
		
	}
	else if (sItem)
	{
		QgsAnnotationItem::MouseMoveAction moveAction = sItem->moveActionForPosition(e->pos());
		if (mCanvas )
		{
			mCanvas->setCursor(QCursor(sItem->cursorShapeForAction(moveAction)));
			itemSelectFlag = true;
		}
	}
	mLastMousePosition = e->pos();

}

//####################�ڲ�����###################################

int MarkerTool::addVertex(const QgsPoint& point){	
	// 1 ������ͷ�λ�õĵ�ת���ɵ�ͼ�ϵ�λ��
	QgsVectorLayer *vlayer = qobject_cast<QgsVectorLayer *>(mCanvas->currentLayer());
	QgsPoint layerPoint = toLayerCoordinates(vlayer, point);
	// 2 ����ͼ��
	if (!mRubberBand) // û��rubber band���ʹ���һ��
	{
		mRubberBand = new QgsRubberBand(mCanvas, QGis::Line);
		mRubberBand->setWidth(2);
		mRubberBand->setColor(QColor(0, 255, 0));

	}
	// 3 ��ͼ���ϱ�ǵ�
	mRubberBand->addPoint(point);
	// 4 ׷�ӵ�
	m_captureList.append(layerPoint);

	m_stringPoints.append(point.toString());	
	//test
	
	return 0;
}

void MarkerTool::markerLine(QgsMapMouseEvent* e)
{
	// ��ȡ��ǰͼ��
	QgsVectorLayer* layer = qobject_cast<QgsVectorLayer*>(mCanvas->currentLayer());
	// �õ������꣬ת��Ϊ��ͼ����
	QgsPoint savePoint = toLayerCoordinates(layer, mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()));
	//��Ӷ���
	addVertex(mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()));

}

//############ item ���� ######################
//����item
QgsSvgAnnotationItem* MarkerTool::createItem(QgsPoint pos, QString svgPath)
{

	QgsSvgMarkerSymbolLayerV2 *svgMarker = new QgsSvgMarkerSymbolLayerV2(svgPath);
	svgMarker->setVerticalAnchorPoint(QgsMarkerSymbolLayerV2::Bottom);//��ͼ��������óɵ׶�
	svgMarker->setSize(8);//����ͼ���С

	QgsSymbolLayerV2List symList;//������������
	symList.append(svgMarker);//��ͼ����뵽����������
	QgsMarkerSymbolV2* markSym = new QgsMarkerSymbolV2(symList);	
	

	QgsSvgAnnotationItem *psvg = new QgsSvgAnnotationItem(mCanvas);
	psvg->setMarkerSymbol(markSym);//������ʾ��ʽ
	psvg->setMapPosition(pos);
	psvg->setFrameSize(QSizeF(0, 0));//������ʾ���С 00ȥ��ʾ��
	//psvg->setFrameBorderWidth(10); ��֪����ɶ
	//psvg->setOffsetFromReferencePoint(QPointF(0, 0)); //�����ƶ���Ⱦ��ʾ���ƫ��λ��
	//QgsRectangle r(0,0,20,20);
	//psvg->setRect(r, true);
	MarkerPointList.append(psvg);//����������
	return psvg;
}
//ɾ��item
int MarkerTool::deleteItem(QgsAnnotationItem* sItem)
{
	if (sItem)
	{
		QGraphicsScene* scene = sItem->scene();
		if (scene)
		{
			scene->removeItem(sItem);
		}
		delete sItem;
		sItem = nullptr;
		return 0;

	}
	else{
		return -1;
	}

}
//ɾ��item
void MarkerTool::deleteItemAll()
{
	QgsAnnotationItem* sItem = selectedItem();
	QGraphicsScene* scene;
	if (sItem){
		if (PathMarkerList.contains(sItem))
		{
			scene = sItem->scene();
			scene->removeItem(sItem);
			pointIndex = PathMarkerList.indexOf(sItem);
			mRubberBand->removePoint(pointIndex);       ///////ɾ��·�����ϵĵ�
			PathMarkerList.removeAt(pointIndex);
		}
		else {
			scene = sItem->scene();
			scene->removeItem(sItem);
		}
		delete sItem;
		sItem = nullptr;
	}
	else{
		//ɾ��svgͼ��
		for (int i = 0; i < PathMarkerList.size(); ++i){
			scene = PathMarkerList.at(i)->scene();
			scene->removeItem(PathMarkerList.at(i));
		}
		PathMarkerList.clear();
		//ɾ����
		delete mRubberBand;
		mRubberBand = NULL;
	}
}

//ѡ��
QgsAnnotationItem* MarkerTool::selectedItem()
{
	if (!mCanvas || !mCanvas->scene())
	{
		return nullptr;
	}
	QList<QGraphicsItem *> gItemList = mCanvas->scene()->selectedItems();
	QList<QGraphicsItem *>::iterator it = gItemList.begin();
	for (; it != gItemList.end(); ++it)
	{
		QgsAnnotationItem* aItem = dynamic_cast<QgsAnnotationItem*>(*it);
		if (aItem)
		{
			return aItem;
		}
	}
	return nullptr;
}

QgsAnnotationItem* MarkerTool::itemAtPos(QPointF pos)
{
	if (!mCanvas)
	{
		return nullptr;
	}

	QList<QGraphicsItem *> graphicItems = mCanvas->items(pos.toPoint());
	QList<QGraphicsItem *>::iterator gIt = graphicItems.begin();
	for (; gIt != graphicItems.end(); ++gIt)
	{
		QgsAnnotationItem* annotationItem = dynamic_cast<QgsAnnotationItem*>(*gIt);
		if (annotationItem)
		{
			return annotationItem;
		}
	}
	return nullptr;
}
//############ ɸѡ ���� ######################
//��ʾ���������е�i�����
void MarkerTool::on_showMarker(int i){
	MarkerPointList.at(i)->setVisible(true);
}
//���س��������е�i�����
void MarkerTool::on_hideMarker(int i){
	MarkerPointList.at(i)->setVisible(false);
}

//############ �ڲ���̬��Ա�ⲿ�ӿ� ���� ######################
//���ñ��ͼ������
void MarkerTool::setMarkerType(int type)
{
	MarkerType = type;
}
//���õ�ǰ���ͼ��
void MarkerTool::setMarkerIconPath(QString path)
{
	MarkerIcon = path;// Path

}
//����Ĭ�ϵı��ͼ��
void MarkerTool::setDefaultMarkerIcon(QString path)
{
	defaultMarkerIcon = path;//Path
}

//########################################################

// ͨ����ȡ���ݿ��г���id��ȡ��������
int MarkerTool::getVehicleTypeId(int aVehicleType)
{
	int id = 0;
	QSqlQuery sqlQuery;

	QString typeStr = "";

	switch (aVehicleType)
	{
	case 6:
		typeStr = QStringLiteral("�Ĵ�");
		break;
	case 8:
		typeStr = QStringLiteral("��Ѳ");
		break;
	case 9:
		typeStr = QStringLiteral("��ʽ");
		break;
	default:
		break;
	}

	sqlQuery.exec(
		QString("select id from t_car where car_type=%1").arg(typeStr)
		);
	if (sqlQuery.next())
	{
		id = sqlQuery.value(0).toInt();
		return id;
	}
	else
	{
		qDebug() << "�޴�����";
		return -1;
	}

}
//�����ݿ���ݳ���id�жϳ��������� 
MarKerVehicleType MarkerTool::getVechileType(int id)
{

	//�������ݿ�ӿ� ��ȡtype
	int typeId = getVehicleTypeId(id);
	// MarkerTool::MarKerVehicleType type = MarkerTool::MarKerVehicleType(typeId);
	switch (typeId){
	case 4:
		return MarKerVehicleType::CommandCar; //ָ�ӳ�
		break;
	case 5:
		return MarKerVehicleType::UAV; //���˻�
		break;
	case 6:
		return MarKerVehicleType::TrackedVehicle;//�Ĵ���
		break;
	case 7:
		return MarKerVehicleType::DumpedCar;//��Ͷ��
		break;
	case 8:
		return MarKerVehicleType::WheelPatrolCar;// ��Ѳ��
		break;
	case 9:
		return MarKerVehicleType::WheeledVehicles;//��ʽ��
		break;
	default:
		return MarKerVehicleType::CarDefault; //�޳� Ĭ�� 
	}

}


//############  API  ###################
//����
void MarkerTool::markerPoint(QgsPoint pos, int type)
{
	//contains(key) ������ �鿴�Ƿ���� 
	//QString path = MapManager::instance()->MarkerIconSvg[type];
	createItem(pos, MarkerIcon);
}
//����
void MarkerTool::markerPoint(QgsMapMouseEvent* e)
{

	QgsSvgMarkerSymbolLayerV2 *svgMarker = new QgsSvgMarkerSymbolLayerV2(MarkerIcon.isNull() ? MarkerIcon : MarkerIcon);
	svgMarker->setVerticalAnchorPoint(QgsMarkerSymbolLayerV2::Bottom);//��ͼ��������óɵ׶�
	qDebug() << MarkerIcon << "  : " << MarkerIcon;
	qDebug() << "Marker symbol";
	QgsSymbolLayerV2List symList;//������������
	symList.append(svgMarker);//��ͼ����뵽����������
	QgsMarkerSymbolV2* markSym = new QgsMarkerSymbolV2(symList);
	svgMarker->setSize(8);//����ͼ���С
	QgsSvgAnnotationItem *psvg = new QgsSvgAnnotationItem(mCanvas);
	psvg->setMarkerSymbol(markSym);//������ʾ��ʽ
	psvg->setMapPosition(mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()));
	PathMarkerList.append(psvg);

	addVertex(mCanvas->mapSettings().mapToPixel().toMapCoordinates(e->pos()));

}
//�ֶ����
void MarkerTool::ManuallyMaker(QgsPoint pos)
{
	//·�� ��������֮�以�� �յ����յ㻥�� ֻ�ܴ���һ��

	if (MarkerType == 1 || MarkerType == 2 || MarkerType == 3){ //·�����
		MarkerRoutePointType ctype = (MarkerRoutePointType)MarkerType;
		markerRoutePoint(pos, ctype);
	}
	else  //�������
	{
		MarKerVehicleType ctype = (MarKerVehicleType)MarkerType;
		VehicleMarker(pos, ctype);
		emit createWidget();//�����ź� ��̬����ɸѡ�ؼ�
	}
}

//������� 
QgsAnnotationItem* MarkerTool::VehicleMarker(QgsPoint pos, MarKerVehicleType type)
{
	
	QString path = RCSettings::getValue(RCSettings::GIS, QString("svg/%1").arg((int)type), "Resources/icon/gis/mkSvg/icon_bhtjd_2.svg").toString();
	//QString path = MapManager::instance()->MarkerIconSvg[ctype];
	QgsAnnotationItem* item = createItem(pos, path);
	return item;
}
//������� 
void MarkerTool::VehicleMarker(QgsPoint pos, int id)
{
	//��泵��
	//QgsAnnotationItem* item = VehicleMarker(pos, getVechileType(id));
	QgsAnnotationItem* item = VehicleMarker(pos,MarKerVehicleType::WheelPatrolCar);
	//�����������	
	if (item)
	{
		CarMarkerMap.insert(id, item);
	}
}
//����λ�ø��� �Ƕ�ҲҪ����
void MarkerTool::updateVehiclePosition(QgsPoint pos, int id)
{
	//���id �������ǲ��Ǳ�����һ���µ� 
	QgsAnnotationItem* sItem=NULL;
	if (CarMarkerMap.contains(id)){
		sItem = CarMarkerMap.value(id);
	}
	else
	{
	    //����޴�id �Ƿ񴴽�һ�����		
		VehicleMarker(pos, id);
		return;
	}
	if (sItem)
	{
		sItem->setMapPosition(pos);
		// sItem->markerSymbol()->setAngle((angle += 6) % 360));// ������ת ����Ŀǰ�޷���ת
		mMovePoint = sItem->mapPosition();
		sItem->update();
	}
}
//ɾ������
void MarkerTool::delteVechile(int id)//ɾ����������
{
	//���id �������ǲ��Ǳ�����һ���µ� 
	QgsAnnotationItem* sItem = NULL;
	if (CarMarkerMap.contains(id)){
		sItem = CarMarkerMap.value(id);
	}
	if (sItem)
	{
		deleteItem(sItem); //ɾ������
		CarMarkerMap.remove(id);//�����������
		sItem = NULL;
	}
}

//·������
void MarkerTool::markerRoutePoint(QgsPoint pos, MarkerRoutePointType type)
{
	QString path = RCSettings::getValue(RCSettings::GIS, QString("svg/%1").arg((int)type), "Resources/icon/gis/mkSvg/icon_bhtjd_2.svg").toString();
	QgsSvgAnnotationItem* svg = createItem(pos, path);			
	PathMarkerList.append(svg);							
	addVertex(pos);//�Ƿ���Ҫ������ط�����

}
//·�����
void MarkerTool::RouteMarker(QList<QgsAnnotationItem*>  PathMarkerList)/*��� �м�� �յ� */
{
	//��������յ�  ѭ������м�� 
	int i = 1;
	markerRoutePoint(PathMarkerList.at(0)->pos(), MarkerRoutePointType::StartPoint);
	for (i=1;i<= PathMarkerList.size()-2;i++){
		markerRoutePoint(PathMarkerList.at(i)->pos(), MarkerRoutePointType::PassPoint);
	}
	markerRoutePoint(PathMarkerList.last()->pos(), MarkerRoutePointType::EndPoint);

}
//·�����
void MarkerTool::RouteMarker(QList<QgsPoint>  PathList)
{

	if (PathList.isEmpty()){
		return;
	}

	//��������յ�  ѭ������м�� 
	int i = 1;
	markerRoutePoint(PathList.at(0), MarkerRoutePointType::StartPoint);
	for (i=1; i<= PathList.size() - 2; i++){
		markerRoutePoint(PathList.at(i), MarkerRoutePointType::PassPoint);
	}
	markerRoutePoint(PathList.last(), MarkerRoutePointType::EndPoint);
}


//����·�����ļ�
void MarkerTool::saveMarkerPath2File()
{
	QString fileName = ("fortest/path/path.txt");
	QFile file(fileName);
	//QStringList m_stringPoints;
	/*-------------��������㵽�ļ�-------------*/
	if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
	{
		qDebug() << "cann't open the file!!!";

	}else{
		qDebug() << "save path!!!";
	}
	QTextStream in(&file);
	QStringList::Iterator it;
	for (it = m_stringPoints.begin(); it != m_stringPoints.end(); ++it){
		in << *it << "\n";//���д���У�ͬ��ѭ������  
	}

	m_captureList.clear();
	m_stringPoints.clear();
	QPoint p = QPoint(500 + 1440, 250);
	QToolTip::showText(p, "save path success!");
	file.close();
	/*-------------------------------------------*/
}
//�����ļ�·������ͼ
void MarkerTool::loadMarkerPath2File()
{
	QString fileName = ("fortest/path/path.txt");
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug() << "cann't open the file!!!";

	}
	else{
		qDebug() << "load path!!!";
	}
	QTextStream in(&file);
	//��ȡ���10��  
	QStringList str[10];
	for (int i = 0; i < 10; i++){
		str[i] = in.readLine().split(',');//��һ��
		if (str[i].at(0) != "" && str[i].at(1) != ""){
			PathMarkerPointList.append( QgsPoint(str[i].at(0).toDouble(), str[i].at(1).toDouble()));
		}
	}
	//�Զ����svg·��ͼ��
	RouteMarker(PathMarkerPointList);
	PathMarkerPointList.clear();//�������֮����Ҫ��
	file.close();
}

//����·����XML�ļ�
void MarkerTool::savePath2xml()
{
	QPoint p = QPoint(500 + 1440, 250); //˫��
	if (m_stringPoints.isEmpty()){
		QToolTip::showText(p, "NO PATH TO SAVE!");
		return;
	}
	QFile file("fortest/path/myPathData.xml");
	if (!file.open(QFile::WriteOnly | QFile::Text))
	{
		qDebug() << "cann't open the file!!!";

	}
	QXmlStreamWriter writer(&file);
	writer.setAutoFormatting(true);
	writer.writeStartDocument();
	writer.writeStartElement("PathsData");

	//׷��д�����·����Ϣ������
	writer.writeTextElement("PathName", "testPath2333");
	writer.writeTextElement("PathLength", QString::number(233, 10));
	writer.writeStartElement("PointsData");
	QStringList::Iterator it;
	for (it = m_stringPoints.begin(); it != m_stringPoints.end(); ++it){
		writer.writeTextElement("PathPoint", *it);
	}

	writer.writeEndElement();
	writer.writeEndElement();
	writer.writeEndDocument();	
	QToolTip::showText( p, "save path success!"); 
	file.close();
}
//����XML�ļ��е�·��
void MarkerTool::loadPath2xml()
{
	QFile file("fortest/path/myPathData.xml");
	if (!file.open(QFile::ReadOnly | QFile::Text))
	{
		qDebug() << "cann't open the file!!!";

	}
	QStringList strList;
	QXmlStreamReader *reader = new QXmlStreamReader(&file);
	while (!reader->atEnd() && !reader->hasError()) {
		QXmlStreamReader::TokenType token = reader->readNext();
		if (token == QXmlStreamReader::StartDocument) {
			continue;
		}
		//TODO 
		if (reader->isStartElement() && reader->name() == "PointsData"){
			while (!reader->atEnd()){
				reader->readNext();
				if (reader->isStartElement() && reader->name() == "PathPoint"){
					//qDebug() << "point" << reader->readElementText(); //��
					QString pt = reader->readElementText();
					strList.append(pt);
				}
			}
		}
	}
	qDebug() << "strList is :" << strList;
	for (int i = 0; i < strList.count(); ++i){
		QString strPoint = strList.at(i);
		QStringList listPoint = strPoint.split(",");
		//addVertex(QgsPoint(listPoint.at(0).toDouble(), listPoint.at(1).toDouble()));
		PathMarkerPointList.append(QgsPoint(listPoint.at(0).toDouble(), listPoint.at(1).toDouble()));
	}
	RouteMarker(PathMarkerPointList);
	PathMarkerPointList.clear();//�������֮����Ҫ��
	m_stringPoints.clear();
	reader->clear();
	file.close();
}


//�����ͼ�ϵı������
void MarkerTool::clearUpMarker()
{
	//���� �������� CarMarkerMap ���� ѭ��ɾ��item ��������������� �ͷ�ָ��	
	QMap<int, QgsAnnotationItem*>::const_iterator i;
	for (i = CarMarkerMap.constBegin(); i != CarMarkerMap.constEnd(); ++i) {
		//qDebug() << i.key() << ":" << i.value();
		deleteItem(i.value()); //ɾ������
	}
	CarMarkerMap.clear();
	//����·������
}


//�ƶ�·�� �������ο�
//����·��
#if 0
void movePath()
{
	if (!mCanvas)
	{
		return;
	}
	if (num < 60){

		QgsAnnotationItem* sItem = selectedItem();
		if (sItem)
		{
			//QgsPoint point = mCanvas->mapSettings().mapToPixel().toMapCoordinates(PathPoint[num]);
			QgsPoint point = mCanvas->mapSettings().mapToPixel().toMapCoordinates(QPoint(num * 10, num * 10));
			sItem->setMapPosition(point);
			// sItem->markerSymbol()->setAngle((angle += 6) % 360));// ������ת ����Ŀǰ�޷���ת
			mMovePoint = sItem->mapPosition();
			sItem->update();
			//QgsProject::instance()->setDirty(true);
			qDebug() << "point::::" << PathPoint[num];
			qDebug() << num;

		}
		num++;
	}
	else{
		num = 0;
	}
}
#endif
