#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    testTimer = new QTimer(this);
    testTimer->setInterval(300);
    connect( testTimer,SIGNAL(timeout()), this, SLOT(SetTime()) );
    decodeTimer = new QTimer(this);//使用另一个timer来更新数据
    decodeTimer->setInterval(300);
    connect( decodeTimer,SIGNAL(timeout()), this, SLOT(autoDecodeDataByte()));
    bufferhead.resize(2);
    bufferhead[0]=0x88;
    bufferhead[1]=0xaf;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
//    QString temp="a";
//    QString q=QString::number(temp.toInt(0,16));
//    ui->textBrowser->append(q+"0");
    myCom=new Win_QextSerialPort("com3");
    if(myCom ->open(QIODevice::ReadOnly))
    {
        myCom->flush();
        myCom->setBaudRate(BAUD115200);
        myCom->setDataBits(DATA_8);
        myCom->setParity(PAR_NONE);
        myCom->setStopBits(STOP_1);
        myCom->setFlowControl(FLOW_OFF);
        myCom->setTimeout(10);
        this->testTimer->start();
        this->decodeTimer->start();
        ui->textBrowser->append("ok");
    }


}
//signed char *p="1";
//unsigned char ch1 = 0x88;
//unsigned char ch2 = 0xaf;
void MainWindow::SetTime()
{

    if (myCom->bytesAvailable()<=0){return;}
    QByteArray temp = myCom->readAll();
    //QString q=temp.toHex().toUpper();
    int length=temp.length();
    //ui->textBrowser->append("2");
    for(int c=0;c<length;c++)
    {
        if((temp[c]==bufferhead[0])&&(temp[c+1]==bufferhead[1])&&(c+32<=length))//判断字节流
        {
           // ui->textBrowser->append("1");
            buffertemp=temp.mid(c,32);
//            if(!decodeTimer->isActive())
//            {
//                decodeTimer->start();
//            }
//            DecodeDataByte(buffertemp);
//            c+=32;
            break;
        }
    }

    //ui->textBrowser->append(q);

}

void MainWindow::on_pushButton_2_clicked()
{
    myCom->close();
    testTimer->stop();
    decodeTimer->stop();
}

int MainWindow::GetData(QString str)
{
    int temp=str.toInt(0,16);
    ch1=temp;
    ch2=ch1;
    temp=ch2;
    return temp;
}

int MainWindow::GetDataByte(QByteArray buffer)//byte to int16
{
    short s=(buffer[1]&0x00ff)|(((buffer[0]<<8)&0xff00));
    int a=s;
    return a;
}

int MainWindow::GetDataBytelong(QByteArray buffer)//byte to int32
{
    int addr = (buffer[0]&0x000000ff)|((buffer[1]<<8)&0x0000ff00)|((buffer[2]<<16)&0x00ff0000)|((buffer[3]<<24)&0xff000000);
    return addr;
}

void MainWindow::autoDecodeDataByte()
{
    DecodeDataByte(buffertemp);
}

