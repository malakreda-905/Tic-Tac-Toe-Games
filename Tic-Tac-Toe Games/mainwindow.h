#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <game1.h>
#include <game2.h>
#include <QDialog>

namespace Ui {
class mainWindow;
}

class mainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit mainWindow(QWidget *parent = nullptr);
    ~mainWindow();

private slots:
    void on_ultimateGame_clicked();

    void on_susGame_clicked();
    void closeEvent(QCloseEvent *event);
private:
    Ui::mainWindow *ui;
    MainWindow *gameOne = nullptr;
    game2 * gameTwo = nullptr;
};

#endif // MAINWINDOW_H
