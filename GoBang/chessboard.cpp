#include "chessboard.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QDebug>
#include <QMouseEvent>
#include <string.h>
void ChessBoard::clear()
{
    mycolor=2;
    len=30;
    isready=0;
    warn=0;
    for (int i=1;i<=15;i++)
        for (int j=1;j<=15;j++)
        {
            ChessPoint[i][j]=QPoint(i*len,j*len);
            Chess[i][j]=0;
        }
}
ChessBoard::ChessBoard(QWidget *parent) : QWidget(parent)
{
    clear();
    connect(this,SIGNAL(getPoint(QPoint)),parent->parent(),SLOT(sendPoint(QPoint)));
    connect(this,SIGNAL(getWin()),parent->parent(),SLOT(haveWin()));
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
    p.setBrush(QBrush(Qt::black));
    p.drawEllipse(ChessPoint[4][4],3,3);
    p.drawEllipse(ChessPoint[4][12],3,3);
    p.drawEllipse(ChessPoint[12][4],3,3);
    p.drawEllipse(ChessPoint[12][12],3,3);
    p.drawEllipse(ChessPoint[8][8],3,3);
    for (int i=1;i<=15;i++)
        for (int j=1;j<=15;j++)
        if (Chess[i][j])
        {
            if (Chess[i][j]==2) p.setBrush(QBrush(Qt::black));
                else p.setBrush(QBrush(Qt::white));
            p.drawEllipse(ChessPoint[i][j],len/2,len/2);
        }
    QPixmap pixmap(":/images/boom");
    pixmap.scaled(1,1,Qt::KeepAspectRatio);
    p.setBrush(pixmap);
    if (warn)
        for (int i=1;i<=15;i++)
            for (int j=1;j<=15;j++)
                if (warnboard[i][j])
                    p.drawPixmap(ChessPoint[i][j].rx()-len/2,ChessPoint[i][j].ry()-len/2,len,len,pixmap);

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
    if (!isready) return;
    if (event->button()==Qt::LeftButton)
    {
        EndPoint=event->pos();
        if ((StartPoint-EndPoint).manhattanLength()<=10)
        {
            QPoint Right=find(StartPoint);
            Chess[Right.rx()][Right.ry()]=mycolor;
            emit(getPoint(Right));
        }
        update();
        isready=0;
        check();
    }
}
QPoint ChessBoard::find(QPoint p)
{
    QPoint near=QPoint(1,1);
    int minlen=999999999;
    for (int i=1;i<=15;i++)
            for (int j=1;j<=15;j++)
                if (!Chess[i][j])
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
void ChessBoard::check()
{
    for (int k=0;k<8;k++)
        for (int i=1;i<=15;i++)
            for (int j=1;j<=15;j++)
                if (Chess[i][j]==mycolor)
                {
                    bool ok=1;
                    for(int len=1;len<=4;len++)
                       {
                        int nx=i+movex[k]*len;
                        int ny=j+movey[k]*len;
                        if (!(nx>=1&&nx<=15&&ny>=1&&ny<=15&&Chess[nx][ny]==mycolor)) ok=0;
                       }
                    if (ok)
                    {
                        emit(getWin());
                        return;
                    }
                }
}

void ChessBoard::setColor(int sytle)
{
    mycolor=sytle;
}
bool ChessBoard::pd(int x,int y)
{
  //  Chess[x][y]=mycolor^=1;
    bool have3=0;
    bool have4=0;
    for (int k=0;k<8;k++)
    {
      bool allcolor=1;
      int nx=x,ny=y;
      for (int len=1;len<=3;len++)
      {
         nx=x+movex[k]*len;
        ny=y+movey[k]*len;
          if (!(nx>=1&&nx<=15&&ny>=1&&ny<=15&&Chess[nx][ny]==(mycolor^1))) allcolor=0;
      }
      if (allcolor) {have4=1;continue;}
      allcolor=1;
      for (int len=1;len<=2;len++)
      {
          nx=x+movex[k]*len;
          ny=y+movey[k]*len;
          if (!(nx>=1&&nx<=15&&ny>=1&&ny<=15&&Chess[nx][ny]==(mycolor^1))) allcolor=0;
      }
      nx=x+movex[k]*3;
      ny=y+movey[k]*3;
      if (allcolor&&(nx>=1&&nx<=15&&ny>=1&&ny<=15&&Chess[nx][ny]==0))allcolor=1;
        else allcolor=0;
      if (allcolor) have3=1;
    }
   // Chess[x][y]=0;
    return have3&have4;
}
void ChessBoard::warning()
{
    warn^=1;
    memset(warnboard,0,sizeof(warnboard));
    for (int i=1;i<=15;i++)
        for (int j=1;j<=15;j++)
            if (Chess[i][j]==0&&pd(i,j)) warnboard[i][j]=1;
    repaint();
}
