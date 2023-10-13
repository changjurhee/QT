#include <QDebug>
#include <QApplication>
#include "sample.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    Sample sam;

    const QMetaObject* mo = sam.metaObject();

    qDebug() << mo->className();

    sam.show();

    return app.exec();
}

