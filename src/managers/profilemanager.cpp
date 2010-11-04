#include "profilemanager.h"

#include "QSqlQuery"
#include "QVariant"


ProfileManager::ProfileManager(QSqlDatabase &db) : Manager(db)
{
}

Profile ProfileManager::get(int id)
{
    QSqlQuery query;
    Profile profile;
    
    query.prepare(
            "SELECT Name, Siret, Adress, Adress2, Zip, City, Phone, Mail, Home, Logo "
            "FROM user WHERE id = :profile_id LIMIT 1;"
        );
    
    query.bindValue(QString(":profile_id"), QVariant(id));
    
    if(!query.exec() || !query.next())
    {
        // dans les managers : lever des exceptions
        // dans le core : emettre un event.
        //emit DBError(query.lastError().databaseText());

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
