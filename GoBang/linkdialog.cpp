#include "linkdialog.h"
#include "ui_linkdialog.h"
#include <QSignalMapper>
#include <QPushButton>
#include <QDebug>
LinkDialog::LinkDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LinkDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("加入"));
    connect(this,SIGNAL(SureAdd(QString)),parent,SLOT(LinkHost(QString)));
    QSignalMapper *mapper=new QSignalMapper(this);
    for (int i=0;i<=11;i++)
    {
        QString number="NumButton"+QString::number(i);
        QPushButton *button=ui->widget->findChild<QPushButton *>(number);
        mapper->setMapping(button,i);
        connect(button,SIGNAL(clicked()),mapper,SLOT(map()));
    }
   connect(mapper,SIGNAL(mapped(int)),this,SLOT(GetEdit(int)));

}

LinkDialog::~LinkDialog()
{
    delete ui;
}

void LinkDialog::on_Q_clicked()
{
    close();
}

void LinkDialog::on_SureButton_clicked()
{
    QString hostadress=ui->lineEdit->text();
    emit SureAdd(hostadress);
    close();
}
void LinkDialog::GetEdit(int number)
{
    if (number<=9) hostaddress+=QString::number(number,10);
    if (number==10) hostaddress+=".";
    if (number==11) hostaddress=hostaddress.left(hostaddress.size()-1);
    ui->lineEdit->setText(hostaddress);
}

