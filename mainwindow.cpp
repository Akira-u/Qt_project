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

    scene->addItem(mario);
    mario->setPos(100,200);// init start location 无限地图下改位置也看不出来
    //test
//    QGraphicsEllipseItem *mariocenter =new QGraphicsEllipseItem(mario->x(),mario->y(),1,1);
//    scene->addItem(mariocenter);
    Trap *t=new Trap(100, 300, PASSIVE, this);
    scene->addItem(t);
    blocks.push_back(t);
    //test

    mario->grabKeyboard();// ensure keyboard event not be thrown
    ui->backgroundView->setScene(scene);

    QTimer *globalTimer = new QTimer(this);
    globalTimer->setInterval(TIMER_INTERVAL);//可以调整间隔改变平滑度
    globalTimer->start();

    connect(globalTimer, SIGNAL(timeout()), this, SLOT(allUpdate()));
    //connect(this, SIGNAL(heroDead()), this, SLOT(gameOver()));
}

MainWindow::~MainWindow(){
    delete ui;
    //delete mario; delete in beattacked()
    for(auto i:blocks){
        delete i;
    }
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
    //to do: add check of monsters becareful of nptr
    //todo：不能跳出去
}
void MainWindow::checkObjsCollide(){
    for(auto i:unitsList){
        if(i!=nullptr){
            i->checkCollideDirection();
        }
    }
}

void MainWindow::allUpdate(){// check all things needed to be check periodically
    checkObjsCollide();
    checkObjsMove();
    if(!mario->isVisible()){
        emit heroDead();
    }
    if(!blocks.isEmpty()){
        for(auto i:blocks){
            i->collideHero(mario);
        }
    }
    if(!unitsList.isEmpty()){
        for(int i=0;i<unitsList.size();i++){
            if(!unitsList[i]->isVisible()){
                unitsList.removeAt(i);
            }
        }
    }
// todo:check unitlist and clear dead

    update();

}
