#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <sys/vfs.h>
#include <sys/stat.h>
#include <dirent.h>

/*判断目录是否存在*/
bool dirIsExist(const char *file_path)
{
    DIR * mydir = NULL;
    if ((mydir = opendir(file_path)) == NULL)
        return false;
    closedir(mydir);
    return true;
}

/*获取磁盘的可用空间以及总空间*/
int getDiskInfo(const char *path,double * available,double *total)
{
    uint64_t blocksize;
    uint64_t totalsize;
    uint64_t availablesize;
    struct statfs diskInfo;
    if(dirIsExist(path))
        statfs(path, &diskInfo);
    else
        return -1 ;
    // 每个block里包含的字节数
    blocksize = diskInfo.f_bsize;
    // 总的字节数，f_blocks为block的数目
    totalsize = blocksize * diskInfo.f_blocks;
    // 可用空间大小
    availablesize = diskInfo.f_bavail * blocksize;
    *available = availablesize ;
    *total = totalsize ;
    return 0 ;
}



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    char av_unit = 'K';
    char total_unit = 'K';
    double availablesize = 0.00 ;
    double totalsize = 0.00 ;
    getDiskInfo("/mnt",&availablesize,&totalsize);
    availablesize /= 1024 ;
    if(availablesize > 1024){
        availablesize /= 1024 ;
        av_unit = 'M';
    }
    if(availablesize > 1024){
        availablesize /= 1024 ;
        av_unit = 'G';
    }
    totalsize /= 1024 ;
    if(totalsize > 1024){
        totalsize /= 1024 ;
        total_unit = 'M';
    }
    if(totalsize > 1024){
        totalsize /= 1024 ;
        total_unit = 'G';
    }
    qDebug() <<"availablesize:" <<  QString("%1%2").arg(QString::number(availablesize, 'f', 1)).arg(av_unit) ;
    qDebug() <<"totalsize:" << QString("%1%2").arg(QString::number(totalsize, 'f', 1)).arg(total_unit) ;
}

MainWindow::~MainWindow()
{
    delete ui;
}

