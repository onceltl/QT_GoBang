#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
class ChessBoard : public QWidget
{
    Q_OBJECT
public:
    explicit ChessBoard(QWidget *parent = 0);
    ~ChessBoard();
private:

    QPoint find(QPoint p);
signals:

public slots:
protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    int len;
    QPoint ChessPoint[16][16];
    int  Chess[16][16];
    QPoint StartPoint,EndPoint;
};

#endif // CHESSBOARD_H
