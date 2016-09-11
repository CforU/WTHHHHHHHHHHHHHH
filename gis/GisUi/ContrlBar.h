#ifndef _ContrlBar_H__
#define  _ContrlBar_H__
#include <qwidget.h>
#include <qpushbutton.h>
#include <qtoolbutton.h>
#include <qsize.h>
#include <qmessagebox.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QTextCodec>
#include <qstringlist.h>

#include "../MarkerTool.h"

class ContrlBar :public QWidget{
	Q_OBJECT
public:
	explicit  ContrlBar(QWidget* parent = 0);
	~ContrlBar();
	
	void creat_ui(void);
	void setlayout(void);//…Ë÷√≤ºæ÷
	void connect_signal(void);
	void setMarkerIcon(QString path);
	void create_iconList(void);

public slots :
		void firstBtn_clicked();
		void secondBtn_clicked();
		void thirdBtn_clicked();
		void fourthBtn_clicked();
		void fifthBtn_clicked();
		void sixthBtn_clicked();
		void seventhBtn_clicked();
		void eighthBtn_clicked();
		void ninthBtn_clicked();

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

	//icon list
	QStringList svgPathlist;
	QStringList iconPathlist;


};


#endif  // _ContrlBar_H__