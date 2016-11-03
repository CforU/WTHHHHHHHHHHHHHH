#ifndef _SCALEWIDGET_H_
#define _SCALEWIDGET_H_

#include <QWidget>
#include <qpainter.h>
#include <QLocale>

class GisSystem;
class GisApp;
class ScaleWidget :public QWidget
{
	Q_OBJECT

public:
	ScaleWidget(QWidget *parent = 0);
	~ScaleWidget();

	void paintEvent(QPaintEvent*);

public slots:
	void getData(int,int);

private:
	double myActualSize ;
	double myScaleBarWidth ;
};

#endif