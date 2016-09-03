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
    void warning();
private:

    QPoint find(QPoint p);
    void setColor(int sytle);
    void check();
    bool pd(int x,int y);
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
    int movex[8]={0,0,1,-1,1,1,-1,-1};
    int movey[8]={1,-1,0,0,1,-1,1,-1};
public:
    int warn;
    int warnboard[16][16];
    int mycolor;
    int  Chess[16][16];
};

#endif // CHESSBOARD_H
