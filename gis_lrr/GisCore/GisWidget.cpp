#include "GisWidget.h"
#include <qpalette.h>
#include <qgridlayout.h>
#include <qpixmap.h>
#include <qbitmap.h>
#include <qpalette.h>
#include <qcolor.h>
#include <qpixmap.h>
#include <qbrush.h>


#include "GisSystem.h"


GisWidget::GisWidget(QWidget * parent) :QWidget(parent)
{
#if 0
	QPixmap pix;
	pix.load("Resources/icon/gis/mobil/bg_map_2.png", 0, Qt::AvoidDither | Qt::ThresholdDither | Qt::ThresholdAlphaDither);
	resize(pix.size());
	setMask(QBitmap(pix.mask()));

	GisSystem * m_gis = new GisSystem();
	QPixmap pix;
	pix.load("Resources/icon/gis/mobil/bg_map_1.png", 0, Qt::AvoidDither | Qt::ThresholdDither | Qt::ThresholdAlphaDither);
	m_gis->resize(pix.size());
	m_gis->setMask(QBitmap(pix.mask()));

	m_gis->setAutoFillBackground(true);
	QPalette gp = m_gis->palette();
	gp.setBrush(QPalette::Foreground, QBrush(QPixmap("Resources/icon/gis/mobil/bg_map_2.png")));
	m_gis->setPalette(gp);

#endif
	setWindowFlags(Qt::FramelessWindowHint);
	
}

//m_gis->setForegroundRole();
//m_gis->setBackgroundRole();
//p.setColor(QPalette::Foreground, QBrush(QPixmap("Resources/icon/gis/mobil/bg_map_2.png"));
//bgpal.setBrush();
//setBackgroundColor()


GisWidget::~GisWidget()
{

}

