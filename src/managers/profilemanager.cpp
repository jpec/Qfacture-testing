#include "profilemanager.h"

#include "QVariant"
#include "QSqlError"


Profile ProfileManager::get(int id)
{
    QSqlQuery query;
    Profile profile;
    
    query.prepare(
            "SELECT id, Name, Siret, Adress, Zip, City, Phone, Mail, Home, Logo "
            "FROM user WHERE id = :profile_id"
        );
    
    query.bindValue(":profile_id", QVariant(id));
    
    if(!query.exec() || !query.next())
    {
        // dans les managers : lever des exceptions
        // dans le core : emettre un event.
        //emit DBError(query.lastError().databaseText());

        return profile;
    }
    
    return makeProfile(query);
}

void ProfileManager::save(Profile &profile)
{
    if(profile.getId() == 0)
        insert(profile);
    else
        update(profile);
}

void ProfileManager::insert(Profile &profile)
{
    // \todo implémenter !
}

void ProfileManager::update(const Profile &profile)
{
    QSqlQuery query;

    query.prepare(
            "UPDATE user "
            "SET Name = :name, Siret = :siret, Adress = :address, "
                " Zip = :zip, City = :city, Phone = :phone, "
                " Mail = :mail, Home = :home "
        "WHERE id = :p_id"
    );

    bindProfile(profile, query);

    std::cout << profile.getName().toStdString() << std::endl;

    if(!query.exec()){
        // \todo Lever une exception
        return;
    }
}

void ProfileManager::bindProfile(const Profile &profile, QSqlQuery &query)
{
    query.bindValue(":p_id", profile.getId());
    query.bindValue(":name", profile.getName());
    query.bindValue(":siret", profile.getSiret());
    query.bindValue(":address", profile.getAddress());
    query.bindValue(":zip", profile.getZipCode());
    query.bindValue(":city", profile.getCity());
    query.bindValue(":phone", profile.getPhone());
    query.bindValue(":mail", profile.getMail());
    query.bindValue(":home", profile.getWebsite());
}

Profile ProfileManager::makeProfile(QSqlQuery &query)
{
    Profile profile;

    profile.setId(query.value(0).toInt());
    profile.setName(query.value(1).toString());
    profile.setSiret(query.value(2).toString());
    profile.setAddress(query.value(3).toString());
    profile.setZipCode(query.value(4).toString());
    profile.setCity(query.value(5).toString());
    profile.setPhone(query.value(6).toString());
    profile.setMail(query.value(7).toString());
    profile.setWebsite(query.value(8).toString());
    profile.setLogo(query.value(9).toByteArray());

    return profile;
}
