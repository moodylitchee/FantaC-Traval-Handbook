#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "define.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    status=new QLabel;

    setWindowTitle("客户端");
    ui->find->setEnabled(false);
    ui->refresh->setEnabled(false);
    ui->statusbar->addWidget(status);
    qDebug()<<"连接";

    socket=new QTcpSocket;
    socket->connectToHost(QHostAddress(QString("127.0.0.1")),10010);
    connect(socket,&QTcpSocket::connected,this,[=](){
        status->setText("已连接到服务器，IP：127.0.0.1，端口：10010");
        ui->find->setEnabled(true);
    });
    connect(this,&MainWindow::findreq,socket,[=](QString in){
        QString send_string=QString::number(SEND_COMMENT)+in;
        socket->write(send_string.toUtf8());
        qDebug()<<send_string;
    });
    connect(socket,&QTcpSocket::readyRead,this,[=](){
        QString data=socket->readAll();
        ui->cont->setText(data);
        status->setText("就绪");
        ui->refresh->setEnabled(true);
    });
    connect(this,&MainWindow::refreq,socket,[=](QString out){
        QString ref_string=QString::number(SEND_REFRESH)+out;
        socket->write(ref_string.toUtf8());
        ui->refresh->setEnabled(false);
        status->setText("已更新");
    });
    connect(socket,&QTcpSocket::disconnected,this,[=](){
        status->setText("已断开连接");
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_find_clicked()
{
    QString fs=ui->findtxt->text();
    qDebug()<<"find";
    emit findreq(fs);
}


void MainWindow::on_refresh_clicked()
{
    QString fr=ui->cont->toPlainText();
    qDebug()<<"refresh";
    emit refreq(fr);
}

