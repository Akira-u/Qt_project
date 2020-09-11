#ifndef SPITTER_H
#define SPITTER_H
#include "unit.h"
#include "bullet.h"
#include <QGraphicsScene>

class Spitter : public Unit
{
    Q_OBJECT
public:
    Spitter(QObject *parent = nullptr, QPixmap pix = QPixmap(":/pics/spitter.png"));
    QString gameType() override{
        return "spitter";
    }
    void move() override;
    void farAttackHero(Unit *, QGraphicsScene *, QList<Unit *>&);
    void monsterAttackHero(Unit *) override{}
};

#endif // SPITTER_H
