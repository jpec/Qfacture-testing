#ifndef CUSTOMERMANAGER_H
#define CUSTOMERMANAGER_H

#include "models/customer.h"

#include <QList>
#include <QSqlQuery>


/**
 * Gestionnaire de clients
 */
class CustomerManager
{
public:
    /**
     * Récupère le profil d'un client
     *
     * @param id L'identifiant du client à charger
     * @param uid Identifiant du profil "possédant" le client
     *
     * @return Customer Le client chargé.
     */
    Customer get(int id, int uid=-1);

    /**
     * Récupère une liste de clients
     *
     * @param uid Identifiant du profil "possédant" les clients
     *
     * @return QList<Customer> Les clients chargés.
     */
    QList<Customer> getList(int uid=-1);

    /**
     * Enregistre ou met à jour le profil d'un client.
     *
     * \note En cas d'un nouveau client, l'id est renseigné lors de l'enregistrement
     *
     * @param customer Le client à enregistrer
     * @param uid Identifiant du profil "possédant" le client
     *
     * @return bool Succès de l'enregistrement
     */
    bool save(Customer &customer, int uid);

    /**
     * Supprime un client.
     *
     * @param id Le client à supprimer
     * @param uid Identifiant du profil "possédant" le client
     *
     * @return bool Succès de la suppression
     */
    bool erase(int id, int uid=-1);

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
     * @param customer Le client à enregistrer
     * @param uid Identifiant du profil "possédant" le client
     *
     * @return bool Succès de l'insertion
     */
    bool insert(Customer &customer, int uid);

    /**
     * Réalise la mise à jour d'un client
     *
     * @param customer Le client à mettre à jour
     * @param uid Identifiant du profil "possédant" le client
     *
     * @return bool Succès de la mise à jour
     */
    bool update(const Customer &customer, int uid);

    /**
     * Effectue un bindValue() sur la query avec les champs du
     * profile.
     *
     * @param customer Client à binder
     * @param query Query à laquelle lier le profile
     * @param uid Identifiant du profil "possédant" le client
     */
    void bindCustomer(const Customer &customer, QSqlQuery &query, int uid=-1);
};

#endif // CUSTOMERMANAGER_H
