#include "qfacturecore.h"
#include "controllers/dbcontroller.h"

#include <QStringList>


QfactureCore::QfactureCore()
{
    initSignals();
}

void QfactureCore::initSignals()
{
    /** Signaux ré-émis **/

    /// DBController
    // erreur lors d'une requête à la DB
    connect(DBController::getInstance(), SIGNAL(DBError(QString)), this,
            SIGNAL(DBError(QString)));

    // erreur à la connexion
    connect(DBController::getInstance(), SIGNAL(DBConnectionError(QString)), this,
            SIGNAL(DBConnectionError(QString)));

    // connexion
    connect(DBController::getInstance(), SIGNAL(DBConnected()), this,
            SIGNAL(DBConnected()));

    // déconnexion
    connect(DBController::getInstance(), SIGNAL(DBDisconnected()), this,
            SIGNAL(DBDisconnected()));
}

/* Wrapper des méthodes du contrôleur de la DB */

QStringList QfactureCore::getAvailableDrivers() const
{
    return DBController::getInstance()->getAvailableDrivers();
}

void QfactureCore::connectDB(const QString &server, int port, const QString &login,
                             const QString &pass, const QString &db_name, const QString &db_type)
{
    return DBController::getInstance()->connectDB(server, port, login, pass,
                                                  db_name, db_type);
}

void QfactureCore::disconnectDB()
{
    return DBController::getInstance()->disconnectDB();
}

bool QfactureCore::isDBConnected() const
{
    return DBController::getInstance()->isDBConnected();
}

QStringList QfactureCore::getDBLabels(const QString& table,
                                      const QStringList& except) const
{
    return DBController::getInstance()->getLabels(table, except);
}


QStringList QfactureCore::getDBColumns(const QString& table,
                                       const QStringList& except) const
{
    return DBController::getInstance()->getColumns(table, except);
}

QString QfactureCore::getDBJoinClause(const QString &from, const QString &with) const
{
    return DBController::getInstance()->getJoinClause(from, with);
}


/* Wrapper des méthodes du contrôleur des profils */

bool QfactureCore::loadLastProfile()
{
    if(!ProfileController::getInstance()->loadLastProfile())
        return false;

    emit lastProfileLoaded();

    return true;
}

Profile& QfactureCore::getCurrentProfile()
{
    return ProfileController::getInstance()->getCurrent();
}

Profile QfactureCore::getProfile(int id)
{
    return ProfileController::getInstance()->get(id);
}

bool QfactureCore::save(Profile &p)
{
    return ProfileController::getInstance()->save(p);
}

bool QfactureCore::saveCurrentProfile()
{
    return ProfileController::getInstance()->saveCurrent();
}

/* Wrapper pour les méthodes du contrôleur des produits */

bool QfactureCore::save(Product &p)
{
    return ProductController::getInstance()->save(p, getCurrentProfile().getId());
}

Product QfactureCore::getProduct(int id)
{
    return ProductController::getInstance()->get(id, getCurrentProfile().getId());
}

bool QfactureCore::eraseProduct(int id)
{
    return ProductController::getInstance()->erase(id, getCurrentProfile().getId());
}

/* Wrapper pour les méthodes du contrôleur des clients */

bool QfactureCore::save(Customer &p)
{
    if(getCurrentProfile().isNew())
        return false;

    return CustomerController::getInstance()->save(p, getCurrentProfile().getId());
}

Customer QfactureCore::getCustomer(int id)
{
    if(getCurrentProfile().isNew())
        return Customer();

    return CustomerController::getInstance()->get(id, getCurrentProfile().getId());
}

bool QfactureCore::eraseCustomer(int id)
{
    if(getCurrentProfile().isNew())
        return false;

    return CustomerController::getInstance()->erase(id, getCurrentProfile().getId());
}

/* Wrapper pour les méthodes du contrôleur des factures */

Invoice QfactureCore::getInvoice(int id)
{
    return InvoiceController::getInstance()->get(id);
}
