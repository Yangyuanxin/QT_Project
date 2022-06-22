#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::Register_Uart_thread()
{
    uartThread = new QThread(this);
    uartWorker  = new SerialThread(Sensor_Uart,Sensor_Baud);
    uartWorker->moveToThread(uartThread);
    connect(uartThread, &QThread::finished, uartWorker, &QObject::deleteLater);
    connect(uartWorker, &SerialThread::reportProgress, this, &MainWindow::updateFileProgress);
    connect(this, &MainWindow::startPrinting, uartWorker, &SerialThread::startPrinting);
    connect(this, &MainWindow::stopPrinting, uartWorker, &SerialThread::stopPrinting);
    connect(this, &MainWindow::pausePrinting, uartWorker, &SerialThread::pausePrinting);
    connect(this, &MainWindow::recovery_print, uartWorker, &SerialThread::recovery_print);
    connect(this, &MainWindow::send_gcode_cmd, uartWorker, &SerialThread::injectCommand);
    connect(this, &MainWindow::send_gcode_file, uartWorker, &SerialThread::setFile);
    connect(this, &MainWindow::setBusy, uartWorker, &SerialThread::setGetPara);
    uartThread->start();
    uartThread->setPriority(QThread::TimeCriticalPriority);
}

void MainWindow::Register_Protocol_Parse_thread()
{
    parserThread = new QThread(this);
    parseWorker = new protocol_parse();
    parseWorker->moveToThread(parserThread);
    connect(parserThread, &QThread::finished, parseWorker, &QObject::deleteLater);
    connect(parseWorker, &protocol_parse::report_heater_temp, this, &MainWindow::Display_Heater_Temp);
    connect(uartWorker, &SerialThread::Data_Process, parseWorker, &protocol_parse::Data_Process);
    parserThread->start();
    parserThread->setPriority(QThread::HighestPriority);
}

