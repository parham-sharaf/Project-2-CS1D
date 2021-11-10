#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include "display_team.h"
#include "trip.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Display_Teams_Button_clicked()
{
    display_team team;
    team.setModal(true);
    team.exec();
}

void MainWindow::on_Trip_Button_clicked()
{
    trip trp;
    trp.setModal(true);
    trp.exec();
}

void MainWindow::on_Login_Button_clicked()
{
    login log;
    log.setModal(true);
    log.exec();
}

void MainWindow::on_Trip_Button_2_clicked()
{
    teamsArena t;
    t.setModal(true);
    t.exec();
}
