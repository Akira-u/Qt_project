#include "unit.h"
#include<QDebug>
Unit::Unit(QPixmap pix, QObject *parent) : QObject(parent), QGraphicsPixmapItem(pix)
{
    width=boundingRect().width();
    height=boundingRect().height();//todo -4?
}

int Unit::getHorizontalSpeed() const{
    return horizontalSpeed;
}
void Unit::setHorizontalMove(int dir){
    horizontalMoveStatus = dir;
}
int Unit::getHorizontalMoveStatus(){
    return horizontalMoveStatus;
}
//QRectF Unit::boundingRect() const{
//    qreal adjust = 1;
//    return QRectF(-MARIO_WIDTH/2-adjust,-MARIO_HEIGHT/2-adjust,MARIO_WIDTH +2 * adjust,MARIO_HEIGHT+ 2 * adjust);
//}

double Unit::getVerticalSpeed() const{
    return verticalSpeed;
}

void Unit::setVerticalSpeed(double value){
    verticalSpeed = value;
}

int Unit::getVerticalMoveStatus() const
{
    return verticalMoveStatus;
}

void Unit::setVerticalMoveStatus(int dir)
{
    verticalMoveStatus = dir;
}

void Unit::move(){

    if(!isOnGround){//drop
        verticalMoveStatus = DOWN;

        if(verticalSpeed < MAXSPEED) verticalSpeed += G;//up is -, down is +
        moveBy(0, verticalSpeed);
    }
    if(!isLeftBlocked&&horizontalMoveStatus==STOP){
        horizontalMoveStatus = LEFT;
    }
    else if(!isRightBlocked&&horizontalMoveStatus==STOP){
        horizontalMoveStatus = RIGHT;
    }
    if(horizontalMoveStatus != STOP){// move
        moveBy(horizontalMoveStatus * horizontalSpeed, 0);
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

void Unit::checkCollideDirection(){
    //prepareGeometryChange();
    collideItemsList = collidingItems(Qt::IntersectsItemBoundingRect);
    if(!collideItemsList.isEmpty()){

        bool bottomFlag = 0;// check is not collided
        bool floorFlag = 0;
        bool leftFlag = 0;
        bool rightFlag = 0;
        for(auto i:collideItemsList){// find Items on the buttom of hero
            if(gameType()=="hero"&&i->y()==900) qDebug()<<i->y() - y()<<y() + height<<i->y() + EPS;
            if(i->y() > y()&&y() + height<i->y() + EPS&&i->x()<x()+width&&i->x()>x()-i->boundingRect().width()){// ensure up and down collide
                if(y() + height>= i->y()&&y()+height<i->y()+EPS){// avoid digging in ground
                    setY(i->y() - height + 1);
                }
                setVerticalSpeed(0);// reset vv
                setVerticalMoveStatus(STOP);
                isOnGround = true;
                bottomFlag = true;
            }

            else if(i->x() > x()&&i->y()<y() + height - 1&&i->y() + i->boundingRect().height()>y()){
               if(gameType()=="hero") qDebug("in");
                isRightBlocked = true;
                rightFlag = true;
            }
            else if(i->x() < x()&&i->y()<y() + height - 1&&i->y() + i->boundingRect().height()>y()/*&&(x() - i->x()<=width/2 + i->boundingRect().width()/2+EPS&&x() - i->x()>=width/2 + i->boundingRect().width()/2-EPS)*/){
                isLeftBlocked = true;
                leftFlag = true;
            }

            else if(i->y() < y()&&(y() - i->y()<=height/2 + i->boundingRect().height()/2+EPS&&y() - i->y()>=height/2 + i->boundingRect().height()/2-EPS)){
                isFloorBlocked = true;
                floorFlag = true;
            }

        }
        if(bottomFlag == false){
            isOnGround = false;
        }
        if(floorFlag == false){
            isFloorBlocked = false;
        }
        if(rightFlag == false){
            isRightBlocked = false;
        }
        if(leftFlag == false){
            isLeftBlocked = false;
        }
    if(gameType()=="hero") qDebug()<<isRightBlocked<<isLeftBlocked<<isFloorBlocked;
    }
    else{
        isOnGround = false;
        isFloorBlocked = false;
        isRightBlocked = false;
        isLeftBlocked = false;
    }

}

void Unit::setIsOnGround(bool value)
{
    isOnGround = value;
}

void Unit::monsterAttackHero(Unit * hero){
    if(collidesWithItem(hero, Qt::IntersectsItemBoundingRect)&&attackInterval <= 0&&isVisible()){
        hero->beAttacked();
        attackInterval = 1000 / TIMER_INTERVAL;
    }
    attackInterval--;
}

void Unit::jump(){
    setVerticalSpeed(JUMPSPEED);
    moveBy(0, -1);
    isOnGround = false;
}
void Unit::beAttacked(){
    health --;
    if(health < 1){
        hide();
    }
}

void Unit::setHealth(int value)
{
    health = value;
}

int Unit::getHealth() const
{
    return health;
}
