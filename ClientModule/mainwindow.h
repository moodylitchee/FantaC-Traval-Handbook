#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QLabel>

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
    void on_refresh_clicked();

    void on_find_clicked();

signals:
    void findreq(QString);
    void refreq(QString);

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QLabel *status;

};
#endif // MAINWINDOW_H
