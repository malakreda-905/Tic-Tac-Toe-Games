#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCloseEvent>
#include <qmessagebox.h>
#include <QGraphicsOpacityEffect>
mainWindow::mainWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::mainWindow)
{
    ui->setupUi(this);
    ui->susGame->clearMask()  ;
}
mainWindow::~mainWindow()
{
    delete ui;
    if (this->gameOne)
     delete this->gameOne;
    if (this->gameTwo)
     delete this->gameTwo;
}




void mainWindow::closeEvent(QCloseEvent *event){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Exit", "Are you sure you want to exit?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        event->accept(); // Allow the window to close
        // resetAll();
    } else {
        event->ignore(); // Ignore the close event
    }
}

void mainWindow::on_ultimateGame_clicked()
{
    this->gameOne = new MainWindow();
    this->gameOne->show();
}


void mainWindow::on_susGame_clicked()
{
    this->gameTwo = new game2();
    this->gameTwo->show();
}

