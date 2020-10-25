#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QTcpSocket>

namespace Ui {
class Client;
}

class Client : public QWidget
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);
    ~Client();

    QTcpSocket *tcpSocket;

private slots:
    void on_buttonConnect_clicked();

    void on_buttonSend_clicked();

    void on_buttonDisconnect_clicked();

private:
    Ui::Client *ui;
};

#endif // CLIENT_H
