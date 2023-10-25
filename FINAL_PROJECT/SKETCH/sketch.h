#ifndef SKETCH_H
#define SKETCH_H

#include <QWidget>
#include <QString>
#include <QMouseEvent>
#include <QPainter>
#include <QImage>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QContextMenuEvent>
#include <QComboBox>
#include <QLCDNumber>
#include <QGridLayout>
#include <QLabel>

/*
 * 1. 선의 색상과 두께를 변경 할 수 있는 코드를 추가 하라.
 * 2. 종료 메뉴와 "제출자"메뉴를 만들어 주세요. "제출자" 메뉴 선택 시 제풀하신 분의 ID를 메세지 박스로 보여 주세요.
 * 3. ContextMenu를 나타내 주세요.
 * 4. (옵션) 그린 그림을 파일로 저장 할 수 있게 제공해 보세요. (채점에 포함 안됨.)
 * 5. "Designer(form editor)"를 사용해도 되고, 직접 코드로만 작성하셔도 됩니다.
 */

class SketchWindow : public QWidget
{
    QImage image;

    QPoint from;
    bool draw = false;

    int pen_width = 5;
    QColor pen_color = Qt::black;

    QAction* ac1;
    QAction* ac2;

    static const int MAX_COLOR = 18;
    QColor p_color[MAX_COLOR] = {
                     Qt::black,
                     Qt::white,
                     Qt::darkGray,
                     Qt::gray,
                     Qt::lightGray,
                     Qt::red,
                     Qt::green,
                     Qt::blue,
                     Qt::cyan,
                     Qt::magenta,
                     Qt::yellow,
                     Qt::darkRed,
                     Qt::darkGreen,
                     Qt::darkBlue,
                     Qt::darkCyan,
                     Qt::darkMagenta,
                     Qt::darkYellow,
                     Qt::transparent
    };

    QString sGlobalColor[MAX_COLOR] = {
        "black",
        "white",
        "darkGray",
        "gray",
        "lightGray",
        "red",
        "green",
        "blue",
        "cyan",
        "magenta",
        "yellow",
        "darkRed",
        "darkGreen",
        "darkBlue",
        "darkCyan",
        "darkMagenta",
        "darkYellow",
        "transparent"
    };

    QSlider *slider;
    QComboBox* combobox;
    QLCDNumber *lcd;
    QGridLayout* g_layout;
    QLabel *imgDisplayLabel;

public:
    SketchWindow() : image(1, 1, QImage::Format_RGB32)
    {
        this->setMinimumSize(500,500);

        QMenuBar* menubar = new QMenuBar(this);
        QMenu* menu = menubar->addMenu("File");

        ac1 = menu->addAction("changjurhee");
        ac2 = menu->addAction("Exit");

        QVBoxLayout* layout = new QVBoxLayout;
        layout->setMenuBar(menubar);
        setLayout(layout);

        image.fill(qRgb(255, 255, 255));

        g_layout = new QGridLayout;

        imgDisplayLabel = new QLabel("");
        imgDisplayLabel->setPixmap(QPixmap::fromImage(image));
        imgDisplayLabel->adjustSize();
        g_layout->addWidget(imgDisplayLabel, 0, 0);

        lcd = new QLCDNumber(this);
        lcd->setObjectName("lcd");
        lcd->display(5);
        g_layout->addWidget(lcd, 1, 0);

        slider = new QSlider(Qt::Horizontal, this);
        slider->setObjectName("slider");
        slider->setRange(1, 100);
        slider->setValue(5);
        g_layout->addWidget(slider, 1, 2);

        combobox = new QComboBox(this);
        combobox->setObjectName("combo");
        for(int i = 0; i < MAX_COLOR; i++)
        {
            combobox->addItem(sGlobalColor[i]);
        }

        combobox->setCurrentIndex(0);
        g_layout->addWidget(combobox, 1, 3);

        layout->addLayout(g_layout);

        connect( ac1, &QAction::triggered, this, &SketchWindow::ShowMessageBox);
        connect( ac2, &QAction::triggered, this, &SketchWindow::close);
        connect(combobox, &QComboBox::currentIndexChanged, this, &SketchWindow::SetPenColor);
        connect(slider, &QSlider::valueChanged, this, &SketchWindow::SetPenWidth);
        connect(slider, SIGNAL(valueChanged(int)), lcd, SLOT(display(int)));
    }

public slots:
    void ShowMessageBox() {
        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setText("changjurhee");
        msgBox->setWindowModality(Qt::NonModal);
        msgBox->setStandardButtons(QMessageBox::Ok);
        msgBox->exec();
    }

    void SetPenColor(){
        pen_color = p_color[combobox->currentIndex()];
        qDebug() << combobox->currentText();
        qDebug() << pen_color;
    }

    void SetPenWidth(){
        pen_width = slider->value();
        qDebug() << slider->value();
    }

protected:
    // mouse right button
    void contextMenuEvent(QContextMenuEvent *event) override
    {
        QMenu menu(this);
        menu.addAction(ac1);
        menu.addAction(ac2);
        menu.exec(event->globalPos());
    }

    void paintEvent(QPaintEvent *event) override
    {
        QPainter g(this);

        QRect rc = event->rect();

        g.drawImage(rc, image, rc);
    }

    void mousePressEvent(QMouseEvent *event) override
    {
        if ( event->button() == Qt::LeftButton)
        {
            draw = true;
            from = event->pos();
        }

    }

    void mouseMoveEvent(QMouseEvent *event) override
    {
        if ( draw )
        {
            QPoint to = event->pos();

            QPainter g(&image);

            g.setPen(QPen(pen_color, pen_width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

            g.drawLine(from, to);

            // update();


            int rad = (pen_width / 2) + 2;
            update(QRect(from, to).normalized().adjusted(-rad, -rad, +rad, +rad));

            from = to;
        }
    }

    void mouseReleaseEvent(QMouseEvent *event) override
    {
        if ( event->button() == Qt::LeftButton)
        {
            draw = false;
        }
    }



    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event) override
    {
        if (width() > image.width() || height() > image.height()) {
            int newWidth = qMax(width() + 128, image.width());
            int newHeight = qMax(height() + 128, image.height());
            resizeImage(&image, QSize(newWidth, newHeight));
            update();
        }
    }

    void resizeImage(QImage *image, const QSize &newSize)
    {
        if (image->size() == newSize)
            return;

        QImage newImage(newSize, QImage::Format_RGB32);
        newImage.fill(qRgb(255, 255, 255));

        QPainter painter(&newImage);
        painter.drawImage(QPoint(0, 0), *image);
        *image = newImage;
    }
};


#endif // SKETCH_H




