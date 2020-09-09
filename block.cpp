#include "block.h"

Block::Block(int x, int y,QPixmap img, QObject *parent) : QObject(parent), QGraphicsPixmapItem(img), location(x, y)
{
    setPos(location);
}

QRectF Block::boundingRect() const{
    qreal adjust = 0.5;
    return QRectF(-BLOCK_LENGTH/2-adjust,-BLOCK_LENGTH/2-adjust,BLOCK_LENGTH+adjust,BLOCK_LENGTH+adjust);
}

void Block::move(){

    return;
}

void Block::collideHero(Hero *hero){
    return;
}
