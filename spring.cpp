#include "spring.h"
#include <QDebug>
Spring::Spring(int x, int y, QPixmap img, QObject *parent):Block(x, y, img, parent)
{

}

void Spring::collideHero(Hero *hero){
    if(collidesWithItem(hero)&&hero->y()<y()){
        hero->setVerticalSpeed(2 * JUMPSPEED);
        hero->setVerticalMoveStatus(DOWN);
        hero->setIsOnGround(false);
        hero->moveBy(0, -1);
    }
}
