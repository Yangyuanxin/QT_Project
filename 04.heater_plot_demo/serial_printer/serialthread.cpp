#include "serialthread.h"

SerialThread::SerialThread(QString port, long baud)
{
    myport = port;
    myBaud = baud;
    paused=false;
    sending=false;
    current_file_pos = 0 ;
    current_file_size = 0 ;
    this->readyReceive = true ;

    serial = new QSerialPort(this);
    view_temp_Timer = new QTimer(this);
    read_timer = new QTimer(this);

    QueuePushTimer = new QTimer(this);
    QueuePopTimer  = new QTimer(this);

    serial->setPortName(myport);
    serial->open(QIODevice::ReadWrite);
    serial->setBaudRate(myBaud);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->setReadBufferSize(0);
    connect(serial, SIGNAL(readyRead()), this, SLOT(timer_uart_rece()));
    connect(read_timer, SIGNAL(timeout()), this, SLOT(read_serial_data()));
    connect(view_temp_Timer, &QTimer::timeout, this, &SerialThread::get_temp_data);
    connect(QueuePushTimer, &QTimer::timeout, this, &SerialThread::GCode_File_To_3d_Printer);
    connect(QueuePopTimer, &QTimer::timeout, this, &SerialThread::sendLine);
    this->QueuePushTimer->start();
    this->QueuePopTimer->start();
    view_temp_Timer->start(TIMER_PERIO);
    start_printer_flag = false ;
    continue_print = false ;
    get_printer_para = true ;
    gobal_var::print_pause = 0 ;
    gobal_var::printer_status = PRINT_PREHEAT ;
}

void SerialThread::timer_uart_rece()
{
    read_timer->start(5);
    recv_buf.append(serial->readAll());
}

void SerialThread::read_serial_data()
{
    int index = 0 ;
    QStringList  list ;
    read_timer->stop();
    while(recv_buf.length() > 0)
    {
        buffer += recv_buf ;
       // qDebug() << buffer ;
        if(buffer.contains("ok"))
        {
            if(1 == gobal_var::print_pause && PRINT_PREHEAT == gobal_var::printer_status)
            {
                readyReceive = false ;
            }
            else
            {
                readyReceive=true;
                get_printer_para = true ;
            }
            emit this->BusyRemove();
        }
        if(buffer.contains("\n"))
        {
            QString splice_str ;
            QStringList list = QString(buffer).split("\n");
            qDebug() << list ;
            for(index = 0 ; index < list.length() ; index++)
            {
                if(!list[index].isEmpty())
                    emit this->Data_Process(list[index].toLocal8Bit());
            }
            buffer.clear();
        }
        recv_buf.clear();
    }
}

void SerialThread::get_temp_data()
{
    if(get_printer_para)
    {
        injectCommand("M105");
        get_printer_para = false ;
    }
}

void SerialThread::injectCommand(QString command)
{
    userCommands.enqueue(command);
}

void SerialThread::close_gcode_file()
{
    infile.close() ;
}

void SerialThread::setFile(QString file_path)
{
    gobal_var::file_path = file_path;
    QFile file(gobal_var::file_path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "文件打开失败";
        return ;
    }
    /*1.获取文件大小*/
    current_file_size = file.size() ;
    current_file_pos = 0 ;
    file.close();
    this->buffer.clear();
    this->recv_buf.clear();
    this->startPrinting();
}

void SerialThread::GCode_File_To_3d_Printer()
{
    string line ;
    if(sending && !paused && this->readyReceive)
    {
        FileProgress p;
        if(!infile.is_open())
            infile.open(gobal_var::file_path.toLocal8Bit(),ios::in);
        streampos sp=infile.tellg();
        this->current_file_pos = sp ;
        /*1.判断当前文件偏移是否大于文件大小，如果大于，则认为已经打完*/
        if(current_file_pos >= current_file_size)
        {
            p.P = current_file_pos;
            p.T = current_file_size;
            emit reportProgress(p);
            sending = false ;
            infile.close();
            return;
        }
        getline(infile,line);
        if(line.empty())
            return ;
        if(line.front() != ';')
        {
            if(strstr(line.c_str(),"G"))
            {
                gobal_var::print_pause= 0 ;
                gobal_var::printer_status = PRINTING ;
            }
            userCommands.enqueue(line.c_str());
            this->readyReceive = false ;
        }
        p.P = current_file_pos;
        p.T = current_file_size;
        emit reportProgress(p);
    }
}

void SerialThread::stopPrinting()
{
    paused = false;
    sending = false;
    userCommands.clear();
    injectCommand("M108");
    injectCommand(QString("M140 S%1").arg(0));
    injectCommand(QString("M104 S%1").arg(0));
    injectCommand("G91");
    injectCommand("G1 Z5");
    injectCommand("G28 X0");
    injectCommand("M84");
    injectCommand("G1 Y180 F2000");
    injectCommand("G90");
    get_printer_para = true ;
    start_printer_flag = false ;
    this->close_gcode_file();
}

void SerialThread::startPrinting()
{
    paused = false ;
    sending = true ;
    get_printer_para = true ;
    start_printer_flag = true ;
}

void SerialThread::pausePrinting()
{
    paused = false ;
    sending = false;
    get_printer_para = true ;
    userCommands.clear();
    injectCommand("M108");
}

void SerialThread::recovery_print()
{
    paused = false ;
    sending = true;
    this->readyReceive = true ;
}

void SerialThread::sendLine()
{
    QString cmd ;
    if(!userCommands.isEmpty())
    {
        if(serial->isOpen() && serial->isWritable())
        {
            cmd = userCommands.dequeue() ;
            serial->write(cmd.toLocal8Bit()+"\n") ;
        }
    }
}

void SerialThread::setGetPara(bool flag)
{
    bool setflag = !flag ;
    this->get_printer_para = setflag ;
}

bool SerialThread::getPara()
{
    return this->get_printer_para ;
}

SerialThread::~SerialThread()
{
    serial->clear();
    serial->close();
    serial->deleteLater();
}
