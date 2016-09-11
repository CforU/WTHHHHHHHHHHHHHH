#ifndef __NAVIGATIONBOX_H__
#define __NAVIGATIONBOX_H__


#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QIcon>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

//导航框
class NavigationBox : public QWidget
{
	Q_OBJECT
public:
	explicit NavigationBox(QWidget *parent = 0);
	void  create_BaseWidget();
	void  create_DeatilWidget();
	void  set_layout();

signals:

public slots :
	//查找路线
	void search_route(void);
	//查找历史路径信息
	void search();

private:

public:
	//导航查询控件
	QWidget      *baseWidget;//基本显示控件
	QLineEdit    *m_MainEdit;
	QPushButton  *m_routebtn;
	QPushButton  *m_searchbtn;

	//导航信息控件
	QWidget     *deatilWidget;//隐藏控件
	QLineEdit   *m_FromEdit;
	QLineEdit   *m_ToEdit;
	QLabel      *m_LeftLab;
	QLine       *m_MidLine;
	QPushButton *m_RightBtn;

	//大小
	QSize    baseWidgetSize;//基本窗体大小
	QSize    deatilWidgetSize;//隐藏窗体大小
	QSize	 MainEditsize; //搜索框大小
	QSize	 EditSize; //编辑框大小

};


#endif //__NAVIGATIONBOX_H__