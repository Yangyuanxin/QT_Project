#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QSerialPort>        //提供访问串口的功能
#include <QSerialPortInfo>    //提供系统中存在的串口的信息
#include "qcustomplot.h"      //包含Qcustomplot库

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void Init_Serial_Para();
    void sensor_data_preprocess(int x, int y) ;
    /*画曲线函数*/
    void Sensor_Draw_Plot(QCustomPlot *customPlot, QVector<double> x, QVector<double> y);

private:
    Ui::MainWindow *ui;
    QSerialPort *Serial ;

    long last_index ;
    QVector<double> display_x;
    QVector<double> display_y;
    QString Serial_Port , Serial_Bauardate,Serial_PariteyBit,Serial_DataBit,Serial_StopBit ;

private slots:
    void Update_Serial_Port(QString Currnet_Select);
    void Update_Serial_Baurdrate(QString Currnet_Select);
    void Update_Serial_ParityBit(QString Currnet_Select);
    void Update_Serial_DataBit(QString Currnet_Select);
    void Update_Serial_StopBit(QString Currnet_Select);
    void on_Connect_Device_clicked();
    void on_Disconnect_Device_clicked();

    void cmd_recv_process();
    void on_Clear_Plot_clicked();
};

#endif // MAINWINDOW_H
