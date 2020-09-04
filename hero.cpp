#include "hero.h"

Hero::Hero(QPixmap pix, QObject *parent) : QObject(parent), QGraphicsPixmapItem(pix)
{

}

int Hero::getSpeed(){
    return speed;
}
void Hero::setHorizontalMove(int dir){
    horizontal_move_status = dir;
}
int Hero::isHorizontalMove(){
    return horizontal_move_status;
}
