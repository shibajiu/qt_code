#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->InitForm();
}


MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::InitForm()
{

    QStringList comList;//串口号
    QStringList baudList;//波特率
    QStringList parityList;//校验位
    QStringList dataBitsList;//数据位
    QStringList stopBitsList;//停止位
    //RxBuffer.resize(1000);

    comList<<"COM1"<<"COM2"<<"COM3"<<"COM4"<<"COM5"<<"COM6"
          <<"COM7"<<"COM8"<<"COM9"<<"COM10"<<"COM11"<<"COM12"
         <<"COM13"<<"COM14"<<"COM15";

    ui->cboxPortName->addItems(comList);
    ui->cboxPortName->setCurrentIndex(0);

    baudList<<"50"<<"75"<<"100"<<"134"<<"150"<<"200"<<"300"
           <<"600"<<"1200"<<"1800"<<"2400"<<"4800"<<"9600"
          <<"14400"<<"19200"<<"38400"<<"56000"<<"57600"
         <<"76800"<<"115200"<<"128000"<<"256000";
    struct PortSettings myComSetting = {BAUD115200,DATA_8,PAR_NONE,STOP_1,FLOW_OFF,20};

    //定义一个结构体，用来存放串口各个参数

    myCom = new Win_QextSerialPort("com3",myComSetting,QextSerialBase::EventDriven);
    ui->cboxBaudRate->addItems(baudList);
    ui->cboxBaudRate->setCurrentIndex(12);
    //    parityList<<"无"<<"奇"<<"偶";
    parityList<<"wu"<<"ji"<<"ou";

    parityList<<"biaozhi";


    parityList<<"kongge";

    ui->cboxParity->addItems(parityList);
    ui->cboxParity->setCurrentIndex(0);

    dataBitsList<<"5"<<"6"<<"7"<<"8";
    ui->cboxDataBit->addItems(dataBitsList);
    ui->cboxDataBit->setCurrentIndex(3);

    stopBitsList<<"1";

    stopBitsList<<"1.5";

    stopBitsList<<"2";

    ui->cboxStopBit->addItems(stopBitsList);
    ui->cboxStopBit->setCurrentIndex(0);

    //读取数据(采用定时器读取数据，不采用事件，方便移植到linux)
    myReadTimer=new QTimer(this);
    myReadTimer->setInterval(300);
    connect(myReadTimer,SIGNAL(timeout()),this,SLOT(ReadMyCom()));

    this->ChangeEnable(false);
    //this->ReadConfigData();//读取发送数据加载到下拉框
    //this->ReadSendData();//读取数据转发文件

    //ui->txtSend->installEventFilter(this);//安装监听器监听发送数据框回车响应
}

void MainWindow::ChangeEnable(bool b)
{
    ui->cboxBaudRate->setEnabled(!b);
    ui->cboxDataBit->setEnabled(!b);
    ui->cboxParity->setEnabled(!b);
    ui->cboxPortName->setEnabled(!b);
    ui->cboxStopBit->setEnabled(!b);

    ui->btnOpen->setEnabled(true);
}



void MainWindow::DecodeData(QByteArray byteTemp)
{
    //double[] Data = new double[3];

    QByteArray raw;
    raw.resize(2);

    raw=byteTemp.mid(3,2);
    a[0]=raw.toShort();
    ui->textBrowser->append(QString("a"));


    //    Array.Copy(byteTemp, 3, raw, 0, 2); Array.Reverse(raw);
    //    a[0] = BitConverter.ToInt16(raw, 0);

    //    Array.Copy(byteTemp, 5, raw, 0, 2); Array.Reverse(raw);
    //    a[1] = BitConverter.ToInt16(raw, 0);

    //    Array.Copy(byteTemp, 7, raw, 0, 2); Array.Reverse(raw);
    //    a[2] = BitConverter.ToInt16(raw, 0);

    //    Array.Copy(byteTemp, 9, raw, 0, 2); Array.Reverse(raw);
    //    w[0] = BitConverter.ToInt16(raw, 0);

    //    Array.Copy(byteTemp, 11, raw, 0, 2); Array.Reverse(raw);
    //    w[1] = BitConverter.ToInt16(raw, 0);

    //    Array.Copy(byteTemp, 13, raw, 0, 2); Array.Reverse(raw);
    //    w[2] = BitConverter.ToInt16(raw, 0);

    //    Array.Copy(byteTemp, 15, raw, 0, 2); Array.Reverse(raw);
    //    h[0] = BitConverter.ToInt16(raw, 0);

    //    Array.Copy(byteTemp, 17, raw, 0, 2); Array.Reverse(raw);
    //    h[1] = BitConverter.ToInt16(raw, 0);

    //    Array.Copy(byteTemp, 19, raw, 0, 2); Array.Reverse(raw);
    //    h[2] = BitConverter.ToInt16(raw, 0);

    //    Array.Copy(byteTemp, 21, raw, 0, 2); Array.Reverse(raw);
    //    Angle[0] = BitConverter.ToInt16(raw, 0)/100;
    //    //pitch = Angle[0];

    //    Array.Copy(byteTemp, 23, raw, 0, 2); Array.Reverse(raw);
    //    Angle[1] = BitConverter.ToInt16(raw, 0)/100;
    //    //roll = Angle[1];

    //    Array.Copy(byteTemp, 25, raw, 0, 2); Array.Reverse(raw);
    //    Angle[2] = BitConverter.ToInt16(raw, 0)/10;
    //    //yaw = Angle[2];

    //    filter();//kalman filter

    //    Pressure = BitConverter.ToInt32(byteTemp, 27);

}
//char* a1="0x88";
//char* a2="0xAF";
void MainWindow::ReadMyCom()
{
    //这个判断尤为重要,否则的话直接延时再接收数据,空闲时和会出现高内存占用
    if (myCom->bytesAvailable()<=0){return;}

    //myHelper::Sleep(100);//延时100毫秒保证接收到的是一条完整的数据,而不是脱节的
    QByteArray buffer=myCom->readAll();

        //bListening = true;

//        QString tempDataHex=myHelper::ByteArrayToHexStr(buffer);
//    ui->textBrowser->append(tempDataHex);

        QString tempBuffer=buffer.toHex().toUpper();
        int usLength=tempBuffer.length();
        ui->textBrowser->append(tempBuffer);
        int c;
        for (c = 0; c < usLength; c++)
        {
            //ui->textBrowser->append(QString("d"));
            if ((tempBuffer.left(4)=="88AF") && (usLength >= 64))
            {
                //Array.Copy(RxBuffer, c, byteTemp, 0, 32);
                //this.Invoke(Update, RxBuffer);
                RxBuffer=tempBuffer.mid(c,64);
                ui->textBrowser->append(QString("a"));
                //MainWindow::DecodeData(RxBuffer);
                c += 64;
            }
        }

}


void MainWindow::on_btnOpen_clicked()
{
    if (ui->btnOpen->text()=="open")
    {


        if (myCom->open(QIODevice::ReadOnly))
        {
            this->ChangeEnable(true);
            ui->btnOpen->setText("close");
            this->myReadTimer->start();
            ui->textBrowser->append(QString("c"));
        }
    }
    else
    {
        myCom->close();
        this->ChangeEnable(false);
        ui->btnOpen->setText("open");
        this->myReadTimer->stop();


    }
}
