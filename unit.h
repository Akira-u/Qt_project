#ifndef UNIT_H
#define UNIT_H

#include "constants.h"

#include <QObject>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>


class Unit : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Unit(QPixmap pix, QObject *parent = nullptr);
    virtual QString gameType(){
        return "unit";
    }
    // functions about move
    int getHorizontalSpeed() const;

    void setHorizontalMove(int dir);
    int getHorizontalMoveStatus();

    double getVerticalSpeed() const;
    void setVerticalSpeed(double value);
    void jump();

    int getVerticalMoveStatus() const;
    void setVerticalMoveStatus(int dir);

    virtual void move();

    // Members about collide
//    QRectF boundingRect() const override;
    QList<QGraphicsItem*> collideItemsList;
    //bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode = Qt::IntersectsItemShape) const override;
    void checkCollideDirection();//set members below
    bool isFloorBlocked = false;
    bool isOnGround = false;// true when unit is on the ground which means it can jump.
    bool isRightBlocked = false;
    bool isLeftBlocked = false;
    int width;
    int height;
    virtual void monsterAttackHero(Unit *);


    //functions about health

    void beAttacked();
protected:
    int horizontalSpeed = 5;
    int horizontalMoveStatus = STOP;// move during A/D is pressed
    double verticalSpeed = 0;// free fall, need to be set
    int verticalMoveStatus = STOP;
    int attackInterval = 1000 / TIMER_INTERVAL;

signals:

private:
    int health = 1;

};

#endif // UNIT_H
