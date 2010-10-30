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

// \todo Chargement du logo
Profile QfactureCore::getProfile(int id)
{
    QSqlQuery query;
    //QPixmap pic;
    Profile profile;
    
    query.prepare(
            "SELECT Name, Siret, Adress, Adress2, Zip, City, Phone, Mail, Home, Logo "
            "FROM user WHERE id = :profile_id LIMIT 1;"
        );
    
    query.bindValue(":profile_id", id);
    
    if(!query.exec() || !query.next())
    {
        emit DBError(query.lastError().databaseText());

        return profile;
    }
    
    profile.setId(id);
    profile.setName(query.value(0).toString().toStdString());
    profile.setSiret(query.value(1).toString().toStdString());
    profile.setAddress(query.value(2).toString().toStdString());
    profile.setZipCode(query.value(3).toString().toStdString());
    profile.setCity(query.value(4).toString().toStdString());
    profile.setPhone(query.value(5).toString().toStdString());
    profile.setMail(query.value(6).toString().toStdString());
    profile.setWebsite(query.value(7).toString().toStdString());
    profile.setLogo(query.value(9).toByteArray());
    
    return profile;
}
