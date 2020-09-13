#include "hero.h"
#include<QDebug>
Hero::Hero(QObject *parent, QPixmap pix) : Unit(pix, parent){
    attackInterval = 0;
    jump_music = new QMediaPlayer;
    jump_music->setMedia(QUrl("qrc:/mu/mp3s/jumpSound.mp3"));
    jump_music->setVolume(50);
}

Hero::~Hero(){
    delete jump_music;
}
void Hero::move(){
    if(isRightBlocked&&horizontalMoveStatus==RIGHT){
        horizontalMoveStatus = STOP;
    }
    if(isLeftBlocked&&horizontalMoveStatus==LEFT){
        horizontalMoveStatus = STOP;
    }
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

void Hero::jump(){
    setVerticalSpeed(JUMPSPEED);
    moveBy(0, -1);
    isOnGround = false;
    jump_music->play();
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

void Hero::setIsBuffed(bool value)
{
    isBuffed = value;
}

void Hero::beAttacked(){
    if(attackInterval==1){
        return;
    }
    health --;
    isBuffed = false;
    if(health < 1){
        hide();
    }
    else{// respawn
        setHorizontalMove(STOP);
        setPos(STARTPOINT_X, STARTPOINT_Y);
        QMessageBox msgBox;
        msgBox.setText("Respawn!Remain life:"+QString::number(health));
        msgBox.exec();
    }
}
void Hero::attack(){
    for(auto i:collideItemsList){
        if(i==this) continue;
        Unit *u=dynamic_cast<Unit*>(i);
        if(u!=nullptr){
            score++;
            u->beAttacked();
            continue;
        }
        Block *b=dynamic_cast<Block *>(i);
        if(b!=nullptr){
             if(b->gameType()=="breakable brick"){
                 b->hide();
             }
        }
    }
}
void Hero::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        if(attackInterval==0){
            attack();
            attackInterval = 1;
            setPixmap(QPixmap(":/pics/mario_attack.png"));
            QTimer::singleShot(500, this, [=](){
                attackInterval = 0;
                setPixmap(QPixmap(":/pics/mario_stop.png"));
            });

        }
    }
}

bool Hero::getIsBuffed() const
{
    return isBuffed;
}
