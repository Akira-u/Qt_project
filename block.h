#ifndef BLOCK_H
#define BLOCK_H

#include "constants.h"
#include "unit.h"
#include <QObject>
#include <QGraphicsItem>
#include <QPoint>

class Block : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Block(int x, int y, QPixmap img=QPixmap(":/pics/ground.png"), QObject *parent = nullptr);
    virtual void move();
    virtual void collideHero(Unit *);
    virtual QString gameType(){
        return "block";
    }
signals:

private:
    QPoint location;
};

#endif // BLOCK_H
