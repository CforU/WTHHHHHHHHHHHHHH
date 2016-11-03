#ifndef ICONMENU_H
#define ICONMENU_H

#include <QScrollBar>
#include <QScrollArea>
#include <QPushButton>
#include <QPixmap>
#include <QSize>
#include <QString>
#include <QVBoxLayout>
#include <QTextCodec>


#include "CustomButton.h"


#define NUM (15)  //图标上限

class IconMenu : public QScrollArea
{
public:
    IconMenu();
    void create_ui();
    void setlay(void);//设置布局
    void connect_signal(void);

public:

     QWidget *centwdg;
     CustomButton  *btn[NUM];
     QStringList Iconpath;
	 const char** NameList;
     QSize BtnSize;
     QSize iconSize;


};

#endif // ICONMENU_H
