#ifndef TRAP_H
#define TRAP_H

#include "block.h"
#include "hero.h"
#include <QObject>
#include <QGraphicsItem>


class Trap : public Block
{
    Q_OBJECT
public:
    explicit Trap(int x, int y,int activeType = -1, QObject *parent = nullptr, QPixmap img=QPixmap(":/pics/firestart.png"));
    void nextFrame();
    void move() override;
    void collideHero(Unit*) override;
    QString gameType() override{
        if(isActive==PASSIVE) return "passive trap";
        else return "active trap";
    }
signals:
private:
    QPixmap allFire = QPixmap(":/pics/fire.png");
    int isActive = PASSIVE;//not an active trap
    //int frameSequence[50]={0,0,0,0,0,0,1,1,1,1,1,1,2,2,2,2,2,2,3,3,3,3,3,3,4,4,4,4,4,4,5,5,5,5,5,6,6,6,6,6,7,7,7,7,7,8,8,8,8,8};
    int counter = 0;
    double fallSpeed = 0;
    QPixmap fires[9];
};

#endif // TRAP_H
