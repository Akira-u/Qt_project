#ifndef SPRING_H
#define SPRING_H
#include "block.h"

class Spring : public Block
{
    Q_OBJECT
public:
    Spring(int x, int y, QPixmap img=QPixmap(":/pics/spring.png"), QObject *parent = nullptr);

    //use Block::move(), can't move
    void collideHero(Unit *) override;
    QString gameType() override{
        return "spring";
    }
};
#endif // SPRING_H
