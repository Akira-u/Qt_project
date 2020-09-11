#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "constants.h"
#include "unit.h"
#include "hero.h"
#include "trap.h"
#include "licker.h"
#include "jumper.h"
#include "spitter.h"
#include <QTimer>
#include <QWidget>
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>
#include <QDir>
#include <QThread>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void checkObjsMove();
    void checkObjsCollide();
    int playOrEdit = PLAYMODE;
    void switchGameStatus(int gameStatus);

    void read(const QString& fileName);
    void write(const QString& fileName);
protected:
    void mousePressEvent(QMouseEvent *event);

public slots:
    void allUpdate();
    void gameOver();
signals:
    void heroDead();

private:
    Ui::MainWindow *ui;
    QTimer *globalTimer;
    QGraphicsScene *backgroundScene;
    QList<Unit*> unitsList;
    Hero *mario = nullptr;// the pointer of unique hero
    QList<Block *>blocksList;

    QTime beginTime;
    QTime endTime;
};
#endif // MAINWINDOW_H
