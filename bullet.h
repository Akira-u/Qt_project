#ifndef BULLET_H
#define BULLET_H

#include "unit.h"
class Bullet : public Unit
{
    Q_OBJECT
public:
    Bullet(QObject *parent = nullptr, QPixmap pix = QPixmap(":/pics/fireball.png"));
    void move() override;
    //Use Unit::monsterAttackHero
    QString gameType() override{
        return "bullet";
    }
};

#endif // BULLET_H
