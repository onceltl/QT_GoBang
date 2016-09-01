#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adddialog.h"
#include "linkdialog.h"
#include <QDebug>
#include <QByteArray>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->RoomText->setText("目前你未进入房间");
    ui->chessBoard->repaint();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_CreatButton_clicked()
{
    AddDialog *addDialog=new AddDialog(this);
    addDialog->exec();
}


void MainWindow::AddHost(QString hostaddress)
{
    ui->RoomText->setText("目前你已进入房间："+hostaddress);
    s1=0;
    Listen=new QTcpServer();
    Listen->listen(QHostAddress(hostaddress),9876);
    connect(Listen,SIGNAL(newConnection()),this,SLOT(acceptConnection()));
}
void MainWindow::acceptConnection()
{
    s2=0;
    MySocket=Listen->nextPendingConnection();
    connect(MySocket,SIGNAL(readyRead()),this,SLOT(GetMessage()));
}
void MainWindow::GetMessage()
{

    QByteArray array=MySocket->readAll();
    QString info=array.data();

    if (info[0]=='1')
    {
        s2=1;
        if (s1&&s2) ui->chessBoard->mycolor=3;
        return;
    }
    if (info[0]=='2')
    {

        int len=0,x=0,y=0;
        QString sx="",sy="";
        while (info[len]!='+')len++;
        len++;
        while (info[len]!='+') {sx+=info[len];len++;}
        len++;
        while (len<info.size()){sy+=info[len];len++;}
        x=sx.toInt(),y=sy.toInt();
        ui->chessBoard->Chess[x][y]=((ui->chessBoard->mycolor)^1);
        ui->chessBoard->readychange(1);
        return;
    }
    if (info[0]=='3')
    {
        QMessageBox::warning(this, tr("遗憾！"), tr("你输了"));
        s1=s2=0;
        ui->chessBoard->clear();
    }

}

void MainWindow::LinkHost(QString hostaddress)
{
    s1=0;s2=0;
    ui->RoomText->setText("目前你已进入房间："+hostaddress);
    MySocket=new QTcpSocket();
    MySocket->connectToHost(QHostAddress(hostaddress),9876);
    connect(MySocket,SIGNAL(readyRead()),this,SLOT(GetMessage()));
}
void MainWindow::on_AddButton_clicked()
{
    LinkDialog *linkDialog=new LinkDialog(this);
    linkDialog->exec();
}
void MainWindow::sendPoint(QPoint point)
{
    QByteArray *array=new QByteArray();
    array->clear();
    array->append("2");
    array->append("+");
    array->append(point.rx());
    array->append("+");
    array->append(point.ry());
    MySocket->write(array->data());
}

void MainWindow::on_StartButton_clicked()
{
    s1=1;
    if (s2)
    {
        ui->chessBoard->mycolor=2;
        ui->chessBoard->readychange(1);
    }
    QByteArray *array=new QByteArray();
    array->clear();
    array->append("1");
    MySocket->write(array->data());
}
void MainWindow::haveWin()
{
    QMessageBox::warning(this, tr("恭喜！"), tr("你赢了"));
    s1=s2=0;
    ui->chessBoard->clear();
    QByteArray *array=new QByteArray();
    array->clear();
    array->append("3");
    MySocket->write(array->data());
}
