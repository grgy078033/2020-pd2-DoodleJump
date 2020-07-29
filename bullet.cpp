#include "bullet.h"
#include "mainwindow.h"
float b_x;
float b_y;
extern int monster_die;

bullet::bullet()
{

}
void bullet::fly()
{
    this->setPos(x(), y() - 5);
    b_x = x();
    b_y = y();
    if(y() < 0) {
        scene()->removeItem(this);
        delete this;
    }
    else if(monster_die == 1){
        monster_die = 0;
        scene()->removeItem(this);
        delete this;
    }

}
