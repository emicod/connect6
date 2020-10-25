#include "client.h"
#include "ui_client.h"
#include <QHostAddress>

Client::Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    this->setWindowTitle("客户端");

    tcpSocket = new QTcpSocket(this);

    //与服务器连接成功时输出文本
    connect(tcpSocket, &QTcpSocket::connected,
            [=](){
                ui->textEdit_read->setText("成功与服务器建立链接");
            }
            );

    connect(tcpSocket, &QTcpSocket::readyRead,
            [=](){
                //读取Socket中的内容
                QByteArray array = tcpSocket->readAll();
                //写入client的编辑区
                ui->textEdit_read->append(array);
            }
            );

}

Client::~Client()
{
    delete ui;
}

void Client::on_buttonConnect_clicked()
{
    //获取端口和ip
    QString ip = ui->lineEdit_ip->text();
    qint16 port = ui->lineEdit_port->text().toUInt();
    //根据端口和ip建立连接
    tcpSocket->connectToHost(QHostAddress(ip), port);
}

void Client::on_buttonSend_clicked()
{
    //获取编辑区的内容
    QString str = ui->textEdit_write->toPlainText();
    //将内容写入Socket
    tcpSocket->write(str.toUtf8().data());
    //清空写入区域
    ui->textEdit_write->clear();
}

void Client::on_buttonDisconnect_clicked()
{
    //与服务器主动断开连接
    tcpSocket->disconnectFromHost();
}
