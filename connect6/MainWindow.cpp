#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("六子棋");

    b1.setParent(this);
    b1.setText("开始游戏");
    b1.setGeometry(350,500,100,30);
    b1.show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

