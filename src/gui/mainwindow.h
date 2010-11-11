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

    /**
     * Sera appelée si une erreur survient lors de la connexion avec la base de
     * données
     */
    void onDBConnectionError(const QString &error);

    /**
     * Sera appelée si une erreur SQL survient.
     */
    void onDBError(const QString &error);

    /**
     * Sera appelée lors de la connexion à la DB
     */
    void onDBConnected();

    /**
     * Sera appelée lors de la déconnexion à la DB
     */
    void onDBDisconnected();

private:
    /**
     * Cette méthode, appelée par le constructeur, s'occupe de connecter les
     * principaux évènements.
     */
    void createActions();

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
     * Affiche une boite de dialogue de type "critical". Utilisée pour informer
     * l'utilisateur d'une erreur
     *
     * @param message Message d'erreur à afficher
     */
    void alert(const QString &message);


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
