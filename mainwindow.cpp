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
    mario=new Hero();
    unitsList.push_front(mario);
    backgroundScene->addItem(mario);
    mario->setPos(STARTPOINT_X,STARTPOINT_Y);// init start location
    }
    //test

    mario->grabKeyboard();// ensure keyboard event not be thrown
    mario->grabMouse();
    ui->backgroundView->setScene(backgroundScene);
    globalTimer = new QTimer(this);
    globalTimer->setInterval(TIMER_INTERVAL);//可以调整间隔改变平滑度
    connect(globalTimer, SIGNAL(timeout()), this, SLOT(allUpdate()));
    connect(ui->startButton,&QPushButton::clicked,[=](){playOrEdit = PLAYMODE;
        this->switchGameStatus(MAPSELECT);});
    connect(ui->enterEditModeButton, &QPushButton::clicked, [=](){playOrEdit = EDITMODE;
        this->switchGameStatus(MAPSELECT);});
    connect(ui->map1Button_2, &QPushButton::clicked, [=](){
        if(!ui->backgroundView->isVisible()){ //hiden in mapselect scene
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
            this->write("map1.json");
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
    connect(this, SIGNAL(heroDead()), this, SLOT(gameOver()));
}

MainWindow::~MainWindow(){
    delete ui;
    delete globalTimer;
    for(auto i:unitsList){

        if(i!=nullptr) delete i;
    }

    for(auto i:blocksList){
        if(i!=nullptr) delete i;
    }
}

void MainWindow::gameOver(){
    endTime = QTime::currentTime();
    globalTimer->stop();
    QString playTime = QString::number(beginTime.secsTo(endTime));
    QMessageBox msgBox;
    msgBox.setText("Time:"+playTime);
    msgBox.exec();
    switchGameStatus(STARTMODE);
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
        ui->comboBox->setCurrentText("Null");
        ui->comboBox->hide();
        ui->elementsLabel->hide();
        ui->mapProgressBar->hide();
        ui->saveButton->hide();

    }
    if(gameStatus==MAPSELECT){//select maps, meanwhile, play or edit is recorded


            ui->startButton->hide();
            ui->enterEditModeButton->hide();
            ui->map1Button_2->show();
            ui->map2Button_2->show();

            ui->backgroundView->hide();
            ui->backToMenuButton->show();// implemented in construct function

            ui->comboBox->setCurrentText("Null");
            ui->comboBox->hide();
            ui->elementsLabel->hide();
            ui->mapProgressBar->hide();//todo:loading
            ui->saveButton->hide();
        //}
//        else if(playOrEdit==EDITMODE){

//            ui->startButton->hide();
//            ui->enterEditModeButton->hide();
//            ui->map1Button_2->show();
//            ui->map2Button_2->show();

//            ui->backgroundView->hide();
//            ui->backToMenuButton->show();

//            ui->comboBox->setCurrentText("Null");
//            ui->comboBox->hide();
//            ui->elementsLabel->hide();
//            ui->mapProgressBar->hide();
//            ui->saveButton->hide();

//        }
    }
    if(gameStatus==PLAYMODE){
        playOrEdit = PLAYMODE;
        ui->startButton->hide();
        ui->enterEditModeButton->hide();
        ui->map1Button_2->hide();
        ui->map2Button_2->hide();
        ui->backgroundView->show();
        ui->backToMenuButton->show();//todo:确认会不会造成异常（由于结束game）

        ui->comboBox->setCurrentText("Null");
        ui->comboBox->hide();
        ui->elementsLabel->hide();
        ui->mapProgressBar->hide();
        ui->saveButton->hide();
        ui->backToMenuButton->show();

        globalTimer->start();
        beginTime = QTime::currentTime();


    }
    if(gameStatus==EDITMODE){
        playOrEdit = EDITMODE;
        ui->startButton->hide();
        ui->enterEditModeButton->hide();
        ui->map1Button_2->hide();
        ui->map2Button_2->hide();
        ui->backgroundView->show();
        ui->backToMenuButton->show();

        ui->comboBox->setCurrentText("Null");
        ui->comboBox->show();
        ui->elementsLabel->show();
        ui->mapProgressBar->hide();
        ui->saveButton->show();
        ui->backToMenuButton->show();
        globalTimer->stop();
    }


}
void MainWindow::checkObjsMove(){
    for(auto u:unitsList){
        u->move();
    }
    //to do: add check of monsters attack
}
void MainWindow::checkObjsCollide(){
    for(auto u:unitsList){
        if(u!=nullptr){
            if(u->gameType()!="spitter"){
                u->monsterAttackHero(mario);
            }
            else{
                Spitter *s=static_cast<Spitter *>(u);
                s->farAttackHero(mario, backgroundScene, unitsList);
            }
            u->checkCollideDirection();
        }
    }
}

void MainWindow::allUpdate(){// check all things needed to be check periodically

    checkObjsMove();
    checkObjsCollide();
    if(!mario->isVisible()){
        emit heroDead();
    }
    if(!blocksList.isEmpty()){// terrain damage
        for(auto b:blocksList){
            b->collideHero(mario);// check terrain damage

            if(!mario->isVisible()){//check if hero alive after every possible damage
                emit heroDead();
            }

            if(!b->isVisible()){
                blocksList.removeOne(b);
                if(b) delete b;
            }
        }
    }
    if(!unitsList.isEmpty()){// clear dead units
        for(auto u:unitsList){
            if(!u->isVisible()){
                if(u) delete u;
                unitsList.removeOne(u);
            }
        }
    }


    update();

}
void MainWindow::read(const QString &fileName)
{
    for(auto u:unitsList){

        if(u!=nullptr/*&&u->gameType()!="hero"*/) delete u;
    }

    for(auto b:blocksList){
        if(b!=nullptr) delete b;
    }
    unitsList.clear();
    blocksList.clear();

//    ui->mapProgressBar->show();
//    for(int i=0;i<=100;i++){
//        QThread::msleep(10);
//        ui->mapProgressBar->setValue(i);
//    }

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
        if(type=="block"){//todo:把每个类都写出来
            auto b = new Block(x, y);
            blocksList.push_back(b);
            backgroundScene->addItem(b);
        }
//        else if(type=="Breakable brick"){
//            auto b = new BreakableBlock(x, y);
//            blocksList.push_back(b);
//            backgroundScene->addItem(b);
//        }
//        else if(type=="Move brick"){
//            auto b = new MoveBlock(x, y);
//            blocksList.push_back(b);
//            backgroundScene->addItem(b);
//        }
        else if(type=="spring"){
            auto b = new Spring(x, y);
            blocksList.push_back(b);
            backgroundScene->addItem(b);
        }
        else if(type=="passive trap"){
            auto b = new Trap(x, y, PASSIVE);
            blocksList.push_back(b);
            backgroundScene->addItem(b);
        }
        else if(type=="active trap"){
            auto b = new Trap(x, y, NOT_TRIGGERED);
            blocksList.push_back(b);
            backgroundScene->addItem(b);
        }
        else if(type=="heart"){
            auto b = new Heart(x, y);
            blocksList.push_back(b);
            backgroundScene->addItem(b);
        }
        //todo mush
        else if(type=="licker"){
            auto u = new Licker;
            u->setPos(x,y);
            unitsList.push_back(u);
            backgroundScene->addItem(u);
        }
        else if(type=="jumper"){
            auto u = new Jumper;
            u->setPos(x,y);
            unitsList.push_back(u);
            backgroundScene->addItem(u);
        }
        else if(type=="spitter"){
            auto u = new Spitter;
            u->setPos(x,y);
            unitsList.push_back(u);
            backgroundScene->addItem(u);
        }

        else if (type=="hero"){
            if(!unitsList.isEmpty()&&unitsList.first()->gameType()=="hero"){
                qDebug("read multiple hero!");
                continue;//only one hero
            }
            auto h = new Hero();
            h->setPos(x,y);
            mario = h;
            unitsList.push_front(h);
            backgroundScene->addItem(h);
            h->grabKeyboard();
            h->grabMouse();
        }

    }
}
void MainWindow::write(const QString &fileName)
{
    QFile mapfile(fileName);
    QJsonArray jsonArray;
    for(auto u:unitsList){
        if(u->gameType()=="bullet"||!u->isVisible()){
            continue;// bullets won't be saved
        }
        QJsonObject obj;
        obj.insert("type",u->gameType());
        obj.insert("x",u->x());
        obj.insert("y",u->y());
        jsonArray.append(obj);
    }
    for(auto b:blocksList){
        if(!b->isVisible()){
            continue;
        }
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
    mapfile.write(ba);//todo clear?
    mapfile.close();
    QMessageBox msgBox;
    msgBox.setText("The Map has been save successfully!");
    msgBox.exec();
}
void MainWindow::mousePressEvent(QMouseEvent *event){

    if(event->button()==Qt::LeftButton&&playOrEdit==EDITMODE&&ui->backgroundView->isVisible()&&event->x()<=ui->backgroundView->width()&&event->y()<=ui->backgroundView->height()){
        if(ui->backgroundView->itemAt(event->x(), event->y())) return;
        if(ui->comboBox->currentText()=="Null") {
            return;
        }
        else if(ui->comboBox->currentText()=="Ground"){
            Block *b=new Block(event->x()/BLOCK_LENGTH*BLOCK_LENGTH, event->y()/BLOCK_LENGTH*BLOCK_LENGTH);
            blocksList.push_back(b);
            backgroundScene->addItem(b);
        }
//        else if(ui->comboBox->currentText()=="Breakable brick"){
//            brickableBrick *b=new brickableBrick(event->x()/BLOCK_LENGTH*BLOCK_LENGTH, event->y()/BLOCK_LENGTH*BLOCK_LENGTH);
//            blocksList.push_back(b);
//            backgroundScene->addItem(b);
//        }
//        else if(ui->comboBox->currentText()=="Move brick"){
//            MoveBrick *b=new MoveBrick(event->x()/BLOCK_LENGTH*BLOCK_LENGTH, event->y()/BLOCK_LENGTH*BLOCK_LENGTH);
//            blocksList.push_back(b);
//            backgroundScene->addItem(b);
//        }
        else if(ui->comboBox->currentText()=="Spring"){
            Spring *b=new Spring(event->x()/BLOCK_LENGTH*BLOCK_LENGTH, event->y()/BLOCK_LENGTH*BLOCK_LENGTH);
            blocksList.push_back(b);
            backgroundScene->addItem(b);
        }
        else if(ui->comboBox->currentText()=="Passive trap"){
            Trap *b=new Trap(event->x()/BLOCK_LENGTH*BLOCK_LENGTH, event->y()/BLOCK_LENGTH*BLOCK_LENGTH);
            blocksList.push_back(b);
            backgroundScene->addItem(b);
        }
        else if(ui->comboBox->currentText()=="Active trap"){
            Trap *b=new Trap(event->x()/BLOCK_LENGTH*BLOCK_LENGTH, event->y()/BLOCK_LENGTH*BLOCK_LENGTH, NOT_TRIGGERED);
            blocksList.push_back(b);
            backgroundScene->addItem(b);
        }
        else if(ui->comboBox->currentText()=="Heart"){
            Heart *b=new Heart(event->x()/BLOCK_LENGTH*BLOCK_LENGTH, event->y()/BLOCK_LENGTH*BLOCK_LENGTH);
            blocksList.push_back(b);
            backgroundScene->addItem(b);
        }
        else if(ui->comboBox->currentText()=="Licker"){
            Licker *u=new Licker;
            u->setPos(event->x()/BLOCK_LENGTH*BLOCK_LENGTH, event->y()/BLOCK_LENGTH*BLOCK_LENGTH);
            unitsList.push_back(u);
            backgroundScene->addItem(u);
        }
        else if(ui->comboBox->currentText()=="Jumper"){
            Jumper *u=new Jumper;
            u->setPos(event->x()/BLOCK_LENGTH*BLOCK_LENGTH, event->y()/BLOCK_LENGTH*BLOCK_LENGTH);
            unitsList.push_back(u);
            backgroundScene->addItem(u);
        }
        else if(ui->comboBox->currentText()=="Spitter"){
            Spitter *u=new Spitter;
            u->setPos(event->x()/BLOCK_LENGTH*BLOCK_LENGTH, event->y()/BLOCK_LENGTH*BLOCK_LENGTH);
            unitsList.push_back(u);
            backgroundScene->addItem(u);
        }
        else if (ui->comboBox->currentText()=="Hero"){

            auto h = new Hero();
            h->setPos(event->x()/BLOCK_LENGTH*BLOCK_LENGTH, event->y()/BLOCK_LENGTH*BLOCK_LENGTH);
            mario = h;
            if(!unitsList.isEmpty()&&unitsList.first()->gameType()=="hero"){
                *unitsList.begin() = h;
            }
            else
                unitsList.push_front(h);
            backgroundScene->addItem(h);
//            h->grabKeyboard();
//            h->grabMouse();
        }
        //todo flower and mush
        repaint();
        QTimer::singleShot(50, [](){});
    }
    // rightButton delete items
    else if(event->button()==Qt::RightButton&&playOrEdit==EDITMODE&&ui->backgroundView->isVisible()&&event->x()<=ui->backgroundView->width()&&event->y()<=ui->backgroundView->height()){
        auto item = ui->backgroundView->itemAt(event->x(), event->y());
        if(item){
            item->hide();
            repaint();
        }
    }
}




