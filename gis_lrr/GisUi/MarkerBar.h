#ifndef _MARKERBAR_H__
#define  _MARKERBAR_H__
#include <qwidget.h>
#include <qpushbutton.h>

#include <qsize.h>
#include "Menu.h"
#include <qscrollarea.h>
#include "qscroller.h"
#include <QScrollBar>
#include <qmessagebox.h>
#include <QAbstractScrollArea>

class MarkerBar :public QWidget{
	Q_OBJECT
public:
	explicit  MarkerBar(QWidget* parent = 0);
	~MarkerBar();
	void creat_ui(void);
	void setlay(void);//设置布局
	void connect_signal(void);

public slots:
	//向上滚动
	void on_Up(void);
	//向下滚动
	void on_Down(void);

public:
	QPushButton * topBtn;//向上按钮
	QWidget     *baseWgt;
	QScrollArea * menuArea;
	Menu   * menu;
	QPushButton * botomBtn;//向下按钮

	QSize iconSize;
	QSize btnSize;
	int   scrolValue=0;
public:

};


#endif  // _MARKERBAR_H__