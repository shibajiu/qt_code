#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "win_qextserialport.h"
#include <QList>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void getIMUAngle(QList<float> *angle);

private slots:
    void on_pushButton_clicked();
    void SetTime();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void autoDecodeDataByte();

private:
    Ui::MainWindow *ui;
    QTimer *testTimer;
    QTimer *decodeTimer;
    Win_QextSerialPort *myCom;
    QByteArray buffertemp;
    unsigned char ch1;
    signed char ch2;
    QByteArray bufferhead;

    int ACC[3];
    int GYRO[3];
    int MGG[3];
    int ANGLE[3];
    int PRESSURE;

private:
    void DecodeData(QString str);
    int GetData(QString str);
    int GetDataByte(QByteArray buffer);
    void DecodeDataByte(QByteArray buffer);
    int GetDataBytelong(QByteArray buffer);

};

#endif // MAINWINDOW_H
