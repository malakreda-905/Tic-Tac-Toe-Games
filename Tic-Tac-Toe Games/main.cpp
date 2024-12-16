#include<game1.h>
#include<game2.h>
#include <mainwindow.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainWindow w;
    w.show();
    return a.exec();
}
