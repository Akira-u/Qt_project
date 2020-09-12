#include "trap.h"
#include <QDebug>
Trap::Trap(int x, int y, int activeType, QObject *parent, QPixmap img) : Block(x, y, img, parent), isActive(activeType)
{
}

void Trap::move(){
    if(isActive < TRIGGERED) return;
// active trap
    moveBy(0, fallSpeed+=G);
}

//void Trap::nextFrame(){
//    counter = (counter + 1) % 50;

//    setPixmap(QPixmap(":/pics/fire.png").copy(frameSequence[counter]*64, 0, 64, 114));
//    update();
//}

void Trap::collideHero(Unit *hero){
    if(isActive==PASSIVE&&collidesWithItem(hero, Qt::IntersectsItemBoundingRect)){// passive trap
        hero->beAttacked();
        return;
    }
    //active trap
    if(isActive==TRIGGERED){
        move();
    }
    else if(hero->y()>y()&&hero->x()>=x()&&hero->x()<=x()+boundingRect().width()){

        isActive = TRIGGERED;
        move();
    }
    if(collidesWithItem(hero, Qt::IntersectsItemBoundingRect)){//todo 落地不动?
        hero->beAttacked();
        //isActive = PASSIVE;
    }

}
