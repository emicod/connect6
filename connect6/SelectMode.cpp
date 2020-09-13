#include "SelectMode.h"

SelectMode::SelectMode(QWidget *parent) : QMainWindow(parent)
{
    this->setWindowTitle("六子棋");
    this->setGeometry(400, 200, 1000, 600);

    b1.setParent(this);
    b1.setText("PvP");
    b1.setGeometry(450, 200, 100, 30);

    b2.setParent(this);
    b2.setText("PvE");
    b2.setGeometry(450, 300, 100, 30);

    b3.setParent(this);
    b3.setText("EvE");
    b3.setGeometry(450, 400, 100, 30);

    b4.setParent(this);
    b4.setText("返回");
    b4.setGeometry(450, 500, 100, 30);


    connect(&b4, &QPushButton::clicked, this, &SelectMode::slot1);



}

void SelectMode::slot1()
{
    emit signal1();
}
