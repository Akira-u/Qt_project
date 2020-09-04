#ifndef TRAP_H
#define TRAP_H

#include <QObject>
#include <QGraphicsItem>

class Trap : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Trap(QObject *parent = nullptr);

signals:

};

#endif // TRAP_H
