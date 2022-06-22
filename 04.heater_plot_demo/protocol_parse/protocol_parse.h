#ifndef PROTOCOL_PARSE_H
#define PROTOCOL_PARSE_H

#include <QMap>
#include <QDebug>
#include <QObject>
#include "gobal_var.h"
#include "public_para.h"

class protocol_parse : public QObject
{
    Q_OBJECT
public:
    explicit protocol_parse(QObject *parent = nullptr);
    void parse_temp_data(const QByteArray& data);
    void parse_unknown_data(const QByteArray& data);
    void Command_Parse(QByteArray type);

    typedef void (protocol_parse:: *QFuncPointer)(const QByteArray&);
    QMap<QByteArray,QFuncPointer> funcPointer ;

signals:
    void report_heater_temp(double,double,double,double);

public slots:
    void Data_Process(QByteArray data);
};

struct Command_parser
{
    QByteArray cmd ;
    protocol_parse::QFuncPointer Pointer ;
};

#endif // PROTOCOL_PARSE_H
