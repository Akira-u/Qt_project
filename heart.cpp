#include "heart.h"

Heart::Heart(int x, int y, QPixmap img, QObject *parent):Block(x, y, img, parent)
{
}
void Heart::collideHero(Hero *hero){
    if(collidesWithItem(hero)){
        hero->setHealth(hero->getHealth() + 1);
        hide();
    }
}
