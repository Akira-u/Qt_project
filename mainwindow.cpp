#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    switchGameStatus(STARTMODE);

    backgroundScene = new QGraphicsScene(this);//background scene
    backgroundScene->setSceneRect(0, 0, 1861, 1061);
    QPixmap backgroundImg(":/pics/background.png");
    backgroundImg.scaled(1861,1061);
    backgroundScene->setBackgroundBrush(QBrush(backgroundImg));


    //test
    if(mario==nullptr){
    mario=new Hero(this);
    unitsList.push_front(mario);
    backgroundScene->addItem(mario);
    mario->setPos(100,200);// init start location
    }
    //test

    mario->grabKeyboard();// ensure keyboard event not be thrown
    ui->backgroundView->setScene(backgroundScene);

    QTimer *globalTimer = new QTimer(this);
    globalTimer->setInterval(TIMER_INTERVAL);//可以调整间隔改变平滑度
    globalTimer->start();

    connect(globalTimer, SIGNAL(timeout()), this, SLOT(allUpdate()));
    connect(ui->startButton,&QPushButton::clicked,[=](){playOrEdit = PLAYMODE;
        this->switchGameStatus(MAPSELECT);});
    connect(ui->enterEditModeButton, &QPushButton::clicked, [=](){playOrEdit = EDITMODE;
        this->switchGameStatus(MAPSELECT);});
    connect(ui->map1Button_2, &QPushButton::clicked, [=](){
        if(!ui->backgroundView->isVisible()){ //hiden in edit scene
            if(playOrEdit==EDITMODE){
            this->read("map1.json");
            this->switchGameStatus(EDITMODE);
            }
            else{
                this->read("map1.json");
                this->switchGameStatus(PLAYMODE);
            }
        }
        else{
            this->write("map2.json");
            ui->map1Button_2->hide();
            ui->map2Button_2->hide();
        }});
    connect(ui->map2Button_2, &QPushButton::clicked, [=](){
        if(!ui->backgroundView->isVisible()){
            if(playOrEdit==EDITMODE){
            this->read("map2.json");
            this->switchGameStatus(EDITMODE);
            }
            else{
                this->read("map2.json");
                this->switchGameStatus(PLAYMODE);
            }
        }
        else{
            this->write("map2.json");
            ui->map1Button_2->hide();
            ui->map2Button_2->hide();

        }});
    connect(ui->saveButton, &QPushButton::clicked, [=](){
        if(ui->backgroundView->isVisible()){
            ui->map1Button_2->show();
            ui->map2Button_2->show();
        }});
    connect(ui->backToMenuButton, &QPushButton::clicked, [=](){this->switchGameStatus(STARTMODE);});
    //connect(this, SIGNAL(heroDead()), this, SLOT(gameOver())); todo: implement gameover
}

MainWindow::~MainWindow(){
    delete ui;
    for(auto i:unitsList){
        delete i;
    }
    //delete mario; delete in beattacked()
    for(auto i:blocksList){
        delete i;
    }
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
        ui->backToMenuButton->show();

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
        ui->saveButton->show();
        ui->backToMenuButton->show();



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
    if(!blocksList.isEmpty()){
        for(auto i:blocksList){
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
void MainWindow::read(const QString &fileName)
{
    qDebug()<< QDir::currentPath() <<Qt::endl;
    QFile mapfile(fileName);
    if(!mapfile.exists()){
        qDebug()<<"file not exist"<<Qt::endl;
    }
    if(!mapfile.open(QIODevice::ReadOnly)){
        qDebug()<<"some error when read the file"<<Qt::endl;
        return;
    }
    QByteArray allData=mapfile.readAll();
    QJsonParseError jsonError;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(allData,&jsonError));

    if(jsonError.error!=QJsonParseError::NoError){
        qDebug()<<"json parse error"<<Qt::endl;
        return ;
    }
    QVariantList dataList=jsonDoc.toVariant().toList();
    for(QVariant &data:dataList){
        QVariantMap dataMap=data.toMap();
        QString type=dataMap.value("type").toString();
        int x=dataMap.value("x").toInt();
        int y=dataMap.value("y").toInt();
        if(type.isNull()){
            qDebug()<<"Invalid data format";
        }
        if(type==""){//todo:把每个类都写出来

        }
        else if(type==""){

        }
        else if (type=="hero"){
            auto h = new Hero(this);
            h->setPos(x,y);
            unitsList.push_front(h);
            backgroundScene->addItem(h);
        }

    }
}
void MainWindow::write(const QString &fileName)
{
    QFile mapfile(fileName);
    QJsonArray jsonArray;
    for(auto u:unitsList){
        QJsonObject obj;
        obj.insert("type",u->gameType());
        obj.insert("x",u->x());
        obj.insert("y",u->y());
        jsonArray.append(obj);
    }
    for(auto b:blocksList){
        QJsonObject obj;
        obj.insert("type",b->gameType());
        obj.insert("x",b->x());
        obj.insert("y",b->y());
        jsonArray.append(obj);
    }
    QJsonDocument doc(jsonArray);
    QByteArray ba=doc.toJson(QJsonDocument::Indented);
    if(!mapfile.open(QIODevice::WriteOnly)){
        qDebug()<<"file write error"<<Qt::endl;
    }
    mapfile.write(ba);
    mapfile.close();
    QMessageBox msgBox;
    msgBox.setText("The Map has been save successfully!");
    msgBox.exec();
}
