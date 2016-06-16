#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "win_qextserialport.h"
#include <QTimer>
#include <QKeyEvent>
#include <QWidget>
#include <QDate>
#include "myhelper.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Win_QextSerialPort *myCom;
    //QTimer *myTimer;

    QTimer *myReadTimer;//定时读取串口数据

    double a[3],w[3],h[3],angle[3],pressure;
    QString RxBuffer;


private:
    void InitForm();//初始化界面以及其他处理
    void ChangeEnable(bool b);//改变状态
    //void DecodeData(QByteArray byteTemp);

private slots:
    void ReadMyCom();
    void DecodeData(QByteArray byteTemp);

    void on_btnOpen_clicked();
};

#endif // MAINWINDOW_H
