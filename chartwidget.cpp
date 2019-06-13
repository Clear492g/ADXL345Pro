#include "chartwidget.h"
#include "ui_chartwidget.h"

#include <QTimer>
#include <QTime>


ChartWidget::ChartWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChartWidget)
{
    ui->setupUi(this);
    setupRealtimeDataDemo(ui->customPlot);
    ui->customPlot->replot();
        this->hide();

   //connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
   // dataTimer.start(1000); // Interval 0 means to refresh as fast as possible
}

ChartWidget::~ChartWidget()
{
    delete ui;
}

//画图初始化
void ChartWidget::setupRealtimeDataDemo(QCustomPlot *customPlot)
{
    customPlot->addGraph(); // blue line
    customPlot->graph(0)->setPen(QPen(Qt::blue));
    customPlot->graph(0)->setName("Pitch");


    customPlot->addGraph(); // red line
    customPlot->graph(1)->setPen(QPen(Qt::red));
    customPlot->graph(1)->setName("Roll");

    customPlot->addGraph(); // yellow line
    customPlot->graph(2)->setPen(QPen(Qt::yellow));
    customPlot->graph(2)->setName("Yaw");

    customPlot->setInteraction(QCP::iRangeDrag, true);
    customPlot->setInteraction(QCP::iRangeZoom, true);

    QDateTime dateTime = QDateTime::currentDateTime();
    double  now = dateTime.toTime_t();//当前时间转化为秒

    //生成时间刻度对象
    QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
    customPlot->xAxis->setTicker(dateTimeTicker);

    dateTimeTicker->setTickCount(12);
    dateTimeTicker->setTickStepStrategy(QCPAxisTicker::tssMeetTickCount);

    customPlot->xAxis->setSubTicks(false);
    customPlot->xAxis->setRange(now, now+3600*24);//x轴范围，从当前时间起往后推24小时

    dateTimeTicker->setDateTimeFormat("s");//设置x轴刻度显示格式

    customPlot->yAxis->setRange(-180,180);
    customPlot->axisRect()->setupFullAxesBox();
    customPlot->legend->setVisible(true);

}


void ChartWidget::realtimeDataSlot(double P,double Y,double R)

{
    //key的单位是秒
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    qsrand(QTime::currentTime().msec() + QTime::currentTime().second() * 10000);
    //使用随机数产生两条曲线

    ui->customPlot->graph(0)->addData(key, P);//添加数据1到曲线1
    ui->customPlot->graph(1)->addData(key, Y);//添加数据2到曲线2
    ui->customPlot->graph(2)->addData(key, R);//添加数据2到曲线2


    ui->customPlot->graph(0)->rescaleValueAxis();
    ui->customPlot->graph(1)->rescaleValueAxis(true);
    ui->customPlot->yAxis->setRange(-180,180);

    ui->customPlot->xAxis->setRange(key+0.25, 8, Qt::AlignRight);//设定x轴的范围

    ui->customPlot->replot();

}
















