#ifndef _RIGHTBAR_H__
#define  _RIGHTBAR_H__
#include <qwidget.h>
#include <qpushbutton.h>
#include <qtoolbutton.h>
#include <qsize.h>
#include <qmessagebox.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QTextCodec>

class RightBar :public QWidget{
	Q_OBJECT
public:
	explicit  RightBar(QWidget* parent = 0);
	~RightBar();
	void creat_ui(void);
	void setlayout(void);//���ò���
	void connect_signal(void);

public slots:


public:
	QToolButton * m_FirstBtn;
	QToolButton * m_SecondBtn;
	QToolButton * m_ThirdBtn;
	QToolButton * m_FourthBtn;
	QToolButton * m_FifthBtn;
	QToolButton * m_SixBtn;
	QToolButton * m_SeventhBtn;
	QToolButton * m_EighthBtn;
	QToolButton * m_ninethBtn;

	QSize iconSize;
	QSize btnSize;

public:

};


#endif  // _LEFTBAR_H__