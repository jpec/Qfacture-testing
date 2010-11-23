#ifndef PRODUCTMANAGER_H
#define PRODUCTMANAGER_H

#include "models/product.h"

#include <QSqlQuery>


/**
 * Gestionnaire de produits
 */
class ProductManager
{
public:
    /**
     * Récupère le détail d'un produit
     *
     * @param id L'identifiant du produit
     *
     * @throws DBErrorException Si la requête à la DB échoue
     *
     * @return Product Le produit chargé.
     */
    Product get(int id);

    /**
     * Enregistre ou met à jour le détail d'un produit.
     *
     * \note En cas d'un nouveau produit, l'id est renseigné lors de l'enregistrement
     *
     * @param p Le produit à enregistrer
     *
     * @return bool Succès de l'enregistrement
     */
    bool save(Product &product);

    /**
     * Supprime un produit.
     *
     * @param p Le produit à supprimer
     *
     * @return bool Succès de la suppression
     */
    bool erase(int id);

private:
    /**
     * Crée un produit à partir des résultats d'une requête
     *
     * \note On suppose que tous les champs d'un produit sont
     *       retournés par la requête
     *
     * @param query La requête qui vient d'être exécutée
     *
     * @return Product Le produit créé
     */
    Product makeProduct(QSqlQuery &query);

    /**
     * Réalise l'enregistrement d'un nouveau produit
     *
     * \note l'id est renseigné ici.
     *
     * @param costumer Le produit à enregistrer
     *
     * @return bool Succès de l'insertion
     */
    bool insert(Product &product);

    /**
     * Réalise la mise à jour d'un produit
     *
     * @param product Le produit à mettre à jour
     *
     * @return bool Succès de la mise à jour
     */
    bool update(const Product &product);

    /**
     * Effectue un bindValue() sur la query avec les champs du
     * profile.
     *
     * @param product Client à binder
     * @param query Query à laquelle lier le profile
     */
    void bindProduct(const Product &product, QSqlQuery &query);
};

#endif // PRODUCTMANAGER_H
