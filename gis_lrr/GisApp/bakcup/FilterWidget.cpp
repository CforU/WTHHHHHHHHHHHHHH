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
	//theQPainter->setPen(Qt::blue); //���û���Ϊ��ɫ
	//theQPainter->drawLine(0, 100, 100, 100); //(0, 0)Ϊ��ʼ���꣬��100, 100��Ϊ��������

	Q_UNUSED(event);

	QPainter p(this);
	p.setPen(Qt::NoPen);
	p.setBrush(Qt::gray);
	p.drawRect(rect());
}