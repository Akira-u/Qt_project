#include "jumper.h"

#include "licker.h"

Jumper::Jumper(QObject *parent, QPixmap pix): Unit(pix, parent)
{}

void Jumper::move(){
    if(!isLeftBlocked&&horizontalMoveStatus==STOP){// hover
        horizontalMoveStatus = LEFT;
    }
    else if(!isRightBlocked&&horizontalMoveStatus==STOP){
        horizontalMoveStatus = RIGHT;
    }
    if(horizontalMoveStatus != STOP){
        moveBy(horizontalMoveStatus * horizontalSpeed, 0);
    }
    if(!isOnGround){//drop
        verticalMoveStatus = DOWN;
        verticalSpeed += G;//up is -, down is +
        moveBy(0, verticalSpeed);
    }
    else{
        jump();

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

