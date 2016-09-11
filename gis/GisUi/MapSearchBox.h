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


//搜索框类

class MapSearchBox : public QWidget
{
    Q_OBJECT
public:
    explicit MapSearchBox(QWidget *parent = 0);

    void  create_BaseWidget();
    void  create_DeatilWidget();

signals:

public slots:
    void search_route(void);
    void search();


private:

public:
    QWidget  *baseWidget;
    QWidget  *deatilWidget;
    QSize    baseWidgetSize;
    QSize    deatilWidgetSize;

    QSize MainEditsize;
    QSize EditSize;

    QLineEdit  *m_MainEdit;
    QPushButton  *m_routebtn;
    QPushButton  *m_searchbtn;


    QLineEdit  *m_FromEdit;
    QLineEdit  *m_ToEdit;
    QLabel     *m_LeftLab;
    QLine      *m_MidLine;
    QPushButton *m_RightBtn;


};

#endif // MAPSEARCHBOX_H
