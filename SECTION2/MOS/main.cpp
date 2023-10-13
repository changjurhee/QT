#include <QDebug>
#include "sample.h"

// C++ 1983, 1998 (STD), 2011 / (3year)
// QT     1995
// MOS
// - signal slots
// - RTTI : 실행 시간에 객체의 타입을 조사하는 기술
// - dynamic property
int main()
{
    Sample sam;

    const QMetaObject* mo = sam.metaObject();

    qDebug() << mo->className();
    //qDebug() << mo->classInfoCount();

    return 0;
}

