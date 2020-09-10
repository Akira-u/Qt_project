#include "unit.h"
#include<QDebug>
Unit::Unit(QPixmap pix, QObject *parent) : QObject(parent), QGraphicsPixmapItem(pix)
{
    width=boundingRect().width();
    height=boundingRect().height();
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
        verticalSpeed += G;//up is -, down is +
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
        setX(1860);
    }
    else if(x()>1860){
        setX(1);
    }
    if(y()<0){
        setY(0);
    }
    else if(y()>1060){
        hide();
    }
}

void Unit::checkCollideDirection(){
    //prepareGeometryChange();
    collideItemsList = collidingItems();
    if(!collideItemsList.isEmpty()){

        bool bottomFlag = 0;// check is not collided
        bool floorFlag = 0;
        bool leftFlag = 0;
        bool rightFlag = 0;
        for(auto i:collideItemsList){// find Items on the buttom of hero
            if(i->y() > y()&&(i->y() - y()<=height/2 + i->boundingRect().height()/2+EPS&&i->y() - y()>=height/2 + i->boundingRect().height()/2-EPS)){// ensure up and down collide
qDebug("enter ground check");
qDebug()<<isOnGround<<collideItemsList.size();
                setVerticalSpeed(0);// reset vv
                setVerticalMoveStatus(STOP);
                isOnGround = true;
                bottomFlag = true;
                if(y() > i->y() - height/2 - i->boundingRect().height()/2){// avoid digging in ground
                    setY(i->y() - height/2 - i->boundingRect().height()/2);

                }
            }
            else if(i->x() > x()&&(i->x() - x()<=width/2 + i->boundingRect().width()/2+EPS&&i->x() - x()>=width/2 + i->boundingRect().width()/2-EPS)){
                isRightBlocked = true;
                rightFlag = true;
            }
            else if(i->x() < x()&&(x() - i->x()<=width/2 + i->boundingRect().width()/2+EPS&&x() - i->x()>=width/2 + i->boundingRect().width()/2-EPS)){
                isLeftBlocked = true;
                leftFlag = true;
            }
            else if(i->y() < y()&&(y() - i->y()<=height/2 + i->boundingRect().height()/2+EPS&&y() - i->y()>=height/2 + i->boundingRect().height()/2-EPS)){
                isFloorBlocked = true;
                floorFlag = true;
            }

        }
        if(bottomFlag == false){
            qDebug("bottomflag");
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

    }
    else{
        isOnGround = false;
        isFloorBlocked = false;
        isRightBlocked = false;
        isLeftBlocked = false;
    }

}

void Unit::monsterAttackHero(Unit * hero){
    if(collidesWithItem(hero)&&attackInterval <= 0&&isVisible()){
        hero->beAttacked();
        attackInterval = 1000 / TIMER_INTERVAL;
    }
    attackInterval--;
}

void Unit::jump(){
    setVerticalSpeed(JUMPSPEED);
    isOnGround = false;
}
void Unit::beAttacked(){
    health --;
    if(health < 1){
        hide();//todo respawn
    }
    else if(gameType()=="hero"){
        setPos(STARTPOINT_X, STARTPOINT_Y);
    }
}
