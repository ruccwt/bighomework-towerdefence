#ifndef TOWER_H
#define TOWER_H
#include "QMainWindow"
#include "QPainter"
class tower
{
public:
    tower(QPoint p,const QPixmap &sprite=QPixmap(":/images/tower1.png") );
    void draw(QPainter *painter);
private:
    QPoint pos;
    QPixmap pics;
    double attackrange;
};

#endif // TOWER_H
