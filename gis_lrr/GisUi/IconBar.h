#ifndef ICONBAR_H
#define ICONBAR_H

#include <QWidget>
#include <QSize>
#include <QScroller>
#include <QScrollBar>
#include <qmessagebox.h>
#include <QAbstractScrollArea>
#include <QPushButton>
#include <QDebug>
#include <QScrollArea>
#include <QPixmap>
#include <QString>
#include <QVBoxLayout>
#include <QAbstractScrollArea>
#include "qsettings.h"

#include "IconMenu.h"
#include "../GisApp/MarkerTool.h"

#include "../../modules/rcsettings/rcsetting.h"


class IconBar : public QWidget
{
    Q_OBJECT
public:
    explicit IconBar(QWidget *parent = 0);
    ~IconBar();
    void creat_ui(void);
    void setlay(void);//设置布局
    void connect_signal(void);

public slots:
    //向上滚动
    void on_Up(void);
    //向下滚动
    void on_Down(void);
    void on_btn_clicked(int,CustomButton*);

public:
    QPushButton * topBtn;//向上按钮
    IconMenu     *baseWgt;
    QPushButton * botomBtn;//向下按钮

    QSize iconSize;
    QSize btnSize;
    int   scrolValue;
private:
	CustomButton* lastBtn=NULL;
public:
    QStringList Iconpath;


public slots:

};

#endif // ICONBAR_H
