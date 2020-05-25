#include "QMainWindow"
#include "QPainter"
#include "tower.h"
tower::tower(QPoint p,const QPixmap &sprite):pos(p),pics(sprite),attackrange(150){}
void tower::draw(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::white);//绘制攻击范围
    painter->drawEllipse(pos.x()-50,pos.y()-50,attackrange,attackrange);
    painter->drawPixmap(pos.x(),pos.y(),pics);
    painter->restore();
}
