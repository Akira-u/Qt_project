#include "destination.h"

Destination::Destination(int x, int y, QPixmap img, QObject *parent):Block(x, y, img, parent)
{

}

void Destination::collideHero(Unit *hero){
    if(hero->collideItemsList.contains(this)&&touchDest==false){
        touchDest = true;
        QMessageBox msgBox;
        msgBox.setText("You win!");
        msgBox.exec();
        hero->setHealth(-1);
        hero->beAttacked();//emit heroDead
    }
}
