#include "MapSearchBox.h"

MapSearchBox::MapSearchBox(QWidget *parent) :
    QWidget(parent)
{ 
	createSearchBox();
	//this->resize(baseSize());

}

void MapSearchBox::createSearchBox()
{
	QTextCodec *codec = QTextCodec::codecForName("GBK");

	mBSize = QSize(250, 40);
	mSSize = QSize(200, 40);
	mSsize = QSize(40, 40);


	mInsertEdit = new QLineEdit;
	mSBtn = new QPushButton;

     //初始化样式
	mInsertEdit->setFixedSize(mSSize);
    //m_MainEdit->setFont();

	 mSBtn->setFixedSize(43, 43);
	 mSBtn->setToolTip(tr("搜索"));
	 mSBtn->setCursor(Qt::PointingHandCursor);//设置鼠标形状
	 mSBtn->setIcon(QIcon("Resources/icon/gis/MapSideIcon/btn_ss_n.png"));
	 mSBtn->setIconSize(QSize(43, 43));
   //  m_searchbtn->setStyleSheet("QPushButton{border-image: url(Resources/icon/gis/MapSideIcon/btn_ss_p.png); background:transparent;}");
	// "QToolButton:pressed{border-image: url(Resources/icon/gis/MapSideIcon/btn_ss_p.png);border-style: flat;}"\
	//	 "QToolButton:checked{border-image:url(Resources/icon/gis/MapSideIcon/btn_ss_n.png);border-style: flat;}");


     //防止文本框输入内容位于按钮之下
   // QMargins margins = m_MainEdit->textMargins();
   //  m_MainEdit->setTextMargins(margins.left(), margins.top(), m_MainEdit->width(), margins.bottom());
   //  m_pSearchLineEdit->setPlaceholderText(QStringLiteral(" 请输入搜索内容 \n"));
	// QString tip = QString("请输入");
	// m_MainEdit->setPlaceholderText(tip);

     //布局
     QHBoxLayout *hlay  = new QHBoxLayout;
	 hlay->addWidget(mInsertEdit);
	 hlay->addWidget(mSBtn);
     hlay->setSpacing(0);
	 hlay->setMargin(0);
     hlay->setContentsMargins(0, 0, 0, 0);
	// hlay->setSizeConstraint(QLayout::SetFixedSize);//设置窗体固定大小 不能拖拽改变
	 this->setLayout(hlay);

	 this->setFixedSize(mBSize);
     //信号和槽函数连接
	 connect(mSBtn, SIGNAL(clicked(bool)), this, SLOT(search()));

}
//下拉框地图路线搜索 暂不实现
#if 0
void MapSearchBox::create_DeatilWidget()
{

}
#endif 


void MapSearchBox::search()
{

#if 0
	QString strText = mInsertEdit->text();
       if (!strText.isEmpty())
       {
         //  QMessageBox::information(this, QStringLiteral("搜索"), QStringLiteral("搜索内容为%1").arg(strText));
            QMessageBox::information(this, tr("搜索"), tr("搜索内容为%1").arg(strText));
       }
#endif  
	
}


