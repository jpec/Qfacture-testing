#ifndef PERSON_H
#define PERSON_H

#include "models/modelbase.h"

#include <QString>


/**
  * Classe représentant une personne.
  */
class Person : public ModelBase
{
public:
    /**
     * Construit une personne "vierge".
     *
     * \note Son identifiant vaut 0
     */
    Person();

    /**
     * Définit l'identifiant de cette personne.
     *
     * \warning Ce n'est possible que s'il n'a pas déjà été défini.
     *
     * @param id L'identifiant à associer à la personne.
     */
    void setId(int id);

    /**
     * Retourne l'identiant de cette personne.
     *
     * @return int L'identifiant, ou 0 s'il n'est pas définit.
     */
    int getId() const;

    /**
     * Définit le nom de cette personne.
     *
     * @param name Le nouveau nom (et prénom)
     */
    void setName(const QString &name);

    /**
     * Retourne le nom de cette personne.
     *
     * @return QString Le nom et le prénom de cette personne.
     */
    QString getName() const;

    /**
     * Définit l'adresse postale de cette personne.
     *
     * @param name La nouvelle adresse postale
     */
    void setAddress(const QString &address);

    /**
     * Retourne l'adresse postale de cette personne.
     *
     * @return QString L'adresse postale de cette personne.
     */
    QString getAddress() const;

    /**
     * Définit le complément d'adresse postale de cette personne.
     *
     * @param name La nouvelle adresse postale
     */
    void setAddressComplement(const QString &complement);

    /**
     * Retourne le complément l'adresse postale de cette personne.
     *
     * @return QString Le complément d'adresse postale de cette personne.
     */
    QString getAddressComplement() const;

    /**
     * Définit le nouveau code postal de cette personne.
     *
     * @param name Le nouveau code postal
     */
    void setZipCode(const QString &zip);

    /**
     * Retourne le code postal de cette personne.
     *
     * @return QString Le code postal de cette personne.
     */
    QString getZipCode() const;

    /**
     * Définit la nouvelle ville de cette personne.
     *
     * @param name La nouvelle ville
     */
    void setCity(const QString &city);

    /**
     * Retourne la ville où réside cette personne (qui correspond normalement au
     * code postal).
     *
     * @return QString La ville de cette personne.
     */
    QString getCity() const;

    /**
     * Définit la nouvelle adresse mail de cette personne.
     *
     * @param name La nouvelle adresse mail
     */
    void setMail(const QString &mail);

    /**
     * Retourne l'adresse mail cette personne.
     *
     * @return QString L'adresse mail de cette personne.
     */
    QString getMail() const;

    /**
     * Définit le nouveau numéro de téléphone de cette personne.
     *
     * @param name Le nouveau numéro. Doit être une série de 10 chiffres ou être
     *             vide
     */
    void setPhone(const QString &phone);

    /**
     * Retourne le numéro de téléphone cette personne.
     *
     * @return QString Le numéro de téléphone (non formaté) de cette personne.
     */
    QString getPhone() const;

private:
    /**
     * Identifiant de la personne
     */
    int id;

    /**
     * Nom (et prénom)
     */
    QString name;

    /**
     * Adresse postale
     */
    QString address;

    /**
     * Complement d'adresse postale
     */
    QString complement;

    /**
     * Code postal (sans espaces. ex : 63000)
     */
    QString zip_code;

    /**
     * Ville
     */
    QString city;

    /**
     * Adresse mail
     */
    QString mail;

    /**
     * Numéro de téléphone (sans espaces. ex : 0483272514)
     */
    QString phone;
};

#endif // PERSON_H
