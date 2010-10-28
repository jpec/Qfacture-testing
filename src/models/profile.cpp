#include "profile.h"

Profile::Profile() : siret(""), website("")
{
    logo = new char[1];
    logo = 0;
}

Profile::~Profile()
{
    delete[] logo;
}


/**
 * \todo Faire des vérifs sur le numéro siret
 */
void Profile::setSiret(const string &siret)
{
    this->siret = siret;
}

string Profile::getSiret() const
{
    return this->siret;
}

/**
 * \todo Faire des vérifs
 */
void Profile::setWebsite(const string &website)
{
    this->website = website;
}

string Profile::getWebsite() const
{
    return this->website;
}
