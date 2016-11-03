#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H
#include <QObject>
#include <QToolButton>

class CustomButton : public QToolButton
{
    Q_OBJECT
public:
    CustomButton(int id);
    ~CustomButton();
    int id();
signals:
    void theClicked(int id,CustomButton* thisObj);
public slots:
    void on_clicked(void);

public:
    CustomButton *obj;
    int mid;
};

#endif // CUSTOMBUTTON_H
