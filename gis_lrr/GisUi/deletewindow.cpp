#include "deletewindow.h"
#include <QPainter>

DeleteWindow::DeleteWindow(QWidget *parent)
	: QWidget(parent)
{
    codec = QTextCodec::codecForName("UTF8");
	createUi();

    //是否把做成单利 重新通过构造 或者 重新show来实现选中的个数显示
	connect(mDelete, SIGNAL(clicked()), this, SLOT(onDelete()));
    connect(mCancel, SIGNAL(clicked()), this, SLOT(close()));
}
#if 0
 DeleteWindow::DeleteWindow(QString &title,QString &info,QString &leftbtn,QString &ringthbtn)
 {
     codec = QTextCodec::codecForName("UTF8");
      createUi();
      mTitle->setText(title);
      mInfo->setText(info);
      mDelete->setText(leftbtn);
      mCancel->setText(ringthbtn);
 }
#endif
void DeleteWindow::createUi()
{
	QFont font("Microsoft YaHei",  75);
	this->setWindowFlags(Qt::FramelessWindowHint);//设置窗体无边框
    this->setAttribute(Qt::WA_TranslucentBackground);//./Resources/icon/vm/vehiclemanager/background
    //pic.load("./Resources/icon/vm/vehiclemanager/background/bg_tc_3.png");//加载图像
    pic.load(":/icon//bg_tc_3.png");//加载图像

	this->resize(pic.size());

	majorLayout = new QVBoxLayout(this);
	mTopLayout = new QVBoxLayout();

	resize(540, 286);
	//setBackground();

	mTitle = new QLabel(this);
	mTitle->setFont(font);
	mTitle->setStyleSheet("color:#ffffff;font-size:24px;");
	mTitle->setText(codec->toUnicode("删除确认"));
	mTitle->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);

	mInfo = new QLabel(this);
	font.setPixelSize(18);
	mInfo->setFont(font);
	mInfo->setStyleSheet("color:#ffffff;font-size:18px;");
    mInfo->setText(codec->toUnicode("选择了两个路径,确定要删除选定的路径吗?"));
	mInfo->setAlignment(Qt::AlignCenter);

	mTopLayout->setMargin(0);
	mTopLayout->setSpacing(0);
	mTopLayout->addWidget(mTitle, 40);
	mTopLayout->addWidget(mInfo, 29);
	majorLayout->addLayout(mTopLayout);
	InitBottomLayout();
	majorLayout->setMargin(0);
	majorLayout->setSpacing(0);
	this->setLayout(majorLayout);
}

//重写绘图事件
void DeleteWindow::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.drawPixmap(0, 0, pic);//绘制图像
}


void DeleteWindow::InitBottomLayout()
{
	QFont font("Microsoft YaHei",  75);

	mBottomLayout = new QHBoxLayout();

	mDelete = new QPushButton(this);
	mCancel = new QPushButton(this);

	mDelete->setFixedWidth(132);
	mDelete->setFixedHeight(50);
	mCancel->setFixedWidth(132);
	mCancel->setFixedHeight(50);

	mDelete->setText(codec->toUnicode("删除"));
    mCancel->setText(codec->toUnicode("取消"));

	mDelete->setFont(font);
	mCancel->setFont(font);
#if 0
	mDelete->setStyleSheet(
		"QPushButton{border-image:url(./Resources/icon/vm/vehiclemanager/btn_2_n.png);color:#ffffff;font-size:20px}"
		"QPushButton:pressed{border-image:url(./Resources/icon/vm/vehiclemanager//btn_2_p.png);color:#ffffff;font-size:20px}"
	);
	mCancel->setStyleSheet(
		"QPushButton{border-image:url(./Resources/icon/vm/vehiclemanager/btn_1_n.png);color:#ffffff;font-size:20px}"
		"QPushButton:pressed{border-image:url(./Resources/icon/vm/vehiclemanager//btn_1_p.png);color:#ffffff;font-size:20px}"
		);
#else
    mDelete->setStyleSheet(
        "QPushButton{border-image:url(:/icon/btn_2_n.png);color:#ffffff;font-size:20px}"
        "QPushButton:pressed{border-image:url(:/icon/btn_2_p.png);color:#ffffff;font-size:20px}"
    );
    mCancel->setStyleSheet(
        "QPushButton{border-image:url(:/icon/btn_1_n.png);color:#ffffff;font-size:20px}"
        "QPushButton:pressed{border-image:url(:/icon/btn_1_p.png);color:#ffffff;font-size:20px}"
        );
#endif
	//mBottomLayout->setContentsMargins(98, 0, 98, 58);
	mBottomLayout->addWidget(mDelete);
	mBottomLayout->addWidget(mCancel);
	mBottomLayout->setSpacing(80);
	
	//mBottomLayout->setMargin(0);
	mBottomLayout->setContentsMargins(98, 0, 98, 58);
	mBottomLayout->setSpacing(0);
	
	majorLayout->addLayout(mBottomLayout);
}

void DeleteWindow::onDelete()
{
	
    emit deletePaht(true);
	close();
}

DeleteWindow::~DeleteWindow()
{

}
