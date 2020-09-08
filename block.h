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
    explicit Block(int x, int y, QString inputId, QPixmap img=QPixmap(":/pics/ground.png"), QObject *parent = nullptr);
    QRectF boundingRect() const override;
    virtual void move();
    virtual void collideHero(Hero*);
signals:

private:
    QPoint location;
    QString type = "block";
    QString id;
};

#endif // BLOCK_H
