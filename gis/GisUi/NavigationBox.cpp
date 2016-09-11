
#include "NavigationBox.h"

NavigationBox::NavigationBox(QWidget *parent) :
QWidget(parent)
{
	//初始化 大小信息
	baseWidgetSize = QSize(250, 40);
	deatilWidgetSize = QSize(160, 100);
	MainEditsize = QSize(250, 40);
	EditSize = QSize(160, 40);
	//调整大小和位置
	this->resize(baseSize());
	//ui 
	create_BaseWidget();
	create_DeatilWidget();
	//layout
	set_layout();
	
	//设置窗体属性
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);//去掉标题栏 
	this->setAttribute(Qt::WA_ContentsPropagated, true);
	this->setAttribute(Qt::WA_TranslucentBackground, true);
	this->setAutoFillBackground(true);
	// this->raise();

}

//创建导航框界面
void NavigationBox::create_BaseWidget()
{

}

//下拉框地图 路线提示 暂不实现
void NavigationBox::create_DeatilWidget()
{

	deatilWidget = new QWidget;
	m_FromEdit = new QLineEdit;
	m_ToEdit = new QLineEdit;
	m_LeftLab = new QLabel;
	m_MidLine = new QLine;
	m_RightBtn = new QPushButton;

	deatilWidget->hide();

}

void NavigationBox::set_layout()
{
	QVBoxLayout *mainlay = new QVBoxLayout;
	mainlay->addWidget(baseWidget);
	mainlay->addWidget(deatilWidget);
	mainlay->setSizeConstraint(QLayout::SetFixedSize);//设置窗体固定大小 不能拖拽改变
	mainlay->setSpacing(0);
	mainlay->setMargin(0);
	this->setLayout(mainlay);
}

void NavigationBox::search_route()
{

}

void NavigationBox::search()
{

}



