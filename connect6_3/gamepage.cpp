#include "gamepage.h"
#include <QPainter>
#include <QPen>
#include <QDebug>
#include <QMessageBox>
#include <QVector>
#include <utility>
#include <stdlib.h>
#include <stdio.h>
#include <QTimerEvent>

#define WhiteTurn 1
#define BlackTurn 2
const int board_size = 21;

gamepage::gamepage(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(1200, 800);
    this->move(350, 100);
    initial();

    b1.setParent(this);
    b1.setText("返回主菜单");
    b1.setGeometry(900, 600, 160, 60);

    connect(&b1, &QPushButton::clicked, this, &gamepage::slot1);//返回按钮
}

void gamepage::initial()
{
    x = 0;
    y = 0;
    turn = BlackTurn;
    if(gamemode == nullptr)
        gamemode = "PvP";
    for(int i=0;i<21;i++)
        for(int j=0;j<21;j++)
            checkerBoard[i][j] = 0;
}

void gamepage::AImove()
{
    getScore();  //计算分值

    //记录最大值的位置，若有多个点，记录最后一个搜索到的点
    int maxScore = 0;
    QVector<QPair<int, int>> maxPoints;//使用vector容器放最大值所在位置
    //vector<pair<int, int> > maxPoints;
    for (int row=1; row<board_size;row++)
        for (int col=1;col<board_size;col++)
        {
            // 前提是这个坐标是空的
            if (checkerBoard[row][col] == 0)
            {
                if (score[row][col] > maxScore)                 // 找最大的数和坐标
                {
                    maxPoints.clear();                          //发现新的最大值，清空容器内之前存储的所有元素
                    maxScore = score[row][col];
                    maxPoints.push_back(qMakePair(row, col));   //放入最新的最大值坐标
                }
                else if (score[row][col] == maxScore)           // 如果有多个最大的数，都放到容器中
                    maxPoints.push_back(qMakePair(row, col));
            }
        }
    // 随机落子，如果有多个点的话
    srand((unsigned)time(0));   //随机种子
    int index = rand() % maxPoints.size();  //随机下标，范围在容器容量

    QPair<int, int> pointPair = maxPoints.at(index);  //取出该位置元素
    x = pointPair.first;
    y = pointPair.second;    //赋值
    checkerBoard[x][y] = turn;
    turn = turn==1?2:1;

    update();
}



bool gamepage::isEnd()
{
    //判断胜利
    connectv=1, connecth=1, connectl=1, connectr=1;
    for(int i=1,j=-1;;)
    {
        if(checkerBoard[x][y+i] == checkerBoard[x][y]){
            i++;
            connectv++;
        }
        else if(checkerBoard[x][y+j] == checkerBoard[x][y]){
            j--;
            connectv++;
        }
        else
            break;
    }
    for(int i=1,j=-1;;)
    {
        if(checkerBoard[x+i][y] == checkerBoard[x][y]){
            i++;
            connecth++;
        }
        else if(checkerBoard[x+j][y] == checkerBoard[x][y]){
            j--;
            connecth++;
        }
        else
            break;
    }
    for(int i=1,j=-1,k=1,l=-1;;)
    {
        if(checkerBoard[x+j][y+i] == checkerBoard[x][y]){
            i++;
            j--;
            connectl++;
        }
        else if(checkerBoard[x+k][y+l] == checkerBoard[x][y]){
            k++;
            l--;
            connectl++;
        }
        else{
            break;
        }
    }
    for(int i=1,j=-1,k=1,l=-1;;)
    {
        if(checkerBoard[x+i][y+k] == checkerBoard[x][y]){
            i++;
            k++;
            connectr++;
        }
        else if(checkerBoard[x+j][y+l] == checkerBoard[x][y]){
            j--;
            l--;
            connectr++;
        }
        else
            break;
    }
    if(connectv>=6 || connecth>=6 || connectl>=6 || connectr>=6){
        if(turn == BlackTurn){
            win.setText("白棋胜利！");
        }
        else{
            win.setText("黑棋胜利！");
        }
        connect(&win, &QMessageBox::buttonClicked, this, &gamepage::slot1);
        win.show();
        return true;
    }
    return false;
}

bool gamepage::isDraw()
{
    for(int i=0;i<board_size;i++)
        for(int j=0;j<board_size;j++)
            if(checkerBoard[i][j] == 0)
                return false;
    draw.setText("和棋");
    connect(&draw, &QMessageBox::buttonClicked, this, &gamepage::slot1);
    draw.show();
    return true;
}

