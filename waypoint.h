#ifndef WAYPOINT_H
#define WAYPOINT_H
#include "QPoint"


// 敌人移动的航线
class QPainter;
class WayPoint
{
public:
    WayPoint(QPoint pos);

    void setNextWayPoint(WayPoint *nextpoint);
    WayPoint* nextWayPoint() const;
    const QPoint pos() const;

    void draw(QPainter *painter) const;

private:
    const QPoint		m_pos;
    WayPoint *			m_nextWayPoint;
};
#endif // WAYPOINT_H
