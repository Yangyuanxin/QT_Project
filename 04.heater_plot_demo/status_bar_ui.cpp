#include "mainwindow.h"
#include "ui_mainwindow.h"

/*plot graph*/
#define GRAPH_NUM 4

void MainWindow::on_clear_plot_clicked()
{
    count = 0 ;
    ui->curveShowWidget->clearGraphs();
    ui->curveShowWidget->xAxis->setRange(0,10);
}

void MainWindow::Display_Heater_Temp(double cur_nozzle_temp,double target_nozzle_temp,double cur_hotbed_temp,double target_hotbed_temp)
{
    static int graph_count ;
    QColor test[GRAPH_NUM] = {Qt:: black, Qt:: red, Qt:: green, Qt:: blue};
    double temp_n_s = cur_nozzle_temp ;
    double temp_n_t = target_nozzle_temp ;
    double temp_b_s = cur_hotbed_temp ;
    double temp_b_t = target_hotbed_temp ;
    ui->hotend_temp->setText(QString("%1 / %2 ℃").arg(temp_n_s).arg(temp_n_t));
    ui->hotbed_temp->setText(QString("%1 / %2 ℃").arg(temp_b_s).arg(temp_b_t));
    /*draw temp plot*/
    graph_count = ui->curveShowWidget->graphCount();
    while(graph_count < GRAPH_NUM)
    {
        count = 0 ;
        ui->curveShowWidget->addGraph();
        ui->curveShowWidget->yAxis->setRange(0,300);
        graph_count = ui->curveShowWidget->graphCount();
        ui->curveShowWidget->yAxis->setLabel(QString(tr("温度℃")));
        ui->curveShowWidget->xAxis->setLabel(QString(tr("number")));
        ui->curveShowWidget->graph(graph_count - 1)->setPen(QPen(test[graph_count - 1]));
        /*图例相关*/
        ui->curveShowWidget->legend->setWrap(1);
        ui->curveShowWidget->legend->setVisible(true);
        ui->curveShowWidget->axisRect()->setupFullAxesBox(true);
        ui->curveShowWidget->graph(graph_count - 1)->setPen(QPen(test[graph_count - 1]));
        ui->curveShowWidget->plotLayout()->addElement(1 , 0, ui->curveShowWidget->legend);
        ui->curveShowWidget->plotLayout()->setMargins(QMargins(0, 0, 0, 30));
        ui->curveShowWidget->axisRect()->insetLayout()->setInsetPlacement(0, QCPLayoutInset::ipFree);
        ui->curveShowWidget->axisRect()->insetLayout()->setInsetRect(0, QRectF(0.0, 1.2, 1.0, 0.1));
        //图例相关
    }
    ui->curveShowWidget->graph(graph_count-GRAPH_NUM+1-1)->setName(QString("喷头当前温度"));
    ui->curveShowWidget->graph(graph_count-GRAPH_NUM+1-1)->addData(count, cur_nozzle_temp);
    ui->curveShowWidget->graph(graph_count-GRAPH_NUM+1-1)->rescaleKeyAxis(true);
    ui->curveShowWidget->graph(graph_count-GRAPH_NUM+1-1)->rescaleValueAxis(true);
    ui->curveShowWidget->graph(graph_count-GRAPH_NUM+1-1)->rescaleAxes(true);

    ui->curveShowWidget->graph(graph_count-GRAPH_NUM+2-1)->setName(QString("喷头目标温度"));
    ui->curveShowWidget->graph(graph_count-GRAPH_NUM+2-1)->addData(count, target_nozzle_temp);
    ui->curveShowWidget->graph(graph_count-GRAPH_NUM+2-1)->rescaleKeyAxis(true);
    ui->curveShowWidget->graph(graph_count-GRAPH_NUM+2-1)->rescaleValueAxis(true);
    ui->curveShowWidget->graph(graph_count-GRAPH_NUM+2-1)->rescaleAxes(true);

    ui->curveShowWidget->graph(graph_count-GRAPH_NUM+3-1)->setName(QString("热床当前温度"));
    ui->curveShowWidget->graph(graph_count-GRAPH_NUM+3-1)->addData(count, cur_hotbed_temp);
    ui->curveShowWidget->graph(graph_count-GRAPH_NUM+3-1)->rescaleKeyAxis(true);
    ui->curveShowWidget->graph(graph_count-GRAPH_NUM+3-1)->rescaleValueAxis(true);
    ui->curveShowWidget->graph(graph_count-GRAPH_NUM+3-1)->rescaleAxes(true);

    ui->curveShowWidget->graph(graph_count-GRAPH_NUM+4-1)->setName(QString("热床目标温度"));
    ui->curveShowWidget->graph(graph_count-GRAPH_NUM+4-1)->addData(count, target_hotbed_temp);
    ui->curveShowWidget->graph(graph_count-GRAPH_NUM+4-1)->rescaleKeyAxis(true);
    ui->curveShowWidget->graph(graph_count-GRAPH_NUM+4-1)->rescaleValueAxis(true);
    ui->curveShowWidget->graph(graph_count-GRAPH_NUM+4-1)->rescaleAxes(true);

    ui->curveShowWidget->replot(QCustomPlot::rpQueuedReplot);
    count++ ;
}


void MainWindow::updateFileProgress(FileProgress p)
{
    double print_process ;
    if(p.P >= p.T)
    {
        ui->print_process->setText(QString("%1%").arg(100));
    }
    else
    {
        print_process = ((float)p.P /p.T) * 100;
        ui->print_process->setText(QString("%1%").arg((int)print_process));
    }
}

