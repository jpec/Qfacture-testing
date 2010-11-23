#include "dbcontroller.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QStringList>


DBController::DBController(){}

DBController* DBController::getInstance()
{
    static DBController instance;

    return &instance;
}


bool DBController::exec(QSqlQuery &query)
{
    if(!query.exec()) {
        emit DBError(query.lastError().databaseText());

        return false;
    }

    return true;
}

QStringList DBController::getAvailableDrivers() const
{
    return this->db.drivers();
}

void DBController::connectDB(const QString &server, int port, const QString &login,
                             const QString &pass, const QString &db_name, const QString &db_type)
{
    if(this->isDBConnected())
        return;

    this->db = QSqlDatabase::addDatabase(db_type);

    this->db.setHostName(server);
    this->db.setPort(port);
    this->db.setUserName(login);
    this->db.setPassword(pass);
    this->db.setDatabaseName(db_name);

    if(this->db.open())
        emit DBConnected();
    else
        emit DBConnectionError(this->db.lastError().databaseText());
}

/**
 * Ferme la connexion avec la base de données si elle existe.
 */
void DBController::disconnectDB()
{
    if(!this->isDBConnected())
        return;

    this->db.commit();

    this->db.close();

    emit DBDisconnected();
}

bool DBController::isDBConnected() const
{
    return db.isOpen();
}
