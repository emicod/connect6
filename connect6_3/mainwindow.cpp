#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>
#include <QAction>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1200, 800);
    this->move(350, 100);
    QMenuBar *menubar = menuBar();
    QMenu *menu1 = menubar->addMenu("游戏模式");
    QMenu *menu2 = menubar->addMenu("游戏规则");
    QAction *action1 = menu1->addAction("PvP");
    QAction *action2 = menu1->addAction("PvE");
    QAction *action3 = menu1->addAction("EvE");
    QAction *action4 = menu1->addAction("network");
    QAction *action5 = menu2->addAction("游戏规则");

    QMessageBox box;//游戏规则提示窗口

    connect(action1, &QAction::triggered,[=](){page.gamemode = "PvP";});
    connect(action2, &QAction::triggered,[=](){page.gamemode = "PvE";});
    connect(action3, &QAction::triggered,[=](){page.gamemode = "EvE";});
    connect(action4, &QAction::triggered,[=](){page.gamemode = "network";});
    connect(action5, &QAction::triggered,
            [=](){
                     QMessageBox::about(this,
                     "游戏规则", "双方分别使用黑白两色的棋子，下在棋盘直线与横线的交叉点上，先形成六子连线者获胜。");
                }
            );

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::slot1);//开始游戏按钮
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::close);//退出游戏按钮
    connect(&page, &gamepage::back, this, &MainWindow::slot2);//返回按钮

    //网络模式下显示服务器与客户端
    connect(ui->pushButton, &QPushButton::clicked,
            [=](){
                if(page.gamemode == "network"){
                    page.server.show();
                    page.client.show();
                }
            }
            );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot1()
{
    this->hide();
    page.show();
    page.initial();
}

void MainWindow::slot2()
{
    this->show();
    page.hide();
}

