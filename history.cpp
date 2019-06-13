#include "history.h"
#include "ui_history.h"
#include "QVector"


History::History(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::History)
{
    ui->setupUi(this);
    setupRealtimeDataDemo(ui->widget);
    ui->widget->replot();
    this->hide();
}

History::~History()
{
    delete ui;
}

void History::setupRealtimeDataDemo(QCustomPlot *customPlot)
{

    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);   //可拖拽+可滚轮缩放
    customPlot->legend->setVisible(true);                              //显示图例
    customPlot->xAxis->setLabel(QStringLiteral("History"));          //X轴文字显示
    customPlot->yAxis->setLabel(QStringLiteral("Angle"));          //Y轴文字显示
    customPlot->xAxis->setRange(0, 100);                         //当前X轴显示的范围
    customPlot->yAxis->setRange(-180,180);                         //当前Y轴显示的范围
    customPlot->addGraph();                              //向绘图区域QCustomPlot添加一条曲线
    customPlot->addGraph();
    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::blue));                //绘制曲线0的画刷颜色为红色
    customPlot->graph(1)->setPen(QPen(Qt::red));
    customPlot->graph(2)->setPen(QPen(Qt::yellow)); //绘制曲线1的画刷颜色为蓝色    //绘制的曲线轨迹
    customPlot->graph(0)->setName("Pitch");
    customPlot->graph(1)->setName("Roll");
    customPlot->graph(2)->setName("Yaw");



}

void History::dateupadte()
{

    for (int i = 0; i<Phistory.size(); i++)
    {
        ui->widget->graph(0)->addData(i, Phistory.at(i));
        ui->widget->graph(1)->addData(i, Yhistory.at(i));
        ui->widget->graph(2)->addData(i, Rhistory.at(i));

    }
        ui->widget->replot();

}




