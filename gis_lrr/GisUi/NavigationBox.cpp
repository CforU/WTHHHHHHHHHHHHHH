
#include "NavigationBox.h"
#include <QPalette>

NavigationBox::NavigationBox(QWidget *parent):QWidget(parent)
{

	//ui 
    create_ui();
	
	//设置窗体属性

}

void NavigationBox::create_ui()
{
    //初始化 大小信息
    baseWidgetSize = QSize(250, 40);
    deatilWidgetSize = QSize(160, 100);
    MainEditsize = QSize(250, 40);
    EditSize = QSize(160, 40);
    //调整大小和位置
    //this->resize(baseSize());

    create_BaseWidget();
  //  set_layout();
  //  create_DeatilWidget();
 //   create_ControlWidget();
 //   create_CollectWidget();



}

//创建导航框界面
void NavigationBox::create_BaseWidget()
{

    baseWidget = new QWidget(this);
    //设置样式
    this->setAutoFillBackground(true);
    QPalette p = this->palette();
    p.setColor(QPalette::Background, QColor(87, 105, 115));
    p.setColor(QPalette::ButtonText, QColor(255, 255, 255));
    this->setPalette(p);

    if (baseWidget->objectName().isEmpty())
              baseWidget->setObjectName(QStringLiteral("baseWidget"));

      //name
      mNameLab = new QLabel(baseWidget);
      mNameLab->setObjectName(QStringLiteral("mNameLab"));
      //mNameLab->setGeometry(16,20,110,20);
      mNameLab->setText("履带-012345");
      //路径收藏
      mMyRoute = new QToolButton(baseWidget);
      mMyRoute->setObjectName(QStringLiteral("mMyRoute"));
      mMyRoute->setText("我的路径");



      mFromLab = new QLabel(baseWidget);
      mFromLab->setObjectName(QStringLiteral("mFromLab"));
      mFromLab->setText("从");
      mToLab = new QLabel(baseWidget);
      mToLab->setObjectName(QStringLiteral("mToLab"));
      mToLab->setText("到");
#if 0
      addBtn = new QPushButton(baseWidget);
      addBtn->setObjectName(QStringLiteral("pushButton_2"));
      addBtn->setFixedSize(20,20);
#endif
      mFromEdit = new QLineEdit(baseWidget);
      mFromEdit->setObjectName(QStringLiteral("mFromEdit"));
      mToEdit = new QLineEdit(baseWidget);
      mToEdit->setObjectName(QStringLiteral("mToEdit"));
      mLine = new QFrame(baseWidget);
      mLine->setObjectName(QStringLiteral("line"));
      mLine->setFrameShape(QFrame::HLine);
      mLine->setFrameShadow(QFrame::Plain);
      mLine->setBackgroundRole(QPalette::Background);

      mLine_2 = new QFrame(baseWidget);
      mLine_2->setObjectName(QStringLiteral("line_2"));
      mLine_2->setFrameShape(QFrame::HLine);
      mLine_2->setFrameShadow(QFrame::Plain);

      mSearch = new QPushButton(baseWidget);
      mSearch->setObjectName(QStringLiteral("mSearch"));
      mSearch->setFixedSize(40,40);




      //布局
      //第一排
    QHBoxLayout *vlay = new QHBoxLayout;
    vlay->addWidget(mNameLab);
    vlay->addStretch(2);
    vlay->addWidget(mMyRoute);

    //第二排 左边
     QGridLayout *glay = new QGridLayout;
     glay->addWidget(mFromLab,0,0,1,1,Qt::AlignCenter);
     glay->addWidget(mFromEdit,0,1,1,6);

     glay->addWidget(mLine,1,1,1,6);

     glay->addWidget(mToLab,2,0,1,1,Qt::AlignCenter);
     glay->addWidget(mToEdit,2,1,1,6);

     glay->addWidget(mLine_2,3,1,1,6);

     //下边一排
     QHBoxLayout *vlay1 = new QHBoxLayout;
     vlay1->addLayout(glay,7);
     vlay1->addWidget(mSearch,2);

    //总布局
    QVBoxLayout *hlay = new QVBoxLayout(baseWidget);
    hlay->addLayout(vlay);
    hlay->addLayout(vlay1);

     baseWidget->resize(358,154);


}

//下拉框地图 路线提示 暂不实现
void NavigationBox::create_DeatilWidget()
{
#if 0
	deatilWidget = new QWidget;
	m_FromEdit = new QLineEdit;
	m_ToEdit = new QLineEdit;
	m_LeftLab = new QLabel;
	m_MidLine = new QLine;
	m_RightBtn = new QPushButton;

	deatilWidget->hide();
#endif
}

void NavigationBox::create_ControlWidget()
{

}

void NavigationBox::create_CollectWidget()
{

}

void NavigationBox::set_layout()
{
//	QVBoxLayout *mainlay = new QVBoxLayout;
//	mainlay->addWidget(baseWidget);
    //mainlay->addWidget(deatilWidget);
//	mainlay->setSizeConstraint(QLayout::SetFixedSize);//设置窗体固定大小 不能拖拽改变
//	mainlay->setSpacing(0);
//	mainlay->setMargin(0);
//	this->setLayout(mainlay);
}

void NavigationBox::search_route()
{

}

void NavigationBox::search()
{

}



