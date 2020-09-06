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
    int getHorizontalSpeed() const;
    void setHorizontalMove(int dir);
    int isHorizontalMove();
    bool isOnGround();// return true when unit is on the ground which means it can jump
    void jump();
    QRectF boundingRect() const override;
    QList<QGraphicsItem*> collideItemsList;
    int getVerticalSpeed() const;
    void setVerticalSpeed(int value);

protected:

signals:
private:
    int horizontalSpeed = 5;
    int horizontalMoveStatus = STOP;// move during A/D is pressed
    int verticalSpeed = 0;
};

#endif // UNIT_H
