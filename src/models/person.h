#ifndef PERSON_H
#define PERSON_H

#include <string>

using namespace std;


/**
  * Classe représentant une personne.
  */
class Person
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
    void setName(const string &name);

    /**
     * Retourne le nom de cette personne.
     *
     * @return string Le nom et le prénom de cette personne.
     */
    string getName() const;

    /**
     * Définit l'adresse postale de cette personne.
     *
     * @param name La nouvelle adresse postale
     */
    void setAddress(const string &address);

    /**
     * Retourne l'adresse postale de cette personne.
     *
     * @return string L'adresse postale de cette personne.
     */
    string getAddress() const;

    /**
     * Définit le nouveau code postal de cette personne.
     *
     * @param name Le nouveau code postal
     */
    void setZipCode(const string &zip);

    /**
     * Retourne le code postal de cette personne.
     *
     * @return string Le code postal de cette personne.
     */
    string getZipCode() const;

    /**
     * Définit la nouvelle ville de cette personne.
     *
     * @param name La nouvelle ville
     */
    void setCity(const string &city);

    /**
     * Retourne la ville où réside cette personne (qui correspond normalement au
     * code postal).
     *
     * @return string La ville de cette personne.
     */
    string getCity() const;

    /**
     * Définit la nouvelle adresse mail de cette personne.
     *
     * @param name La nouvelle adresse mail
     */
    void setMail(const string &mail);

    /**
     * Retourne l'adresse mail cette personne.
     *
     * @return string L'adresse mail de cette personne.
     */
    string getMail() const;

    /**
     * Définit le nouveau numéro de téléphone de cette personne.
     *
     * @param name Le nouveau numéro. Doit être une série de 10 chiffres ou être
     *             vide
     */
    void setPhone(const string &phone);

    /**
     * Retourne le numéro de téléphone cette personne.
     *
     * @return string Le numéro de téléphone (non formaté) de cette personne.
     */
    string getPhone() const;

private:
    /**
     * Identifiant de la personne
     */
    int id;

    /**
     * Nom (et prénom)
     */
    string name;

    /**
     * Adresse postale
     */
    string address;

    /**
     * Code postal (sans espaces. ex : 63000)
     */
    string zip_code;

    /**
     * Ville
     */
    string city;

    /**
     * Adresse mail
     */
    string mail;

    /**
     * Numéro de téléphone (sans espaces. ex : 0483272514)
     */
    string phone;
};

#endif // PERSON_H
