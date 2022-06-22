#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QFile>
#include <QDebug>
#include <QtMath>
#include <QThread>
#include <QObject>
#include <QPainter>
#include <QMainWindow>
#include <QFileDialog>
#include "public_para.h"
#include "serial_printer/serialthread.h"
#include "protocol_parse/protocol_parse.h"

#include "qcustomplot.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void init_control_page_ui();
    void init_3d_printer_uart();
    void Register_MetaType();

    void Register_Uart_thread();
    void Register_Protocol_Parse_thread();

signals:
    void setBusy(bool);
    void stopPrinting();
    void startPrinting();
    void pausePrinting();
    void recovery_print();
    void send_gcode_file(QString);
    void setGodeFile(QString filename);
    void send_gcode_cmd(QByteArray cmd);
    void openFile(const QString &filepath);

public slots:
    void updateFileProgress(FileProgress p);
    void GCode_File_Info(int size,int all_layer_num);
    void Display_Heater_Temp(double,double,double,double);

private slots:
    void on_debug_clicked();
    void on_open_gcode_file_clicked();
    void on_start_print_clicked();
    void on_pause_print_clicked();
    void on_stop_print_clicked();
    void on_recovery_print_clicked();
    void on_send_cmd_clicked();
    void on_clear_plot_clicked();

private:
    Ui::MainWindow *ui;
    SerialThread   *uartWorker;
    protocol_parse *parseWorker;
    QThread *parserThread;
    QThread *uartThread;
    int count;
};
#endif // MAINWINDOW_H
