#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

//#include "ui_widget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; } // c++의 경우 포인터만 사용할 경우 전방 선언만으로 사용 가능함.
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

public slots:
    void button2_click()
    {
        qDebug() << __func__;
    }

    void button3_click()
    {
        qDebug() << __func__;
    }

    void on_pushButton_4_clicked()
    {
        qDebug() << __func__;
    }
};
#endif // WIDGET_H











