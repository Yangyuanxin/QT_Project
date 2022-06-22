#ifndef PUBLIC_PARA_H
#define PUBLIC_PARA_H

#include <string>
#include <vector>
#include <limits>
#include <cmath>
#include <QString>
#include <QTranslator>
#include "gobal_var.h"
#define Sensor_Uart "COM6"
#define Sensor_Baud 115200
#define TIMER_PERIO 100

using namespace std;

typedef struct
{
    QString raw;
    double e_c, b_c;
    double e_t, b_t;
} TemperatureReadings;

typedef struct
{
    int T, P;
} FileProgress;

enum
{
    PRINT_PREHEAT = 0,
    PRINTING
};

enum
{
    IDLE_STATUS=0,
    PRINT_STATUS
};



#endif // PUBLIC_PARA_H
