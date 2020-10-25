#include "server.h"
#include "ui_server.h"

Server::Server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);
    this->setWindowTitle("服务器:8888");

    tcpServer = new QTcpServer(this);
    tcpSocket = new QTcpSocket(this);

    tcpServer->listen(QHostAddress::Any, 8888);//设置服务器端口为8888

    //成功建立连接时，在服务器端显示文本
    connect(tcpServer, &QTcpServer::newConnection,
            [=](){
                tcpSocket = tcpServer->nextPendingConnection();//取出通信套接字
                QString ip = tcpSocket->peerAddress().toString();//取出ip地址
                qint16 port = tcpSocket->peerPort();//取出端口
                ui->textEdit_read->setText(QString("[%1:%2]:连接成功").arg(ip).arg(port));//显示文本

                connect(tcpSocket, &QTcpSocket::readyRead,
                        [=](){
                            QByteArray array = tcpSocket->readAll();
                            ui->textEdit_read->append(array);
                        }
                        );
            }
            );
}

Server::~Server()
{
    delete ui;
}

void Server::on_buttonSend_clicked()
{
    //将输入区的内容存储到str中
    QString str = ui->textEdit_write->toPlainText();
    //将str写入通信套接字
    tcpSocket->write(str.toUtf8().data());
    //清空写入区域
    ui->textEdit_write->clear();
}

void Server::on_buttonDisconnect_clicked()
{
    //与客户端主动断开连接
    tcpSocket->disconnectFromHost();
}
