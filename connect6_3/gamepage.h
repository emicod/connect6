#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include "server.h"
#include "client.h"
#include <QWidget>
#include <QString>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QMessageBox>
#include <QPushButton>
#include <QTimerEvent>

class gamepage : public QWidget
{
    Q_OBJECT
public:
    explicit gamepage(QWidget *parent = nullptr);

    bool flag1, flag2;//判断是否和棋或胜利
    int id;//定时器id，用于killtimer
    int x, y, turn, connectv, connecth, connectl, connectr;
    int checkerBoard[21][21], score[21][21];//0代表无棋子，1代表白棋，2代表黑棋
    QString gamemode;
    QMessageBox box;//鼠标点击处已有棋子时弹出
    QMessageBox win;//胜利时弹出
    QMessageBox draw;//和棋时弹出
    QPushButton b1;

    Server server;//服务器
    Client client;//客户端


    void initial();//初始化棋盘
    void AImove();//AI下棋
    void getScore();//计算棋盘上每个点的值（用于AI算法）
    bool isEnd();//判断输赢
    bool isDraw();//判断和棋
    void sendBoardMessage();

    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

public slots:
    void slot1();

signals:
    void back();

};

#endif // GAMEPAGE_H
