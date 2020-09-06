#ifndef STARTMENU_H
#define STARTMENU_H
#include "mainwindow.h"
#include "constants.h"
#include <QMainWindow>

namespace Ui {
class StartMenu;
}

class StartMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartMenu(QWidget *parent = nullptr);
    ~StartMenu();
public slots:
    void toStartMapSelectWindow();
    void toEditMapSelectWindow();
private:
    Ui::StartMenu *ui;
    MainWindow mw;
};

#endif // STARTMENU_H
