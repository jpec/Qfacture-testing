#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include <QHash>
#include <QObject>
#include <QSqlDatabase>


/**
 * Contrôleur pour la base de données
 */
class DBController : public QObject
{
    Q_OBJECT

    friend class QfactureCore;

    friend class CustomerManager;
    friend class ProductManager;
    friend class ProfileManager;

    friend class SQLTable;

private:
    /**
     * Exécute la requête passée en paramètre, et émet un signal
     * si elle échoue.
     *
     * @param query La requête à exécuter
     *
     * @return bool True si elle a été exécutée correctement, false sinon.
     */
    bool exec(QSqlQuery &query);

    /**
     * Retourne une instance unique du contrôleur
     *
     * @return DBController* L'instance du contrôleur
     */
    static DBController* getInstance();

    /**
     * Retourne la liste des drivers supportés.
     *
     * @return QStringList La liste des identifiants des drivers
     */
    QStringList getAvailableDrivers() const;

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
                   const QString &pass, const QString &db_name,
                   const QString &db_type="QMYSQL");

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
     * Retourne la liste des labels des colonnes d'une table donnée.
     *
     * @param table Nom de la table
     * @param except Liste des noms des colonnes dont on ne veut pas le label
     */
    QStringList getLabels(const QString& table, const QStringList& except) const;

    /**
     * Retourne le label correspondant à une colonne
     *
     * @param table Nom de la table
     * @param column Nom de la colonne dont on veut le label
     */
    QString getLabel(const QString &table, const QString &column) const;

    /**
     * Retourne la liste des colonnes d'une table donnée.
     *
     * @param table Nom de la table
     * @param except Colonnes à exclure
     */
    QStringList getColumns(const QString& table, const QStringList& except) const;

    /**
     * Retourne la condition de jointure permettant de lier les tables from et
     * with
     */
    QString getJoinClause(const QString &from, const QString &with) const;

    /**
     * Pour avoir un singleton
     */
    DBController();
    DBController(const DBController&);
    DBController& operator =(const DBController&);


    /**
     * Instance de la connexion à la base de données.
     */
    QSqlDatabase db;

    /**
     * Dictionnaire associant les noms des tables de la DB avec
     * un autre dictionnaire contenant les noms des colonnes associés à leurs
     * labels
     */
    QHash<QString, QHash<QString, QString> > tables_definitions;

    /**
     * Dictionnaire recensant les clauses de jointures des tables
     */
    QHash<QString, QHash<QString, QString> > join_clauses;

signals:
    /**
     * Émit lorsque une erreur lors d'une requête à la DB survient
     *
     * @param error Le message d'erreur retourné
     */
    void DBError(const QString &error);

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
};

#endif // DBCONTROLLER_H
