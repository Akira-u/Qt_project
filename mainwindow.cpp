#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);//background scene
    scene->setSceneRect(0, 0, 1000, 600);
    QPixmap backgroundImg(":/pics/background.png");
    backgroundImg.scaled(1000,600);
    scene->setBackgroundBrush(QBrush(backgroundImg));

    mario=new Hero(QPixmap(":/pics/mario_stop.png"),this);
    unitsList.push_back(mario);
    block=new Block(100,300,QPixmap(":/pics/brick.png"), this);
    scene->addItem(block);
    scene->addItem(mario);
    mario->setPos(100,250);// init start location 无限地图下改位置也看不出来

    mario->grabKeyboard();// ensure keyboard event not be thrown
    ui->backgroundView->setScene(scene);

    QTimer *globalTimer = new QTimer(this);
    globalTimer->setInterval(TIMER_INTERVAL);//可以调整间隔改变平滑度
    globalTimer->start();

    connect(globalTimer, SIGNAL(timeout()), this, SLOT(allUpdate()));
}

MainWindow::~MainWindow(){
    delete ui;
    delete mario;
    //delete all units
}


void MainWindow::checkObjsMove(){
    if(mario->getHorizontalMoveStatus() != STOP){
        mario->moveBy(mario->getHorizontalMoveStatus() * mario->getHorizontalSpeed(), 0);
    }
    // left out = right in
    if(mario->pos().x()<0){
        mario->setX(999);
    }
    else if(mario->pos().x()>1000){
        mario->setX(1);
    }
    if(!mario->isOnGround){//drop
        mario->setVerticalMoveStatus(DOWN);

        mario->setVerticalSpeed(mario->getVerticalSpeed() + G);//up is -, down is +
        mario->moveBy(0, mario->getVerticalSpeed());
    }
    //to do: add check of monsters
    //todo：不能跳出去
}
void MainWindow::checkObjsCollide(){
    for(auto i:unitsList){
        i->checkCollideDirection();
    }
}

void MainWindow::allUpdate(){// check all things needed to be check periodically
    checkObjsCollide();
    checkObjsMove();

    update();

}
