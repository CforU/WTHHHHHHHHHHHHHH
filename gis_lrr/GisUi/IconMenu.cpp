#include "iconmenu.h"
#include "../GisCore/MapManager.h"
IconMenu::IconMenu()
{
    create_ui();
    setlay();
#if 0
	//设置样式
	this->setAutoFillBackground(true);
	QPalette p = this->palette();
	p.setColor(QPalette::Background, QColor(45, 55, 61));
	p.setColor(QPalette::ButtonText, QColor(255, 255, 255));
	this->setPalette(p);
#endif

    this->setWidget(centwdg);

    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setWidgetResizable(true);//
    this->setFixedSize(120,568);//固定大小
    this->setFrameShape(QFrame::NoFrame);//无边框

    this->horizontalScrollBar()->setRange(0,1500);


}


void IconMenu::create_ui()
{
    BtnSize = QSize(100, 100);
    iconSize = QSize(80, 80);

	int i;

#if 0
	MapManager* mm = MapManager::instance();//获取地图管理器 从其获取标绘图标和现实图标
	if (mm == NULL)
	{
	
		// 如果没有 按照默认设置设置标绘图标

		Iconpath << "Resources/icon/gis/mkPng/icon_bhtjd_2.png"  //画点
			<< "Resources/icon/gis/mkPng/icon_bhqd_2.png"   //起点
			<< "Resources/icon/gis/mkPng/icon_bhty_2.png"   //中点
			<< "Resources/icon/gis/mkPng/icon_bhzd_2.png"   //终点
			<< "Resources/icon/gis/mkPng/icon_bhzhc_2.png"  //指挥车
			<< "Resources/icon/gis/mkPng/icon_bhwrj_3.png"  //无人机
			<< "Resources/icon/gis/mkPng/icon_bhlx_3.png"   //轮巡
			<< "Resources/icon/gis/mkPng/icon_bhxld_13.png" //履带
			<< "Resources/icon/gis/mkPng/icon_bhls_3.png"   //轮式
			<< "Resources/icon/gis/mkPng/icon_bhld_3.png"
			<< "Resources/icon/gis/mkPng/icon_bhgdq_3.png"
			<< "Resources/icon/gis/mkPng/icon_bhspc_3.png"
			<< "Resources/icon/gis/mkPng/icon_bhls_3.png"   //轮式
			<< "Resources/icon/gis/mkPng/icon_bhld_3.png"
			<< "Resources/icon/gis/mkPng/icon_bhgdq_3.png"
			<< "Resources/icon/gis/mkPng/icon_bhspc_3.png"
			<< "Resources/icon/gis/mkPng/icon_bhls_3.png"   //轮式
			<< "Resources/icon/gis/mkPng/icon_bhld_3.png"
			<< "Resources/icon/gis/mkPng/icon_bhgdq_3.png"
			<< "Resources/icon/gis/mkPng/icon_bhspc_3.png";

		//名字暂时未使用
		const char* Name[] = { "画点", "起点", "中点", "终点", "指挥车 ", "无人机 ",
			"轮巡", "履带", "轮式", "test", "test", "test", "test", "test", "test", "test""test", "test", "test" };
		NameList = Name;
	}
	else
	{
	  //使用以下方式处理
		//使用迭代器进行迭代 效率应该会高一些   优化的时候做
		for (i = 0; i < NUM; i++){
			Iconpath << mm->MarkerIcon[i];
		}
	}
	
#else

	//通过配置文件读取
	for (i = 0; i < NUM; i++){
		//QString index = "png/ %0 ".
		Iconpath << RCSettings::getValue(RCSettings::GIS, QString("png/%1").arg(i), "Resources/icon/gis/mkPng/icon_bhtjd_2.png").toString();
	}
	
#endif
	

    centwdg = new QWidget;
    //centwdg->resize(120,768);
	//翻译器
	QTextCodec *codec = QTextCodec::codecForName("GBK");

    //创建按钮
 
#if 1
	
	for (i = 0; i<NUM; i++){
        btn[i] = new CustomButton(i);
        btn[i]->resize(BtnSize);
		btn[i]->setIcon(QIcon(QPixmap(Iconpath.at(i))));
        btn[i]->setIconSize(iconSize);
		btn[i]->setStyleSheet("QToolButton{border: none; background: rgb(45, 55, 61); color: rgb(0, 160, 230);}");
		//btn[i]->setText(codec->toUnicode("test"));
        //btn[i]->setFlat(true); //toolbutton  
        // btn[i]->setFocusPolicy(Qt::NoFocus);//焦点框
        // btn[i]->setStyleSheet("border: 0px");//消除边框，取消点击效果
        // btn[i]->setAttribute(Qt::WA_Disabled,true);//可能用来取消透明电极效果的
        // btn[i]->setWindowFlags(Qt::Tool|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);

    }
	
#else
	for (i = 0; i<NUM; i++){
		btn[i] = new  CustomButton(i);
		btn[i]->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
		btn[i]->setIcon(QPixmap(Iconpath.at(i)).scaled(80, 80));
		btn[i]->setText(codec->toUnicode(NameList[i]));
		btn[i]->setAutoRaise(true);
		btn[i]->setStyleSheet("QToolButton{border: none; background: rgb(45, 55, 61); color: rgb(0, 160, 230);}");
		btn[i]->resize(BtnSize);
	}
#endif
}

void IconMenu::setlay()
{
    QVBoxLayout *vlay = new QVBoxLayout(centwdg);
    vlay->setAlignment(Qt::AlignCenter);
    vlay->setMargin(0);
    vlay->setSpacing(0);
    int i;
	for (i = 0; i<NUM; i++){
        vlay->addWidget(btn[i],i,Qt::AlignCenter);
    }


}

