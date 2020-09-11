#ifndef BLOCK_H
#define BLOCK_H

#include "constants.h"
#include "hero.h"
#include <QObject>
#include <QGraphicsItem>
#include <QPoint>

class Block : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Block(int x, int y, QPixmap img=QPixmap(":/pics/ground.png"), QObject *parent = nullptr);
//    QRectF boundingRect() const override;
    virtual void move();
    virtual void collideHero(Hero*);
    virtual QString gameType(){
        return "block";
    }
signals:

private:
    QPoint location;
};

#endif // BLOCK_H
