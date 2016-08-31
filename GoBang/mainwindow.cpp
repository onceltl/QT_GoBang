#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
      ui->setupUi(this);
    ui->RoomText->setText("房间地址：");
    ui->chessBoard->repaint();
}

MainWindow::~MainWindow()
{
    delete ui;
}