void gamepage::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    QPen pen;
    pen.setWidth(2);
    p.setPen(pen);
    //画棋盘
    for(int x=35;x<736;x+=35)
        p.drawLine(x,35,x,735);
    for(int y=35;y<736;y+=35)
        p.drawLine(35,y,735, y);

    //画棋子
    QBrush brush(Qt::white);
    for(int i=0;i<board_size;i++)
    {
        for(int j=0;j<board_size;j++)
        {
            if(checkerBoard[i][j])
            {
                if(checkerBoard[i][j] == WhiteTurn)
                    brush.setColor(Qt::white);
                if(checkerBoard[i][j] == BlackTurn)
                    brush.setColor(Qt::black);
                p.setBrush(brush);
                QPoint center(35*i+35, 35*j+35);
                p.drawEllipse(center, 15, 15);
            }
        }
    }
}

void gamepage::mousePressEvent(QMouseEvent *event)
{
    if(gamemode == "PvP"){
        x = (event->x()-17.5)/35;
        y = (event->y()-17.5)/35;
        //判断下棋的合法性
        if(checkerBoard[x][y] != 0){
            box.setText("该处已有棋子！");
            box.show();
            turn = turn==1?2:1;
        }
        else
            checkerBoard[x][y] = turn;
        turn = turn==1?2:1;
        isEnd();
    }

    else if(gamemode == "PvE"){
        x = (event->x()-17.5)/35;
        y = (event->y()-17.5)/35;
        //判断下棋的合法性
        if(checkerBoard[x][y] != 0){
            box.setText("该处已有棋子！");
            box.show();
            turn = turn==1?2:1;
        }
        else
            checkerBoard[x][y] = turn;
        turn = turn==1?2:1;
        isEnd();
        isDraw();
        AImove();
        isEnd();
        isDraw();
    }

    else if(gamemode == "EvE"){
        id = startTimer(500);
    }

    else{
        id = startTimer(500);
    }

    update();

}

void gamepage::timerEvent(QTimerEvent *event)
{
    //判断游戏类型
    if(gamemode == "EvE"){
        AImove();
        if(isDraw())
            killTimer(id);
        if(isEnd())
            killTimer(id);
    }
    //若为network模式，则发送整个棋面信息
    //server端的agent执黑棋，client端的agent执白棋
    else{        
        if(turn == BlackTurn){
            AImove();
            if(isDraw())
                killTimer(id);
            if(isEnd())
                killTimer(id);
            sendBoardMessage();
        }
        else{
            AImove();
            if(isDraw())
                killTimer(id);
            if(isEnd())
                killTimer(id);
            sendBoardMessage();
        }
    }
}

void gamepage::sendBoardMessage()
{
    //将棋面数据转化为QString类型
    QString str;
    for(int i=0;i<board_size;i++){
        for(int j=0;j<board_size;j++){
            if(checkerBoard[i][j] == 0)
                str[i*board_size+j] = '0';
            else if(checkerBoard[i][j] == BlackTurn)
                str[i*board_size+j] = '2';
            else
                str[i*board_size+j] = '1';
        }
    }
    //发送棋面信息
    if(turn == BlackTurn){
        server.tcpSocket->write(str.toUtf8().data());
    }
    else{
        client.tcpSocket->write(str.toUtf8().data());
    }
}

void gamepage::slot1()
{
    emit back();//返回主菜单信号
}

