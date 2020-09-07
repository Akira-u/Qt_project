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

void Trap::collideHero(Hero *hero){
    if(isActive==PASSIVE&&collidesWithItem(hero)){// passive trap
        hero->beAttacked(1);
        qDebug("crash");
        return;
    }
    //active trap
    if(hero->y()>boundingRect().top()&&hero->x()>=boundingRect().left()&&hero->x()<=boundingRect().left()+boundingRect().width()){
        //when under the trap
        isActive = TRIGGERED;
        move();
    }
    if(collidesWithItem(hero)){
        hero->beAttacked(1);
        isActive = PASSIVE;
    }
}
