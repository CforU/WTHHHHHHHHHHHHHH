#ifndef _FILTERWIDGET_H_
#define _FILTERWIDGET_H_

#include "qwidget.h"
#include "qpainter.h"
class FilterWidget : public QWidget
{
	Q_OBJECT
public:
	FilterWidget(QWidget *parent = 0);
	~FilterWidget();
	void paintEvent(QPaintEvent* event);
private:

};



#endif