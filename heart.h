#ifndef HEART_H
#define HEART_H
#include "block.h"

class Heart : public Block
{
    Q_OBJECT
public:
    Heart(int x, int y, QPixmap img=QPixmap(":/pics/heart.png"), QObject *parent = nullptr);
    // use Block::move, can't move
    void collideHero(Unit *) override;
    QString gameType() override{
        return "heart";
    }
};

#endif // HEART_H
