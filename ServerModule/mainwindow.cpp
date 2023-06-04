#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "define.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    server=new QTcpServer(this);
    server->listen(QHostAddress(QString("127.0.0.1")),10010);
    ui->text->append("连接已建立\n");
    setWindowTitle("服务器");
    ft=new fileTree;

    ui->disconnect->setEnabled(true);

    connect(server,&QTcpServer::newConnection,this,[=](){
        QTcpSocket* tsocket=server->nextPendingConnection();
        socket.append(tsocket);
        con_cnt++;

        connect(tsocket,&QTcpSocket::connected,this,[=](){
            ui->disconnect->setEnabled(true);
        });
        connect(tsocket,&QTcpSocket::readyRead,this,[=](){
            qint32 ff=tsocket->read(5).toInt();
            QString fl=tsocket->readAll();
            qDebug()<<fl;
            if(ff==SEND_COMMENT){
                tsocket->write(ft->find(fl).toUtf8());
                ui->text->append("用户访问："+fl+"\n");
            }
            else if(ff==SEND_REFRESH){
                ft->refresh(ft->last_find,fl);
                ui->text->append("用户修改："+ft->last_find+"为"+fl+"\n");
            }
        });
        connect(tsocket,&QTcpSocket::disconnected,this,[=](){
            tsocket->close();
            tsocket->deleteLater();
            socket.removeAll(tsocket);
            con_cnt--;
            ui->text->append("连接已断开\n");
        });
    });
}

MainWindow::~MainWindow()
{
    delete ui;
    delete ft;
    delete server;
}


void MainWindow::on_disconnect_clicked()
{
    for(auto i=socket.begin();i!=socket.end();i++){
        (*i)->close();
        (*i)->deleteLater();
    }
    con_cnt=0;
}

