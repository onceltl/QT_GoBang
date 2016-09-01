#ifndef LINKDIALOG_H
#define LINKDIALOG_H

#include <QDialog>

namespace Ui {
class LinkDialog;
}

class LinkDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LinkDialog(QWidget *parent = 0);
    ~LinkDialog();
signals:
    void SureAdd(QString);
private slots:
    void on_Q_clicked();
    void GetEdit(int);
    void on_SureButton_clicked();

private:
    Ui::LinkDialog *ui;
    QString hostaddress;
};

#endif // LINKDIALOG_H
