#include "RightBar.h"

RightBar::RightBar(QWidget * parent) :QWidget(parent)
{
	iconSize = QSize(50,50);
	btnSize = QSize(70,70);

	//设置样式
	this->setAutoFillBackground(true);
	QPalette p = this->palette();
	p.setColor(QPalette::Background, QColor(45, 55, 61));
	p.setColor(QPalette::ButtonText, QColor(255, 255, 255));
	this->setPalette(p);

	creat_ui();
	setlayout();
	connect_signal();

}
RightBar::~RightBar()
{

}
void RightBar::creat_ui(void){
	//翻译器
	QTextCodec *codec = QTextCodec::codecForName("GBK");
	//按键样式 暂未使用
	QString sheetStyle = "QToolButton{background-color:rgb(10, 22, 37);color:rgb(255, 255, 255);border-radius:12px;border:2px groove \
						 						 		gray; border - style:outset; font: 75 12pt Ubuntu;}"\
														"QToolButton:hover{ background - color:white; color:black; }"\
														"QToolButton : pressed{ background - color:rgb(85, 170, 255); border - style:inset; }";
	//局部样式
	QString sheetStyle1 = "QPushButton{background-color:rgb(10, 22, 37);color:rgb(255, 255, 255);;border: 0px}";
#if 0
	m_FirstBtn = new QToolButton(this);
	m_FirstBtn->setFixedSize(btnSize);
	m_FirstBtn->setStyleSheet("QToolButton{border-image: url(Resources/icon/gis/MapSideIcon/btn_dtfc_n.png);border-style: flat;}"\
		"QToolButton:pressed{border-image: url(Resources/icon/gis/MapSideIcon/btn_dtfc_p.png);border-style: flat;}");



	 m_SecondBtn = new QToolButton;
	 m_SecondBtn->setFixedSize(btnSize);
	 m_SecondBtn->setStyleSheet("QToolButton{border-image: url(Resources/icon/gis/MapSideIcon/btn_dtsx_n.png);border-style: flat;}"\
		 "QToolButton:pressed{border-image: url(Resources/icon/gis/MapSideIcon/btn_dtsx_p.png);border-style: flat;}");


	 m_ThirdBtn = new QToolButton;
	 m_ThirdBtn->setFixedSize(btnSize);
	 m_ThirdBtn->setStyleSheet("QToolButton{border-image: url(Resources/icon/gis/MapSideIcon/btn_dtcl_n.png);border-style: flat;}"\
		 "QToolButton:pressed{border-image: url(Resources/icon/gis/MapSideIcon/btn_dtcl_p.png);border-style: flat;}");
#else
	 childWdt = new RightChildWidget;
#endif
	 m_FourthBtn = new QToolButton;
	 m_FourthBtn->setFixedSize(btnSize);
	 m_FourthBtn->setStyleSheet("QToolButton{border-image: url(Resources/icon/gis/MapSideIcon/btn_left_n.png);border-style: flat;}"\
		 "QToolButton:pressed{border-image: url(Resources/icon/gis/MapSideIcon/btn_left_p.png);border-style: flat;}");


	 m_FifthBtn = new QToolButton;
	 m_FifthBtn->setFixedSize(btnSize);
	 m_FifthBtn->setStyleSheet("QToolButton{border-image: url(Resources/icon/gis/MapSideIcon/btn_right_n.png);border-style: flat;}"\
		 "QToolButton:pressed{border-image: url(Resources/icon/gis/MapSideIcon/btn_right_p.png);border-style: flat;}");


	 m_SixBtn = new QToolButton;
	 m_SixBtn->setFixedSize(btnSize);
	 m_SixBtn->setStyleSheet("QToolButton{border-image: url(Resources/icon/gis/MapSideIcon/btn_up_n.png);border-style: flat;}"\
		 "QToolButton:pressed{border-image: url(Resources/icon/gis/MapSideIcon/btn_up_p.png);border-style: flat;}");


	 m_SeventhBtn = new QToolButton;
	 m_SeventhBtn->setFixedSize(btnSize);
	 m_SeventhBtn->setStyleSheet("QToolButton{border-image: url(Resources/icon/gis/MapSideIcon/btn_down_n.png);border-style: flat;}"\
		 "QToolButton:pressed{border-image: url(Resources/icon/gis/MapSideIcon/btn_down_p.png);border-style: flat;}");


	 m_EighthBtn = new QToolButton;
	 m_EighthBtn->setFixedSize(btnSize);
	 m_EighthBtn->setStyleSheet("QToolButton{border-image: url(Resources/icon/gis/MapSideIcon/btn_enter_n.png);border-style: flat;}"\
		 "QToolButton:pressed{border-image: url(Resources/icon/gis/MapSideIcon/btn_enter_p.png);border-style: flat;}");


	 m_ninethBtn = new QToolButton;
	 m_ninethBtn->setFixedSize(btnSize);
	 m_ninethBtn->setStyleSheet("QToolButton{border-image: url(Resources/icon/gis/MapSideIcon/btn_cancel_n.png);border-style: flat;}"\
		 "QToolButton:pressed{border-image: url(Resources/icon/gis/MapSideIcon/btn_cancel_p.png);border-style: flat;}");

}
//设置布局
void RightBar::setlayout(void){

	QVBoxLayout *vlay = new QVBoxLayout(this);
	vlay->setMargin(0);
	vlay->setSpacing(0);
#if 0
	vlay->addWidget(m_FirstBtn, 0, Qt::AlignCenter);
	vlay->addWidget(m_SecondBtn, 0, Qt::AlignCenter);
	vlay->addWidget(m_ThirdBtn, 0, Qt::AlignCenter);
#else
	vlay->addWidget(childWdt, 3, Qt::AlignCenter);
	
#endif
	vlay->addWidget(m_FourthBtn, 1, Qt::AlignCenter);
	vlay->addWidget(m_FifthBtn, 1, Qt::AlignCenter);
	vlay->addWidget(m_SixBtn, 1, Qt::AlignCenter);
	vlay->addWidget(m_SeventhBtn, 1, Qt::AlignCenter);
	vlay->addWidget(m_EighthBtn, 1, Qt::AlignCenter);
	vlay->addWidget(m_ninethBtn, 1, Qt::AlignCenter);
	
}

void RightBar::connect_signal(void)
{
	
}















