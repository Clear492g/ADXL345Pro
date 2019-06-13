#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QWidget>
#include "qcustomplot.h"
#include <QTimer>

namespace Ui {
class ChartWidget;
}

class ChartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChartWidget(QWidget *parent = 0);
    ~ChartWidget();

    void setupRealtimeDataDemo(QCustomPlot *customPlot);

private slots:
    //添加实时数据槽
    void realtimeDataSlot(double P,double Y,double R);

private:
    Ui::ChartWidget *ui;
    QTimer dataTimer;


};

#endif // CHARTWIDGET_H
