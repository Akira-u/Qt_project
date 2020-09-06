#include "hero.h"

Hero::Hero(QPixmap pix, QObject *parent) : Unit(pix, parent){}



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
