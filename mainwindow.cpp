#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);//background scene
    scene->setBackgroundBrush(QBrush(Qt::gray));//to do: add bkground
    mario=new Hero(QPixmap(":/png/mario_stop.png"),this);
    scene->addItem(mario);
    ui->backgroundView->setScene(scene);

    QTimer *globalTimer = new QTimer(this);
    globalTimer->setInterval(TIMER_INTERVAL);//可以调整间隔改变平滑度
    globalTimer->start();
    connect(globalTimer, SIGNAL(timeout()), this, SLOT(checkObjsMove()));
    connect(globalTimer, SIGNAL(timeout()), this, SLOT(update()));
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_D){// hero move right
        mario->setHorizontalMove(RIGHT);
    }
    else if(event->key() == Qt::Key_A){// hero move left
        mario->setHorizontalMove(LEFT);
    }
    else{
        QMainWindow::keyPressEvent(event);
    }
}
void MainWindow::keyReleaseEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_D||event->key() == Qt::Key_A){// stop move
        mario->setHorizontalMove(STOP);
    }
    else{
        QMainWindow::keyReleaseEvent(event);
    }
}
void MainWindow::checkObjsMove(){
    if(mario->isHorizontalMove() != STOP){
        mario->moveBy(mario->isHorizontalMove() * mario->getSpeed(), 0);
    }
    //to do: add check of monsters
}
