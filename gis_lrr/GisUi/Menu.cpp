#include "Menu.h"

Menu::Menu(QWidget * parent):QWidget(parent)
{
	BtnSize = QSize(100, 86);
	iconSize = QSize(70, 70);

	//设置样式
	this->setAutoFillBackground(true);
	QPalette p = this->palette();
	p.setColor(QPalette::Background, QColor(10, 22, 37));
	p.setColor(QPalette::ButtonText, QColor(255, 255, 255));
	this->setPalette(p);


	creat_ui();
	setlay();

}
Menu::~Menu(){

}

void Menu::creat_ui(void){
	
#if 0
	btn1 = new QToolButton;
	btn1->resize(BtnSize);
	btn1->setText("ZSJJQ");
	btn1->setIcon(QPixmap("Resources/icon/menuicon/01.png"));
	btn1->setIconSize(iconSize);
	//btn1->setFlat(true);
	//btn1->setFocusPolicy(Qt::NoFocus);//焦点框
	//btn1->setStyleSheet("border: 0px");//消除边框，取消点击效果

	btn2 = new QToolButton;
	btn2->setText(("BDXDKZ 1"));
	btn2->setIconSize(iconSize);
	btn2->setIcon(QPixmap("Resources/icon/menuicon/04.png"));
	btn2->setAutoRaise(true);
	btn2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	//  btn4->setStyleSheet("border: 0px");

	btn3 = new QToolButton;
	btn4 = new QToolButton;
	btn5 = new QToolButton;
	btn6 = new QToolButton;
	btn7 = new QToolButton;
	btn8 = new QToolButton;
	btn9 = new QToolButton;
#else


	//创建按钮
	btn1 = new QPushButton;
	btn2 = new QPushButton;
	btn3 = new QPushButton;
	btn4 = new QPushButton;
	btn5 = new QPushButton;
	btn6 = new QPushButton;
	
	btn7 = new QPushButton;
	btn8 = new QPushButton;
	btn9 = new QPushButton;

	// btn1->resize(BtnSize);
	QPixmap p1("Resources/icon/MapImages/1.bmp");
	btn1->setIcon(QIcon(p1));
	btn1->setIconSize(BtnSize);
	btn1->setFlat(true);
	// btn1->setFocusPolicy(Qt::NoFocus);//焦点框
	// btn1->setStyleSheet("border: 0px");//消除边框，取消点击效果
	//  btn1->setAttribute(Qt::WA_Disabled,true);//可能用来取消透明电极效果的
	//  btn1->setWindowFlags(Qt::Tool|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);

	// btn1->setFixedSize(BtnSize);//好像是用来固定大小的


	btn2->resize(BtnSize);
	QPixmap p2("Resources/icon/MapImages/2.bmp");
	btn2->setIcon(QIcon(p2));
	btn2->setIconSize(btn2->size());
	btn2->setFlat(true);
	//btn2->setFocusPolicy(Qt::NoFocus);//焦点框
	//btn2->setStyleSheet("border: 0px");//消除边框，取消点击效果

	btn3->resize(BtnSize);
	QPixmap p3("Resources/icon/MapImages/3.bmp");
	btn3->setIcon(QIcon(p3));
	btn3->setIconSize(btn3->size());
	btn3->setFlat(true);
	//btn3->setFocusPolicy(Qt::NoFocus);//焦点框
	//btn3->setStyleSheet("border: 0px");//消除边框，取消点击效果

	btn4->resize(BtnSize);
	QPixmap p4("Resources/icon/MapImages/4.bmp");
	btn4->setIcon(QIcon(p4));
	btn4->setIconSize(btn4->size());
	btn4->setFlat(true);
	// btn4->setFocusPolicy(Qt::NoFocus);//焦点框
	// btn4->setStyleSheet("border: 0px");//消除边框，取消点击效果


	btn5->resize(BtnSize);
	QPixmap p5("Resources/icon/MapImages/5.bmp");
	btn5->setIcon(QIcon(p5));
	btn5->setIconSize(btn5->size());
	btn5->setFlat(true);
	// btn5->setFocusPolicy(Qt::NoFocus);//焦点框
	// btn5->setStyleSheet("border: 0px");//消除边框，取消点击效果

	btn6->resize(BtnSize);
	QPixmap p6("Resources/icon/MapImages/6.bmp");
	btn6->setIcon(QIcon(p6));
	btn6->setIconSize(btn6->size());
	btn6->setFlat(true);
	// btn6->setFocusPolicy(Qt::NoFocus);//焦点框
	// btn6->setStyleSheet("border: 0px");//消除边框，取消点击效果

	btn7->resize(BtnSize);
	QPixmap p7("Resources/icon/MapImages/6.bmp");
	btn7->setIcon(QIcon(p7));
	btn7->setIconSize(btn7->size());
	btn7->setFlat(true);
	// btn7->setFocusPolicy(Qt::NoFocus);//焦点框
	// btn7->setStyleSheet("border: 0px");//消除边框，取消点击效果

	btn8->resize(BtnSize);
	QPixmap p8("Resources/icon/MapImages/6.bmp");
	btn8->setIcon(QIcon(p8));
	btn8->setIconSize(btn8->size());
	btn8->setFlat(true);
	// btn8->setFocusPolicy(Qt::NoFocus);//焦点框
	// btn8->setStyleSheet("border: 0px");//消除边框，取消点击效果

	btn9->resize(BtnSize);
	QPixmap p9("Resources/icon/MapImages/6.bmp");
	btn9->setIcon(QIcon(p9));
	btn9->setIconSize(btn9->size());
	btn9->setFlat(true);
	// btn9->setFocusPolicy(Qt::NoFocus);//焦点框
	// btn9->setStyleSheet("border: 0px");//消除边框，取消点击效果

#endif
	
}
//设置布局
void Menu::setlay(void){

	//QHBoxLayout *vlay = new QHBoxLayout(this);
	QVBoxLayout *vlay = new QVBoxLayout(this);
	vlay->addWidget(btn1,0,Qt::AlignCenter);
	vlay->addWidget(btn2, 0, Qt::AlignCenter);
	vlay->addWidget(btn3, 0, Qt::AlignCenter);
	vlay->addWidget(btn4, 0, Qt::AlignCenter);
	vlay->addWidget(btn5, 0, Qt::AlignCenter);
	vlay->addWidget(btn6, 0, Qt::AlignCenter);
	vlay->addWidget(btn7, 0, Qt::AlignCenter);
	vlay->addWidget(btn8, 0, Qt::AlignCenter);
	vlay->addWidget(btn9, 0, Qt::AlignCenter);
	vlay->setAlignment(Qt::AlignCenter);
}