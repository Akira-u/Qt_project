#include "spring.h"
#include <QDebug>
Spring::Spring(int x, int y, QPixmap img, QObject *parent):Block(x, y, img, parent)
{

}

void Spring::collideHero(Unit *u){
    Hero *hero = dynamic_cast<Hero*>(u);
    if(hero==nullptr) return;
    if(hero->collideItemsList.contains(this)&&hero->y()<y()){
        hero->setVerticalSpeed(2 * JUMPSPEED);
        hero->setVerticalMoveStatus(DOWN);
        hero->setIsOnGround(false);
        hero->moveBy(0, -1);
        hero->playJumpMusic();
    }
}
