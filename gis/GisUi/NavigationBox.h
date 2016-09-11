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

//������
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
	//����·��
	void search_route(void);
	//������ʷ·����Ϣ
	void search();

private:

public:
	//������ѯ�ؼ�
	QWidget      *baseWidget;//������ʾ�ؼ�
	QLineEdit    *m_MainEdit;
	QPushButton  *m_routebtn;
	QPushButton  *m_searchbtn;

	//������Ϣ�ؼ�
	QWidget     *deatilWidget;//���ؿؼ�
	QLineEdit   *m_FromEdit;
	QLineEdit   *m_ToEdit;
	QLabel      *m_LeftLab;
	QLine       *m_MidLine;
	QPushButton *m_RightBtn;

	//��С
	QSize    baseWidgetSize;//���������С
	QSize    deatilWidgetSize;//���ش����С
	QSize	 MainEditsize; //�������С
	QSize	 EditSize; //�༭���С

};


#endif //__NAVIGATIONBOX_H__