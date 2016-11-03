#include "CustomButton.h"


CustomButton::CustomButton(int id):mid(id)
{
    //设置样式
#if 0
    this->setAutoFillBackground(true);
    QPalette p = this->palette();
	p.setColor(QPalette::Background, QColor(45, 55, 61));
	p.setColor(QPalette::ButtonText, QColor(255, 255, 255));
    this->setPalette(p);
#endif
    connect(this,SIGNAL(clicked()),this,SLOT(on_clicked()));
}

CustomButton::~CustomButton()
{

}

void CustomButton::on_clicked()
{
    obj = this;
    emit theClicked(mid,obj);
}

int CustomButton::id()
{
    return mid;
}
