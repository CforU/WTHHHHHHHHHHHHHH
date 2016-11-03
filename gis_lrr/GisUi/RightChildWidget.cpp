#include "RightChildWidget.h"

RightChildWidget::RightChildWidget(QWidget *parent) :
    QStackedWidget(parent)
{

    iconSize = QSize(50,50);
    btnSize = QSize(70,70);

        //设置样式
    this->setAutoFillBackground(true);
    QPalette p = this->palette();
    p.setColor(QPalette::Background, QColor(45, 55, 61));
    p.setColor(QPalette::ButtonText, QColor(255, 255, 255));
    this->setPalette(p);


    create_ui();
    connect_signal();


   // this->resize(120,300);

}

void RightChildWidget::create_ui()
{

  //##########################################################
    baseWdt = new QWidget; //基本
    base_btn1 = new QToolButton;
    base_btn2= new QToolButton;
    base_btn3= new QToolButton;
#if 1
    base_btn1->setFixedSize(btnSize);
    base_btn1->setStyleSheet("QToolButton{border-image: url(Resources/icon/gis/MapSideIcon/btn_dtfc_n.png);border-style: flat;}"\
        "QToolButton:pressed{border-image: url(Resources/icon/gis/MapSideIcon/btn_dtfc_p.png);border-style: flat;}");

     base_btn2->setFixedSize(btnSize);
     base_btn2->setStyleSheet("QToolButton{border-image: url(Resources/icon/gis/MapSideIcon/btn_dtsx_n.png);border-style: flat;}"\
         "QToolButton:pressed{border-image: url(Resources/icon/gis/MapSideIcon/btn_dtsx_p.png);border-style: flat;}");

     base_btn3->setFixedSize(btnSize);
     base_btn3->setStyleSheet("QToolButton{border-image: url(Resources/icon/gis/MapSideIcon/btn_dtcl_n.png);border-style: flat;}"\
         "QToolButton:pressed{border-image: url(Resources/icon/gis/MapSideIcon/btn_dtcl_p.png);border-style: flat;}");
#endif
     QVBoxLayout * baseLayout = new QVBoxLayout(baseWdt);
    // QHBoxLayout * baseLayout = new QHBoxLayout(baseWdt);
     baseLayout->addWidget(base_btn1,1,Qt::AlignCenter);
     baseLayout->addWidget(base_btn2,1,Qt::AlignCenter);
     baseLayout->addWidget(base_btn3,1,Qt::AlignCenter);
	 baseLayout->setMargin(0);
	 baseLayout->setSpacing(0);

//##########################################################
    StratifiedWdt = new QWidget; //分层
    Stratified_btn1= new QToolButton;
#if 1
    Stratified_btn1->setFixedSize(btnSize);
    Stratified_btn1->setStyleSheet("QToolButton{border-image: url(Resources/icon/gis/MapSideIcon/btn_qxsc_n.png);border-style: flat;}"\
        "QToolButton:pressed{border-image: url(Resources/icon/gis/MapSideIcon/btn_qxsc_p.png);border-style: flat;}");

#endif
    QVBoxLayout * StratifiedLayout = new QVBoxLayout(StratifiedWdt);
   // QHBoxLayout * StratifiedLayout = new QHBoxLayout(StratifiedWdt);
    StratifiedLayout->addWidget(Stratified_btn1,1,Qt::AlignCenter);
    StratifiedLayout->addStretch(1);
    StratifiedLayout->addStretch(1);
	StratifiedLayout->setMargin(0);
	StratifiedLayout->setSpacing(0);

//##########################################################
    filterWdt = new QWidget; //筛选
    filter_btn1= new QToolButton;
#if 1
    filter_btn1->setFixedSize(btnSize);
    filter_btn1->setStyleSheet("QToolButton{border-image: url(Resources/icon/gis/MapSideIcon/btn_qxsc_n.png);border-style: flat;}"\
        "QToolButton:pressed{border-image: url(Resources/icon/gis/MapSideIcon/btn_qxsc_p.png);border-style: flat;}");

#endif
    QVBoxLayout * filterLayout = new QVBoxLayout(filterWdt);
   // QHBoxLayout * filterLayout = new QHBoxLayout(filterWdt);
    filterLayout->addWidget(filter_btn1,1,Qt::AlignCenter);
    filterLayout->addStretch(1);
    filterLayout->addStretch(1);
	filterLayout->setMargin(0);
	filterLayout->setSpacing(0);

//##########################################################
    measuringWdt = new QWidget; // 测量
    measure_btn1= new QToolButton;
    measure_btn2= new QToolButton;
	reset_btn3 = new QToolButton;
#if 1
    measure_btn1->setFixedSize(btnSize);
    measure_btn1->setStyleSheet("QToolButton{border-image: url(Resources/icon/gis/MapSideIcon/btn_dtcj_n.png);border-style: flat;}"\
        "QToolButton:pressed{border-image: url(Resources/icon/gis/MapSideIcon/btn_dtcj_p.png);border-style: flat;}");

     measure_btn2->setFixedSize(btnSize);
     measure_btn2->setStyleSheet("QToolButton{border-image: url(Resources/icon/gis/MapSideIcon/btn_dtmj_n.png);border-style: flat;}"\
         "QToolButton:pressed{border-image: url(Resources/icon/gis/MapSideIcon/btn_dtmj_p.png);border-style: flat;}");

	 reset_btn3->setFixedSize(btnSize);
	 reset_btn3->setStyleSheet("QToolButton{border-image: url(Resources/icon/gis/MapSideIcon/btn_czss_n.png);border-style: flat;}"\
		 "QToolButton:pressed{border-image: url(Resources/icon/gis/MapSideIcon/btn_czss_p.png);border-style: flat;}");

#endif
    QVBoxLayout * measureLayout = new QVBoxLayout(measuringWdt);
   // QHBoxLayout * measureLayout = new QHBoxLayout(measuringWdt);
    measureLayout->addWidget(measure_btn1,1,Qt::AlignCenter);
    measureLayout->addWidget(measure_btn2,1,Qt::AlignCenter);
	measureLayout->addWidget(reset_btn3,  1, Qt::AlignCenter);
	measureLayout->setMargin(0);
	measureLayout->setSpacing(0);


  //################

    this->addWidget(baseWdt);
    this->addWidget(StratifiedWdt);
    this->addWidget(filterWdt);
    this->addWidget(measuringWdt);


}

void RightChildWidget::connect_signal()
{
 //  connect(base_btn1,SIGNAL(clicked()),this,SLOT(base_btn1_on_clicked()));
 //  connect(base_btn2,SIGNAL(clicked()),this,SLOT(base_btn2_on_clicked()));
 //  connect(base_btn3,SIGNAL(clicked()),this,SLOT(base_btn3_on_clicked()));

}
//槽函数 #####################################

void RightChildWidget::base_btn1_on_clicked()
{
    setCurrentIndex(1);
}

void RightChildWidget::base_btn2_on_clicked()
{
    setCurrentIndex(2);
}

void RightChildWidget::base_btn3_on_clicked()
{
    setCurrentIndex(3);
}
