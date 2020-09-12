#ifndef BREAKABLEBRICK_H
#define BREAKABLEBRICK_H
#include "block.h"

class BreakableBlock : public Block
{
    Q_OBJECT
public:
    BreakableBlock(int x, int y, QPixmap img=QPixmap(":/pics/breakable_block.png"), QObject *parent = nullptr);
    QString gameType() override{
        return "breakable brick";
    }
};

#endif // BREAKABLEBRICK_H
