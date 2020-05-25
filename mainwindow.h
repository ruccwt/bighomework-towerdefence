#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "towerposition.h"
#include "tower.h"
#include "waypoint.h"
#include "enemy.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
    void loadtowerposition();
    void mousePressEvent(QMouseEvent *event);
    bool canbuytower();
    void addwaypoint();
    void getHpDamage(int damage = 1);
    void removedEnemy(Enemy *enemy);
    bool loadwave();
public slots:
    void updatemap();
private:
    Ui::MainWindow *ui;
    QList<towerposition> towerpositionslist;
    QList<tower *> attacktowerlist;
    QList<WayPoint *> waypointlist;
    QList<Enemy *>enemylist;
    int waves;
    bool win;
};

#endif // MAINWINDOW_H
