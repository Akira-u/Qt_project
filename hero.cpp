#include "hero.h"
#include<QDebug>
Hero::Hero(QObject *parent, QPixmap pix) : Unit(pix, parent){}



void Hero::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_D){// hero move right
        if(isRightBlocked){
            qDebug()<<"rightBlocked"<<isRightBlocked;
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
