#ifndef TOWERPOSITION_H
#define TOWERPOSITION_H
#include "QMainWindow"
#include "QPainter"
class towerposition
{
public:
    towerposition(QPoint p,const QPixmap &sprite=QPixmap(":/images/base.png"));
    void sethastower(bool t);
    bool gethastower();
   const  QPoint central();
   bool ifcontain(const QPoint &po);
   void draw(QPainter *painter);
   QPoint getpos();


private:
    QPoint pos;
    bool hastower;
    QPixmap pic;
    static const QSize fixedsize;
};

#endif // TOWERPOSITION_H
