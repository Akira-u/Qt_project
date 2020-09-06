#include "block.h"

Block::Block(int x, int y, QPixmap img, QObject *parent) : QObject(parent), QGraphicsPixmapItem(img), location(x, y)
{
    setPos(location);
}