void gamepage::getScore()
{
    int value=0;
    int value2=0;
    int flag=1;   //白子
    int flag2=2;    //黑子

    //初始化score
    for(int i=0;i<board_size;i++)
        for(int j=0;j<board_size;j++)
            score[i][j] = 0;

    for(int x=0;x<board_size;x++)
        {
            for(int y=0;y<board_size;y++)
            {
                if(checkerBoard[x][y]!=0) continue;
                value=0;
                value2=0;

                for(int i=-1;i<=1;i++)
                {
                    for(int j=-1;j<=1;j++)
                    {
                        if(x+6*i>=0&&x+6*i<board_size&&y+6*j>=0&&y+6*j<board_size&&x+5*i>=0&&y+5*j>=0&&x+4*i>=0&&y+4*j>=0
                                &&x+3*i>=0&&y+3*j>=0&&x+2*i>=0&&y+2*j>=0&&x+i>=0
                                &&y+j>=0&&x+5*i<board_size&&y+5*j<board_size&&x+4*i<board_size&&y+4*j<board_size
                                &&x+3*i<board_size&&y+3*j<board_size&&x+2*i<board_size&&y+2*j<board_size&&x+i<board_size
                                &&y<board_size&&checkerBoard[x+i*1][y+j*1]==flag
                                &&checkerBoard[x+i*2][y+j*2]==flag&&checkerBoard[x+i*3][y+j*3]==flag
                                &&checkerBoard[x+i*4][y+j*4]==flag&&checkerBoard[x+i*5][y+j*5]==flag&&checkerBoard[x+i*6][y+j*6]==0) //活五
                        {
                            value+=600000;
                        }
                        else if(x+6*i>=0&&x+6*i<board_size&&y+6*j>=0&&y+6*j<board_size&&x+5*i>=0&&y+5*j>=0&&x+4*i>=0&&y+4*j>=0
                                &&x+3*i>=0&&y+3*j>=0&&x+2*i>=0&&y+2*j>=0&&x+i>=0
                                &&y+j>=0&&x+5*i<board_size&&y+5*j<board_size&&x+4*i<board_size&&y+4*j<board_size
                                &&x+3*i<board_size&&y+3*j<board_size&&x+2*i<board_size&&y+2*j<board_size&&x+i<board_size
                                &&y<board_size&&checkerBoard[x+i*1][y+j*1]==flag
                                &&checkerBoard[x+i*2][y+j*2]==flag&&checkerBoard[x+i*3][y+j*3]==flag
                                &&checkerBoard[x+i*4][y+j*4]==flag&&checkerBoard[x+i*5][y+j*5]&&checkerBoard[x+i*6][y+j*6]==1)   //死五
                        {
                            value+=500000;
                        }
                        else if(x+5*i>=0&&y+5*j>=0&&x+4*i>=0&&y+4*j>=0
                                &&x+3*i>=0&&y+3*j>=0&&x+2*i>=0&&y+2*j>=0&&x+i>=0
                                &&y+j>=0&&x+5*i<board_size&&y+5*j<board_size&&x+4*i<board_size&&y+4*j<board_size
                                &&x+3*i<board_size&&y+3*j<board_size&&x+2*i<board_size&&y+2*j<board_size&&x+i<board_size
                                &&y<board_size&&checkerBoard[x+i*1][y+j*1]==flag
                                &&checkerBoard[x+i*2][y+j*2]==flag&&checkerBoard[x+i*3][y+j*3]==flag
                                &&checkerBoard[x+i*4][y+j*4]==flag&&checkerBoard[x+i*5][y+j*5]==0)  //活四
                        {
                            value+=400000;
                        }
                        else if(x+5*i>=0&&y+5*j>=0&&x+4*i>=0&&y+4*j>=0
                                &&x+3*i>=0&&y+3*j>=0&&x+2*i>=0&&y+2*j>=0&&x+i>=0
                                &&y+j>=0&&x+5*i<board_size&&y+5*j<board_size&&x+4*i<board_size&&y+4*j<board_size
                                &&x+3*i<board_size&&y+3*j<board_size&&x+2*i<board_size&&y+2*j<board_size&&x+i<board_size
                                &&y<board_size&&checkerBoard[x+i*1][y+j*1]==flag
                                &&checkerBoard[x+i*2][y+j*2]==flag&&checkerBoard[x+i*3][y+j*3]==flag
                                &&checkerBoard[x+i*4][y+j*4]==flag&&checkerBoard[x+i*5][y+j*5]==1)  //死四
                        {
                            value+=250000;
                        }
                        else if(x+4*i>=0&&y+4*j>=0
                                &&x+3*i>=0&&y+3*j>=0&&x+2*i>=0&&y+2*j>=0&&x+i>=0
                                &&y+j>=0&&x+4*i<board_size&&y+4*j<board_size
                                &&x+3*i<board_size&&y+3*j<board_size&&x+2*i<board_size&&y+2*j<board_size&&x+i<board_size
                                &&y<board_size&&checkerBoard[x+i*1][y+j*1]==flag
                                &&checkerBoard[x+i*2][y+j*2]==flag&&checkerBoard[x+i*3][y+j*3]==flag
                                &&checkerBoard[x+i*4][y+j*4]==0)  //活三
                         {
                             value+=300000;
                         }
                        else if(x+4*i>=0&&y+4*j>=0
                                &&x+3*i>=0&&y+3*j>=0&&x+2*i>=0&&y+2*j>=0&&x+i>=0
                                &&y+j>=0&&x+4*i<board_size&&y+4*j<board_size
                                &&x+3*i<board_size&&y+3*j<board_size&&x+2*i<board_size&&y+2*j<board_size&&x+i<board_size
                                &&y<board_size&&checkerBoard[x+i*1][y+j*1]==flag
                                &&checkerBoard[x+i*2][y+j*2]==flag&&checkerBoard[x+i*3][y+j*3]==flag
                                &&checkerBoard[x+i*4][y+j*4]==1)  //死三
                        {
                            value+=150000;
                        }
                        else if(x+3*i>=0&&y+3*j>=0&&x+2*i>=0&&y+2*j>=0&&x+i>=0
                                &&y+j>=0&&x+3*i<board_size&&y+3*j<board_size&&x+2*i<board_size&&y+2*j<board_size&&x+i<board_size
                                &&y<board_size&&checkerBoard[x+i*1][y+j*1]==flag
                                &&checkerBoard[x+i*2][y+j*2]==flag&&checkerBoard[x+i*3][y+j*3]==0)  //活二
                        {
                            value+=200000;
                        }
                        else if(x+3*i>=0&&y+3*j>=0&&x+2*i>=0&&y+2*j>=0&&x+i>=0
                                &&y+j>=0&&x+3*i<board_size&&y+3*j<board_size&&x+2*i<board_size&&y+2*j<board_size&&x+i<board_size
                                &&y<board_size&&checkerBoard[x+i*1][y+j*1]==flag
                                &&checkerBoard[x+i*2][y+j*2]==flag&&checkerBoard[x+i*3][y+j*3]==1)  //死二
                        {
                            value+=100000;
                        }
                        else if(x+1*i>=0&&x+1*i<board_size&&y+1*j>=0&&y+j*1<board_size&&checkerBoard[x+1*i][y+1*j]==flag)  //一个棋子
                        {
                            value+=2000;
                        }
                        else  //其他
                        {
                            value+=1000;
                        }
                    }
                }

                for(int i=-1;i<=1;i++)
                {
                    for(int j=-1;j<=1;j++)
                    {
                        if(x+6*i>=0&&x+6*i<board_size&&y+6*j>=0&&y+6*j<board_size&&x+5*i>=0&&y+5*j>=0&&x+4*i>=0&&y+4*j>=0
                                &&x+3*i>=0&&y+3*j>=0&&x+2*i>=0&&y+2*j>=0&&x+i>=0
                                &&y+j>=0&&x+5*i<board_size&&y+5*j<board_size&&x+4*i<board_size&&y+4*j<board_size
                                &&x+3*i<board_size&&y+3*j<board_size&&x+2*i<board_size&&y+2*j<board_size&&x+i<board_size
                                &&y<board_size&&checkerBoard[x+i*1][y+j*1]==flag2
                                &&checkerBoard[x+i*2][y+j*2]==flag2&&checkerBoard[x+i*3][y+j*3]==flag2
                                &&checkerBoard[x+i*4][y+j*4]==flag2&&checkerBoard[x+i*5][y+j*5]==flag2&&checkerBoard[x+i*6][y+j*6]==0) //活五
                        {
                            value2+=600000;
                        }
                        else if(x+6*i>=0&&x+6*i<board_size&&y+6*j>=0&&y+6*j<board_size&&x+5*i>=0&&y+5*j>=0&&x+4*i>=0&&y+4*j>=0
                                &&x+3*i>=0&&y+3*j>=0&&x+2*i>=0&&y+2*j>=0&&x+i>=0
                                &&y+j>=0&&x+5*i<board_size&&y+5*j<board_size&&x+4*i<board_size&&y+4*j<board_size
                                &&x+3*i<board_size&&y+3*j<board_size&&x+2*i<board_size&&y+2*j<board_size&&x+i<board_size
                                &&y<board_size&&checkerBoard[x+i*1][y+j*1]==flag2
                                &&checkerBoard[x+i*2][y+j*2]==flag2&&checkerBoard[x+i*3][y+j*3]==flag2
                                &&checkerBoard[x+i*4][y+j*4]==flag2&&checkerBoard[x+i*5][y+j*5]==flag2&&checkerBoard[x+i*6][y+j*6]==-1)   //死五
                        {
                            value2+=500000;
                        }
                        else if(x+5*i>=0&&y+5*j>=0&&x+4*i>=0&&y+4*j>=0
                                &&x+3*i>=0&&y+3*j>=0&&x+2*i>=0&&y+2*j>=0&&x+i>=0
                                &&y+j>=0&&x+5*i<board_size&&y+5*j<board_size&&x+4*i<board_size&&y+4*j<board_size
                                &&x+3*i<board_size&&y+3*j<board_size&&x+2*i<board_size&&y+2*j<board_size&&x+i<board_size
                                &&y<board_size&&checkerBoard[x+i*1][y+j*1]==flag2
                                &&checkerBoard[x+i*2][y+j*2]==flag2&&checkerBoard[x+i*3][y+j*3]==flag2
                                &&checkerBoard[x+i*4][y+j*4]==flag2&&checkerBoard[x+i*5][y+j*5]==0)  //活四
                        {
                            value2+=400000;
                        }
                        else if(x+5*i>=0&&y+5*j>=0&&x+4*i>=0&&y+4*j>=0
                                &&x+3*i>=0&&y+3*j>=0&&x+2*i>=0&&y+2*j>=0&&x+i>=0
                                &&y+j>=0&&x+5*i<board_size&&y+5*j<board_size&&x+4*i<board_size&&y+4*j<board_size
                                &&x+3*i<board_size&&y+3*j<board_size&&x+2*i<board_size&&y+2*j<board_size&&x+i<board_size
                                &&y<board_size&&checkerBoard[x+i*1][y+j*1]==flag2
                                &&checkerBoard[x+i*2][y+j*2]==flag2&&checkerBoard[x+i*3][y+j*3]==flag2
                                &&checkerBoard[x+i*4][y+j*4]==flag2&&checkerBoard[x+i*5][y+j*5]==-1)  //死四
                        {
                            value2+=250000;
                        }
                        else if(x+4*i>=0&&y+4*j>=0
                                &&x+3*i>=0&&y+3*j>=0&&x+2*i>=0&&y+2*j>=0&&x+i>=0
                                &&y+j>=0&&x+4*i<board_size&&y+4*j<board_size
                                &&x+3*i<board_size&&y+3*j<board_size&&x+2*i<board_size&&y+2*j<board_size&&x+i<board_size
                                &&y<board_size&&checkerBoard[x+i*1][y+j*1]==flag2
                                &&checkerBoard[x+i*2][y+j*2]==flag2&&checkerBoard[x+i*3][y+j*3]==flag2
                                &&checkerBoard[x+i*4][y+j*4]==0)  //活三
                         {
                             value2+=300000;
                         }
                        else if(x+4*i>=0&&y+4*j>=0
                                &&x+3*i>=0&&y+3*j>=0&&x+2*i>=0&&y+2*j>=0&&x+i>=0
                                &&y+j>=0&&x+4*i<board_size&&y+4*j<board_size
                                &&x+3*i<board_size&&y+3*j<board_size&&x+2*i<board_size&&y+2*j<board_size&&x+i<board_size
                                &&y<board_size&&checkerBoard[x+i*1][y+j*1]==flag2
                                &&checkerBoard[x+i*2][y+j*2]==flag2&&checkerBoard[x+i*3][y+j*3]==flag2
                                &&checkerBoard[x+i*4][y+j*4]==-1)  //死三
                        {
                            value2+=150000;
                        }
                        else if(x+3*i>=0&&y+3*j>=0&&x+2*i>=0&&y+2*j>=0&&x+i>=0
                                &&y+j>=0&&x+3*i<board_size&&y+3*j<board_size&&x+2*i<board_size&&y+2*j<board_size&&x+i<board_size
                                &&y<board_size&&checkerBoard[x+i*1][y+j*1]==flag2
                                &&checkerBoard[x+i*2][y+j*2]==flag2&&checkerBoard[x+i*3][y+j*3]==0)  //活二
                        {
                            value2+=200000;
                        }
                        else if(x+3*i>=0&&y+3*j>=0&&x+2*i>=0&&y+2*j>=0&&x+i>=0
                                &&y+j>=0&&x+3*i<board_size&&y+3*j<board_size&&x+2*i<board_size&&y+2*j<board_size&&x+i<board_size
                                &&y<board_size&&checkerBoard[x+i*1][y+j*1]==flag2
                                &&checkerBoard[x+i*2][y+j*2]==flag2&&checkerBoard[x+i*3][y+j*3]==-1)  //死二
                        {
                            value2+=100000;
                        }
                        else if(x+1*i>=0&&x+1*i<board_size&&y+1*j>=0&&y+j*1<board_size&&checkerBoard[x+1*i][y+1*j]==flag2)  //一个棋子
                        {
                            value2+=2000;
                        }
                        else        //其他
                        {
                            value2+=1000;
                        }
                    }
                }

                score[x][y]=value>value2?value:value2;
        }
    }

}

