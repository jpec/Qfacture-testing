#ifndef CUSTOMERMANAGER_H
#define CUSTOMERMANAGER_H

#include "models/customer.h"
#include "managers/basemanager.h"

#include <QSqlQuery>


/**
 * Gestionnaire de clients
 */
class CustomerManager : public BaseManager
{
public:
    /**
     * Récupère le profil d'un client
     *
     * @param id L'identifiant du profil à utiliser
     *
     * @throws DBErrorException Si la requête à la DB échoue
     *
     * @return Customer Le client chargé.
     */
    Customer get(int id);

    /**
     * Enregistre ou met à jour le profile d'un client.
     *
     * \note En cas d'un nouveau client, l'id est renseigné lors de l'enregistrement
     *
     * @param p Le client à enregistrer
     *
     * @return bool Succès de l'enregistrement
     */
    bool save(Customer &customer);

    /**
     * Supprime un client.
     *
     * @param p Le client à supprimer
     *
     * @return bool Succès de la suppression
     */
    bool erase(int id);

private:
    /**
     * Crée un profile à partir des résultats d'une requête
     *
     * \note On suppose que tous les champs d'un client sont
     *       retournés par la requête
     *
     * @param query La requête qui vient d'être exécutée
     *
     * @return Customer Le client créé
     */
    Customer makeCustomer(QSqlQuery &query);

    /**
     * Réalise l'enregistrement d'un nouveau client
     *
     * \note l'id est renseigné ici.
     *
     * @param costumer Le client à enregistrer
     *
     * @return bool Succès de l'insertion
     */
    bool insert(Customer &customer);

    /**
     * Réalise la mise à jour d'un client
     *
     * @param customer Le client à mettre à jour
     *
     * @return bool Succès de la mise à jour
     */
    bool update(const Customer &customer);

    /**
     * Effectue un bindValue() sur la query avec les champs du
     * profile.
     *
     * @param customer Client à binder
     * @param query Query à laquelle lier le profile
     */
    void bindCustomer(const Customer &customer, QSqlQuery &query);
};

#endif // CUSTOMERMANAGER_H
