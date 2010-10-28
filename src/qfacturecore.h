#ifndef QFACTURECORE_H
#define QFACTURECORE_H

#include <QSqlDatabase>
#include <QObject>
#include <string>

using namespace std;


/**
 * Fait office de contrôleur géant et sera utilisé par la GUI.
 */ 
class QfactureCore : public QObject
{
    Q_OBJECT
    
public:
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
    void deconnectDB();
    
    /**
     * Indique si l'application est connectée à la base de données ou non
     *
     * @return true si la connexion est établie, false sinon.
     */
    bool isDBConnected() const;
    
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
    void DBDError(const QString &error);

private:
    /**
     * Instance de la connexion à la base de données.
     */
    QSqlDatabase db;
};

#endif // QFACTURECORE_H
