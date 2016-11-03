#include "childWidget.h"
#include <QStandardItem>
#include <QFormLayout>

childWidget::childWidget(QWidget *parent):QWidget(parent)
{
    creat_ui();

}

void childWidget::creat_ui()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
#if 0
    mLine = new QFrame(this);
    mLine->setFrameShape(QFrame::HLine);
    mLine->setFrameShadow(QFrame::Raised);
   // mLine->setStyleSheet("");
  //  mLine->setStyleSheet("{ background: rgb(45, 55, 61); color: rgb(0, 160, 230);}");
#endif
    mChekButton = new QPushButton(this);
    mChekButton->setCheckable(true);
    mChekButton->setChecked(true);
    mChekButton->setFixedSize(40,40);
    mChekButton->setStyleSheet("QPushButton{border-image: url(Resources//icon/btn_sxxx_n.png);border-style: flat;}"\
            "QPushButton:checked{border-image:url(Resources//icon/btn_sxxx_s.png);border-style: flat;}");
	
  //  mChekButton->setStyleSheet("QPushButton{border-image: url(Resources/icon/gis/MapSideIcon/btn_ss_n.png);border-style: flat;}"\
           "QPushButton:pressed{border-image: url(Resources/icon/gis/MapSideIcon/btn_ss_p.png);border-style: flat;}"\
            "QPushButton:checked{border-image:url(Resources/icon/gis/MapSideIcon/btn_ss_p.png);border-style: flat;}");


    mLab = new QLabel(this);
    mLab->resize(40,120);
    //mLab->setText("Point");

     QFormLayout *form = new QFormLayout(this);
     form->addRow(mChekButton,mLab);

    this->setFixedSize(200,50);
}

void childWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
  //  painter.save();
    painter.setPen(QColor(139, 139, 139));
   // painter.drawLine(mLine->pos(),mLine->x()+mLine->wight());
    painter.drawLine(0,0,260 ,0);
   // painter.restore();
}

