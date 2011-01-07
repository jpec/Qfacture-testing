#ifndef CUSTOMERCONTROLLER_H
#define CUSTOMERCONTROLLER_H

#include "managers/customermanager.h"

#include <QList>


/**
 * Contrôleur permettant de gérer les clients
 */
class CustomerController
{
    friend class QfactureCore;

private:
    /**
     * Retourne une instance unique du contrôleur
     *
     * @return CustomerController* L'instance du contrôleur
     */
    static CustomerController* getInstance();

    /**
     * Enregistre ou met à jour un client.
     *
     * \note En cas d'un nouveau client, l'id est renseigné lors de l'enregistrement
     *
     * @param p Le client à enregistrer
     * @param uid Identifiant du profil "possédant" le client
     */
    bool save(Customer &p, int uid);

    /**
     * Récupère un client
     *
     * @param id L'identifiant du client
     * @param uid Identifiant du profil "possédant" le client
     *
     * @return Customer Le client chargé.
     */
    Customer get(int id, int uid);

    /**
     * Récupère une liste de clients
     *
     * @param uid Identifiant du profil "possédant" les clients
     *
     * @return QList<Customer> Les clients chargés.
     */
    QList<Customer> getList(int uid, const QString &name_filter="");

    /**
     * Supprime un client
     *
     * @param id L'identifiant du client
     * @param uid Identifiant du profil "possédant" le client
     *
     * @return bool Booléen indiquant le succès ou l'échec de la suppression
     */
    bool erase(int id, int uid);


    CustomerController();
    CustomerController(const CustomerController&);
    CustomerController& operator =(const CustomerController&);

    /**
     * Instance du gestionnaire de clients
     */
    CustomerManager manager;
};

#endif // CUSTOMERCONTROLLER_H
