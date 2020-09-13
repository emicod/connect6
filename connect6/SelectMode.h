#ifndef SELECTMODE_H
#define SELECTMODE_H

#include <QMainWindow>
#include <QPushButton>

class SelectMode : public QMainWindow
{
    Q_OBJECT
public:
    explicit SelectMode(QWidget *parent = nullptr);

    QPushButton b1;
    QPushButton b2;
    QPushButton b3;
    QPushButton b4;

    void slot1();

signals:
    void signal1();

};

#endif // SELECTMODE_H
