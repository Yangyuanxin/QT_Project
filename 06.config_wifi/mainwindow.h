#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QDateTime>
#include <QVariant>
#include <QString>
#include <QSettings>
#include <QProcess>
#include <QDebug>
#include <QTimer>
#include <QMutex>
#include<QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:

private slots:

    void on_Connect_server_clicked();

    void Read_NetWork_Data();

    void on_SEND_SSID_AND_PASSWORD_clicked();
    void on_SEND_SERVER_IP_AND_PORT_clicked();

private:
    Ui::MainWindow *ui;
    int Number ;
    int Serach_Number ;
    QString str_value ;
    QTcpSocket* m_client;
};

#endif // MAINWINDOW_H
