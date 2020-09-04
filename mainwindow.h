#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "constants.h"
#include "hero.h"
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
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

public slots:
    void checkObjsMove();

private:
    Ui::MainWindow *ui;
    //to do: set current status(editing/gaming/results...)
    Hero *mario;// the pointer of unique hero
    //to do: write class Monster inheriting Item and add list of monsters
};
#endif // MAINWINDOW_H
