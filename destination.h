#ifndef DESTINATION_H
#define DESTINATION_H

#include "block.h"
class Destination : public Block
{
    Q_OBJECT
public:
    Destination(int x, int y, QPixmap img=QPixmap(":/pics/destination.png"), QObject *parent = nullptr);
    QString gameType() override{
        return "destination";
    }
    void collideHero(Unit *) override;
    bool touchDest = false;
};

#endif // DESTINATION_H
