#include "gobal_var.h"



int8_t gobal_var::motor_lock_status = 0;
int8_t gobal_var::printer_status = 0 ;
int8_t gobal_var::print_pause= 0 ;
QString gobal_var::print_time;

/*当前文件大小*/
long long int gobal_var::cur_file_size = 0;
/*当前文件偏移*/
long long int gobal_var::cur_file_pos  = 0;
/*当前文件路径*/
QString gobal_var::file_path;


void gobal_var::sleep(int sectime)
{
    QTime dieTime = QTime::currentTime().addMSecs(sectime);

    while (QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}
