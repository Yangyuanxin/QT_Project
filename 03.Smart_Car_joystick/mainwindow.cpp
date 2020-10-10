#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFocusPolicy(Qt::StrongFocus);
    this->setWindowTitle(tr("智能小车控制%1%2").arg(tr("----2020年5月31日")).arg(tr("----开发者:杨源鑫")));
    client = new QTcpSocket(this);
    client->abort();
    //连接TCP客户端处理相关的信号与槽
    // connect(client,SIGNAL(readyRead()),this,SLOT(ReadData()));
    // connect(client,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(ReadError(QAbstractSocket::SocketError)));

    connect(client,SIGNAL(disconnected()),this,SLOT(ReadData()));
    //连接服务器
    client->connectToHost("192.168.4.1",8080);
    if (client->waitForConnected(1000))
        ui->label->setText("已连接智能小车");
    else
        ui->label->setText("连接智能小车失败!");
    KeyValue = 0;
    connect(this,SIGNAL(car_control(int)),this,SLOT(car_status_handler(int)));
}

void MainWindow::car_status_handler(int car_status)
{
    blockSignals(true);
    switch(car_status)
    {
    case 0:
        ui->label1->setText("停止");
        client->write("STOP");
        client->waitForBytesWritten();
        break ;
    case 1:
        ui->label1->setText("前进");
        client->write("GO");
        client->waitForBytesWritten();
        break ;
    case 2:
        ui->label1->setText("后退");
        client->write("BACK");
        client->waitForBytesWritten();
        break ;
    case 3:
        ui->label1->setText("左转");
        client->write("LEFT");
        client->waitForBytesWritten();
        break ;
    case 4:
        ui->label1->setText("右转");
        client->write("RIGHT");
        client->waitForBytesWritten();
        break ;
    }
   // this->client->flush();
    blockSignals(false);
}


//按键按下
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Up:
        KeyValue =  1 ;
        break ;
    case Qt::Key_Down:
        KeyValue =  2 ;
        break ;
    case Qt::Key_Left:
        KeyValue =  3 ;
        break ;
    case Qt::Key_Right:
        KeyValue =  4 ;
        break ;
    }
    emit car_control(KeyValue);
}



//释放按键
void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    KeyValue = 0 ;
    emit car_control(KeyValue);
}


void MainWindow::ReadData()
{
    QByteArray buffer = client->readAll();
    qDebug() << buffer ;
}

void MainWindow::ReadError(QAbstractSocket::SocketError)
{
    client->disconnectFromHost();
}


MainWindow::~MainWindow()
{
    delete client ;
    delete ui;
}

#if 0
void MainWindow::on_car_go_pressed()
{
    client->write("GO");
    ui->label1->setText("前进");
}

void MainWindow::on_car_back_pressed()
{
    client->write("BACK");
    ui->label1->setText("后退");
}

void MainWindow::on_car_left_pressed()
{
    client->write("LEFT");
    ui->label1->setText("左转");
}

void MainWindow::on_car_right_pressed()
{
    client->write("RIGHT");
    ui->label1->setText("右转");
}

void MainWindow::on_car_go_released()
{
    ui->label1->setText("停止");
    client->write("STOP");
}

void MainWindow::on_car_back_released()
{
    ui->label1->setText("停止");
    client->write("STOP");
}

void MainWindow::on_car_left_released()
{
    ui->label1->setText("停止");
    client->write("STOP");
}

void MainWindow::on_car_right_released()
{
    ui->label1->setText("停止");
    client->write("STOP");
}
#endif
