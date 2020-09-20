#include "PvP.h"
#include <QPainter>
#include <QEvent>
#include <QPen>
#include <QTimer>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include <QBrush>
#include <QPoint>

#define WhiteTurn 1
#define BlackTurn 2

PvP::PvP(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("PvP模式");
    this->setGeometry(400, 150, 1000, 780);
//    setMouseTracking(true);

    x = 0;
    y = 0;
    isFirst = 1;
    turn = 0;
    checkerBoard = new CheckerBoard;
}

void PvP::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    QPen pen;
    pen.setWidth(2);
    p.setPen(pen);
    //画棋盘
    for(int x=35;x<701;x+=35)
        p.drawLine(x,35,x,700);
    for(int y=35;y<701;y+=35)
        p.drawLine(35,y,700, y);

    //画棋子
    if(!isFirst)
    {
        QBrush brush(Qt::white);
        for(int i=0;i<20;i++)
        {
            for(int j=0;j<20;j++)
            {
                qDebug()<<checkerBoard->chessNode[0][0]<<checkerBoard->chessNode[1][1]<<checkerBoard->chessNode[1][5];
                if(checkerBoard->chessNode[i][j])
                {
                    if(checkerBoard->chessNode[i][j] == WhiteTurn)
                        brush.setColor(Qt::white);
                    if(checkerBoard->chessNode[i][j] == BlackTurn)
                        brush.setColor(Qt::black);
                    p.setBrush(brush);
                    QPoint center(35*i+35, 35*j+35);
                    p.drawEllipse(center, 15, 15);
                }
            }
        }
    }
    isFirst = 0;

}

void PvP::mousePressEvent(QMouseEvent *event)
{
    turn = !turn;
    x = (event->x()-17.5)/35;
    y = (event->y()-17.5)/35;
    checkerBoard->chessNode[x][y] = turn+1;
//    qDebug()<<checkerBoard->chessNode[x][y];
    //qDebug()<<event->x()<<event->y();
    update();
}

/*
void PvP::mouseMoveEvent(QMouseEvent *event)
{
//    if(x<752.5 && x>17.5 && y<752.5 && y>17.5)
    {
        x = (event->x()-17.5)/35;
        y = (event->y()-17.5)/35;
        qDebug()<<x<<y;
    }
}
*/
