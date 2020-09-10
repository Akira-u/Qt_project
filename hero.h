#ifndef HERO_H
#define HERO_H
#include "unit.h"
#include <QObject>


class Hero : public Unit
{
    Q_OBJECT
public:
    explicit Hero(QObject *parent = nullptr, QPixmap pix = QPixmap(":/pics/mario_stop.png"));
    QString gameType() override{
        return "hero";
    }
    void move() override;
    void monsterAttackHero(Unit *) override{}
    void attack();//todo:implement
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    //void mousePressEvent(QGraphicsSceneMouseEvent *event) override;


signals:

};

#endif // HERO_H
