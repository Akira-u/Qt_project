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

void Unit::checkCollideDirection(){
    prepareGeometryChange();
    collideItemsList = collidingItems();
    if(!collideItemsList.isEmpty()){
        bool bottomFlag = 0;// check is not collided
        bool floorFlag = 0;
        bool leftFlag = 0;
        bool rightFlag = 0;
        for(auto i:collideItemsList){// find Items on the buttom of hero
            if(i->y() > y()&&(i->y() - y()==height/2 + i->boundingRect().height()/2)){// ensure up and down collide
                setVerticalSpeed(0);// reset vv
                setVerticalMoveStatus(STOP);
                isOnGround = true;
                bottomFlag = true;
                if(y() > i->y() - height/2 - i->boundingRect().height()/2){// avoid digging in ground
                    setY(i->y() - height/2 - i->boundingRect().height()/2);
                    qDebug()<<"mario:"<<pos().y()<<Qt::endl<<"brick:"<<i->pos().y();
                }
            }
            else if(i->x() > x()&&(i->x() - x()==width/2 + i->boundingRect().width()/2)){
                isRightBlocked = true;
                rightFlag = true;
            }
            else if(i->x() < x()&&(x() - i->x()==width/2 + i->boundingRect().width()/2)){
                isLeftBlocked = true;
                leftFlag = true;
            }
            else if(i->y() < y()&&(y() - i->y()==height/2 + i->boundingRect().height()/2)){
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

    }

}

void Unit::jump(){
    setVerticalSpeed(JUMPSPEED);
    isOnGround = false;
}
void Unit::beAttacked(int damage){
    health -=damage;
    if(health < 1){
        hide();
    }
}
