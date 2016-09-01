#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>

namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = 0);
    ~AddDialog();
signals:
    void SureAdd(QString hostadress);
private slots:
    void on_QuitButton_clicked();

    void on_SureButton_clicked();

private:
    Ui::AddDialog *ui;
};

#endif // ADDDIALOG_H
