#include "spitter.h"
#include <QDebug>

Spitter::Spitter(QObject *parent, QPixmap pix): Unit(pix, parent)
{
    attackInterval=0;
}

void Spitter::farAttackHero(Unit *hero, QGraphicsScene *scene, QList<Unit *> &unitsList){

    if(isVisible()&&attackInterval==0&&hero->y()<y()+boundingRect().height()&&hero->y()>y()-hero->boundingRect().height()){

        auto *bu = new Bullet(scene);

        if(hero->x()>x()){//s h
            bu->setPos(x() + 100, y());
            bu->setHorizontalMove(RIGHT);
        }
        else if(hero->x()<x()){//h s
            bu->setPos(x() - 100, y());
            bu->setHorizontalMove(LEFT);
        }
        scene->addItem(bu);
        unitsList.push_back(bu);
        attackInterval = 1000 / TIMER_INTERVAL;
    }
    if(attackInterval>0) attackInterval--;
}

void Spitter::move(){
    if(!isOnGround){//drop
        verticalMoveStatus = DOWN;

        if(verticalSpeed < MAXSPEED) verticalSpeed += G;//up is -, down is +
        moveBy(0, verticalSpeed);
    }
    else{
        jump();
    }
    // left out = right in
    if(x()<0){
        setX(VIEW_WIDTH);
    }
    else if(x()>VIEW_WIDTH){
        setX(1);
    }
    if(y()<0){
        setY(0);
    }
    else if(y()>VIEW_HEIGHT){
        hide();
    }
}
