#include "qfacturecore.h"

#include <QSqlError>


void QfactureCore::connectDB(const QString &server, int port, const QString &login,
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
void QfactureCore::deconnectDB()
{
    if(!this->isDBConnected())
        return;
    
    this->db.close();
    
    emit DBDisconnected();
}

bool QfactureCore::isDBConnected() const
{
    return db.isOpen();
}
