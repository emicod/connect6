#include "GameStart.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameStart w;
    w.show();
    return a.exec();
}
