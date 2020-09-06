#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "constants.h"
#include "unit.h"
#include "hero.h"
#include "block.h"
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
    int currentGameStatus = PLAYMODE;

public slots:
    void allUpdate();

private:
    Ui::MainWindow *ui;
    QList<Unit*> unitsList;
    Hero *mario;// the pointer of unique hero
    //to do: write class Monster inheriting Item and add list of monsters
    Block *block;
};
#endif // MAINWINDOW_H
