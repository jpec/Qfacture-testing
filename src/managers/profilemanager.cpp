#include "profilemanager.h"
#include "controllers/dbcontroller.h"

#include "QVariant"

#include <iostream>
Profile ProfileManager::get(int id)
{
    QSqlQuery query;
    Profile p;

    query.prepare(
            "SELECT "
                "uID, name, siret, address, complement, zip, city, phone, "
                "mail, website, logo, fac_reference_format "
            "FROM user WHERE uID = :profile_id"
        );

    query.bindValue(":profile_id", QVariant(id));

    if(!DBController::getInstance()->exec(query))
        return p;

    // pas de profil avec l'ID demandé, on ne remonte pas d'erreur
    // mais juste un profil vide
    if(query.next())
        p = makeProfile(query);

    query.finish();

    return p;
}

bool ProfileManager::save(Profile &profile)
{
    return profile.isNew() ? insert(profile) : update(profile);
}

bool ProfileManager::insert(Profile &profile)
{
    // \todo implémenter !
    return false;
}

bool ProfileManager::update(const Profile &profile)
{
    QSqlQuery query;

    query.prepare(
            "UPDATE user "
            "SET name = :name, siret = :siret, address = :address, "
                "complement = :complement, zip = :zip, city = :city, "
                "phone = :phone, mail = :mail, website = :website, "
                "logo = :logo, fac_reference_format = :fac_reference_format "
            "WHERE uID = :p_id"
    );

    bindProfile(profile, query);

    if(DBController::getInstance()->exec(query))
    {
        query.finish();

        return true;
    }

    return false;
}

void ProfileManager::bindProfile(const Profile &profile, QSqlQuery &query)
{
    query.bindValue(":p_id", profile.getId());
    query.bindValue(":name", profile.getName());
    query.bindValue(":siret", profile.getSiret());
    query.bindValue(":address", profile.getAddress());
    query.bindValue(":complement", profile.getAddressComplement());
    query.bindValue(":zip", profile.getZipCode());
    query.bindValue(":city", profile.getCity());
    query.bindValue(":phone", profile.getPhone());
    query.bindValue(":mail", profile.getMail());
    query.bindValue(":website", profile.getWebsite());
    query.bindValue(":logo", profile.getLogo());
    query.bindValue(":fac_reference_format", "");
}

Profile ProfileManager::makeProfile(QSqlQuery &query)
{
    Profile profile;

    profile.setId(query.value(0).toInt());
    profile.setName(query.value(1).toString());
    profile.setSiret(query.value(2).toString());
    profile.setAddress(query.value(3).toString());
    profile.setAddressComplement(query.value(4).toString());
    profile.setZipCode(query.value(5).toString());
    profile.setCity(query.value(6).toString());
    profile.setPhone(query.value(7).toString());
    profile.setMail(query.value(8).toString());
    profile.setWebsite(query.value(9).toString());
    profile.setLogo(query.value(10).toByteArray());

    return profile;
}
