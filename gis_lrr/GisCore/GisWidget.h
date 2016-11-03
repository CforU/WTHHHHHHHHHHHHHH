#ifndef  _GISWIDGET_H__
#define  _GISWIDGET_H__

#include <qwidget.h>

class GisWidget :public QWidget{
	Q_OBJECT
public:
	explicit  GisWidget(QWidget* parent = 0);
	~GisWidget();
	

};


#endif  // _GISWIDGET_H__
