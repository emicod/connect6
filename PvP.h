#ifndef PVP_H
#define PVP_H

#include <QMainWindow>
#include <QWidget>
#include <CheckerBoard.h>

class PvP : public QWidget
{
    Q_OBJECT
public:
    explicit PvP(QWidget *parent = nullptr);

    int x, y;
    bool isFirst;
    bool isChess;
    CheckerBoard checherBoard;

    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

signals:

};

#endif // PVP_H
