#include "FilterWidget.h"

FilterWidget::FilterWidget(QWidget *parent) :
QWidget(parent)
{
	mCount = 0;
	create_ui();

}

void FilterWidget::create_ui()
{
	//  LayersNum = 6;
	//mTitleLab = new QLabel(this);
	//mTitleLab->setText("ɸѡ");
	//mTitleLab->setAlignment(Qt::AlignCenter);
	//mTitleLab->setMinimumHeight(40);

	bottomListWidget = new QListWidget(this);
	bottomListWidget->setSelectionMode(QAbstractItemView::NoSelection);
	bottomListWidget->setFrameShape(QFrame::NoFrame); //�����ޱ߿�
	bottomListWidget->setFocusPolicy(Qt::NoFocus);//ȥ��ѡ�����߿�
	bottomListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//ȥ��ˮƽ������
	bottomListWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	// this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);//ȥ��������
	//bottomListWidget->setFrameShape(QFrame::NoFrame);
	QVBoxLayout *vlay = new  QVBoxLayout(this);
	//vlay->addWidget(mTitleLab);
	vlay->addWidget(bottomListWidget);
	vlay->setMargin(0);
	vlay->setSpacing(0);

	//������ʽ
	this->setAutoFillBackground(true);
	QPalette p = this->palette();
	p.setColor(QPalette::Background, QColor(87, 105, 115));
	p.setColor(QPalette::ButtonText, QColor(255, 255, 255));
	this->setPalette(p);
	bottomListWidget->setPalette(p);
	//bottomListWidget->setBackgroundRole();

	this->resize(200, 250);

}

void FilterWidget::addItem()
{
	//int i;
	childWidget* childwdt = new childWidget(bottomListWidget);
	listPushBtn.append(childwdt->mChekButton);
	mCount++;
	childwdt->mLab->setText("Point " + QString::number(mCount , 10) );
	QListWidgetItem* ci = new QListWidgetItem;
	bottomListWidget->addItem(ci);
	ci->setSizeHint(QSize(childwdt->rect().width(), childwdt->rect().height()));
	//listWdgItem[i]->setSizeHint (QSize(listcwdt[i]->rect().width()+10,listcwdt[i]->rect().height()+10));
	bottomListWidget->setItemWidget(ci, childwdt);

	listcwdt.append(childwdt);
	listWdgItem.append(ci);
	connect(childwdt->mChekButton, SIGNAL(clicked()), this, SLOT(updateBtnStatus()));
}

void FilterWidget::updateBtnStatus(){
	for (int i = 0; i < listPushBtn.count(); ++i){
		if (listPushBtn.at(i)->isChecked()){
			emit showMarker(i);
		}
		else{
			emit hideMarker(i);
		}
	}
}

void FilterWidget::createItem()
{

#if 0

	/*
	wdg = new childWidget(bottomListWidget);
	item = new QListWidgetItem;
	bottomListWidget->addItem(item);
	item->setSizeHint (QSize(wdg->rect().width(),wdg->rect().height()));
	bottomListWidget->setItemWidget(item,wdg);
	*/


	//�µ���
	QListWidgetItem *item = new QListWidgetItem();
	bottomListWidget->addItem(item);
	//ÿ��Ԫ�ذ󶨲���
	childWidget *myItem = new childWidget(bottomListWidget);
	//����Ԫ�ش�С����
	item->setSizeHint(QSize(myItem->rect().width(), myItem->rect().height()));
	bottomListWidget->setItemWidget(item, myItem);
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
	for (i = 0; i<LayersNum; i++)
	{
		listcwdt.append(new childWidget);
		listWdgItem.append(new QListWidgetItem(bottomListWidget));


	}
	for (i = 0; i<LayersNum; i++)
	{

		bottomListWidget->addItem(listWdgItem.at(i));
		bottomListWidget->setItemWidget(listWdgItem.at(i), listcwdt.at(i));

	}
#endif
}



