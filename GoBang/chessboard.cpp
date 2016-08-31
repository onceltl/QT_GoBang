#include "chessboard.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QDebug>
#include <QMouseEvent>

ChessBoard::ChessBoard(QWidget *parent) : QWidget(parent)
{
    len=30;
    for (int i=1;i<=15;i++)
        for (int j=1;j<=15;j++)
        {
            ChessPoint[i][j]=QPoint(i*len,j*len);
            Chess[i][j]=0;
        }
}

ChessBoard::~ChessBoard()
{

}
void ChessBoard::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    QBrush brush;
    brush.setColor(QColor(255,236,139));
    brush.setStyle(Qt::SolidPattern);
    p.setPen(QPen(Qt::black));
    p.setBrush(brush);
    p.drawRect(len,len,len*14,len*14);
    for (int x=len;x<=len*14;x+=len)
    {
        p.drawLine(QPoint(x,len),QPoint(x,len*15));
    }
    for (int y=len;y<=len*14;y+=len)
    {
        p.drawLine(QPoint(len,y),QPoint(len*15,y));
    }
    for (int i=1;i<=15;i++)
        for (int j=1;j<=15;j++)
        if (Chess[i][j])
        {
            if (Chess[i][j]==1) p.setBrush(QBrush(Qt::black));
                else p.setBrush(QBrush(Qt::white));
            p.drawEllipse(ChessPoint[i][j],len/2,len/2);
        }
}
void ChessBoard::mousePressEvent(QMouseEvent *event)
{
    if (event->button()==Qt::LeftButton)
    {
        StartPoint=event->pos();
    }
}
void ChessBoard::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button()==Qt::LeftButton)
    {
        EndPoint=event->pos();
        if ((StartPoint-EndPoint).manhattanLength()<=10)
        {
            QPoint Right=find(StartPoint);
            Chess[Right.rx()][Right.ry()]=2;
        }
        update();
    }
}
QPoint ChessBoard::find(QPoint p)
{
    QPoint near=QPoint(1,1);
    int minlen=(p.rx()-ChessPoint[1][1].rx())*(p.rx()-ChessPoint[1][1].rx())+(p.ry()-ChessPoint[1][1].ry())*(p.ry()-ChessPoint[1][1].ry());
    for (int i=1;i<=15;i++)
            for (int j=1;j<=15;j++)
            {
                int len=(p.rx()-ChessPoint[i][j].rx())*(p.rx()-ChessPoint[i][j].rx())+(p.ry()-ChessPoint[i][j].ry())*(p.ry()-ChessPoint[i][j].ry());
                if (len<minlen)
                {
                    near=QPoint(i,j);
                    minlen=len;
                }
            }
   return near;
}
