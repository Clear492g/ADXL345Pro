#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QtCore/QTextStream>
#include <QtCore/QFile>
#include <QtCore/QIODevice>

extern "C" {
#include <adxl345dri.h>
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QTimer *timer = new QTimer(this);
    w=new ChartWidget();
    h=new History();
    g=new GLWidget();

    connect(this,SIGNAL(newdataED(double,double ,double)),w,SLOT(realtimeDataSlot(double ,double ,double )));
    connect(this,SIGNAL(newdataED(double,double ,double)),g,SLOT(xyzupdate(double ,double ,double )));
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpDate()));

    ui->setupUi(this);


    ADXL345DDR=GetADXL345fd();
    if(-1 == ADXL345DDR)
    {
        qDebug()<<"ADXL345 setup error";
    }
    else
    {
         qDebug() << "ADXL345 setup successfully!";
         adxl345_init(ADXL345DDR);
         ui->label_4->setText("ADXL345连接状态：已连接");
         timer->start(500);
    }



}
void MainWindow::timerUpDate()
{

    emit newdataED(mydata.pitch,mydata.yaw,mydata.roll);

    mydata=adxl345_read_xyz(ADXL345DDR);
    ui->label->setText(
                       "原始数据：  "+
                       QString::number(mydata.x,10,2)+"  "+
                       QString::number(mydata.y,10,2)+"  "+
                       QString::number(mydata.z,10,2)
                       );
    ui->label_2->setText(
                        "加速度：  "+
                        QString::number(mydata.xg,10,2)+"  "+
                        QString::number(mydata.yg,10,2)+"  "+
                        QString::number(mydata.zg,10,2)
                        );
    ui->label_3->setText(
                        "欧拉角（PYR）：  "+
                        QString::number(mydata.pitch,10,2)+"  "+
                        QString::number(mydata.yaw,10,2)+"  "+
                        QString::number(mydata.roll,10,2)
                        );


    h->Phistory.append(mydata.pitch);
    h->Yhistory.append(mydata.yaw);
    h->Rhistory.append(mydata.roll);

    if(h->Phistory.size()>100)
    {
        h->Phistory.removeFirst();
        h->Yhistory.removeFirst();
        h->Rhistory.removeFirst();
    }

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    w->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    h->dateupadte();
    h->show();

}

void MainWindow::on_pushButton_3_clicked()
{
  g->show();
}
