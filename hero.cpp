#include "hero.h"
#include<QDebug>
Hero::Hero(QObject *parent, QPixmap pix) : Unit(pix, parent){}


void Hero::move(){
    if(horizontalMoveStatus != STOP){//move
        moveBy(horizontalMoveStatus * horizontalSpeed, 0);

    }

    if(!isOnGround){//drop

        verticalMoveStatus = DOWN;
        if(verticalSpeed < MAXSPEED) verticalSpeed += G;//up is -, down is +
        moveBy(0, verticalSpeed);
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


void Hero::keyPressEvent(QKeyEvent *event){

    if(event->key() == Qt::Key_D){// hero move right
        if(isRightBlocked){
            setHorizontalMove(STOP);
            return;
        }
        setHorizontalMove(RIGHT);
    }
    else if(event->key() == Qt::Key_A){// hero move left
        if(isLeftBlocked){
            setHorizontalMove(STOP);
            return;
        }
        setHorizontalMove(LEFT);
    }
    else if(event->key() == Qt::Key_W){
        if(isOnGround){
            jump();

            return;
        }
    }
    else{
        QGraphicsPixmapItem::keyPressEvent(event);
    }
}

void Hero::keyReleaseEvent(QKeyEvent *event){
    if((event->key() == Qt::Key_D&&getHorizontalMoveStatus()==RIGHT)||(event->key() == Qt::Key_A&&getHorizontalMoveStatus()==LEFT)){// stop move when dir=the key released
        setHorizontalMove(STOP);
    }
    else{
        QGraphicsPixmapItem::keyReleaseEvent(event);
    }
}
