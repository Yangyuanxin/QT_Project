#include "protocol_parse.h"


struct Command_parser GCode_Reply_Parser[] =
{
{"T:",(&protocol_parse::parse_temp_data)},
{"echo:Unknown command:",(&protocol_parse::parse_unknown_data)},
};

protocol_parse::protocol_parse(QObject *parent) : QObject(parent)
{
    for(unsigned long long  i = 0 ; i < sizeof(GCode_Reply_Parser)/sizeof (GCode_Reply_Parser[0]) ; i++)
        funcPointer.insert(GCode_Reply_Parser[i].cmd,GCode_Reply_Parser[i].Pointer);
}

void protocol_parse::Command_Parse(QByteArray type)
{
    QFuncPointer RefFunction = NULL;
    for(unsigned long long  i = 0 ; i < sizeof(GCode_Reply_Parser)/sizeof (GCode_Reply_Parser[0]) ; i++)
    {
        if(type.contains(GCode_Reply_Parser[i].cmd))
        {
            RefFunction = funcPointer[GCode_Reply_Parser[i].cmd];
            (this->*RefFunction)(type);
            break ;
        }
    }
}

void protocol_parse::Data_Process(QByteArray data)
{
    if(!data.isEmpty())
        Command_Parse(data);
}

void protocol_parse::parse_temp_data(const QByteArray& data)
{
    int p = 0;
    TemperatureReadings r;
    QStringList data_list    ;
    QRegExp temperatureRegxp("-?(([0-9]\\d*\\.\\d*)|(0\\.\\d*[0-9]\\d*)|([0-9]\\d*))");
    while ((p = temperatureRegxp.indexIn(data, p)) != -1)
    {
        data_list.append(temperatureRegxp.cap(1));
        p += temperatureRegxp.matchedLength();
    }
    if(data_list.length()!= 6)
        return ;
    r.raw = QString(data);
    r.e_c = data_list[0].toDouble();
    r.e_t = data_list[1].toDouble();
    r.b_c = data_list[2].toDouble();
    r.b_t = data_list[3].toDouble();
    report_heater_temp(r.e_c,r.e_t,r.b_c,r.b_t);
}


void protocol_parse::parse_unknown_data(const QByteArray& data)
{
    qDebug() << "未识别数据:" << data ;
}


