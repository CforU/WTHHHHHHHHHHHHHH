#ifndef DELETEWINDOW_H
#define DELETEWINDOW_H

#include <QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QPixmap>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QTextCodec>


class DeleteWindow : public QWidget
{
	Q_OBJECT

public:
	DeleteWindow(QWidget *parent = 0);
  //  DeleteWindow(QString title,QString info,QString leftbtn,QString ringthbtn);
	~DeleteWindow();

	void createUi();
	void InitBottomLayout();
	void paintEvent(QPaintEvent *);
	void setId(int);
signals:
    void deletePaht(int handle);
public slots:
	void onDelete();
private:
	QTextCodec *codec;
	QVBoxLayout *majorLayout;
	QVBoxLayout* mTopLayout;
	QHBoxLayout* mBottomLayout;
	QPixmap pic;

	QLabel* mTitle;
	QLabel* mInfo;
	QPushButton* mDelete;
	QPushButton* mCancel;
	int mId;
};

#endif // DELETEWINDOW_H
