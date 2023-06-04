#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>
#include "filetree.h"
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_disconnect_clicked();

signals:
    void find(QString);

private:
    Ui::MainWindow *ui;
    QTcpServer *server;
    fileTree *ft;

    qint32 con_cnt;
    QVector<QTcpSocket*> socket;
};
#endif // MAINWINDOW_H
