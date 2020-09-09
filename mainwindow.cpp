#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAcceptDrops(true);// accept drag and drop
    switchGameStatus(STARTMODE);
    connect(ui->backToMenuButton, &QPushButton::clicked, [=](){this->switchGameStatus(STARTMODE);});
    QGraphicsScene *scene = new QGraphicsScene(this);//background scene
    scene->setSceneRect(0, 0, 1000, 600);
    QPixmap backgroundImg(":/pics/background.png");
    backgroundImg.scaled(1000,600);
    scene->setBackgroundBrush(QBrush(backgroundImg));

    mario=new Hero(QPixmap(":/pics/mario_stop.png"),this);
    unitsList.push_back(mario);
    scene->addItem(mario);
    mario->setPos(100,200);// init start location
    //test


    //test
    //todo: when gamemode editbuttons hide

    mario->grabKeyboard();// ensure keyboard event not be thrown
    ui->backgroundView->setScene(scene);

    QTimer *globalTimer = new QTimer(this);
    globalTimer->setInterval(TIMER_INTERVAL);//可以调整间隔改变平滑度
    globalTimer->start();

    connect(globalTimer, SIGNAL(timeout()), this, SLOT(allUpdate()));
    //connect(this, SIGNAL(heroDead()), this, SLOT(gameOver())); todo: implement gameover
}

MainWindow::~MainWindow(){
    delete ui;
    //delete mario; delete in beattacked()
    for(auto i:blocks){
        delete i;
    }
    //delete all units
}

void MainWindow::switchGameStatus(int gameStatus){

    if(gameStatus==STARTMODE){
        qDebug()<<"Start"<<Qt::endl;
        QPixmap backgroundImg = QPixmap(":/pics/background.png").scaled(1000,600);
        QPalette palette(this->palette());
        palette.setBrush(QPalette::Background, QBrush(backgroundImg));
        this->setPalette(palette);
        ui->startButton->show();
        ui->enterEditModeButton->show();
        ui->map1Button_2->hide();
        ui->map2Button_2->hide();
        ui->backgroundView->hide();
        ui->backToMenuButton->hide();
        ui->comboBox->hide();
        ui->elementsLabel->hide();
        ui->mapProgressBar->hide();
        ui->saveButton->hide();
        connect(ui->startButton,&QPushButton::clicked,[=](){playOrEdit = PLAYMODE;
            this->switchGameStatus(MAPSELECT);});
        connect(ui->enterEditModeButton, &QPushButton::clicked, [=](){playOrEdit = EDITMODE;
            this->switchGameStatus(MAPSELECT);});
    }
    if(gameStatus==MAPSELECT){//select maps, meanwhile, play or edit is recorded
        if(playOrEdit==PLAYMODE){
            ui->startButton->hide();
            ui->enterEditModeButton->hide();
            ui->map1Button_2->show();//todo:写读取
            ui->map2Button_2->show();

            ui->backgroundView->hide();
            ui->backToMenuButton->show();// implemented in construct function

            ui->comboBox->hide();
            ui->elementsLabel->hide();
            ui->mapProgressBar->hide();//todo:loading
            ui->saveButton->hide();
        }
        else if(playOrEdit==EDITMODE){
            ui->startButton->hide();
            ui->enterEditModeButton->hide();
            ui->map1Button_2->show();
            ui->map2Button_2->show();

            ui->backgroundView->hide();
            ui->backToMenuButton->show();
            ui->comboBox->hide();
            ui->elementsLabel->hide();
            ui->mapProgressBar->hide();
            ui->saveButton->hide();
        }
    }
    if(gameStatus==PLAYMODE){
        playOrEdit = PLAYMODE;
        ui->startButton->hide();
        ui->enterEditModeButton->hide();
        ui->map1Button_2->hide();
        ui->map2Button_2->hide();
        ui->backgroundView->show();
        ui->backToMenuButton->show();//todo:确认会不会造成异常（由于结束game）
        ui->comboBox->hide();
        ui->elementsLabel->hide();
        ui->mapProgressBar->hide();
        ui->saveButton->hide();
        QString jsonName="map.json";
//        Map* m=new Map(jsonName,Map::State::IDLE);
//        Util::RemoveLayout(centralWidget());

        connect(ui->backToMenuButton, SIGNAL(clicked()), this, SLOT(switchGameStatus(STARTMODE)));
        ui->backToMenuButton->show();
//        setCentralWidget(m);
    }
    if(gameStatus==EDITMODE){
        playOrEdit = PLAYMODE;
        ui->startButton->hide();
        ui->enterEditModeButton->hide();
        ui->map1Button_2->hide();
        ui->map2Button_2->hide();
        ui->backgroundView->show();
        ui->backToMenuButton->show();
        ui->comboBox->show();
        ui->elementsLabel->show();
        ui->mapProgressBar->hide();
        ui->saveButton->show();//todo connect
        QString jsonName="map.json";
//        Map* m=new Map(jsonName,Map::State::EDIT);
//        Util::RemoveLayout(centralWidget());

        ui->backToMenuButton->show();
//        setCentralWidget(m);



//        connect(dock,&Dock::save,m,&Map::save);
    }


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
