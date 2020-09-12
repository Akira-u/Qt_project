#ifndef MUSHROOM_H
#define MUSHROOM_H
#include "block.h"
#include "hero.h"

class Mushroom : public Block
{
    Q_OBJECT
public:
    Mushroom(int x, int y, QObject *parent = nullptr, QPixmap img=QPixmap(":/pics/mushroom.png"));
    QString gameType() override{
        return "mushroom";
    }
    void collideHero(Unit *) override;
};

#endif // MUSHROOM_H
