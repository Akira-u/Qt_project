#ifndef HERO_H
#define HERO_H

#include "constants.h"
#include <QObject>
#include <QGraphicsItem>


class Hero : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Hero(QPixmap pix, QObject *parent = nullptr);
    int getSpeed();
    void setHorizontalMove(int dir);
    int isHorizontalMove();
signals:
private:
    int speed = 5;
    int horizontal_move_status = STOP;// move during A/D is pressed
};

#endif // HERO_H
