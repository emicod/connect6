#ifndef SELECTMODE_H
#define SELECTMODE_H

#include <QMainWindow>
#include <QPushButton>
#include <QPaintEvent>
#include <QPainter>
#include "PvP.h"

class SelectMode : public QMainWindow
{
    Q_OBJECT
public:
    explicit SelectMode(QWidget *parent = nullptr);

    bool flag = 0;

    QPushButton b1;
    QPushButton b2;
    QPushButton b3;
    QPushButton b4;

    PvP pvp;

    void slot1();//用于返回的槽函数
    void slot2();//PvP模式

signals:
    void signal1();

};

#endif // SELECTMODE_H
