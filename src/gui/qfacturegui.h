#ifndef QFACTUREGUI_H
#define QFACTUREGUI_H

#include <QMainWindow>
#include "qfacturecore.h"

namespace Ui {
    class QfactureGui;
}

class QfactureGui : public QMainWindow
{
    Q_OBJECT

public:
    explicit QfactureGui(QfactureCore *core, QWidget *parent = 0);
    ~QfactureGui();
    
private slots:
    /**
     * Déclenche la (dé)connexion à la DB en fonction des informations
     * contenues dans les champs.
     */
    void handleDBConnection();
    
    /**
     * Sera appelée lorsque l'état de la connexion à la DB (connecté / déconnecté)
     * changera.
     */
    void onDBConnectionStateChanged();
    
    /**
     * Sera appelée lorsque la connexion avec la base de données sera établie
     */
    void onDBConnected();
    
    /**
     * Sera appelée si une erreur survient lors de la connexion avec la base de
     * données
     */
    void onDBConnectionError(const QString &error);
    
    /**
     * Réalise la fermeture de l'application : coupe la connexion à la DB,
     * enregistre les paramètres de l'utilisateur, etc.
     */
    void onQuit();

private:
    /**
     * Cette méthode, appelée par le constructeur, s'occupe de connecter les
     * principaux évènements.
     */
    void setupActions();
    
    /**
     * Sauvegarde les paramètres de l'application (dimensions et emplacement de
     * la fenêtre, identifiants de connexion à la DB, etc.)
     */
    void saveSettings();
    
    /**
     * Restaure les paramètres de l'application
     */
    void restoreSettings();
    
    
    /**
     * Pointeur vers la GUI "pure"
     */
    Ui::QfactureGui *ui;
    
    /**
     * Pointeur vers le coeur logique de l'application.
     */
    QfactureCore *core;
};

#endif // QFACTUREGUI_H
