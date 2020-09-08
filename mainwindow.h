#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "constants.h"
#include "unit.h"
#include "hero.h"
#include "trap.h"
#include <QTimer>
#include <QWidget>
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QKeyEvent>



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

public slots:
    void allUpdate();
    //void gameOver();//todo implement
signals:
    void heroDead();

private:
    Ui::MainWindow *ui;
    QList<Unit*> unitsList;
    Hero *mario;// the pointer of unique hero
    //to do: write class Monster inheriting Item and add list of monsters
    QList<Block *>blocks;
};
#endif // MAINWINDOW_H
