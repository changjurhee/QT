#ifndef WINDOW_H
#define WINDOW_H
#include <QDebug>
#include <QWidget>
#include <QPushButton>

// signal slot 기술은 반드시 헤더 파일 내에 기술해야 한다.

class Window : public QWidget
{
    Q_OBJECT

    QPushButton* btn;
public:
    Window()
    {
        btn = new QPushButton("OK", this);

//      QObject::connect( btn, SIGNAL(clicked()), this, SLOT(btn_clicked()));
        QObject::connect( btn, SIGNAL(clicked()), this, SLOT(close()));
        QObject::connect( btn, SIGNAL(pressed()), this, SLOT(btn_pressed()));
        QObject::connect( btn, SIGNAL(released()), this, SLOT(btn_released()));

        btn_clicked();
    }

public slots:
    void btn_clicked() { qDebug(__func__); close();}
    void btn_pressed() { qDebug(__func__); }
    void btn_released() { qDebug(__func__); }

};



#endif // WINDOW_H











