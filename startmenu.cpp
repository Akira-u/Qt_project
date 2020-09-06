#include "startmenu.h"
#include "ui_startmenu.h"

StartMenu::StartMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartMenu)
{
    ui->setupUi(this);
    QPixmap backgroundImg = QPixmap(":/pics/background.png").scaled(1000,600);
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(backgroundImg));
    this->setPalette(palette);
    ui->map1Button->hide();
    ui->map2Button->hide();
    ui->map3Button->hide();
    ui->backToMenuButton->hide();
    connect(ui->startButton,SIGNAL(clicked()),this,SLOT(toStartMapSelectWindow()));
    connect(ui->enterEditModeButton,SIGNAL(clicked()),this,SLOT(toEditMapSelectWindow()));
}

StartMenu::~StartMenu()
{
    delete ui;
}

void StartMenu::toStartMapSelectWindow(){
    ui->startButton->hide();
    ui->enterEditModeButton->hide();
    ui->map1Button->show();
    ui->map2Button->show();
    ui->map3Button->show();
    ui->backToMenuButton->show();
    mw.currentGameStatus = PLAYMODE;
}

void StartMenu::toEditMapSelectWindow(){
    ui->startButton->hide();
    ui->enterEditModeButton->hide();
    ui->map1Button->show();
    ui->map2Button->show();
    ui->map3Button->show();
    ui->backToMenuButton->show();
    mw.currentGameStatus = EDITMODE;
}
