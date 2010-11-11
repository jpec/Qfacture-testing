#ifndef QFACTURECORE_H
#define QFACTURECORE_H

#include "controllers/controller.h"
#include "controllers/dbcontroller.h"

#include <QHash>
#include <QObject>
#include <QSettings>


/**
 * Fait office de contrôleur géant et sera utilisé par la GUI.
 */
class QfactureCore : public QObject
{
    Q_OBJECT

public:
    /**
     * Constructeur du core. Il s'occupe pour le moment d'initialiser les
     * différents managers tels que celui qui assure la gestion des paramètres.
     */
    QfactureCore();

    /**
     * Destructeur
     */
    ~QfactureCore();


    /**
     * Enregistre un paramètre de l'application.
     *
     * @param group Groupe d'appartenance du paramètre. Ex : DB pour tous les
     *              paramètres liés à la base de données.
     * @param key Nom du paramètre
     * @param value Valeur du paramètre
     */
    void setSetting(const QString &group, const QString &key, const QVariant &value);

    /**
     * Récupère la valeur d'un paramètre de l'application.
     *
     * @param group Groupe d'appartenance du paramètre. Ex : DB pour tous les
     *              paramètres liés à la base de données.
     * @param key Nom du paramètre
     * @param default_value Valeur retournée si le paramètre demandé n'existe pas.
     */
    QVariant getSetting(const QString &group, const QString &key, const QVariant &default_value = QVariant()) const;

    /**
     * Retourne un pointeur vers le contrôleur demandé
     *
     * @param name Nom du contrôleur voulu
     *
     * @return Controller* Pointeur vers le contrôleur
     */
    Controller* getController(const QString &name) const;

    /**
     * Retourne un pointeur vers le contrôleur de base de données
     *
     * @return DBController* Le pointeur vers le contrôleur
     */
    DBController* getDBController();

    /**
     * Retourne le numéro de version du logiciel.
     *
     * \todo Déplacer la définition du n° ailleurs (fichier dédié ?).
     */
    QString version() const { return "1.0 alpha"; }

private:
    /**
     * Initialise les "sous-contrôleurs"
     */
    void createControllers();

    /**
     * Instance de la classe chargée de la gestion des paramètres.
     */
    QSettings *settings;

    /**
     * Contiendra les différents "sous-contrôleurs"
     */
    QHash<QString, Controller*> controllers;
};

#endif // QFACTURECORE_H
