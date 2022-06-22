#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::init_control_page_ui()
{
    //this->setGeometry(0,0,600,1024);
    qDebug() << "主线程: " << QThread::currentThread();
    // this->setWindowFlags(Qt::FramelessWindowHint);
}

void MainWindow::GCode_File_Info(int size,int all_layer_num)
{
    ui->model_size->setText(QString("%1KB").arg(size));
    ui->all_layer_num->setText(QString("%1").arg(all_layer_num));

    ui->start_print->setEnabled(true);
    ui->stop_print->setEnabled(false);
    ui->pause_print->setEnabled(false);
    ui->recovery_print->setEnabled(false);
}

void MainWindow::Register_MetaType()
{
    qRegisterMetaType< QVector<QString> >("QList<QString>");
    qRegisterMetaType<FileProgress>("FileProgress");
}

void MainWindow::init_3d_printer_uart()
{
    this->Register_MetaType();
    this->Register_Uart_thread();
    this->Register_Protocol_Parse_thread();
    ui->all_layer_num->setText("0");
    ui->stop_print->setEnabled(false);
    ui->pause_print->setEnabled(false);
    ui->recovery_print->setEnabled(false);
    ui->start_print->setEnabled(false);
    ui->debug->setEnabled(true);
    QCPTextElement *m_title;
    ui->curveShowWidget->plotLayout()->insertRow(0);
    m_title = new QCPTextElement(ui->curveShowWidget,QString(tr("3D打印机喷头-热床温度曲线显示")));
    m_title->setTextColor(QColor(0,0,0));
    ui->curveShowWidget->plotLayout()->addElement(0, 0, m_title);
    ui->curveShowWidget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom|
                                         QCP :: iSelectPlottables|QCP::iSelectItems|
                                         QCP :: iSelectAxes| QCP::iSelectLegend);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->init_control_page_ui();
    this->init_3d_printer_uart();
}

MainWindow::~MainWindow()
{
    parserThread->quit();
    parserThread->wait();
    uartThread->quit();
    uartThread->wait();
    delete ui;
}


void MainWindow::on_debug_clicked()
{
    qDebug() << "3D Printer....";
}

void MainWindow::on_open_gcode_file_clicked()
{
    QString filename;
    filename = QFileDialog::getOpenFileName(this,
                                            tr("Open GCODE"),
                                            "D:\\Users\\Desktop\\test",
                                            "GCODE (*.g *.gco *.gcode *.nc)");
    if(filename.isEmpty() || filename.isNull()) return;
    ui->model_name->setText(filename);
    emit this->send_gcode_file(filename);
    ui->start_print->setEnabled(true);
}


void MainWindow::on_start_print_clicked()
{
    emit this->startPrinting();
    ui->start_print->setEnabled(false);
    ui->pause_print->setEnabled(true);
    ui->stop_print->setEnabled(true);
}


void MainWindow::on_pause_print_clicked()
{
    emit this->pausePrinting();
    ui->recovery_print->setEnabled(true);
    ui->pause_print->setEnabled(false);
}


void MainWindow::on_stop_print_clicked()
{
    emit this->stopPrinting();
    ui->stop_print->setEnabled(false);
    ui->pause_print->setEnabled(false);
    ui->recovery_print->setEnabled(false);
    ui->start_print->setEnabled(false);
    ui->debug->setEnabled(false);
}


void MainWindow::on_recovery_print_clicked()
{
    emit this->recovery_print();
    ui->recovery_print->setEnabled(false);
    ui->pause_print->setEnabled(true);
}


void MainWindow::on_send_cmd_clicked()
{
    qDebug() << ui->lineEdit->text().toLocal8Bit() ;
    emit this->send_gcode_cmd(ui->lineEdit->text().toLocal8Bit()+"\r\n");
}



