#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->SEND_SSID_AND_PASSWORD->setEnabled(false);
    ui->SEND_SERVER_IP_AND_PORT->setEnabled(false);
    //建立TCPSocket
    m_client = new QTcpSocket(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Connect_server_clicked()
{
    int port = 0 ;
    QString address = ui->server_addr->text();
    QString __port =  ui->server_port->text();
    if(address.isNull()){
        qDebug() << "输入地址为空";
        return ;
    }
    if(__port.isNull())
    {
        qDebug() << "输入端口为空";
        return ;
    }
    port =__port.toInt(0,10);
    m_client->connectToHost(address,port);
    //通过信号接收服务器数据
    connect(m_client,SIGNAL(readyRead()),this,SLOT(Read_NetWork_Data()));
    ui->SEND_SSID_AND_PASSWORD->setEnabled(true);
    ui->SEND_SERVER_IP_AND_PORT->setEnabled(true);
}

//获取网络数据
void MainWindow::Read_NetWork_Data()
{
    //接收数据
    QByteArray array = m_client->readAll();
    ui->textBrowser->append(array);
}


//发送ssid和密码
void MainWindow::on_SEND_SSID_AND_PASSWORD_clicked()
{
    char *cmd = NULL ;
    QString ap_ssid = ui->input_ap->text();
    QString ap_password = ui->input_ap_password->text();
    if(ap_ssid.isNull())
    {
        qDebug() << "输入ssid为空";
        return ;
    }
    if(ap_password.isNull())
    {
        qDebug() << "输入密码为空";
        return ;
    }
    QString cmd_str = "SSID=" + ap_ssid + ";" + "PASSWORD=" + ap_password + ";" ;
    QByteArray send_cmd = cmd_str.toLatin1();
    cmd = send_cmd.data();
    qDebug() << cmd ;
    m_client->write(cmd);
    //m_client->write("SSID=5763;PASSWORD=12345678;");
}

//发送服务器ip和端口号
void MainWindow::on_SEND_SERVER_IP_AND_PORT_clicked()
{
    char *cmd = NULL ;
    QString server_ip = ui->input_server_ip->text();
    QString server_port = ui->input_server_port->text();
    if(server_ip.isNull())
    {
        qDebug() << "输入服务器ip为空";
        return ;
    }
    if(server_port.isNull())
    {
        qDebug() << "输入服务器端口号为空";
        return ;
    }
    QString cmd_str = "SERVER_IP=" + server_ip + ";" + "PORT=" + server_port + ";" ;
    QByteArray send_cmd = cmd_str.toLatin1();
    cmd = send_cmd.data();
    qDebug() << cmd ;
    m_client->write(cmd);
    // m_client->write("SERVER_IP=120.78.136.134;PORT=9002;");
}
