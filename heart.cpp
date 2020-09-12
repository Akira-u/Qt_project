#include "heart.h"
#include<QDebug>
Heart::Heart(int x, int y, QPixmap img, QObject *parent):Block(x, y, img, parent)
{
}
void Heart::collideHero(Unit *hero){
    if(collidesWithItem(hero, Qt::IntersectsItemBoundingRect)){
        qDebug("hit heart");
        hero->setHealth(hero->getHealth() + 1);
        hide();
    }
}
