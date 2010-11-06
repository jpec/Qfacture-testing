#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHash>

#include "qfacturecore.h"


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QfactureCore *core, QWidget *parent = 0);
    ~MainWindow();

private slots:
    /**
     * Réalise la fermeture de l'application : coupe la connexion à la DB,
     * enregistre les paramètres de l'utilisateur, etc.
     */
    void onQuit();
    
    /**
     * Affiche la boite de dialogue "À propos"
     */
    void about();
    
private:
    /**
     * Cette méthode, appelée par le constructeur, s'occupe de connecter les
     * principaux évènements.
     */
    void setupActions();
    
    /**
     * Crée les différents onglets qui composent l'appli.
     */
    void setupTabs();
    
    /**
     * Sauvegarde les paramètres de l'application (dimensions et emplacement de
     * la fenêtre)
     */
    void saveSettings();
    
    /**
     * Restaure les paramètres de l'application
     */
    void restoreSettings();
    
    
    /**
     * Pointeur vers la GUI "pure"
     */
    Ui::MainWindow *ui;
    
    /**
     * Pointeur vers le coeur logique de l'application.
     */
    QfactureCore *core;
};

#endif // MAINWINDOW_H
