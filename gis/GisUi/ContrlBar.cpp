#include "ContrlBar.h"

ContrlBar::ContrlBar(QWidget * parent) :QWidget(parent)
{
	iconSize = QSize(50, 50);
	btnSize = QSize(70, 70);

	//设置样式
	this->setAutoFillBackground(true);
	QPalette p = this->palette();
	p.setColor(QPalette::Background, QColor(45, 55, 61));
	p.setColor(QPalette::ButtonText, QColor(255, 255, 255));
	this->setPalette(p);

	create_iconList();
	creat_ui();
	setlayout();
	connect_signal();
    

}
ContrlBar::~ContrlBar()
{

}
void ContrlBar::creat_ui(void){
	//翻译器
	QTextCodec *codec = QTextCodec::codecForName("GBK");
	//按键样式 暂未使用
	QString sheetStyle = "QToolButton{background-color:rgb(10, 22, 37);color:rgb(255, 255, 255);border-radius:12px;border:2px groove \
						 						 		gray; border - style:outset; font: 75 12pt Ubuntu;}"\
														"QToolButton:hover{ background - color:white; color:black; }"\
														"QToolButton : pressed{ background - color:rgb(85, 170, 255); border - style:inset; }";
	//局部样式
	QString sheetStyle1 = "QPushButton{background-color:rgb(10, 22, 37);color:rgb(255, 255, 255);;border: 0px}";

	m_FirstBtn = new QToolButton(this);
	m_FirstBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	m_FirstBtn->setIcon(QPixmap(iconPathlist.at(0)).scaled(60,60));
	m_FirstBtn->setText(codec->toUnicode("画点"));
	m_FirstBtn->setAutoRaise(true);
	//m_FirstBtn->setStyleSheet("border-image: url(Resources/icon/MapImages/15.bmp)");
	m_FirstBtn->setStyleSheet("QToolButton{border: none; background: rgb(45, 55, 61); color: rgb(0, 160, 230);}");
	m_FirstBtn->resize(btnSize);


	 m_SecondBtn = new QToolButton;
	 m_SecondBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	 m_SecondBtn->setIcon(QPixmap(iconPathlist.at(1)).scaled(60, 60));
	 m_SecondBtn->setText(codec->toUnicode("起点"));
	 m_SecondBtn->setAutoRaise(true);
	// m_SecondBtn->setStyleSheet("border-image: url(Resources/icon/MapImages/15.bmp)");
	 m_SecondBtn->setStyleSheet("QToolButton{border: none; background: rgb(45, 55, 61); color: rgb(0, 160, 230);}");
	 m_SecondBtn->resize(btnSize); 

	 m_ThirdBtn = new QToolButton;
	 m_ThirdBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	 m_ThirdBtn->setIcon(QPixmap(iconPathlist.at(2)).scaled(60, 60));
	 m_ThirdBtn->setText(codec->toUnicode("中间点"));
	 m_ThirdBtn->setAutoRaise(true);
	 //m_ThirdBtn->setStyleSheet("border-image: url(Resources/icon/MapImages/15.bmp)");
	 m_ThirdBtn->setStyleSheet("QToolButton{border: none; background: rgb(45, 55, 61); color: rgb(0, 160, 230);}");
	 m_ThirdBtn->resize(btnSize);

	 m_FourthBtn = new QToolButton;
	 m_FourthBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	 m_FourthBtn->setIcon(QPixmap(iconPathlist.at(3)).scaled(60, 60));
	 m_FourthBtn->setText(codec->toUnicode("终点"));
	 m_FourthBtn->setAutoRaise(true);
	 //m_FourthBtn->setStyleSheet("border-image: url(Resources/icon/MapImages/15.bmp)");
	 m_FourthBtn->setStyleSheet("QToolButton{border: none; background: rgb(45, 55, 61); color: rgb(0, 160, 230);}");
	 m_FourthBtn->resize(btnSize);

	 m_FifthBtn = new QToolButton;
	 m_FifthBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	 m_FifthBtn->setIcon(QPixmap(iconPathlist.at(4)).scaled(60, 60));
	 m_FifthBtn->setText(codec->toUnicode("指挥车"));
	 m_FifthBtn->setAutoRaise(true);
	 //m_FifthBtn->setStyleSheet("border-image: url(Resources/icon/MapImages/15.bmp)");
	 m_FifthBtn->setStyleSheet("QToolButton{border: none; background: rgb(45, 55, 61); color: rgb(0, 160, 230);}");
	 m_FifthBtn->resize(btnSize);

	 m_SixBtn = new QToolButton;
	 m_SixBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	 m_SixBtn->setIcon(QPixmap(iconPathlist.at(5)).scaled(60, 60));
	 m_SixBtn->setText(codec->toUnicode("无人机"));
	 m_SixBtn->setAutoRaise(true);
	 //m_SixBtn->setStyleSheet("border-image: url(Resources/icon/MapImages/15.bmp)");
	 m_SixBtn->setStyleSheet("QToolButton{border: none; background: rgb(45, 55, 61); color: rgb(0, 160, 230);}");
	 m_SixBtn->resize(btnSize);

	 m_SeventhBtn = new QToolButton;
	 m_SeventhBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	 m_SeventhBtn->setIcon(QPixmap(iconPathlist.at(6)).scaled(60, 60));
	 m_SeventhBtn->setText(codec->toUnicode("轮巡"));
	 m_SeventhBtn->setAutoRaise(true);
	 //m_SeventhBtn->setStyleSheet("border-image: url(Resources/icon/MapImages/15.bmp)");
	 m_SeventhBtn->setStyleSheet("QToolButton{border: none; background: rgb(45, 55, 61); color: rgb(0, 160, 230);}");
	 m_SeventhBtn->resize(btnSize);

	 m_EighthBtn = new QToolButton;
	 m_EighthBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	 m_EighthBtn->setIcon(QPixmap(iconPathlist.at(7)).scaled(60, 60));
	 m_EighthBtn->setText(codec->toUnicode("履带"));
	 m_EighthBtn->setAutoRaise(true);
	 //m_EighthBtn->setStyleSheet("border-image: url(Resources/icon/MapImages/15.bmp)");
	 m_EighthBtn->setStyleSheet("QToolButton{border: none; background: rgb(45, 55, 61); color: rgb(0, 160, 230);}");
	 m_EighthBtn->resize(btnSize);

	 m_ninethBtn = new QToolButton;
	 m_ninethBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	 m_ninethBtn->setIcon(QPixmap(iconPathlist.at(8)).scaled(60, 60));
	 m_ninethBtn->setText(codec->toUnicode("轮式"));
	 m_ninethBtn->setAutoRaise(true);
	 //m_ninethBtn->setStyleSheet("border-image: url(Resources/icon/MapImages/15.bmp)");
	 m_ninethBtn->setStyleSheet("QToolButton{border: none; background: rgb(45, 55, 61); color: rgb(0, 160, 230);}");
	 m_ninethBtn->resize(btnSize);

}
//设置布局
void ContrlBar::setlayout(void){


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

void ContrlBar::connect_signal(void)
{

	connect(m_FirstBtn, SIGNAL(clicked()), this, SLOT(firstBtn_clicked()));
	connect(m_SecondBtn, SIGNAL(clicked()), this, SLOT(secondBtn_clicked()));
	connect(m_ThirdBtn, SIGNAL(clicked()), this, SLOT(thirdBtn_clicked()));
	connect(m_FourthBtn, SIGNAL(clicked()), this, SLOT(fourthBtn_clicked()));
	connect(m_FifthBtn, SIGNAL(clicked()), this, SLOT(fifthBtn_clicked()));
	connect(m_SixBtn, SIGNAL(clicked()), this, SLOT(sixthBtn_clicked()));
	connect(m_SeventhBtn, SIGNAL(clicked()), this, SLOT(seventhBtn_clicked()));
	connect(m_EighthBtn, SIGNAL(clicked()), this, SLOT(eighthBtn_clicked()));
	connect(m_ninethBtn, SIGNAL(clicked()), this, SLOT(ninthBtn_clicked()));
}
void ContrlBar::create_iconList()
{
	
	svgPathlist << "Resources/icon/gis/mkSvg/icon_bhtjd_2.svg"  //画点
		<< "Resources/icon/gis/mkSvg/icon_bhqd_1.svg"   //起点
		<< "Resources/icon/gis/mkSvg/icon_bhty_1.svg"   //中点
		<< "Resources/icon/gis/mkSvg/icon_bhzd_1.svg"   //终点
		<< "Resources/icon/gis/mkSvg/icon_bhzhc_1.svg"  //指挥车
		<< "Resources/icon/gis/mkSvg/icon_bhwrj_3.svg"  //无人机
		<< "Resources/icon/gis/mkSvg/icon_bhlx_3.svg"   //轮巡
		<< "Resources/icon/gis/mkSvg/icon_bhxld_13.svg" //履带
		<< "Resources/icon/gis/mkSvg/icon_bhls_3.svg"   //轮式
		<< "Resources/icon/gis/mkSvg/icon_bhld_3.svg"
		<< "Resources/icon/gis/mkSvg/icon_bhgdq_3.svg"
		<< "Resources/icon/gis/mkSvg/icon_bhspc_3.svg";

	iconPathlist << "Resources/icon/gis/mkPng/icon_bhtjd_2.png"  //画点
		<< "Resources/icon/gis/mkPng/icon_bhqd_1.png"   //起点
		<< "Resources/icon/gis/mkPng/icon_bhty_1.png"   //中点
		<< "Resources/icon/gis/mkPng/icon_bhzd_1.png"   //终点
		<< "Resources/icon/gis/mkPng/icon_bhzhc_1.png"  //指挥车
		<< "Resources/icon/gis/mkPng/icon_bhwrj_3.png"  //无人机
		<< "Resources/icon/gis/mkPng/icon_bhlx_3.png"   //轮巡
		<< "Resources/icon/gis/mkPng/icon_bhxld_13.png" //履带
		<< "Resources/icon/gis/mkPng/icon_bhls_3.png"   //轮式
		<< "Resources/icon/gis/mkPng/icon_bhld_3.png"
		<< "Resources/icon/gis/mkPng/icon_bhgdq_3.png"
		<< "Resources/icon/gis/mkPng/icon_bhspc_3.png";
}
void ContrlBar::setMarkerIcon(QString path)
{
	MarkerTool::setMarkerIconPath(path);
}

//############## btn clicked slot

void ContrlBar::firstBtn_clicked()
{
	setMarkerIcon(svgPathlist.at(0));
}
void ContrlBar::secondBtn_clicked()
{
	QString path = svgPathlist.at(1);
	if (path.isNull())
		return;
	setMarkerIcon(path);
	qDebug() << path;
	qDebug() << "second btn clidekd";
}
void ContrlBar::thirdBtn_clicked()
{
	QString path = svgPathlist.at(2);
	if (path.isNull())
		return;
	setMarkerIcon(path);
}
void ContrlBar::fourthBtn_clicked()
{
	QString path = svgPathlist.at(3);
	if (path.isNull())
		return;
	setMarkerIcon(path);

}
void ContrlBar::fifthBtn_clicked()
{
	QString path = svgPathlist.at(4);
	if (path.isNull())
		return;
	setMarkerIcon(path);
}
void ContrlBar::sixthBtn_clicked()
{
	QString path = svgPathlist.at(5);
	if (path.isNull())
		return;
	setMarkerIcon(path);
}
void ContrlBar::seventhBtn_clicked()
{
	QString path = svgPathlist.at(6);
	if (path.isNull())
		return;
	setMarkerIcon(path);
}
void ContrlBar::eighthBtn_clicked()
{
	QString path = svgPathlist.at(7);
	if (path.isNull())
		return;
	setMarkerIcon(path);
}
void ContrlBar::ninthBtn_clicked()
{
	QString path = svgPathlist.at(8);
	if (path.isNull())
		return;
	setMarkerIcon(path);
}

