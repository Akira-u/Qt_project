#include "hero.h"
#include<QDebug>
Hero::Hero(QObject *parent, QPixmap pix) : Unit(pix, parent){}


void Hero::move(){
    if(horizontalMoveStatus != STOP){//move
        moveBy(horizontalMoveStatus * horizontalSpeed, 0);
    }

    if(!isOnGround){//drop

        verticalMoveStatus = DOWN;
        verticalSpeed += G;//up is -, down is +
        moveBy(0, verticalSpeed);
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


void Hero::keyPressEvent(QKeyEvent *event){
    qDebug("keyreceive");
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
            qDebug("jump called");
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
