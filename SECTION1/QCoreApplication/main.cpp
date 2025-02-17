#include <QDebug>
#include <QTimer>
#include <QCoreApplication>     // console event loop
//#include <QGuiApplication>    // GUI event loop
//#include <QApplication>       // Widget event-loop

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);

    qDebug("start main");

    QTimer timer;

  timer.callOnTimeout(  [](){qDebug("tick");}  );
//    timer.callOnTimeout(  [&app](){qDebug("tick"); app.exit();}  );

    timer.start(1000); // 1초마다 타이머 이벤트 발생

    return app.exec();
}
