#include <QtGui/QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    int result = app.exec();

    window.saveSettings();

    return result;
}
