#include "mushroom.h"

Mushroom::Mushroom(int x, int y, QObject *parent, QPixmap img):Block(x, y, img, parent)
{
}

void Mushroom::collideHero(Unit *u){
    Hero *hero=dynamic_cast<Hero*>(u);
    if(hero!=nullptr){
        hero->setIsBuffed(true);
        hero->setHealth(hero->getHealth() + 1);
        hide();
    }
}
