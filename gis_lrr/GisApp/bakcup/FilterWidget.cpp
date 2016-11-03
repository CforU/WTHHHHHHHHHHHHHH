#include "FilterWidget.h"
#include "qcolor.h"
FilterWidget::FilterWidget(QWidget *parent) :
QWidget(parent)
{

}
FilterWidget::~FilterWidget()
{

}

void FilterWidget::paintEvent(QPaintEvent* event){

	//QPainter* theQPainter = new QPainter(this);
	//theQPainter->setPen(Qt::blue); //设置画笔为灰色
	//theQPainter->drawLine(0, 100, 100, 100); //(0, 0)为初始坐标，（100, 100）为最终坐标

	Q_UNUSED(event);

	QPainter p(this);
	p.setPen(Qt::NoPen);
	p.setBrush(Qt::gray);
	p.drawRect(rect());
}