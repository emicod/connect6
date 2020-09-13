#ifndef GAMESTART_H
#define GAMESTART_H

#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <SelectMode.h>

QT_BEGIN_NAMESPACE
namespace Ui { class GameStart; }
QT_END_NAMESPACE

class GameStart : public QMainWindow
{
    Q_OBJECT

public:
    GameStart(QWidget *parent = nullptr);
    ~GameStart();

    QMessageBox box;
    QPushButton b1;
    QPushButton b2;
    SelectMode m;

    void slot1();
    void slot2();

    Ui::GameStart *ui;
};
#endif // GAMESTART_H
