#ifndef HISTORY_H
#define HISTORY_H

#include <QWidget>
#include "qcustomplot.h"
#include "QList"


namespace Ui {
class History;
}

class History : public QWidget
{
    Q_OBJECT

public:
    explicit History(QWidget *parent = 0);
    ~History();

    void setupRealtimeDataDemo(QCustomPlot *customPlot);
    void dateupadte();

    QList<double> Phistory;
    QList<double> Yhistory;
    QList<double> Rhistory;



private:
    Ui::History *ui;

};

#endif // HISTORY_H
