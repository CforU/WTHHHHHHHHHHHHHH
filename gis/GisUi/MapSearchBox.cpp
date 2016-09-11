#include "MapSearchBox.h"

MapSearchBox::MapSearchBox(QWidget *parent) :
    QWidget(parent)
{

    baseWidgetSize = QSize(250,40);
    deatilWidgetSize = QSize(160,100);
    MainEditsize = QSize(250,40);
    EditSize = QSize(160,40);

    this->resize(baseSize());

	//ui and layout
	create_BaseWidget();
	create_DeatilWidget();
	QVBoxLayout *mainlay = new QVBoxLayout;
	mainlay->addWidget(baseWidget);
	mainlay->addWidget(deatilWidget);
	mainlay->setSizeConstraint(QLayout::SetFixedSize);//设置窗体固定大小 不能拖拽改变
	mainlay->setSpacing(0);
	mainlay->setMargin(0);
	this->setLayout(mainlay);

	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);//去掉标题栏 
	this->setAttribute( Qt::WA_ContentsPropagated, true);
	this->setAttribute(Qt::WA_TranslucentBackground, true);
	this->setAutoFillBackground(true);
   // this->raise();




}

void MapSearchBox::create_BaseWidget()
{
     baseWidget = new QWidget;
     m_MainEdit = new QLineEdit;
     m_routebtn = new QPushButton;
     m_searchbtn = new QPushButton;

     //初始化样式
     m_MainEdit->setFixedSize(MainEditsize);
     //m_MainEdit->setFont();



     m_routebtn->setFixedSize(40, 40);
     m_routebtn->setToolTip(tr("路线"));
     m_routebtn->setCursor(Qt::PointingHandCursor);//设置鼠标形状
     m_routebtn->setStyleSheet("QPushButton{border-image:url(icon/jiantou.png); background:transparent;}");

     m_searchbtn->setFixedSize(40, 40);
     m_searchbtn->setToolTip(tr("搜索"));
     m_searchbtn->setCursor(Qt::PointingHandCursor);//设置鼠标形状
     m_searchbtn->setStyleSheet("QPushButton{border-image:url(icon/sousuo.png); background:transparent;}");


     //防止文本框输入内容位于按钮之下
   // QMargins margins = m_MainEdit->textMargins();
   //  m_MainEdit->setTextMargins(margins.left(), margins.top(), m_MainEdit->width(), margins.bottom());
   //  m_pSearchLineEdit->setPlaceholderText(QStringLiteral(" 请输入搜索内容 \n"));
	 m_MainEdit->setPlaceholderText(QString(tr(" 请输入搜索内容\r\n")));



     //布局

     QHBoxLayout *hlay  = new QHBoxLayout;
     hlay->addWidget(m_MainEdit);
     hlay->addWidget(m_routebtn);
     hlay->addWidget(m_searchbtn);
     hlay->setSpacing(0);
     hlay->setContentsMargins(0, 0, 0, 0);

     baseWidget->setLayout(hlay);

     //型号和槽函数连接
     connect(m_routebtn, SIGNAL(clicked(bool)), this, SLOT(search_route()));
     connect(m_searchbtn, SIGNAL(clicked(bool)), this, SLOT(search()));


}
//下拉框地图路线搜索 暂不实现
void MapSearchBox::create_DeatilWidget()
{

    deatilWidget = new QWidget;
    m_FromEdit = new QLineEdit;
    m_ToEdit   = new QLineEdit;
    m_LeftLab = new QLabel;
    m_MidLine = new QLine;
    m_RightBtn = new QPushButton;


    deatilWidget->hide();

}

void MapSearchBox::search_route()
{

}

void MapSearchBox::search()
{

    /*
    QString strText = m_MainEdit->text();
       if (!strText.isEmpty())
       {
         //  QMessageBox::information(this, QStringLiteral("搜索"), QStringLiteral("搜索内容为%1").arg(strText));
            QMessageBox::information(this, tr("搜索"), tr("搜索内容为%1").arg(strText));
       }
    */

}


