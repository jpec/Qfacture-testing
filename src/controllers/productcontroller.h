#ifndef PRODUCTCONTROLLER_H
#define PRODUCTCONTROLLER_H

#include "managers/productmanager.h"


/**
 * Contrôleur permettant de gérer les produits
 */
class ProductController
{
    friend class QfactureCore;

private:
    /**
     * Retourne une instance unique du contrôleur
     *
     * @return ProductController* L'instance du contrôleur
     */
    static ProductController* getInstance();

    /**
     * Enregistre ou met à jour un produit.
     *
     * \note En cas d'un nouveau produit, l'id est renseigné lors de l'enregistrement
     *
     * @param p Le produit à enregistrer
     */
    bool save(Product &p);

    /**
     * Récupère un produit
     *
     * @param id L'identifiant du produit
     *
     * @return Product Le produit chargé.
     */
    Product get(int id);

    /**
     * Supprime un produit
     *
     * @param id L'identifiant du produit
     */
    bool erase(int id);


    ProductController();
    ProductController(const ProductController&);
    ProductController& operator =(const ProductController&);

    /**
     * Instance du gestionnaire de produits
     */
    ProductManager manager;
};

#endif // PRODUCTCONTROLLER_H
