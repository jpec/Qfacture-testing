#include "qfacturecore.h"

#include <QSqlError>
#include <QSqlQuery>


QfactureCore::QfactureCore()
{
    this->settings = new QSettings("Qfacture", "Qfacture", this);
}

QfactureCore::~QfactureCore()
{
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
    return profile_manager.get(id);
}

bool QfactureCore::saveProfile(Profile &p)
{
    return profile_manager.save(p);
}

/**
 * Charge le dernier profile d'utilisateur géré
 */
bool QfactureCore::loadLastProfile()
{
    this->profile = getProfile(getSetting("Profile", "id", QVariant(1)).toInt());

    if(this->profile.getId() == 0)
        return false;

    emit lastProfileLoaded();

    return true;
}

Profile& QfactureCore::getCurrentProfile()
{
    return profile;
}
