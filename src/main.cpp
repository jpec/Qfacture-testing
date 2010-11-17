#include "qfacturecore.h"
#include "gui/mainwindow.h"

#include <QtGui/QApplication>

#include "controllers/dbcontroller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QfactureCore core;
    MainWindow w(&core);

    a.connect(&a, SIGNAL(lastWindowClosed()), &w, SLOT(onQuit()));

    w.show();

    return a.exec();
}
