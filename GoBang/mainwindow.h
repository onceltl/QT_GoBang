#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_CreatButton_clicked();
    void AddHost(QString hostaddress);
    void LinkHost(QString hostaddress);
    void on_AddButton_clicked();
    void acceptConnection();
    void GetMessage();
    void sendPoint(QPoint);
    void on_StartButton_clicked();
    void haveWin();
private:
    Ui::MainWindow *ui;
    QTcpServer *Listen;
    QTcpSocket *MySocket;
    bool s1,s2;
};

#endif // MAINWINDOW_H
