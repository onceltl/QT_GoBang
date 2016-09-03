#include "adddialog.h"
#include "ui_adddialog.h"
#include <QHostInfo>
AddDialog::AddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);
    QHostInfo info=QHostInfo::fromName(QHostInfo::localHostName());
    QList<QHostAddress> alladress=info.addresses();
    this->setWindowTitle(tr("创建"));
    ui->lineEdit->setText(alladress[6].toString());
    connect(this,SIGNAL(SureAdd(QString)),parent,SLOT(AddHost(QString)));
}

AddDialog::~AddDialog()
{
    delete ui;
}

void AddDialog::on_QuitButton_clicked()
{
    close();
}

void AddDialog::on_SureButton_clicked()
{
    QString hostadress=ui->lineEdit->text();
    emit SureAdd(hostadress);
    close();
}
