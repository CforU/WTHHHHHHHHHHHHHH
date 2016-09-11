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
	void setlay(void);//���ò���
	void connect_signal(void);

public slots:
	//���Ϲ���
	void on_Up(void);
	//���¹���
	void on_Down(void);

public:
	QPushButton * topBtn;//���ϰ�ť
	QWidget     *baseWgt;
	QScrollArea * menuArea;
	Menu   * menu;
	QPushButton * botomBtn;//���°�ť

	QSize iconSize;
	QSize btnSize;
	int   scrolValue=0;
public:

};


#endif  // _MARKERBAR_H__