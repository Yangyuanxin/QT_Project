#ifndef RECORD_INFO_H
#define RECORD_INFO_H
#include <QString>

class record_info
{
public:
    record_info();
    record_info(QString, QString, QString, QString , QString, QString,QString);

    QString inspection_serial;  //流水号
    QString inspection_mode;    //检测模式
    QString inspection_time;        //检测时间
    QString inspection_place;       //地点坐标
    QString inspection_detail;      //报警强度
    QString inspection_type;        //炸药类型
    QString inspection_text1 ;      //当前是否已经将数据上传
};

#endif // RECORD_INFO_H
