#ifndef HERO_H
#define HERO_H
#include "unit.h"
#include <QObject>

class Hero : public Unit
{
    Q_OBJECT
public:
    explicit Hero(QPixmap pix, QObject *parent = nullptr);



protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

signals:

};

#endif // HERO_H
