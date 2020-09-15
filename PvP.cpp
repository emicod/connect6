#include "PvP.h"
#include <QPainter>
#include <QEvent>
#include <QPen>
#include <QTimer>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>

PvP::PvP(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("PvP模式");
    this->setGeometry(400, 150, 1000, 780);
//    setMouseTracking(true);

    x = 0;
    y = 0;
    isFirst = 1;
    isChess = 0;
}

void PvP::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    QPen pen;
    pen.setWidth(2);
    p.setPen(pen);
//    if(isFirst)
    {
        for(int x=35;x<701;x+=35)
            p.drawLine(x,35,x,700);
        for(int y=35;y<701;y+=35)
            p.drawLine(35,y,700, y);
        isFirst = 0;
    }
    if(isChess)
    {
        pen.setWidth(40);
        p.drawPoint(35*x+35, 35*y+35);
    }

}

void PvP::mousePressEvent(QMouseEvent *event)
{
    x = (event->x()-17.5)/35;
    y = (event->y()-17.5)/35;
    if(x<21 && y<21)
        isChess = 1;
    qDebug()<<event->x()<<event->y();
    qDebug()<<x<<y;
    update();
}

void PvP::mouseMoveEvent(QMouseEvent *event)
{
//    if(x<752.5 && x>17.5 && y<752.5 && y>17.5)
    {
        x = (event->x()-17.5)/35;
        y = (event->y()-17.5)/35;
        qDebug()<<x<<y;
    }
}

