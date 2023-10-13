#ifndef SAMPLE_H
#define SAMPLE_H

#include <QWidget>

class Sample : public QWidget
{
    Q_OBJECT
public:
    explicit Sample(QWidget *parent = nullptr);

    void food();
signals:

};

#endif // SAMPLE_H
