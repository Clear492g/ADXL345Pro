#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "chartwidget.h"
#include "history.h"
#include "glwidget.h"
#include "QList"



struct acc_dat
    {
        int x;/*原始值*/ float xg;/*重力加速度*/
        int y;          float yg;
        int z;          float zg;

        float pitch;//俯仰角 x
        float yaw;//偏航角 y
        float roll;//翻滚角 z

    };

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int ADXL345DDR;
    acc_dat mydata;
    ChartWidget *w;
    History *h;
    GLWidget *g;


private slots:

    void on_pushButton_clicked();
    void timerUpDate();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

signals:
    void newdataED(double,double ,double );


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
