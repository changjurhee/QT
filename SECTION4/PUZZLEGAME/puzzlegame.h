#ifndef PUZZLEGAME_H
#define PUZZLEGAME_H

#include <QWidget>
#include <QString>
#include <QDebug>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include <algorithm>

// further works
// 1. update()할때 영역의 크기를 계산해서 꼭 필요한 부분만 업데이트
// 2. 다 맞추었는지 확인 하는 기능
// 3. 섞는 기능 (메뉴 등을 추가)
// 4. count를 변경 할 수 있는 기능
// 5. 그림을 변경 할 수 있는 기능
// 6. 맞추는데 걸린 시간, 횟수 등을 관리하는 기능 (score)s

class PuzzleWindow : public QWidget
{
    static constexpr int COUNT = 5;
    static constexpr int EMPTY = COUNT * COUNT - 1;

    QPixmap pm;

    int block_w, block_h;

    int board[COUNT][COUNT];

public:
    PuzzleWindow()
    {
        pm.load("D:\\puzzle.jpg");
        qDebug() << pm;
        this->setFixedSize( pm.width(), pm.height());

        block_w = pm.width()  / COUNT;
        block_h = pm.height() / COUNT;


        for( int y = 0; y < COUNT; ++y)
        {
            for (int x = 0; x < COUNT; ++x)
            {
                board[y][x] = x + y * COUNT; // 0 ~ 24
            }
        }
    }



protected:
    void paintEvent(QPaintEvent *event) override
    {
        QPainter g(this);


        for( int y = 0; y < COUNT; ++y)
        {
            for (int x = 0; x < COUNT; ++x)
            {

                if ( board[y][x] == EMPTY)
                {
                    g.fillRect( x*block_w, y * block_h, block_w, block_h, Qt::white );
                    continue;
                }

                int no = board[y][x];
                int bx = no % COUNT;
                int by = no / COUNT;
                g.drawPixmap(block_w * x, block_h * y,
                             block_w - 1, block_h - 1,
                             pm,
                             bx * block_w, by * block_h,
                             block_w, block_h);
            }
        }


    }

    void mousePressEvent(QMouseEvent *event) override
    {
        QPoint pt = event->pos();

        int bx = pt.x() / block_w;
        int by = pt.y() / block_h;

        if (bx < 0 || by < 0 || bx >= COUNT || by >= COUNT)
            return;


        // RIGHT 가 empty 조사
        if (bx < COUNT - 1 && board[by][bx + 1] == EMPTY)
        {
            std::swap(board[by][bx], board[by][bx+1]);
        }
        else if (bx > 0 && board[by][bx-1] == EMPTY)
        {
            std::swap(board[by][bx], board[by][bx-1]);
        }
        else if (by < COUNT - 1 && board[by + 1][bx] == EMPTY)
        {
            std::swap(board[by][bx], board[by+1][bx]);
        }
        else if (by > 0 && board[by - 1][bx] == EMPTY)
        {
            std::swap(board[by][bx], board[by-1][bx]);
        }
        else
        {
            QApplication::beep();
            return;
        }

        // 다시 그리게 한다.
        update();

    }
};












#endif // PUZZLEGAME_H
