#include "RouteWidget.h"

RouteWidget::RouteWidget(QWidget *parent) :
    QWidget(parent)
{
    create_ui();
    for(int i=0;i<10;i++){
        addItem();
    }

}

void RouteWidget::create_ui()
{
  //  LayersNum = 6;

    mSelectAllBtn = new QPushButton;
    mSelectAllBtn->setCheckable(true);
    mSelectAllBtn->setFixedSize(90,50);
    mDeleteBtn = new QPushButton;
    mDeleteBtn->setCheckable(true);
    mDeleteBtn->setFixedSize(74,50);
    mSelectAllBtn->setStyleSheet(
        "QPushButton{border-image:url(Resources/icon/btn_wdljqx_n.png);color:#ffffff;font-size:20px}"
        "QPushButton:checked{border-image:url(Resources//icon/btn_wdljqx_s.png);color:#ffffff;font-size:20px}"
    );
    mDeleteBtn->setStyleSheet(
        "QPushButton{border-image:url(Resources//icon/btn_wdljsc_d.png);color:#ffffff;font-size:20px}"
        "QPushButton:checked{border-image:url(Resources//icon/btn_wdljsc_p.png);color:#ffffff;font-size:20px}"
        );

 //   "QPushButton{border-image: url(:/icon/btn_sxxx_n.png);border-style: flat;}"\
                "QPushButton:checked{border-image:url(:/icon/btn_sxxx_s.png);border-style: flat;
 //
   QHBoxLayout *hlay = new QHBoxLayout;
   hlay->addWidget(mSelectAllBtn);
   hlay->addStretch();
   hlay->addWidget(mDeleteBtn);

   //底部VIEW

    bottomListWidget = new QListWidget(this);
    bottomListWidget->setSelectionMode(QAbstractItemView::NoSelection);
    bottomListWidget->setFrameShape(QFrame::NoFrame); //设置无边框
    bottomListWidget->setFocusPolicy(Qt::NoFocus);//去除选中虚线框
    bottomListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//去掉水平滚动条
    bottomListWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);//去掉标题栏
    //bottomListWidget->setFrameShape(QFrame::NoFrame);
    QVBoxLayout *vlay=new  QVBoxLayout(this);
    vlay->addLayout(hlay);
    vlay->addWidget(bottomListWidget);
    vlay->setMargin(0);
    vlay->setSpacing(0);
#if 0
    //设置样式
    this->setAutoFillBackground(true);
    QPalette p = this->palette();
    p.setColor(QPalette::Background, QColor(87, 105, 115));
    p.setColor(QPalette::ButtonText, QColor(255, 255, 255));
    this->setPalette(p);
    bottomListWidget->setPalette(p);
    //bottomListWidget->setBackgroundRole();
#endif
    this->resize(218,400);

}

void RouteWidget::addItem()
{
    int i;
    childWidget* cw = new childWidget(bottomListWidget);
    QListWidgetItem* ci = new QListWidgetItem;
    bottomListWidget->addItem(ci);
    ci->setSizeHint (QSize(cw->rect().width(),cw->rect().height()));
    //listWdgItem[i]->setSizeHint (QSize(listcwdt[i]->rect().width()+10,listcwdt[i]->rect().height()+10));
    bottomListWidget->setItemWidget( ci, cw);

    listcwdt.append(cw);
    listWdgItem.append(ci);
}

void RouteWidget::createItem()
{

#if 0

    /*
        wdg = new childWidget(bottomListWidget);
        item = new QListWidgetItem;
        bottomListWidget->addItem(item);
        item->setSizeHint (QSize(wdg->rect().width(),wdg->rect().height()));
        bottomListWidget->setItemWidget(item,wdg);
      */


    //新的行
    QListWidgetItem *item = new QListWidgetItem();
    bottomListWidget->addItem(item);
    //每个元素绑定布局
    childWidget *myItem = new childWidget(bottomListWidget);
    //布局元素大小更新
    item->setSizeHint (QSize(myItem->rect().width(),myItem->rect().height()));
    bottomListWidget->setItemWidget(item,myItem);
#endif




    /*
    int i;
    listcwdt[0] = new childWidget;
    listcwdt[1] = new childWidget;
    listWdgItem[0] = new QListWidgetItem(bottomListWidget);
    listWdgItem[1] = new QListWidgetItem(bottomListWidget);
    bottomListWidget->addItem(listWdgItem[0]);
    bottomListWidget->setItemWidget(listWdgItem[0],listcwdt[0]);
    bottomListWidget->addItem(listWdgItem[1]);
    bottomListWidget->setItemWidget(listWdgItem[1],listcwdt[1]);




*/

#if 0
    for(i=0;i<LayersNum;i++)
    {
        listcwdt.append(new childWidget);
        listWdgItem.append(new QListWidgetItem(bottomListWidget) );


    }
    for(i=0;i<LayersNum;i++)
    {

        bottomListWidget->addItem(listWdgItem.at(i));
        bottomListWidget->setItemWidget(listWdgItem.at(i),listcwdt.at(i));

    }
#endif
}



