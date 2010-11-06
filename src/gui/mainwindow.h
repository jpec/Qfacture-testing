#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "qfacturecore.h"


/**
 * Fenêtre principale de l'application
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QfactureCore *core, QWidget *parent = 0);

private:
    /**
     * Cette méthode, appelée par le constructeur, s'occupe de connecter les
     * principaux évènements.
     */
    void setupActions();


    /**
     * Pointeur vers le contrôleur associé à la fenêtre principale
     */
    QfactureCore *core;
};

#endif // MAINWINDOW_H
