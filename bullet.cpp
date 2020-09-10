#include "bullet.h"

Bullet::Bullet(QObject *parent, QPixmap pix): Unit(pix, parent)
{

}
void Bullet::move(){
    if(horizontalMoveStatus != STOP){// move
        moveBy(horizontalMoveStatus * horizontalSpeed, 0);
    }
    if(!isLeftBlocked||isRightBlocked){
        horizontalMoveStatus = STOP;
        hide();
    }

    // left out = right in
    if(x()<0){
        setX(999);
    }
    else if(x()>1000){
        setX(1);
    }
    if(y()<0){
        setY(0);
    }
    else if(y()>1300){
        hide();
    }
}

