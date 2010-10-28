#ifndef PROFILE_H
#define PROFILE_H

#include <string>
#include "person.h"

using namespace std;


class Profile : public Person
{
public:
    Profile();
    ~Profile();
    
    /**
     * Définit le nouveau numéro Siret pour ce profile.
     *
     * @param name Le nouveau numéro siret
     */
    void setSiret(const string &siret);
    
    /**
     * Retourne le numéro Siret pour ce profile
     *
     * @return string Le numéro Siret non formaté.
     */
    string getSiret() const;
    
    /**
     * Définit l'adresse du site web pour ce profile.
     *
     * @param name Le nouveau site web
     */
    void setWebsite(const string &website);
    
    /**
     * Retourne l'URL du website pour ce profile
     *
     * @return string L'URL du website
     */
    string getWebsite() const;

private:
    /**
     * Numéro Siret correspondant au profile
     */
    string siret;
    
    /**
     * Adresse du site web
     */
    string website;
    
    /**
     * Contenu du logo du profile
     */
    char * logo;
};

#endif // PROFILE_H
