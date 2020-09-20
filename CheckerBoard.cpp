#include "CheckerBoard.h"
#include <QString>
#include <QDebug>

CheckerBoard::CheckerBoard()
{
    for(int i=0;i<21;i++)
        for(int j=0;j<22;j++)
            chessNode[i][j] = 0;
//    qDebug()<<"constructor of CheckerBoard is excecuted!";
}
