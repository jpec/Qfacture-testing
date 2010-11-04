#ifndef PROFILE_H
#define PROFILE_H

#include <QByteArray>
#include <QString>

#include "person.h"


class Profile : public Person
{
public:
    Profile();
    
    /**
     * Définit le nouveau numéro Siret pour ce profile.
     *
     * @param name Le nouveau numéro siret
     */
    void setSiret(const QString &siret);
    
    /**
     * Retourne le numéro Siret pour ce profile
     *
     * @return QString Le numéro Siret non formaté.
     */
    QString getSiret() const;
    
    /**
     * Définit l'adresse du site web pour ce profile.
     *
     * @param name Le nouveau site web
     */
    void setWebsite(const QString &website);
    
    /**
     * Retourne l'URL du website pour ce profile
     *
     * @return QString L'URL du website
     */
    QString getWebsite() const;
    
    /**
     * Définit le logo utilisé par le profile.
     *
     * @param data Les données du logo.
     */
    void setLogo(const QByteArray &data);
    
    /**
     * Retourne le logo du profile
     *
     * @return QByteArray Les données du logo.
     */
    QByteArray getLogo() const;

private:
    /**
     * Numéro Siret correspondant au profile
     */
    QString siret;
    
    /**
     * Adresse du site web
     */
    QString website;
    
    /**
     * Contenu du logo du profile
     */
    QByteArray logo;
};

#endif // PROFILE_H
