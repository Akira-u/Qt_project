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
int Unit::isHorizontalMove(){
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


bool Unit::isOnGround(){
    if(!collideItemsList.isEmpty()){
        for(auto i:collideItemsList){// find Items on the buttom of hero
            if(i->y()<y()){
                return true;
            }
        }
    }
    return 0;
}

void Unit::jump(){
    int v = JUMPSPEED;
    moveBy(0, v);
    v -= G;
    //todo：写一个竖直运动状态
}
