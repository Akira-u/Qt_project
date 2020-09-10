#ifndef JUMPER_H
#define JUMPER_H
#include "unit.h"

class Jumper : public Unit
{
    Q_OBJECT
public:
    explicit Jumper(QObject *parent = nullptr, QPixmap pix = QPixmap(":/pics/jumper.png"));
    void move() override;
    QString gameType() override{
        return "jumper";
    }
};

#endif // JUMPER_H
