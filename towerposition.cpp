#include"QPainter"
#include"QMainWindow"
#include"towerposition.h"
const QSize towerposition::fixedsize(54, 54);
towerposition::towerposition(QPoint p,const QPixmap &sprite)
{
    pos=p;
    hastower=false;
    pic=sprite;
}
void towerposition:: sethastower(bool t)
{
    hastower=t;
}//查有没有塔
bool towerposition::gethastower()
{
    return hastower;
}
const  QPoint towerposition:: central()
{
    QPoint offsetPoint(fixedsize.width()/2,fixedsize.height()/2);
    return pos+offsetPoint;
}//中心点？
bool towerposition::ifcontain(const QPoint &po)
{
    bool isxhere= pos.x() < po.x() && po.x() < (pos.x() + fixedsize.width());
    bool isyhere=pos.y() < po.y() && po.y() < (pos.y() + fixedsize.height());
    return isxhere&&isyhere;
}//某点的坐标是否在指定范围内，与mouseevent联系

void towerposition::draw(QPainter *painter)

{

    painter->drawPixmap(pos.x(), pos.y(),pic);


}//画基座
QPoint towerposition::getpos()
{
    return pos;
}
