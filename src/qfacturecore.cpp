#include "qfacturecore.h"

#include <QSqlError>
#include <QSqlQuery>


QfactureCore::QfactureCore()
{
    this->settings = new QSettings("Qfacture", "Qfacture", this);
    this->profile_manager = new ProfileManager(this->db);
}

QfactureCore::~QfactureCore()
{
    delete profile_manager;
    delete settings;
}


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
void QfactureCore::disconnectDB()
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

void QfactureCore::setSetting(const QString &group, const QString &key, const QVariant &value)
{
    this->settings->beginGroup(group);
    this->settings->setValue(key, value);
    this->settings->endGroup();
}

QVariant QfactureCore::getSetting(const QString &group, const QString &key, const QVariant &default_value) const
{
    QVariant val;
    
    this->settings->beginGroup(group);
    val = this->settings->value(key, default_value);
    this->settings->endGroup();
    
    return val;
}

Profile QfactureCore::getProfile(int id)
{
    return profile_manager->get(id);
}

void QfactureCore::saveProfile(Profile &p)
{
    
}
