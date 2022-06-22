#ifndef GOBAL_VAR_H
#define GOBAL_VAR_H

#include <QTime>
#include <QRegExp>
#include <stdint.h>
#include <QEventLoop>
#include <QCoreApplication>

class gobal_var
{
public:
    static int8_t motor_lock_status ;
    static int8_t printer_status ;
    static int8_t print_pause ;
    static QString print_time ;

    /*当前文件大小*/
    static long long int cur_file_size ;
    /*当前文件偏移*/
    static long long int cur_file_pos  ;


    static QString file_path;

    static void sleep(int sectime);
};

#endif // GOBAL_VAR_H
