#ifndef ROUTEWIDGET_H
#define ROUTEWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QRadioButton>
#include <QPushButton>
#include <QLabel>
#include <QLine>
#include <QFrame>
#include <QGridLayout>
#include <QListWidgetItem>

#include "childWidget.h"

#include <QAbstractScrollArea>
#include <QScrollArea>


class RouteWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RouteWidget(QWidget *parent = 0);
    void create_ui();
    void addItem();
    void createItem();
signals:

public slots:

public:
    //主界面
    QPushButton *mSelectAllBtn;
    QPushButton *mDeleteBtn;
    QListWidget *bottomListWidget;

    //listView 插入内容
    QList<childWidget*>  listcwdt;
    QList<QListWidgetItem*>  listWdgItem;


};

#endif // ROUTEWIDGET_H
