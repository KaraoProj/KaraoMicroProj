#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Jeu-Karaoke");
    MainWindow w;
    w.show();

    return a.exec();
}
