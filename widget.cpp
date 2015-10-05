#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    rcTimer = new QTimer;
    coordsSendTimer = new QTimer;
    galsSendTimer = new QTimer;
    socket = new QTcpSocket();
    coordsFile = new QFile();
    galsFile = new QFile();
    rcTimer->start(1000);
    ui->IPEdit->setText("192.168.1.217");
    //socket->connectToHost(ip,12345);
    connect(socket,SIGNAL(connected()),this,SLOT(connected()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(tryReconnect()));
    connect(rcTimer,SIGNAL(timeout()),this,SLOT(openConnection()));
    connect(coordsSendTimer,SIGNAL(timeout()),this,SLOT(sendCoords()));
    connect(galsSendTimer,SIGNAL(timeout()),this,SLOT(sendGals()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_cordsSendButton_clicked()
{
    if(fileCoordsName =="")
        return;
    delete coordsFile;
    coordsFile = new QFile(fileCoordsName);
    if(coordsFile->open(QIODevice::ReadOnly))
        coordsSendTimer->start(50);
}

void Widget::on_toolButton_clicked()
{
    fileCoordsName = "";
    fileCoordsName = QFileDialog::getOpenFileName(this,tr("Open coords file"),"/home/coala",tr("coords file (*.txt)"));
    ui->coordsFileEdit->setText(fileCoordsName);
}

void Widget::connected()
{
    qDebug()<<"connected";
    rcTimer->stop();
}
void Widget::tryReconnect()
{
    qDebug()<<"dc";
    coordsSendTimer->stop();
    rcTimer->start(1000);
}

void Widget::openConnection()
{
    qDebug()<<"try connect";
    socket->connectToHost(ip,12345);
}

void Widget::sendCoords()
{
    QString tmpStr;
    if(coordsFile->atEnd())
    {
        coordsSendTimer->stop();
        return;
    }
    tmpStr = coordsFile->readLine();
    socket->write(tmpStr.toUtf8());
    socket->waitForBytesWritten(1000);
}

void Widget::sendGals()
{
    QString tmpStr;
    if(galsFile->atEnd())
    {
        galsSendTimer->stop();
        return;
    }
    tmpStr = galsFile->readLine();
    socket->write(tmpStr.toUtf8());
    socket->waitForBytesWritten(1000);
}

void Widget::on_toolButton_2_clicked()
{
    fileGalsName = "";
    fileGalsName = QFileDialog::getOpenFileName(this,tr("Open gals file"),"/home/coala",tr("gals file (*.txt)"));
    ui->galsFileEdit->setText(fileGalsName);
}

void Widget::on_GalsSendButton_clicked()
{
    if(fileGalsName =="")
        return;
    delete galsFile;
    galsFile = new QFile(fileGalsName);
    if(galsFile->open(QIODevice::ReadOnly))
        galsSendTimer->start(50);
}

void Widget::on_ipSetButton_clicked()
{
    ip = ui->IPEdit->text();
}

void Widget::on_pushButton_clicked()
{
    coordsSendTimer->stop();
}
