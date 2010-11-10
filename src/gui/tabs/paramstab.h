#ifndef PARAMSTAB_H
#define PARAMSTAB_H

#include <QWidget>

#include "qfacturecore.h"


namespace Ui {
    class ParamsTab;
}

class ParamsTab : public QWidget
{
    Q_OBJECT

public:
    explicit ParamsTab(QfactureCore *core, QWidget *parent = 0);
    ~ParamsTab();

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
     * Sera appelée si une erreur survient lors de la connexion avec la base de
     * données
     */
    void onDBConnectionError(const QString &error);
    
    /**
     * Sera appelée si une erreur SQL survient.
     */
    void onDBError(const QString &error);

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
    Ui::ParamsTab *ui;
    
    /**
     * Pointeur vers le coeur logique de l'application.
     */
    QfactureCore *core;
};

#endif // PARAMSTAB_H
