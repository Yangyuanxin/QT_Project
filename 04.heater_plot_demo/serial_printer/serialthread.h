#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

#include <QFile>
#include <QMutex>
#include <QDebug>
#include <QObject>
#include <QThread>
#include <QVector>
#include <QTimer>
#include <QQueue>
#include <QTime>
#include <QCoreApplication>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <sstream>
#include <fstream>
#include <cstring>
#include <iostream>
#include "public_para.h"
using namespace std;

class SerialThread : public QObject
{
    Q_OBJECT
public:
    QMutex mutexlock;
    bool Start_Flag ;
    bool readyReceive ;
    ~SerialThread();
    explicit SerialThread(QString, long);

signals:
    void Data_Process(QByteArray);
    void reportProgress(FileProgress);
    void BusyRemove();

public slots:
    void sendLine();
    void get_temp_data();
    void timer_uart_rece();
    void read_serial_data();
    void injectCommand(QString);

    void GCode_File_To_3d_Printer();
    void close_gcode_file();
    void setFile(QString);
    void setGetPara(bool);
    bool getPara();

    void stopPrinting();
    void startPrinting();
    void pausePrinting();
    void recovery_print();
private:
    long myBaud;
    QString myport;
    QSerialPort *serial;
    QByteArray buffer ;
    QByteArray recv_buf ;

    bool paused;
    bool sending;
    bool continue_print ;
    bool busy_flag ;

    ifstream infile;
    QTimer *read_timer ;
    QTimer *view_temp_Timer ;


    QQueue <QString> userCommands;
    QQueue <QString> sendQueue;

    bool start_printer_flag ;
    bool get_printer_para ;

    QTimer *QueuePushTimer;
    QTimer *QueuePopTimer ;

    //long int currentLine;
    //long long int all_line ;
    long long int current_file_pos ;
    long long int current_file_size ;
};

#endif // SERIALTHREAD_H