void MainWindow::DecodeDataByte(QByteArray buffer)
{
    ACC[0]=GetDataByte(buffer.mid(3,2));
    ACC[1]=GetDataByte(buffer.mid(5,2));
    ACC[2]=GetDataByte(buffer.mid(7,2));
    GYRO[0]=GetDataByte(buffer.mid(9,2));
    GYRO[1]=GetDataByte(buffer.mid(11,2));
    GYRO[2]=GetDataByte(buffer.mid(13,2));
    MGG[0]=GetDataByte(buffer.mid(15,2));
    MGG[1]=GetDataByte(buffer.mid(17,2));
    MGG[2]=GetDataByte(buffer.mid(19,2));
    ANGLE[0]=GetDataByte(buffer.mid(21,2))*0.01;
    ANGLE[1]=GetDataByte(buffer.mid(23,2))*0.01;
    ANGLE[2]=GetDataByte(buffer.mid(25,2))*0.1;
    PRESSURE=GetDataBytelong(buffer.mid(27,4));
    ui->textBrowser->setText(QString::number(ACC[0]) + " mg\r\n"
            + QString::number(ACC[1]) + " mg\r\n"
            + QString::number(ACC[2]) + " mg\r\n\r\n"
            + QString::number(GYRO[0]) + " °/s\r\n"
            + QString::number(GYRO[1]) + " °/s\r\n"
            + QString::number(GYRO[2]) + " °/s\r\n\r\n"
            + QString::number(ANGLE[0]) + " °\r\n"
            + QString::number(ANGLE[1]) + " °\r\n"
            + QString::number(ANGLE[2]) + " °\r\n\r\n"
            + QString::number(MGG[0]) + " mG\r\n"
            + QString::number(MGG[1]) + " mG\r\n"
            + QString::number(MGG[2]) + " mG\r\n\r\n"
            + QString::number(PRESSURE) + " Pa\r\n");
    QString str=buffer.toHex();
    ui->textBrowser_2->setText(str.mid(6,4)+ " mg\r\n"
    +str.mid(10,4)+ " mg\r\n" +
    str.mid(14,4)+ " mg\r\n\r\n" +
    str.mid(18,4) + " °/s\r\n"+
    str.mid(22,4) + " °/s\r\n" +
    str.mid(26,4) + " °/s\r\n\r\n"+
    str.mid(42,4)+ " °\r\n"+
    str.mid(46,4)+ " °\r\n"+
    str.mid(50,4) + " °\r\n\r\n"+
      str.mid(30,4)+ " mG\r\n"+
      str.mid(34,4)+ " mG\r\n"+
      str.mid(38,4)+ " mG\r\n\r\n"+
    str.mid(54,8)+ " Pa\r\n");
}

void MainWindow::DecodeData(QString str)
{

    //ui->textBrowser->append(str);
    ACC[0]=GetData(str.mid(6,4));
    ACC[1]=GetData(str.mid(10,4));
    ACC[2]=GetData(str.mid(14,4));
    GYRO[0]=GetData(str.mid(18,4));
    GYRO[1]=GetData(str.mid(22,4));
    GYRO[2]=GetData(str.mid(26,4));
    MGG[0]=GetData(str.mid(30,4));
    MGG[1]=GetData(str.mid(34,4));
    MGG[2]=GetData(str.mid(38,4));
    ANGLE[0]=GetData(str.mid(42,4))*0.01;
    ANGLE[1]=GetData(str.mid(46,4))*0.01;
    ANGLE[2]=GetData(str.mid(50,4))*0.1;
    PRESSURE=GetData(str.mid(54,8));
    ui->textBrowser->setText(QString::number(ACC[0]) + " mg\r\n"
            + QString::number(ACC[1]) + " mg\r\n"
            + QString::number(ACC[2]) + " mg\r\n\r\n"
            + QString::number(GYRO[0]) + " °/s\r\n"
            + QString::number(GYRO[1]) + " °/s\r\n"
            + QString::number(GYRO[2]) + " °/s\r\n\r\n"
            + QString::number(ANGLE[0]) + " °\r\n"
            + QString::number(ANGLE[1]) + " °\r\n"
            + QString::number(ANGLE[2]) + " °\r\n\r\n"
            + QString::number(MGG[0]) + " mG\r\n"
            + QString::number(MGG[1]) + " mG\r\n"
            + QString::number(MGG[2]) + " mG\r\n\r\n"
            + QString::number(PRESSURE) + " Pa\r\n");
    ui->textBrowser_2->setText(str.mid(6,4)+ " mg\r\n"
    +str.mid(10,4)+ " mg\r\n" +
    str.mid(14,4)+ " mg\r\n\r\n" +
    str.mid(18,4) + " °/s\r\n"+
    str.mid(22,4) + " °/s\r\n" +
    str.mid(26,4) + " °/s\r\n\r\n"+
    str.mid(42,4)+ " °\r\n"+
    str.mid(46,4)+ " °\r\n"+
    str.mid(50,4) + " °\r\n\r\n"+
      str.mid(30,4)+ " mG\r\n"+
      str.mid(34,4)+ " mG\r\n"+
      str.mid(38,4)+ " mG\r\n\r\n"+
    str.mid(54,8)+ " Pa\r\n");

}

void MainWindow::on_pushButton_3_clicked()
{
    QString test="1a";
    bool ok;
    QString result=QString::number(test.toInt(&ok,16));
    ui->textBrowser->append(result);
}

void MainWindow::getIMUAngle(QList<float> *angle)
{
    (*angle)[0]=ANGLE[0];
    (*angle)[1]=ANGLE[1];
    (*angle)[2]=ANGLE[2];
}
