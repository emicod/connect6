#include "GameStart.h"
#include "ui_GameStart.h"
#include <QMessageBox>
#include <QPushButton>

GameStart::GameStart(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameStart)
{
    ui->setupUi(this);
    this->setWindowTitle("六子棋");
    this->setGeometry(400, 200, 1000, 600);

    b1.setParent(this);
    b1.setText("游戏规则");
    b1.setGeometry(450, 300, 100, 30);

    b2.setParent(this);
    b2.setText("开始游戏");
    b2.setGeometry(450, 400, 100, 30);

    box.setWindowTitle("游戏规则");
    box.setText("双方分别使用黑白两色的棋子，下在棋盘直线与横线的交叉点上，先形成六子连线者获胜。");

    connect(&b1, &QPushButton::clicked, &box, &QMessageBox::show);
    connect(&b2, &QPushButton::clicked, this, &GameStart::slot1);
    connect(&m, &SelectMode::signal1, this, &GameStart::slot2);

}

GameStart::~GameStart()
{
    delete ui;
}

void GameStart::slot1()
{
    this->hide();
    m.show();
}

void GameStart::slot2()
{
    this->show();
    m.hide();
}



