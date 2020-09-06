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

    int getVerticalSpeed() const;
    void setVerticalSpeed(int value);
    void jump();

    int getVerticalMoveStatus() const;
    void setVerticalMoveStatus(int dir);


    // Members about collide
    QRectF boundingRect() const override;
    QList<QGraphicsItem*> collideItemsList;
    void checkCollideDirection();//set members below
    bool isFloorBlocked;
    bool isOnGround;// true when unit is on the ground which means it can jump.
    bool isRightBlocked;
    bool isLeftBlocked;
    //todo 一个函数更新四个状态。
protected:

signals:
private:
    int horizontalSpeed = 5;
    int horizontalMoveStatus = STOP;// move during A/D is pressed
    int verticalSpeed = 0;// free fall, need to be set
    int verticalMoveStatus = STOP;
};

#endif // UNIT_H
