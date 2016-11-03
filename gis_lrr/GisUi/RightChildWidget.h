#ifndef RIGHTCHILDWIDGET_H
#define RIGHTCHILDWIDGET_H


#include <QStackedWidget>
#include <QWidget>
#include <QPushButton>
#include <QToolButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSize>

class RightChildWidget : public QStackedWidget
{
    Q_OBJECT
public:
    explicit RightChildWidget(QWidget *parent = 0);
    void create_ui();
    void connect_signal();


signals:

public slots:
    void base_btn1_on_clicked();
    void base_btn2_on_clicked();
    void base_btn3_on_clicked();

public:
    QWidget *baseWdt; //基本
    QToolButton *base_btn1;
    QToolButton *base_btn2;
    QToolButton *base_btn3;

    QWidget *StratifiedWdt; //分层
    QToolButton *Stratified_btn1;

    QWidget *filterWdt; //筛选
    QToolButton *filter_btn1;

    QWidget *measuringWdt; // 测量
    QToolButton *measure_btn1;
    QToolButton *measure_btn2;
	QToolButton *reset_btn3;

    QSize iconSize;
    QSize btnSize ;


};

#endif // RIGHTCHILDWIDGET_H
