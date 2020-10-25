#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class Server;
}

class Server : public QWidget
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = nullptr);
    ~Server();

    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;

private slots:
    void on_buttonSend_clicked();

    void on_buttonDisconnect_clicked();

private:
    Ui::Server *ui;
};

#endif // SERVER_H
