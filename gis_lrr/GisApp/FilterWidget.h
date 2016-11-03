#ifndef _FILTERWIDGET_H
#define _FILTERWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QRadioButton>
#include <QPushButton>
#include <QLabel>
#include <QLine>
#include <QFrame>
#include <QGridLayout>
#include <QListWidgetItem>

#include "gis/GisUi/childWidget.h"

#include <QAbstractScrollArea>
#include <QScrollArea>


class FilterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FilterWidget(QWidget *parent = 0);
    void create_ui();
    //void addItem();
    void createItem();

signals:
	void showMarker(int i);
	void hideMarker(int i);

public slots:
	void addItem();
	void updateBtnStatus();
public:
	//������
    QLabel *mTitleLab;
    QListWidget *bottomListWidget;

	//listView ��������
	QList<childWidget*>  listcwdt;
    QList<QListWidgetItem*>  listWdgItem;

	//����pushButton
	QVector<QPushButton*> listPushBtn;
	int mCount;
};

#endif // 
