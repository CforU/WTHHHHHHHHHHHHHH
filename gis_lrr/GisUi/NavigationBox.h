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
#include <QFormLayout>

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>


//导航框
class NavigationBox : public QWidget
{
	Q_OBJECT
public:
	explicit NavigationBox(QWidget *parent = 0);
    void  create_ui();
	void  create_BaseWidget();
    void  set_layout();
	void  create_DeatilWidget();
    void  create_ControlWidget();
    void  create_CollectWidget();

signals:

public slots :
	//查找路线
	void search_route(void);
	//查找历史路径信息
	void search();

private:

public:
    //导航查询控件  第一部分
	QWidget      *baseWidget;//基本显示控件
//	QLineEdit    *m_MainEdit;
//	QPushButton  *m_routebtn;
//	QPushButton  *m_searchbtn;
    //
   QLabel       *mNameLab;
   QLabel       *mFromLab;
   QLabel       *mToLab;
   QPushButton  *addBtn;
   QLineEdit    *mFromEdit;
   QLineEdit    *mToEdit;
   QFrame       *mLine;
   QFrame       *mLine_2;
   QPushButton  *mSearch;
   QToolButton  *mMyRoute;


    //导航信息控件 提示框 第二部分
	QWidget     *deatilWidget;//隐藏控件
	QLineEdit   *m_FromEdit;
	QLineEdit   *m_ToEdit;
	QLabel      *m_LeftLab;
	QLine       *m_MidLine;
	QPushButton *m_RightBtn;


    //地图 操作框 第三部分
    QWidget     *controlWidget;//隐藏控件
    QPushButton   *m_Collect; //收藏
    QPushButton   *m_determine;//确定

    //收藏
    QWidget     *CollectWidget;//收藏展示窗体


	//大小
	QSize    baseWidgetSize;//基本窗体大小
	QSize    deatilWidgetSize;//隐藏窗体大小
	QSize	 MainEditsize; //搜索框大小
	QSize	 EditSize; //编辑框大小

};


#endif //__NAVIGATIONBOX_H__
