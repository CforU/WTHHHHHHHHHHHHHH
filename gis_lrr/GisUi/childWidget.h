#ifndef CHILDWIDGET_H
#define CHILDWIDGET_H

#include <QWidget>

#include <QWidget>
#include <QListWidget>
#include <QRadioButton>
#include <QPushButton>
#include <QLabel>
#include <QLine>
#include <QFrame>
#include <QGridLayout>
#include <QListWidgetItem>

#include <QPainter>
#include <QPaintEvent>

class childWidget :public QWidget
{
    Q_OBJECT
public:
    explicit childWidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent *e);
    void creat_ui();

public:
  //  QFrame *mLine;
    QPushButton *mChekButton;
    QLabel  *mLab;
};


#endif // CHILDWIDGET_H
