
#include "NavigationBox.h"

NavigationBox::NavigationBox(QWidget *parent) :
QWidget(parent)
{
	//��ʼ�� ��С��Ϣ
	baseWidgetSize = QSize(250, 40);
	deatilWidgetSize = QSize(160, 100);
	MainEditsize = QSize(250, 40);
	EditSize = QSize(160, 40);
	//������С��λ��
	this->resize(baseSize());
	//ui 
	create_BaseWidget();
	create_DeatilWidget();
	//layout
	set_layout();
	
	//���ô�������
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);//ȥ�������� 
	this->setAttribute(Qt::WA_ContentsPropagated, true);
	this->setAttribute(Qt::WA_TranslucentBackground, true);
	this->setAutoFillBackground(true);
	// this->raise();

}

//�������������
void NavigationBox::create_BaseWidget()
{

}

//�������ͼ ·����ʾ �ݲ�ʵ��
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
	mainlay->setSizeConstraint(QLayout::SetFixedSize);//���ô���̶���С ������ק�ı�
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



