#ifndef UNIT_H
#define UNIT_H

#include "constants.h"

#include <QObject>
#include <QGraphicsItem>
#include <QKeyEvent>


class Unit : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Unit(QPixmap pix, QObject *parent = nullptr);
    // functions about move
    int getHorizontalSpeed() const;

    void setHorizontalMove(int dir);
    int getHorizontalMoveStatus();

    double getVerticalSpeed() const;
    void setVerticalSpeed(double value);
    void jump();

    int getVerticalMoveStatus() const;
    void setVerticalMoveStatus(int dir);


    // Members about collide
//    QRectF boundingRect() const override;
    QList<QGraphicsItem*> collideItemsList;
    void checkCollideDirection();//set members below
    bool isFloorBlocked;
    bool isOnGround;// true when unit is on the ground which means it can jump.
    bool isRightBlocked;
    bool isLeftBlocked;
    int width;
    int height;

    //functions about health
    void attack();//todo:implement
    void beAttacked(int);
protected:

signals:

private:
    int horizontalSpeed = 5;
    int horizontalMoveStatus = STOP;// move during A/D is pressed
    double verticalSpeed = 0;// free fall, need to be set
    int verticalMoveStatus = STOP;

    int health = 1;
};

#endif // UNIT_H
