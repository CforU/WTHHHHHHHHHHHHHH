#include "MarkerBar.h"

MarkerBar::MarkerBar(QWidget * parent) :QWidget(parent)
{
	iconSize = QSize(85,85);
	btnSize = QSize(110,86);

	//设置样式
	this->setAutoFillBackground(true);
	QPalette p = this->palette();
	p.setColor(QPalette::Background, QColor(45, 55, 61));
	p.setColor(QPalette::ButtonText, QColor(255, 255, 255));
	this->setPalette(p);

	
	creat_ui();
	setlay();
	connect_signal();


}
MarkerBar::~MarkerBar()
{

}
void MarkerBar::creat_ui(void){
	topBtn = new QPushButton;//向上按钮
	topBtn->setIcon(QIcon(QPixmap("Resources/icon/MapImages/up.bmp")));
	topBtn->setIconSize(iconSize);
	topBtn->resize(btnSize);
	topBtn->setFlat(true);
	//topBtn->setStyleSheet("border: 0px");

	baseWgt = new QWidget(this);
	menuArea = new QScrollArea(baseWgt);
	menu = new Menu;
	menu->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	menuArea->setWidget(menu);
	menuArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	menuArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//menuArea->setCornerWidget(menu); //?
	//menuArea->setMidLineWidth(0);  //?
	//menuArea->setMinimumSize(QSize(120, 450));
	menuArea->setWidgetResizable(true);
	menuArea->setFixedSize(120,400);
	menuArea->setFrameShape(QFrame::NoFrame);

	botomBtn = new QPushButton;//向下按钮
	botomBtn->setIcon(QIcon(QPixmap("Resources/icon/MapImages/down.bmp")));
	botomBtn->setIconSize(iconSize);
	botomBtn->resize(btnSize);
	botomBtn->setFlat(true);
	//botomBtn->setStyleSheet("border: 0px");

}
//设置布局
void MarkerBar::setlay(void){

	QVBoxLayout *vlay = new QVBoxLayout(this);
	vlay->addWidget(topBtn);
	vlay->addWidget(baseWgt);
	vlay->addWidget(botomBtn);
	
}

void MarkerBar::connect_signal(void)
{
	connect(topBtn, SIGNAL(clicked()), this, SLOT(on_Up()));
	connect(botomBtn, SIGNAL(clicked()), this, SLOT(on_Down()));
	
}

//向上滚动
void MarkerBar::on_Up(void)
{
	if (scrolValue>menuArea->verticalScrollBar()->maximumHeight() )
		scrolValue += 50;
	//menuArea->scroll(0,100);//这个是滚动去整体滚动
	//menuArea->ensureVisible(0, scrolValue);
	//this->MarkerBar->menuArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);  //不知道效果
	//menuArea->scrollContentsBy(100, 100);//保护的 外部无法使用
	//this->MarkerBar->menuArea->horizontalScrollBar()->setValue(200); //左右 水平方向
	//this->MarkerBar->menuArea->verticalScrollBar()->setValue(100);//可以设置到具体的值 垂直上下方向
	//this->MarkerBar->menuArea->ensureVisible(0, 200);//向下滚动
	//this->MarkerBar->menuArea->ensureVisible(0, 200); //向下滚动

	//menuArea->ensureVisible(0, 100);
	menuArea->verticalScrollBar()->setValue(scrolValue);
}
//向下滚动
void MarkerBar::on_Down(void)
{
	if (scrolValue>50)
		scrolValue -= 50;
	menuArea->verticalScrollBar()->setValue(scrolValue);
	//menuArea->ensureVisible(0, scrolValue);
}














