#ifndef BLOCK_H
#define BLOCK_H

#include <QObject>
#include <QGraphicsItem>
#include <QPoint>

class Block : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Block(int x, int y, QPixmap img=QPixmap(":/pics/brick.png"), QObject *parent = nullptr);

signals:

private:
    QPoint location;
};

#endif // BLOCK_H
