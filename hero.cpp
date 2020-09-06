#include "hero.h"

Hero::Hero(QPixmap pix, QObject *parent) : Unit(pix, parent){}



void Hero::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_D){// hero move right
        if(!collideItemsList.isEmpty()){
            for(auto i:collideItemsList){// find Items on the right of hero
                if(i->x()>x()){
                    setHorizontalMove(STOP);
                    return;
                }
            }
        }

        setHorizontalMove(RIGHT);
    }
    else if(event->key() == Qt::Key_A){// hero move left
        if(!collideItemsList.isEmpty()){
            for(auto i:collideItemsList){
                if(i->x() < x()){
                    setHorizontalMove(STOP);
                    return;
                }
            }
        }

        setHorizontalMove(LEFT);
    }
    else if(event->key() == Qt::Key_W){
        if(isOnGround()){
            jump();
            return;
        }
    }
    else{
        QGraphicsPixmapItem::keyPressEvent(event);
    }
}

void Hero::keyReleaseEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_D||event->key() == Qt::Key_A){// stop move
        setHorizontalMove(STOP);
    }
    else{
        QGraphicsPixmapItem::keyReleaseEvent(event);
    }
}
