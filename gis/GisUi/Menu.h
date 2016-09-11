#ifndef __MENU_H__
#define __MENU_H__

#include <qwidget.h>
#include <qtoolbutton.h>
#include <QFrame>
#include <QToolButton>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QIcon>

class  Menu :public QWidget
{
public:
	explicit  Menu(QWidget* parent = 0);
	~Menu();
	void creat_ui(void);
	void setlay(void);//…Ë÷√≤ºæ÷

public:
	
#if 0
	QToolButton * btn1;
	QToolButton * btn2;
	QToolButton * btn3;
	QToolButton * btn4;
	QToolButton * btn5;
	QToolButton * btn6;
	QToolButton * btn7;
	QToolButton * btn8;
	QToolButton * btn9;
#else
	QPushButton * btn1;
	QPushButton * btn2;
	QPushButton * btn3;
	QPushButton * btn4;
	QPushButton * btn5;
	QPushButton * btn6;
	QPushButton * btn7;
	QPushButton * btn8;
	QPushButton * btn9;
#endif

private:
	QSize BtnSize;
	QSize iconSize;
};

#endif // __MENU_H__
