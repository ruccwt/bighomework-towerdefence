#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPainter"
#include <QMouseEvent>
#include "waypoint.h"
#include <QtGlobal>
#include <QMessageBox>
#include "QObject"
#include "QTimer"
void MainWindow::loadtowerposition()
{
    QPoint posi[]=
    {
        QPoint(190,100),
        QPoint(270,160),
        QPoint(350,160),
        QPoint(450,140),
        QPoint(410,270),
        QPoint(570,210),
        QPoint(405,385),
        QPoint(480,440),
        QPoint(560,445),
        QPoint(645,440),
        QPoint(725,440)

    };
    int len=sizeof(posi)/sizeof(posi[0]);
    for(int i=0;i<len;++i)
    {
        towerpositionslist.push_back(posi[i]);
    }
}
void MainWindow::addwaypoint()
{
    WayPoint *wayPoint1 = new WayPoint(QPoint(815,420));
    waypointlist.push_back(wayPoint1);

    WayPoint *wayPoint2 = new WayPoint(QPoint(485,420));
    waypointlist.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);

    WayPoint *wayPoint3 = new WayPoint(QPoint(480,265));
    waypointlist.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint4 = new WayPoint(QPoint(545,265));
    waypointlist.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);

    WayPoint *wayPoint5 = new WayPoint(QPoint(545,205));
    waypointlist.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    WayPoint *wayPoint6 = new WayPoint(QPoint(425,200));
    waypointlist.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);

    WayPoint *wayPoint7 = new WayPoint(QPoint(415,140));
    waypointlist.push_back(wayPoint7);
    wayPoint7->setNextWayPoint(wayPoint6);

    WayPoint *wayPoint8 = new WayPoint(QPoint(265,140));
    waypointlist.push_back(wayPoint8);
    wayPoint8->setNextWayPoint(wayPoint7);

    WayPoint *wayPoint9 = new WayPoint(QPoint(265,90));
    waypointlist.push_back(wayPoint9);
    wayPoint9->setNextWayPoint(wayPoint8);
}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    waves(0),
    win(false)
{

    ui->setupUi(this);
    loadtowerposition();
    addwaypoint();
    loadwave();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updatemap()));
    timer->start(30);
    }



MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,QPixmap(":/images/background.png"));
    QPainter *p=&painter;

    for(int i=0;i<towerpositionslist.size();++i)
    {
        towerpositionslist[i].draw(p);

    }
    foreach(tower*tow,attacktowerlist)
        tow->draw(&painter);
    foreach(WayPoint*wp,waypointlist)
        wp->draw(&painter);
    foreach (Enemy *enemy, enemylist)
        enemy->draw(&painter);

}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {QPoint pressPos = event->pos();

    auto it = towerpositionslist.begin();

    while (it != towerpositionslist.end())

    {
        if (canbuytower() && it->ifcontain(pressPos) && !it->gethastower())
        {
            it->sethastower(true);
            tower *tow = new tower(it->getpos());
            attacktowerlist.push_back(tow);
            update();
            break;
        }
        ++it;
    }
    }
   if(event->button()==Qt::RightButton)
   {
       QPoint _posi=event->pos();
       auto it =towerpositionslist.begin();
       while(it!=towerpositionslist.end())
       {
           if(it->ifcontain(_posi)&&it->gethastower())
           {
               it->sethastower(false);
               attacktowerlist.pop_back();
               update();
               break;
           }
           ++it;
       }
   }
}
bool MainWindow::canbuytower()
{
    return true;
}
void MainWindow::getHpDamage(int damage/* = 1*/)
{
    ;
}

void MainWindow::removedEnemy(Enemy *enemy)
{
    Q_ASSERT(enemy);

    enemylist.removeOne(enemy);
    delete enemy;

    if (enemylist.empty())
    {
        ++waves;
        if (!loadwave())
        {
            win = true;
            // 游戏胜利转到游戏胜利场景
            // 这里暂时以打印处理
        }
    }
}
bool MainWindow::loadwave()
{
    if (waves >= 6)
        return false;

    WayPoint *startWayPoint = waypointlist.back();
    int enemyappearinterval[]={100,500,600,1000,3000,6000};

    for (int i = 0; i < 6; ++i)
    {

        Enemy *enemy = new Enemy(startWayPoint, this);
        enemylist.push_back(enemy);
        QTimer::singleShot(enemyappearinterval[i], enemy, SLOT(doActivate()));
    }

    return true;
}


void MainWindow::updatemap()

{

    foreach (Enemy *enemy, enemylist)

        enemy->move();

    update();

}



