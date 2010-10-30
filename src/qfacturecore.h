#ifndef QFACTURECORE_H
#define QFACTURECORE_H

#include <QSqlDatabase>
#include <QSettings>
#include <QObject>

#include <string>

#include "models/profile.h"

using namespace std;


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
     * Tente de connecter l'application à la base de données. Émet le signal
     * DBConnected() si elle y parvient, DBConnectionError() sinon.
     *
     * \note Ne fait rien si on est déjà connecté à la DB
     *
     * @param server Adresse IP ou nom d'hôte du serveur
     * @param port Port du serveur
     * @param login Nom d'utilisateur de la base de données
     * @param pass Mot de passe associé au nom d'utilisateur
     * @param db_name Nom de la base à laquelle on veut se connecter
     * @param db_type Type de base de données.
     *
     * @see http://doc.qt.nokia.com/4.6/qsqldatabase.html#addDatabase-2
     */
    void connectDB(const QString &server, int port, const QString &login, 
                   const QString &pass, const QString &db_name, const QString &db_type="QMYSQL");
    
    /**
     * Déconnecte l'application de la base de données et émet le signal 
     * DBDisconnected()
     */
    void disconnectDB();
    
    /**
     * Indique si l'application est connectée à la base de données ou non
     *
     * @return true si la connexion est établie, false sinon.
     */
    bool isDBConnected() const;
    
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
     * Récupère le profile d'un utilisateur
     *
     * @param id L'identifiant du profile à utiliser
     *
     * @return Profile Le profile chargé.
     */
    Profile getProfile(int id);
    
signals:
    /**
     * Émit lorsque une connexion a été établie avec la base de données
     */
    void DBConnected();
    
    /**
     * Émit lorsque la connexion avec la base de données a été rompue
     */
    void DBDisconnected();
    
    /**
     * Émit lorsque la connexion avec la base de donnée a échoué
     */
    void DBConnectionError(const QString &error);
    
    /**
     * Émit lorsque une erreur lors d'une requête à la DB survient
     */
    void DBError(const QString &error);

private:
    /**
     * Instance de la connexion à la base de données.
     */
    QSqlDatabase db;
    
    /**
     * Instance de la classe chargée de la gestion des paramètres.
     */
    QSettings *settings;
};

#endif // QFACTURECORE_H
