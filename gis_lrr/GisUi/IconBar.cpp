#include "iconbar.h"

IconBar::IconBar(QWidget *parent) :
    QWidget(parent)
{
    iconSize = QSize(60,60);
    btnSize = QSize(60,60);
    scrolValue = 0;

    //设置样式
    this->setAutoFillBackground(true);
    QPalette p = this->palette();
    p.setColor(QPalette::Background, QColor(45, 55, 61));
    p.setColor(QPalette::ButtonText, QColor(255, 255, 255));
    this->setPalette(p);

    creat_ui();
    setlay();
    connect_signal();

    this->resize(85,600);

}

IconBar::~IconBar()
{

}
void IconBar::creat_ui(void){

    Iconpath << "Resources/icon/gis/mkPng/btn_up_n.png"
             << "Resources/icon/gis/mkPng/btn_down_n.png";

    topBtn = new QPushButton;//向上按钮
    topBtn->setIcon(QIcon(QPixmap(Iconpath.at(0))));
    topBtn->setIconSize(iconSize);
    topBtn->resize(btnSize);
    topBtn->setFlat(true);
    //topBtn->setStyleSheet("border: 0px");

    botomBtn = new QPushButton;//向下按钮
    botomBtn->setIcon(QIcon(QPixmap(Iconpath.at(1))));
    botomBtn->setIconSize(iconSize);
    botomBtn->resize(btnSize);
    botomBtn->setFlat(true);
    //botomBtn->setStyleSheet("border: 0px");

   baseWgt = new IconMenu;

}
//设置布局
void IconBar::setlay(void){

    QVBoxLayout *vlay = new QVBoxLayout(this);
    vlay->addWidget(topBtn);
    vlay->addWidget(baseWgt);
    vlay->addWidget(botomBtn);
    vlay->setMargin(0);
    vlay->setSpacing(0);

}

void IconBar::connect_signal(void)
{
    connect(topBtn, SIGNAL(clicked()), this, SLOT(on_Up()));
    connect(botomBtn, SIGNAL(clicked()), this, SLOT(on_Down()));

    int i;
    for(i=0;i<NUM;i++){
       connect(baseWgt->btn[i],SIGNAL(theClicked(int,CustomButton*)),this,SLOT(on_btn_clicked(int,CustomButton*)));
    }
}

//向上滚动
void IconBar::on_Up(void)
{
    if (scrolValue < baseWgt->verticalScrollBar()->maximumHeight() )
        scrolValue += 100;
    //menuArea->scroll(0,100);//这个是滚动去整体滚动
    //menuArea->ensureVisible(0, scrolValue);
    //this->leftBar->menuArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);  //不知道效果
    //menuArea->scrollContentsBy(100, 100);//保护的 外部无法使用
    //this->leftBar->menuArea->horizontalScrollBar()->setValue(200); //左右 水平方向
    //this->leftBar->menuArea->verticalScrollBar()->setValue(100);//可以设置到具体的值 垂直上下方向
    //this->leftBar->menuArea->ensureVisible(0, 200);//向下滚动
    //this->leftBar->menuArea->ensureVisible(0, 200); //向下滚动

//    baseWgt->ensureVisible(0, scrolValue);
    baseWgt->verticalScrollBar()->setValue(scrolValue);
}
//向下滚动
void IconBar::on_Down(void)
{
    if (scrolValue > 100)
        scrolValue -= 100;
    baseWgt->verticalScrollBar()->setValue(scrolValue);
  //  baseWgt->ensureVisible(0, scrolValue);

}

void IconBar::on_btn_clicked(int id,CustomButton* obj)
{
	
	QPalette p;
	//还原上一个颜色
	obj->setAutoFillBackground(true);
	if (lastBtn){
		p.setColor(QPalette::Background, QColor(45, 55, 61));
		p.setColor(QPalette::ButtonText, QColor(255, 255, 255));
		lastBtn->setPalette(p);
		lastBtn->setStyleSheet("background-color: rgb(45, 55, 61);border:0px");

	}
	//渲染当前按钮颜色
	obj->setStyleSheet("background-color: rgb(0,20,87)");
	//记录这次按钮
	lastBtn = obj;

	QString path = RCSettings::getValue(RCSettings::GIS, QString("svg/%1").arg(id), "Resources/icon/gis/mkSvg/icon_bhtjd_2.svg").toString();
	QString defpath = RCSettings::getValue(RCSettings::GIS, "svg/0", "Resources/icon/gis/mkSvg/icon_bhtjd_2.svg").toString();
	
	MarkerTool::setMarkerIconPath(path);
	MarkerTool::setDefaultMarkerIcon(defpath);
	MarkerTool::setMarkerType(id);
	qDebug() << "id=" << id << ": obj=" << obj;

#if 0
	obj->setStyleSheet();
	"QToolButton{background-color:rgb(10, 22, 37);color:rgb(255, 255, 255);border-radius:12px;border:2px groove \
							 						 		gray; border - style:outset; font: 75 12pt Ubuntu;}"\
															"QToolButton:hover{ background - color:white; color:black; }"\
												"QToolButton : pressed{ background - color:rgb(85, 170, 255); border - style:inset; }";
#endif
}


