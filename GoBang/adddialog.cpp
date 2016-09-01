#include "adddialog.h"
#include "ui_adddialog.h"

AddDialog::AddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("创建"));
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
