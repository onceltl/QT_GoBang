#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
class ChessBoard : public QWidget
{
    Q_OBJECT
public:
    explicit ChessBoard(QWidget *parent = 0);
    ~ChessBoard();
    void readychange(bool ok){isready=ok;}
    void clear();
private:

    QPoint find(QPoint p);
    void setColor(int sytle);
    void check();
signals:
    void getPoint(QPoint);
    void getWin();
public slots:
protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    int len;
    QPoint ChessPoint[16][16];
    QPoint StartPoint,EndPoint;
    bool isready;
    int movex[6]={0,0,0,0,0,0};
    int movey[6];
public:

    int mycolor;
    int  Chess[16][16];
};

#endif // CHESSBOARD_H
