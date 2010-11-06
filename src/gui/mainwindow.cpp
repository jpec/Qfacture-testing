#include "mainwindow.h"

MainWindow::MainWindow(QfactureCore *core, QWidget *parent) : QMainWindow(parent)
{
    this->core = core;

    this->setupActions();
}

void MainWindow::setupActions()
{

}
