#include <QtGui/QApplication>
#include "gui/qfacturegui.h"
#include "qfacturecore.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QfactureCore core;
    QfactureGui w(&core);
    
    a.connect(&a, SIGNAL(lastWindowClosed()), &w, SLOT(onQuit()));
    
    w.show();

    return a.exec();
}
