#include "MarkerBar.h"

MarkerBar::MarkerBar(QWidget * parent) :QWidget(parent)
{
	iconSize = QSize(85,85);
	btnSize = QSize(110,86);

	//������ʽ
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
	topBtn = new QPushButton;//���ϰ�ť
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

	botomBtn = new QPushButton;//���°�ť
	botomBtn->setIcon(QIcon(QPixmap("Resources/icon/MapImages/down.bmp")));
	botomBtn->setIconSize(iconSize);
	botomBtn->resize(btnSize);
	botomBtn->setFlat(true);
	//botomBtn->setStyleSheet("border: 0px");

}
//���ò���
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

//���Ϲ���
void MarkerBar::on_Up(void)
{
	if (scrolValue>menuArea->verticalScrollBar()->maximumHeight() )
		scrolValue += 50;
	//menuArea->scroll(0,100);//����ǹ���ȥ�������
	//menuArea->ensureVisible(0, scrolValue);
	//this->MarkerBar->menuArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);  //��֪��Ч��
	//menuArea->scrollContentsBy(100, 100);//������ �ⲿ�޷�ʹ��
	//this->MarkerBar->menuArea->horizontalScrollBar()->setValue(200); //���� ˮƽ����
	//this->MarkerBar->menuArea->verticalScrollBar()->setValue(100);//�������õ������ֵ ��ֱ���·���
	//this->MarkerBar->menuArea->ensureVisible(0, 200);//���¹���
	//this->MarkerBar->menuArea->ensureVisible(0, 200); //���¹���

	//menuArea->ensureVisible(0, 100);
	menuArea->verticalScrollBar()->setValue(scrolValue);
}
//���¹���
void MarkerBar::on_Down(void)
{
	if (scrolValue>50)
		scrolValue -= 50;
	menuArea->verticalScrollBar()->setValue(scrolValue);
	//menuArea->ensureVisible(0, scrolValue);
}














