#ifndef LICKER_H
#define LICKER_H
#include "unit.h"

class Licker : public Unit
{
    Q_OBJECT
public:
    explicit Licker(QObject *parent = nullptr, QPixmap pix = QPixmap(":/pics/licker.png"));

    QString gameType() override{
        return "licker";
    }
};

#endif // LICKER_H
