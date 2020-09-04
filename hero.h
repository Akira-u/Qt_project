#ifndef HERO_H
#define HERO_H

#include <QObject>
#include <QGraphicsItem>

const int STOP = 0;
const int LEFT = -1;
const int RIGHT = 1;
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
    int speed = 30;
    int horizontal_move_status = STOP;// move during A/D is pressed
};

#endif // HERO_H
