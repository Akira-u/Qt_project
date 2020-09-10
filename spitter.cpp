#include "spitter.h"

Spitter::Spitter(QObject *parent, QPixmap pix): Unit(pix, parent)
{
    attackInterval=0;
}

void Spitter::farAttackHero(Unit *hero, QGraphicsScene *scene, QList<Unit *> &unitsList){
    if(isVisible()&&attackInterval==0&&hero->y()<y()+boundingRect().height()&&hero->y()>y()-hero->boundingRect().height()){
        auto *bu = new Bullet(scene);
        scene->addItem(bu);
        unitsList.push_back(bu);
    }
    attackInterval--;

}
