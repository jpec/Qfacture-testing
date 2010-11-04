#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>


/**
 * Classe servant de base à tous les managers
 */
class Manager
{
public:
    /**
     * Construit le manager
     *
     * @param db L'instance de la DB à utiliser
     */
    Manager(QSqlDatabase &db);

protected:
    /**
     * Instance de la DB à utiliser
     */
    QSqlDatabase db;
};

#endif // DBMANAGER_H
