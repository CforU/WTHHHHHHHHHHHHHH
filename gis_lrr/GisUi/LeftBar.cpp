#include "LeftBar.h"

LeftBar::LeftBar(QWidget * parent) :QWidget(parent)
{
	iconSize = QSize(50,50);
	btnSize = QSize(85,80);

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
LeftBar::~LeftBar()
{

}
void LeftBar::creat_ui(void){
	//翻译器
	QTextCodec *codec = QTextCodec::codecForName("GBK");
	//按键样式 暂未使用
	QString sheetStyle = "QToolButton{background-color:rgb(10, 22, 37);color:rgb(255, 255, 255);border-radius:12px;border:2px groove \
						 						 		gray; border - style:outset; font: 75 12pt Ubuntu;}"\
														"QToolButton:hover{ background - color:white; color:black; }"\
														"QToolButton : pressed{ background - color:rgb(85, 170, 255); border - style:inset; }";
	//局部样式
	//QString btn1SheetStyle1 = "QPushButton{background-color:rgb(10, 22, 37);color:rgb(255, 255, 255);;border: 0px}";

	m_FirstBtn = new QToolButton(this);
	m_FirstBtn->setFixedSize(btnSize);
	m_FirstBtn->setStyleSheet("QToolButton{border-image: url(Resources/icon/gis/MapSideIcon/btn_ss_n.png);border-style: flat;}"\
		"QToolButton:pressed{border-image: url(Resources/icon/gis/MapSideIcon/btn_ss_p.png);border-style: flat;}"\
		"QToolButton:checked{border-image:url(Resources/icon/gis/MapSideIcon/btn_ss_p.png);border-style: flat;}");

	//m_FirstBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	//m_FirstBtn->setIcon(QPixmap("Resources/icon/gis/MapSideIcon/btn_dtwdwz_p.png"));
	//m_FirstBtn->setIconSize(btnSize);
	//m_FirstBtn->setText(codec->toUnicode("搜索"));
	//m_FirstBtn->setAutoRaise(true);
	//m_FirstBtn->setStyleSheet("border-image: url(Resources/icon/MapImages/15.bmp)");
	//m_FirstBtn->setStyleSheet("QToolButton{border: none; background: rgb(68, 69, 73); color: rgb(0, 160, 230);}");
	//m_FirstBtn->resize(btnSize);
	
	/*
	m_FirstBtn->setStyleSheet("QToolButton{border-image: url(Resources/icon/gis/MapSideIcon/btn_dtwdwz_n.png);}\
			  	QToolButton : pressed{ border-image: url(Resources/icon/gis/MapSideIcon/btn_dtwdwz_p.png);}");
				*/
	//m_FirstBtn->setStyleSheet("background:url(Resources/icon/gis/MapSideIcon/btn_dtwdwz_p.png)"); 
	//QString firstStyle = "QToolButton{background-color:rgb(10, 22, 37);color:rgb(255, 255, 255);border-radius:12px;border:2px groove \
						 gray; border - style:outset; font: 75 12pt Ubuntu;}"\
						"QToolButton:hover{ background - color:white; color:black; }"\
						"QToolButton : pressed{ background - color:rgb(85, 170, 255); border - style:inset; }";


	 m_SecondBtn = new QToolButton;
	 m_SecondBtn->setFixedSize(btnSize);
	 m_SecondBtn->setStyleSheet("QToolButton{border-image: url(Resources/icon/gis/MapSideIcon/btn_dtlj_n.png);border-style: flat;}"\
		 "QToolButton:pressed{border-image: url(Resources/icon/gis/MapSideIcon/btn_dtlj_p.png);border-style: flat;}"\
		 "QToolButton:checked{border-image:url(Resources/icon/gis/MapSideIcon/btn_dtlj_p.png);border-style: flat;}");

	 /*
	 m_SecondBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	 m_SecondBtn->setIcon(QPixmap("Resources/icon/MapImages/16.bmp").scaled(50,50));
	 m_SecondBtn->setText(codec->toUnicode("路径"));
	 m_SecondBtn->setAutoRaise(true);
	// m_SecondBtn->setStyleSheet("border-image: url(Resources/icon/MapImages/15.bmp)");
	 m_SecondBtn->setStyleSheet("QToolButton{border: none; background: rgb(68, 69, 73); color: rgb(0, 160, 230);}");
	 m_SecondBtn->resize(btnSize); 
	 */

	 m_ThirdBtn = new QToolButton;
	 m_ThirdBtn->setFixedSize(btnSize);
	 m_ThirdBtn->setStyleSheet("QToolButton{border-image: url(Resources/icon/gis/MapSideIcon/btn_dtdr_n.png);border-style: flat;}"\
		 "QToolButton:pressed{border-image: url(Resources/icon/gis/MapSideIcon/btn_dtdr_p.png);border-style: flat;}"\
		 "QToolButton:checked{border-image:url(Resources/icon/gis/MapSideIcon/btn_dtdr_p.png);border-style: flat;}");


	 m_FourthBtn = new QToolButton;
	 m_FourthBtn->setFixedSize(btnSize);
	 m_FourthBtn->setStyleSheet("QToolButton{border-image: url(Resources/icon/gis/MapSideIcon/btn_dtdt_n.png);border-style: flat;}"\
		 "QToolButton:pressed{border-image: url(Resources/icon/gis/MapSideIcon/btn_dtdt_p.png);border-style: flat;}"\
		 "QToolButton:checked{border-image:url(Resources/icon/gis/MapSideIcon/btn_dtdt_p.png);border-style: flat;}");


	 m_FifthBtn = new QToolButton;
	 m_FifthBtn->setFixedSize(btnSize);
	 m_FifthBtn->setStyleSheet("QToolButton{border-image: url(Resources/icon/gis/MapSideIcon/btn_dtwdwz_n.png);border-style: flat;}"\
		 "QToolButton:pressed{border-image: url(Resources/icon/gis/MapSideIcon/btn_dtwdwz_p.png);border-style: flat;}");


	 m_SixBtn = new QToolButton;
	 m_SixBtn->setFixedSize(btnSize);
	 m_SixBtn->setStyleSheet("QToolButton{border-image: url(Resources/icon/gis/MapSideIcon/btn_dtfd_n.png);border-style: flat;}"\
		 "QToolButton:pressed{border-image: url(Resources/icon/gis/MapSideIcon/btn_dtfd_p.png);border-style: flat;}"\
		 "QToolButton:checked{border-image:url(Resources/icon/gis/MapSideIcon/btn_dtfd_p.png);border-style: flat;}");


	 m_SeventhBtn = new QToolButton;
	 m_SeventhBtn->setFixedSize(btnSize);
	 m_SeventhBtn->setStyleSheet("QToolButton{border-image: url(Resources/icon/gis/MapSideIcon/btn_dtsxxs_n.png);border-style: flat;}"\
		 "QToolButton:pressed{border-image: url(Resources/icon/gis/MapSideIcon/btn_dtsxxs_p.png);border-style: flat;}"\
		 "QToolButton:checked{border-image:url(Resources/icon/gis/MapSideIcon/btn_dtsxxs_p.png);border-style: flat;}");


	 m_EighthBtn = new QToolButton;
	 m_EighthBtn->setFixedSize(btnSize);
	 m_EighthBtn->setStyleSheet("QToolButton{border-image: url(Resources/icon/gis/MapSideIcon/btn_dttd_n.png);border-style: flat;}"\
		 "QToolButton:pressed{border-image: url(Resources/icon/gis/MapSideIcon/btn_dttd_p.png);border-style: flat;}"\
		 "QToolButton:checked{border-image:url(Resources/icon/gis/MapSideIcon/btn_dttd_p.png);border-style: flat;}");


	 m_ninethBtn = new QToolButton;
	 m_ninethBtn->setFixedSize(btnSize);
	 m_ninethBtn->setStyleSheet("QToolButton{border-image: url(Resources/icon/gis/MapSideIcon/btn_dtbh_n.png);border-style: flat;}"\
		 "QToolButton:pressed{border-image: url(Resources/icon/gis/MapSideIcon/btn_dtbh_p.png);border-style: flat;}"\
		 "QToolButton:checked{border-image:url(Resources/icon/gis/MapSideIcon/btn_dtbh_p.png);border-style: flat;}");

}
//设置布局
void LeftBar::setlayout(void){

	QVBoxLayout *vlay = new QVBoxLayout(this);
	vlay->setMargin(0);
	vlay->setSpacing(0);
	vlay->addWidget(m_FirstBtn, 0, Qt::AlignCenter);
	vlay->addWidget(m_SecondBtn, 0, Qt::AlignCenter);
	vlay->addWidget(m_ThirdBtn, 0, Qt::AlignCenter);
	vlay->addWidget(m_FourthBtn, 0, Qt::AlignCenter);
	vlay->addWidget(m_FifthBtn, 0, Qt::AlignCenter);
	vlay->addWidget(m_SixBtn, 0, Qt::AlignCenter);
	vlay->addWidget(m_SeventhBtn, 0, Qt::AlignCenter);
	vlay->addWidget(m_EighthBtn, 0, Qt::AlignCenter);
	vlay->addWidget(m_ninethBtn, 0, Qt::AlignCenter);
	
}

void LeftBar::connect_signal(void)
{
	
}















