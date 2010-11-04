#include "profile.h"


Profile::Profile() : siret(""), website("")
{
}


/**
 * \todo Faire des vérifs sur le numéro siret
 */
void Profile::setSiret(const QString &siret)
{
    this->siret = siret;
}

QString Profile::getSiret() const
{
    return this->siret;
}

/**
 * \todo Faire des vérifs
 */
void Profile::setWebsite(const QString &website)
{
    this->website = website;
}

QString Profile::getWebsite() const
{
    return this->website;
}

void Profile::setLogo(const QByteArray &data)
{
    this->logo = data;
}

QByteArray Profile::getLogo() const
{
    return this->logo;
}
