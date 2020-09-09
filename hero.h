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


protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

signals:

};

#endif // HERO_H
