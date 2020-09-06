#include "unit.h"

Unit::Unit(QPixmap pix, QObject *parent) : QObject(parent), QGraphicsPixmapItem(pix)
{

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
QRectF Unit::boundingRect() const{
    qreal adjust = 1;
    return QRectF(-58-adjust,-68-adjust,115+adjust,136+adjust);
}

int Unit::getVerticalSpeed() const{
    return verticalSpeed;
}

void Unit::setVerticalSpeed(int value){
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

void Unit::checkCollideDirection(){
    collideItemsList = collidingItems();
    if(!collideItemsList.isEmpty()){
        for(auto i:collideItemsList){// find Items on the buttom of hero
            if(i->y() < y()){
                isOnGround = true;
            }
            if(i->x() > x()){
                isRightBlocked = true;
            }
            if(i->x() < x()){
                isLeftBlocked = true;
            }
            if(i->y() > y()){
                isFloorBlocked = true;
            }
        }
    }

}

void Unit::jump(){
    setVerticalSpeed(JUMPSPEED);
}
