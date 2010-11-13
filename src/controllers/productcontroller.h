#ifndef PRODUCTCONTROLLER_H
#define PRODUCTCONTROLLER_H

#include "controller.h"
#include "managers/productmanager.h"


/**
 * Contrôleur permettant de gérer les produits
 */
class ProductController : public Controller
{
    Q_OBJECT

public:
    explicit ProductController(QObject *parent = 0);

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

signals:
    /**
     * Émit lorsque une erreur lors d'une requête à la DB survient
     *
     * @param error Le message d'erreur retourné
     */
    void DBError(const QString &error);

private:
    /**
     * Instance du gestionnaire de produits
     */
    ProductManager manager;
};

#endif // PRODUCTCONTROLLER_H
