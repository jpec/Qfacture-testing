#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QString>
#include <QVariant>
#include <QSettings>


/**
 * Classe s'occupant de la gestion des paramètres.
 * Wrappe juste QSettings
 */
class SettingsManager
{
public:
    ~SettingsManager();

    /**
     * Retourne l'instance du gestionnaire
     *
     * @return SettingsManager& Une unique instance du gestionnaire
     */
    static SettingsManager& getInstance();

    /**
     * Enregistre un paramètre de l'application.
     *
     * @param group Groupe d'appartenance du paramètre. Ex : DB pour tous les
     *              paramètres liés à la base de données.
     * @param key Nom du paramètre
     * @param value Valeur du paramètre
     */
    void set(const QString &group, const QString &key, const QVariant &value);

    /**
     * Récupère la valeur d'un paramètre de l'application.
     *
     * @param group Groupe d'appartenance du paramètre. Ex : DB pour tous les
     *              paramètres liés à la base de données.
     * @param key Nom du paramètre
     * @param default_value Valeur retournée si le paramètre demandé n'existe pas.
     */
    QVariant get(const QString &group, const QString &key, const QVariant &default_value=QVariant()) const;

private:
    SettingsManager();


    /**
     * Instance de la classe chargée de la gestion des paramètres.
     */
    QSettings *settings;
};

#endif // SETTINGSMANAGER_H
