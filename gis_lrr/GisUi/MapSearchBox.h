#ifndef MAPSEARCHBOX_H
#define MAPSEARCHBOX_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

#include <QLabel>
#include <QIcon>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <qtextcodec.h>

//搜索框类

class MapSearchBox : public QWidget
{
    Q_OBJECT
public:
    explicit MapSearchBox(QWidget *parent = 0);
    void    createSearchBox();

signals:

public slots:
	//搜索
    void search();
private:
   
	QLineEdit  *mInsertEdit;//输入框
	QPushButton  *mSBtn;//搜索按钮
    QSize    mBSize;//总大小
	QSize    mSSize;//搜索框大小
    QSize    mSsize;//按钮大小
  
};

#endif // MAPSEARCHBOX_H
